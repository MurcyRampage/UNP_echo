#ifndef MULTI_THREAD_ECHO_CLIENT_H_INCLUDED
#define MULTI_THREAD_ECHO_CLIENT_H_INCLUDED
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
#include<pthread.h>
const static int MAX_LINE = 100;
const static int STD_IN_FD = 0;
const static int STD_OUT_FD = 1;
class Multi_Thread_echo_client{
public:
    Multi_Thread_echo_client() = delete;
    Multi_Thread_echo_client(const char *ip,int port);
    void start();
    static void* send_to_socket(void*);
private:
   int sockfd;
    const char* server_ip;
    int server_port;
    sockaddr_in serveraddr;
    static int stdineof ;
};

#endif // MULTI_THREAD_ECHO_CLIENT_H_INCLUDED
