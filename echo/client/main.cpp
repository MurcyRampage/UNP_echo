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
#include"TCPechoClient.h"
using namespace std;
const int STD_IN_FD = 0;
const int STD_OUT_FD = 1;
const int MAXLINE = 100;
void str_cli(istream&,int);
//static void connect_alarm(int signo){return;}
typedef void Sigfunc(int);
int main()
{
    TCPechoClient client("127.0.0.1",9878);
    client.start();
   return 0;
}

