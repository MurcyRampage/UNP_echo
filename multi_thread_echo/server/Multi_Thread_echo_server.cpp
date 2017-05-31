#include"Multi_Thread_echo_server.h"
struct client_info{
    sockaddr_in addrp;
    int sockp;
};
Multi_Thread_echo_server::Multi_Thread_echo_server(int port):server_port(port){
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr));
    listen(listenfd,MAX_QUEUE);
}
void Multi_Thread_echo_server::loop(){
    pthread_t tid;
    int* connfd;
    sockaddr_in client_addr;
    for(;;){
        int connfd=-1;
        if((connfd=accept(listenfd,nullptr,nullptr))<0){
            std::cout<<strerror(errno)<<std::endl;
        }
        //std::cout<<"accepted connfd  ->"<<connfd<<std::endl;
        client_info *info = (client_info*)malloc(sizeof(client_info));
        memcpy(&info->addrp,&client_addr,sizeof(sockaddr_in));
        memcpy(&info->sockp,&connfd,sizeof(int));
        std::cout<<"connected with  "<<inet_ntoa(info->addrp.sin_addr)<<"  "<<ntohs(info->addrp.sin_port)<<std::endl;

        pthread_create(&tid,nullptr,connection,info);
    }
}
void* Multi_Thread_echo_server::connection(void* args){
    client_info *ptr = (client_info*)args;
    int connfd = ptr->sockp;
    char line[MAX_LINE];
    int n = 0;
    //std::cout<<connfd<<std::endl;
    while((n = read(connfd,&line,MAX_LINE))>0){
       // std::cout<<n<<std::endl;
        write(connfd,&line,n);
    }
    std::cout<<inet_ntoa(ptr->addrp.sin_addr)<<"  "<<ntohs(ptr->addrp.sin_port)<<"   disconnected"<<std::endl;
    free(args);
    close(connfd);
    return nullptr;
}
