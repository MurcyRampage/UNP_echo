#ifndef MULTI_THREAD_ECHO_SERVER_H_INCLUDED
#define MULTI_THREAD_ECHO_SERVER_H_INCLUDED
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
const static int MAX_FD_SIZE = 20;
const static int MAX_QUEUE = 100;
const static int MAX_LINE = 100;
class Multi_Thread_echo_server{
private:
    int listenfd;
    int server_port;
    sockaddr_in serveraddr;
public:
    Multi_Thread_echo_server() = delete;
    Multi_Thread_echo_server(int port);
    void loop();
private:
    static void* connection(void*);
};

#endif // MULTI_THREAD_ECHO_SERVER_H_INCLUDED
