#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>


char path[]= "./namo_amitabha";

int main(void){

    printf("hello,server\n");

    int socket_srv = -1;
    int socket_client = -1;
    // int t = -1;
    int len = 0;
    struct sockaddr_un addr_srv, addr_client;
    char str[1024] = {0};
    // memset(str,0,sizeof(char)*100);
    

    if((socket_srv = socket(AF_UNIX, SOCK_STREAM, 0))<0){
        printf("create domain socket failed\n");
        return -1;
    }else{
        printf("create domain socket\n");
    }

    //create server socket

    printf("start cpy path\n");
    addr_srv.sun_family = AF_UNIX;
    memset(addr_srv.sun_path,0 ,sizeof(addr_srv.sun_path));
    strncpy(addr_srv.sun_path,path,sizeof(path));

    printf("domain:[%s]\n",addr_srv.sun_path);

    if(remove(path) == -1&& errno != ENOENT){
        perror("remove error");
        return -1;
    }else{
        printf("remove\n");
    }
    

    if(bind(socket_srv,(struct sockaddr*)&addr_srv,sizeof(addr_srv))<0){
        printf("bind failed\n");
        perror("bind error");
        return -1;
    }

    if(listen(socket_srv, 100)<0){
        return -1;
    }

    while(1){
        int nRecv;
        if((socket_client = accept(socket_srv,NULL,NULL)) == -1){ //(struct sockaddr *)&addr_client,&sz
            printf("accept failed\n");
            return -1;
        }
        printf("accept one  %d\n",socket_client);
        if((nRecv = recv(socket_client,str,1024,0))<0){
            perror("recv failed");
            close(socket_client);
            break;
        }else{
            str[nRecv] = '\0';
            printf("get client content [%s],%d\n",str,nRecv);
            
        }
        printf("nRecv %d\n",nRecv);
        if(send(socket_client,str,nRecv,0)<0){
            perror("send failed");
            close(socket_client);
            break;
        }
        close(socket_client);
    }

    close(socket_srv);
    printf("close server\n");

    return 0;
}
