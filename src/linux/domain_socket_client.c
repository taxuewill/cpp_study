#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

/**/

char path[]= "./namo_amitabha";

int main(void){

    printf("hello,client\n");
    int socket_client = -1;
    int data_len = 0;
    int addr_size = 0;
    struct sockaddr_un addr_srv;
    char str[100];
    memset(str,0,sizeof(char)*100);
    char content[] = "This is test for UDS";
    strncpy(str, content,sizeof(content));

    if((socket_client = socket(AF_UNIX, SOCK_STREAM, 0))<0){
        printf("create domain socket failed\n");
        return -1;
    }
    addr_srv.sun_family = AF_UNIX;
    strncpy(addr_srv.sun_path,path,sizeof(path));
    printf("domain:[%s]\n",addr_srv.sun_path);
    if(connect(socket_client,(struct sockaddr *)&addr_srv,sizeof(addr_srv)) < 0){
        perror("connect failed");
        return -1;
    }

    printf("connect success\n");
    
    if(send(socket_client,content,sizeof(content),0)<0){
        perror("send failed");
        close(socket_client);
        return -1;
    }else{
        printf("send success\n");
    }
    if((data_len = recv(socket_client,str,100,0))>0){
        str[data_len] = '\0';
        printf("echo from server:%s",str);
    }else{
        perror("recv failed");
        close(socket_client);
        return -1;
    }
    close(socket_client);
    return 0;
}

