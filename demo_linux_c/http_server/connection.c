#include "connection.h"
#include "service.h"

int recv_data(connection *client) {
  if (0 == client->sockfd) {
    return -1;
  }
  int remain_len = client->recv_max_bytes - client->recv_last;
  if (remain_len > 0) {
    char *data = client->recv_buffer + client->recv_last;
    ssize_t recvBytes = recv(client->sockfd, data, remain_len, 0);
    printf("recvBytes=%d", recvBytes);
    if (recv < 0) {
      printf("recv_data error");
    }
    if (recvBytes == 0) {
      return -1;
    }
    client->recv_last += recvBytes;
    client->recv_buffer[client->recv_last] = 0;

    return recvBytes;
  } else {
    client->recv_buffer_full = 1;
  }
  return 0;
};

int push_data(connection *client, char *data, int len) {
  if (0 == client->sockfd) {
    return -1;
  }
  int remain_len = client->send_max_bytes - client->send_last;
  if (remain_len > 0) {
    memcpy(client->send_buffer + client->send_last, data, len);
    client->send_last += len;
  } else {
    client->send_buffer_full = 1;
  }

  return 0;
};

int write_data(connection *client) {

  if (client->sockfd == 0) {
    return -1;
  }

  if (client->send_last > 0) {

    int sendBytes = send(client->sockfd, client->send_buffer, client->send_last, 0);

    if (sendBytes == 0) {
      printf("writeData fail %s\r\n", strerror(errno));
      return -1;
    } else if (sendBytes < 0) {
      printf("writeData fail %s\r\n", strerror(errno));
      return -1;
    } else if (sendBytes == client->send_last) {

      //一次性发送完
      memset(client->send_buffer, 0, sizeof(client->send_buffer));
      client->send_last = 0;
      client->send_buffer_full = 0;
    } else {

      //发送一半的情况下
      client->send_last -= sendBytes;
      memcpy(client->send_buffer, client->send_buffer + sendBytes, client->send_last);
      return sendBytes;
    }
  }
};