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
#include"TCPechoServer.h"
using namespace std;
const int MAXFD = 20;
const int MAXLINE = 100;
int main()
{
    TCPechoServer server(9878);
    server.loop();
    return 0;
}
