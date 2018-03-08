#include "csapp.h"

void echo(int connfd);

int main(int argc,char **argv){//命令行输入监听套接字的端口
    int listenfd, connfd, port;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;//容纳任意大小的socket
    char client_hostname[MAXLINE],client_port[MAXLINE];

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);//没有输入端口
        printf("usage: %s <port>\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);//创建监听套接字
    while (1){//无限循环直到获取客户端的请求
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);//获得已连接描述符
        getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}

void echo(int connfd){
    size_t  n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE))!= 0){
        printf("%d bytes\n", (int)n);
        Rio_writen(connfd, buf, n);
    }
}