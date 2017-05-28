#include"TCPechoClient.h"
TCPechoClient::TCPechoClient(const char *ip,int port):server_ip(ip),server_port(port){
    bzero(&server_addr,sizeof(server_addr));
    inet_pton(AF_INET,server_ip,&server_addr.sin_addr);
    server_addr.sin_port = htons(server_port);
    server_addr.sin_family = AF_INET;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
}
void TCPechoClient::start(){
    FD_ZERO(&rset);
    FD_ZERO(&wset);
    tostart = toend = to;
    frstart = frend = fr;
    int val=0,stdineof = 0;
    ssize_t nread=0,nwrite=0,n=0;
    int ret = 0;
     if((ret =connect(sockfd,(sockaddr*)&server_addr,sizeof(server_addr)))<0)
        std::cout<<strerror(errno)<<std::endl;
    val = fcntl(STDIN_FD,F_GETFL,0);
    fcntl(STDIN_FD,F_SETFL,val|O_NONBLOCK);
    val = fcntl(STDOUT_FD,F_GETFL,0);
    fcntl(STDOUT_FD,F_SETFL,val|O_NONBLOCK);
    val = fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd,F_SETFL,val|O_NONBLOCK);
    int maxfd = std::max(std::max(STDIN_FD,STDOUT_FD),sockfd);

    for(;;){
        if(stdineof==0&&toend<&to[MAX_LINE])
            FD_SET(STDIN_FD,&rset);
        if(frstart!=frend)
            FD_SET(STDOUT_FD,&wset);
        if(tostart!=toend)
            FD_SET(sockfd,&wset);
        if(frend<&fr[MAX_LINE])
            FD_SET(sockfd,&rset);
        select(maxfd+1,&rset,&wset,NULL,NULL);
        if(FD_ISSET(STDIN_FD,&rset)){
            if((nread = read(STDIN_FD,toend,&to[MAX_LINE]-toend))<0){
                if(errno != EWOULDBLOCK){
                    std::cout<<"stdin error"<<std::endl;
                    exit(0);
                }
            }else if(nread ==0){
                stdineof = 1;
                shutdown(sockfd,SHUT_WR);
            }else{
                toend+=nread;
                FD_SET(sockfd,&wset);
            }
        }
        if(FD_ISSET(sockfd,&rset)){
            if((nread = read(sockfd,frend,&fr[MAX_LINE]-frend))<0){
                if(errno != EWOULDBLOCK){
                    std::cout<<"socket read error"<<std::endl;
                    exit(0);
                }else if(nread == 0){
                    if(stdineof==0){
                        std::cout<<"server shutdown"<<std::endl;
                        exit(0);
                    }else
                        shutdown(sockfd,SHUT_RD);
                }else{
                    frend+=nread;
                    FD_SET(STDOUT_FD,&wset);
                }
            }
        }
        if(FD_ISSET(STDOUT_FD,&wset)&&(n=frend-frstart)>0){
            if((nwrite = write(STDOUT_FD,frstart,n))<0){
                if(errno != EWOULDBLOCK){
                    std::cout<<"stdout error"<<std::endl;
                    exit(0);
                }
            }else{
                frstart += nwrite;
                if(frstart == frend)
                    frstart = frend = fr;
            }
        }
        if(FD_ISSET(sockfd,&wset)&&(n = toend-tostart)>0){
            if((nwrite = write(sockfd,tostart,n))<0){
                if(errno != EWOULDBLOCK){
                    std::cout<<"socket write error"<<std::endl;
                    exit(0);
                }
            }else{
                tostart+=nwrite;
                if(tostart ==toend){
                    tostart = toend = to;
                    if(stdineof)
                        shutdown(sockfd,SHUT_WR);
                }
            }
        }
    }
}
