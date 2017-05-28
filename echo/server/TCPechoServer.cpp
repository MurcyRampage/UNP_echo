#include"TCPechoServer.h"
TCPechoServer::TCPechoServer(int port,uint32_t ip):server_port(port),server_ip(ip){
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_addr.s_addr = htonl(server_ip);
    server_addr.sin_port = htons(server_port);
    server_addr.sin_family = AF_INET;
    bind(listenfd,(sockaddr*)&server_addr,sizeof(server_addr));
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    for(int i =0;i<MAX_FD_SIZE;++i)
        clients[i] = -1;
    maxfd = listenfd;

}
void TCPechoServer::loop(){
    listen(listenfd,QSIZE);
    FD_SET(listenfd,&allset);
    int connfd=-1;
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int nready = 0;
    int i=0;
    for(;;){
        rset = allset;
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(FD_ISSET(listenfd,&rset)){
            connfd = accept(listenfd,(sockaddr*)&client_addr,&client_len);
            std::cout<<"connect with "<<inet_ntoa(client_addr.sin_addr)<<" "<<ntohs(client_addr.sin_port)<<std::endl;
            for(i=0;i<MAX_FD_SIZE;++i)
                if(clients[i] = -1){
                    clients[i] = connfd;
                    break;
                }
            if(i==MAX_FD_SIZE){
                std::cout<<"too many fd!"<<std::endl;
                exit(0);
            }
            if(connfd>maxfd)
                maxfd = connfd;
            if(i>maxi )
                maxi = i;
            FD_SET(connfd,&allset);
            if(--nready <=0)
                continue;
        }

        int ready_socket;
        int n=0;
        for(i=0;i<=maxi;++i){
            if((ready_socket = clients[i])<0)
                continue;
            if(FD_ISSET(ready_socket,&rset)){
                if((n=read(ready_socket,&buf,MAX_LINE))==0){
                    clients[i] = -1;
                    FD_CLR(ready_socket,&allset);
                    close(ready_socket);
                }else
                    write(ready_socket,&buf,n);
                if(--nready<=0)
                    break;
            }
        }
    }
}
