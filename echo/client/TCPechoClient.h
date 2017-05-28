#ifndef TCPECHOCLIENT_H_INCLUDED
#define TCPECHOCLIENT_H_INCLUDED
#include <iostream>
#include <iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<signal.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
const static int MAX_LINE = 100;
const static int STDIN_FD = 0;
const static int STDOUT_FD = 1;
class TCPechoClient{
    int sockfd;
    const char *server_ip;
    int server_port;
    sockaddr_in server_addr;
    fd_set rset,wset;
    char to[MAX_LINE],fr[MAX_LINE];
    char *tostart,*toend,*frstart,*frend;
public:
    TCPechoClient(const char *ip,int port);
    TCPechoClient() = delete;
    TCPechoClient(const TCPechoClient&) = delete;
    void start();
};


#endif // TCPECHOCLIENT_H_INCLUDED
