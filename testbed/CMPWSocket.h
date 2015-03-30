/* 
 * File:   CMPWSocket.h
 * Author: mayue
 *
 * Created on March 29, 2015, 12:07 AM
 */

#ifndef CMPWSOCKET_H
#define	CMPWSOCKET_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include <fcntl.h>

class CMPWSocket {
public:
    CMPWSocket();
    virtual ~CMPWSocket();
    int tcpServer(int port);
    //int socketAccept(int listen_fd, struct sockaddr *cliaddr, socklen_t *clilen);
    int m_listen_fd;
    int m_client_fd;
private:

    int m_connect_fd;
    
    int socketCreate(int domain);
    int socketListen(int s, struct sockaddr *sa, socklen_t len);
    

};

#endif	/* CMPWSOCKET_H */

