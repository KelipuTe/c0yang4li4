#include "connection.h"
#include "service.h"

int recv_data(connection *conn) {
  if (0 == conn->connfd) {
    // 无效的client的socket句柄
    return -1;
  }
  if (1 == conn->recv_buffer_full) {
    // 接收缓冲区满了，则直接返回0
    return 0;
  }
  // 计算剩余空间长度
  int remain_len = conn->recv_buffer_max - conn->recv_buffer_last;
  if (remain_len > 0) {
    // 接收缓冲区还有空间，接收数据
    // 计算剩余空间的第1个字节的内存地址
    char *temp_index = conn->recv_buffer + conn->recv_buffer_last;
    ssize_t recv_bytes = -1;
    recv_bytes = recv(conn->connfd, temp_index, remain_len, 0);
    if (is_debug() == 1) {
      printf("[debug]:recv_data(),recv_bytes=%d\r\n", recv_bytes);
    }
    if (-1 == recv_bytes) {
      printf("[error]:recv_data(),-1==recv_bytes");
      printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
      return -1;
    }
    if (0 == recv_bytes) {
      // 测试一下对端是不是已关闭
      ssize_t send_bytes = -1;
      send_bytes = send(conn->connfd, "", 0, 0);
      if (-1 == send_bytes || 0 == send_bytes) {
        // 对端已关闭，返回异常
        printf("[error]:recv_data(),-1==recv_bytes");
        printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
        return -1;
      } else {
        // 真的没接收到数据
        if (is_debug() == 1) {
          printf("[debug]:recv_data(),send(),send_bytes=%d\r\n", send_bytes);
        }
        return -1;
      }
    } else {
      // 收到数据，返回本次接收到的数据长度
      conn->recv_buffer_last += recv_bytes;
      // recv_buffer末尾要加`\0`
      conn->recv_buffer[conn->recv_buffer_last] = '\0';

      return recv_bytes;
    }
  } else {
    // 接收缓冲区满了，标记一下，然后返回0
    conn->recv_buffer_full = 1;

    return 0;
  }
};

int push_data(connection *conn, char *res_data, int res_data_len) {
  if (0 == conn->connfd) {
    return -1;
  }
  if (1 == conn->send_buffer_full) {
    return 0;
  }
  int remain_len = conn->send_buffer_max - conn->send_buffer_last;
  if (res_data_len <= remain_len) {
    char *temp_index = conn->send_buffer + conn->send_buffer_last;
    memcpy(temp_index, res_data, res_data_len);
    conn->send_buffer_last += res_data_len;

    return res_data_len;
  } else {
    conn->send_buffer_full = 1;

    return 0;
  }
};

int write_data(connection *conn) {
  if (0 == conn->connfd) {
    return -1;
  }

  if (is_debug() == 1) {
    printf("[debug]:write_data(),conn->connfd=%d\r\n", conn->connfd);
  }
  if (conn->send_buffer_last > 0) {
    // 发送缓冲区有数据才发
    int send_bytes = -1;
    if (is_debug() == 1) {
      printf("[debug]:write_data(),conn->send_buffer_last=%d\r\n", conn->send_buffer_last);
      printf("[debug]:write_data(),send(),conn->send_buffer=\r\n%s\r\n", conn->send_buffer);
    }
    send_bytes = send(conn->connfd, conn->send_buffer, conn->send_buffer_last, 0);
    if (is_debug() == 1) {
      printf("[debug]:write_data(),send(),send_bytes=%d\r\n", send_bytes);
    }
    if (-1 == send_bytes || 0 == send_bytes) {
      printf("[error]:write_data(),-1==send_bytes,0==send_bytes");
      printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
      return -1;
    }
    if (send_bytes == conn->send_buffer_last) {
      //一次性发送完，直接重置发送缓冲区
      memset(conn->send_buffer, 0, sizeof(conn->send_buffer));
      conn->send_buffer_last = 0;
      conn->send_buffer_full = 0;

      return 0;
    } else {
      // 只发了一半，没发送完
      // 发出去的是发送缓冲区前面的数据
      // 计算发送缓冲区还有多少数据没有发送出去
      conn->send_buffer_last -= send_bytes;
      // 把后面的数据移到前面覆盖前面已经发送过的数据
      memcpy(conn->send_buffer, conn->send_buffer + send_bytes, conn->send_buffer_last);

      return 1;
    }
  }

  return 0;
};