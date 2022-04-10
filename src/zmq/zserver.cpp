//
// Created by will on 2022/4/8.
//
#include <cassert>
#include <string.h>
#include <unistd.h>

#include <zmq.h>

int main(int argc,char ** argv){
    void * context = zmq_ctx_new();
    void * publisher = zmq_socket(context,ZMQ_PUB);
    int rc = zmq_bind(publisher,"tcp://127.0.0.1:5566");
    assert(rc == 0);
    char header[] = "header";
    int header_length = strlen(header);
    char  data[] = "this is data";
    int length = strlen(data);

    while(1){
        zmq_msg_t header_msg;
        zmq_msg_init_size(&header_msg,header_length);
        memcpy(zmq_msg_data(&header_msg),header,header_length);
        zmq_msg_send(&header_msg,publisher,ZMQ_SNDMORE);

        zmq_msg_t msg;
        zmq_msg_init_size(&msg,length);
        memcpy(zmq_msg_data(&msg), &data, length);
        zmq_msg_send(&msg,publisher,0);
        sleep(5);
    }

    zmq_ctx_destroy(context);
    return 0;
}