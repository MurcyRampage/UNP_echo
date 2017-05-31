#include"Multi_Thread_echo_client.h"
int Multi_Thread_echo_client::stdineof = 0;
Multi_Thread_echo_client::Multi_Thread_echo_client(const char *ip,int port):server_ip(ip),server_port(port){
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET,server_ip,&serveraddr.sin_addr);
    serveraddr.sin_family = AF_INET;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
}
void Multi_Thread_echo_client::start(){
    if(connect(sockfd,(sockaddr*)&serveraddr,sizeof(serveraddr))<0)
        std::cout<<strerror(errno)<<std::endl;
    pthread_t tid;
    int* ptr=(int*)malloc(sizeof(int));
    *ptr = sockfd;
    pthread_create(&tid,nullptr,send_to_socket,ptr);
    //std::cout<<"Thread created"<<std::endl;
    ssize_t n;
    char recv[MAX_LINE];
    while((n = read(sockfd,recv,MAX_LINE))>0)
        write(STD_OUT_FD,&recv,n);
    //std::cout<<"shutdown read"<<std::endl;
    //if(n==0)std::cout<<"server shutdown"<<std::endl;
    if(stdineof==0)std::cout<<"server termination prematurely!"<<std::endl;
    shutdown(sockfd,SHUT_RD);
}
void *Multi_Thread_echo_client::send_to_socket(void* args){
    //std::cout<<"thread starting"<<std::endl;
    ssize_t n;
    int sockfd =*((int*)args);
    free(args);
    char send[MAX_LINE];
    //std::cout<<"start write"<<std::endl;
    while((n=read(STD_IN_FD,&send,MAX_LINE))>0){
        write(sockfd,&send,n);
        //std::cout<<"write  "<<n<<"  bytes"<<std::endl;
    }
    stdineof = 1;
    shutdown(sockfd,SHUT_WR);
    return nullptr;
}
