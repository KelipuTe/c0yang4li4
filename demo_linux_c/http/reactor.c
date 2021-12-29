//
// Created by Administrator on 2021/8/9 0009.
//

#include "service.h"
#include "epoll.h"
#include "connection.h"
#include "thread.h"
#include <pthread.h>

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void addConnection(reactor *cell,connection client)
{

    int i;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < MAX_CONNECTIONS; ++i) {
        if(cell->clientsBuffer[i].sockfd==0){
            break;
        }
    }

    cell->clientsBuffer[i] = client;
    cell->current_client_num++;

    pthread_mutex_unlock(&mutex);

}

connection *findClient(reactor *cell,int fd)
{
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if(cell->clients[i].sockfd==fd&&cell->clients[i].sockfd!=0){
            return &cell->clients[i];
        }
    }
    return NULL;
}

void removeClient(reactor *cell,connection *client)
{

    client->recv_last=0;
    client->send_last=0;
    client->send_max_bytes=0;
    client->recv_max_bytes=0;
    client->recv_buffer_full=0;
   // client->ip={0};
   memset(client->ip,0, sizeof(client->ip));
    client->port=0;
    memset(client->recv_buffer,0, sizeof(client->recv_buffer));
    memset(client->send_buffer,0, sizeof(client->send_buffer));
    free(client->data);
    eventDel(cell->epfd,EPOLLIN,client->sockfd);
    close(client->sockfd);
    //printf("客户端关闭了连接%d\r\n",client->sockfd);
    client->sockfd=0;


}
int set_file_nonblock(int fd)
{
    //把文件设置为非阻塞模式  非阻塞的文件描述符称为非阻塞IO
    int option = fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,option|O_NONBLOCK);
    return 1;
}
void *CellEventLoop(void *arg) {
    int ix = *(int *) arg;
    int epfd = epoll_create(MAX_CONNECTIONS);
    if (epfd == -1) {
        printf("epoll_create failr\r\n");
        exit(0);
    }
    reactor *cell = &server.cell[ix];
    cell->epfd = epfd;
    struct epoll_event events[MAX_CONNECTIONS];
    while (cell->run_flag) {

        pthread_mutex_lock(&mutex);
        if (cell->current_client_num > 0) {

            for (int i = 0; i < MAX_CONNECTIONS; ++i) {

                if (cell->clientsBuffer[i].sockfd > 0) {

                    for (int j = 0; j < MAX_CONNECTIONS; ++j) {


                        if (cell->clients[j].sockfd == 0) {

                            cell->clients[j] = cell->clientsBuffer[i];
                            set_file_nonblock(cell->clients[j].sockfd);
                            eventAdd(cell->epfd, EPOLLIN, cell->clients[j].sockfd);
                            break;
                        }
                    }
                    cell->clientsBuffer[i].sockfd = 0;
                }
            }
            cell->current_client_num = 0;
        }
        pthread_mutex_unlock(&mutex);

        int ret = epoll_wait(cell->epfd, events, MAX_CONNECTIONS, 1);

        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;

        }
        if (ret > 0) {
            for (int i = 0; i < ret; i++) {
                int fd = events[i].data.fd;
                if (events[i].events & EPOLLIN) {
                    connection *client = findClient(cell, fd);

                    int x = recvData(client);
                    /**收到数据，要处理，并且要清理一下接收缓冲区的内容***/

                    // printf("recv msg=%s\r\n",client->recv_buffer);

                    //memset(client->recv_buffer,0, sizeof(client->recv_buffer));
                    //client->recv_last=0;
                    /**收到数据，要处理，并且要清理一下接收缓冲区的内容***/

                    //printf("x=%d\r\n",x);
                    if (x == -1) {
                        removeClient(cell, client);
                    } else {

                        //开始进行http协议 解析处理

                        if (hasMessage(client) != -1) {

                            //表示已经接收一条完整的HTTP数据了

                            http_parse(client);
                            //执行onRequest事件 业务逻辑一般在这函数处理
                            server.onRequest(client);


                            popMessage(client);
                        }
                        int writeRet = writeData(client);
                        if (writeRet == -1) {
                            removeClient(cell, client);
                        } else if (writeRet > 0) {
                            eventSet(cell->epfd, EPOLLOUT | EPOLLIN, client->sockfd);
                        }

                    }
                }
                if (events[i].events & EPOLLOUT) {
                    connection *client = findClient(cell, fd);
                    int writeRet = writeData(client);

                    if (writeRet == -1) {
                        removeClient(cell, client);
                    } else if (writeRet == 0) {
                        eventSet(cell->epfd, EPOLLIN, client->sockfd);
                    }
                }


            }
        }
    }

    printf("连接线程结束可以做一些清理工作\r\n");
    close(cell->epfd);
    for (int i = 0; i < MAX_CONNECTIONS; ++i){

        if (cell->clientsBuffer[i].sockfd > 0) {

            close(cell->clientsBuffer[i].sockfd);
        }
        if (cell->clients[i].sockfd > 0) {

            close(cell->clients[i].sockfd);
        }
    }
    free(cell->clients);
    free(cell->clientsBuffer);
    notifyThread();
}


