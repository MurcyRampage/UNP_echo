#ifndef TCPECHOSERVER_H_INCLUDED
#define TCPECHOSERVER_H_INCLUDED
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
const static int MAX_FD_SIZE = 20;
const static  int MAX_LINE = 100;
const static int QSIZE = 20;
class TCPechoServer{
private:
    fd_set rset,allset;
    int clients[MAX_FD_SIZE];
    char buf[MAX_LINE];
    int listenfd;
    int maxfd=0;
    int maxi=-1;
    int server_port;
   uint32_t server_ip;
    sockaddr_in server_addr;
public:
    TCPechoServer(int port,uint32_t ipaddr = INADDR_ANY);
    TCPechoServer() = delete;
    TCPechoServer(const TCPechoServer &) = delete;
    void loop();
};


#endif // TCPECHOSERVER_H_INCLUDED
