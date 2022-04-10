//
// Created by will on 2022/4/8.
//

#include <zmq.h>
#include <cstring>
#include <cassert>

int main(int argc,char ** argv){
    void * context = zmq_ctx_new();
    void * subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, "tcp://127.0.0.1:5566");
    assert(rc == 0);
    rc = zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,"", 0);
    assert(rc == 0);

    while(1){
        zmq_msg_t msg;
        zmq_msg_init(&msg);
        zmq_msg_recv(&msg,subscriber,0);
        printf("msg size %d\n", zmq_msg_size(&msg));
        char * data_point = (char *)zmq_msg_data(&msg);
        for(int i = 0 ; i < zmq_msg_size(&msg);i++){
            printf("%c",data_point[i]);
        }
        printf("\n");
        char buffer[zmq_msg_size(&msg)+1];
        memcpy(&buffer, (char *)zmq_msg_data(&msg), zmq_msg_size(&msg));
        buffer[zmq_msg_size(&msg)] = '\0';
        printf("content is %s\n",buffer);
        if(zmq_msg_more(&msg)){
            zmq_msg_recv(&msg,subscriber,0);
            printf("has more msg size %d\n", zmq_msg_size(&msg));
            char * data_point = (char *)zmq_msg_data(&msg);
            for(int i = 0 ; i < zmq_msg_size(&msg);i++){
                printf("%c",data_point[i]);
            }
            printf("\n");

        }
        zmq_msg_close(&msg);

    }

    zmq_ctx_destroy(context);
    return 0;
}
