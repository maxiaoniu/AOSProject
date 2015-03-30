/* 
 * File:   CMPWSocket.cpp
 * Author: mayue
 * 
 * Created on March 29, 2015, 12:07 AM
 */

#include "CMPWSocket.h"

CMPWSocket::CMPWSocket() : m_listen_fd(-1),m_connect_fd(-1), m_client_fd(-1){
}


CMPWSocket::~CMPWSocket() {
      if (m_listen_fd >= 0) {
        close(m_listen_fd);
      }
      if (m_client_fd >= 0) {
        close(m_client_fd);
      }
      if (m_connect_fd >= 0) {
        close(m_connect_fd);
      }
}

int CMPWSocket::tcpServer(int port) {
    int s;
    struct sockaddr_in sa;
    
    if((s = socketCreate(AF_INET)) == -1)
    {
        return -1;
    }
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port); //16bit port from host order to network order
    sa.sin_addr.s_addr = htonl(INADDR_ANY); //Address to accept any incoming messages
    
    if(socketListen(s,(struct sockaddr *)&sa, sizeof(sa))==-1) {
        return -1;
    }
    m_listen_fd = s;
    return s;
}

//int CMPWSocket::socketAccept(int listen_fd, struct sockaddr *cliaddr, socklen_t *clilen) {
//    int fd;
//    while (1) {
//        fd = accept(listen_fd, cliaddr, clilen);
//        if (fd == -1) {
//            if (errno == EINTR)
//                continue;
//            else {
//                fprintf(stderr, "accept: %s", strerror(errno));
//                return -1;
//            }
//        }
//        break;
//    }
//    
//    return fd;
//}

int CMPWSocket::socketCreate(int domain) {

    return socket(domain, SOCK_STREAM, 0);   
}

int CMPWSocket::socketListen(int s, sockaddr* sa, socklen_t len)
{
    if(bind(s, sa, len) == -1) {
        close(s);
        return -1;
    }
    
    if(listen(s,511)==-1){
        close(s);
        return -1;
    }
    return 1;
}