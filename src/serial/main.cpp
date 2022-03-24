//
// Created by will on 2022/3/18.
//
#include <iostream>
#include <thread>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "serial/userCrc16.h"


using namespace std;

const string kSerialDevice("/dev/ttyUSB0");

char buffer[1024];
int fd = 0;


bool open_port(int & fd){
    int temp = open(kSerialDevice.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
    if(temp == -1){
        cout<<"Can't Open Serial Port"<<endl;
        return false;
    }else{
        cout<<"Open Serial Port Success"<<endl;
        fd = temp;
        return true;
    }
}


int32_t HostSerialConfig(int32_t fd, int32_t baud)
{

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if(tcgetattr(fd, &tty) != 0) {
        return -1;
    }

    cfsetispeed(&tty, baud);
    cfsetospeed(&tty, baud);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = ~(ICANON | ECHO | ECHOE | ISIG);;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = ~OPOST;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 1;                                //0.n seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL);     // shut off xon/xoff ctrl; Don't translate CR to newline

    tty.c_cflag |= (CLOCAL | CREAD);                    // ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);                  // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if(tcsetattr(fd, TCSANOW, &tty) != 0) {
        return -1;
    }

    return 0;
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;

    if ( tcgetattr( fd,&oldtio) != 0) {
        perror("SetupSerial 1");

        return -1;
    }

    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }

    switch( nEvent )
    {
        case 'O':
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'E':
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'N':
            newtio.c_cflag &= ~PARENB;
            break;
    }

    switch( nSpeed )
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }

    if( nStop == 1 )
    {
        newtio.c_cflag &= ~CSTOPB;
    }
    else if ( nStop == 2 )
    {
        newtio.c_cflag |= CSTOPB;
    }

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);

    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");

        return -1;
    }

    printf("set done!\n");

    return 0;
}

void ComRead()
{
    uint8_t read_buffer[128];
    int read_size = 19;
    while(1){
        int nread = read(fd,read_buffer,1280);

        if(nread>0)
        {
            read_size -=nread;

        }
        if(read_size == 0){
            for(int i = 0;i < 19;i++){
                printf("%02x ",read_buffer[i]);
            }
            printf("\n");
            printf("crc is %04x\n",GetCrc16(read_buffer+2,15));
            break;
//            printf("get size is %d\n",nread);
        }
    }
}

uint16_t siCheckSum(uint8_t *pdata,uint16_t len)
{
//    uint16_t sum = 0;
//    uint16_t i;
//    for(i = 0;i < len;i ++) sum +=pdata[i];
//    sum = ~sum;
//    return sum;
    uint16_t sum = 0;
    sum= GetCrc16(pdata,len);

    return sum;
}



int main(int argc, char **argv) {
    cout<<"Serial Test"<<endl;

    if(!open_port(fd)){
        return 0;
    }

    if(HostSerialConfig(fd,B57600)<0){
        close(fd);
        perror("set_opt error");
        return 1;
    }else{
        cout<<"set Config success"<<endl;
    }

    size_t my_size = 18;
    uint8_t writedata[my_size];
    writedata[0] = 0x5A;
    writedata[1] = 0xA5;
    writedata[2] = 9;
    writedata[3] = 0x1C ;  //src
    writedata[4] = 0x20 ;  //dst
    writedata[5] = 0x03; //cmd
    writedata[6] = 0x23;    //index
    writedata[7] = 0x00;    //time
    writedata[8] = 0x00;
    writedata[9] = 0x00;
    writedata[10] = 0x00;
    writedata[11] = 0x00;
    writedata[12] = 0x00;
    writedata[13] = 0x00;
    writedata[14] = 0x00;
    writedata[15] = 1;
    writedata[16] = 0x00;
    writedata[17] = 0x00;

    uint16_t checkSum = siCheckSum(writedata +2,14);
    printf("check sum is %d\n",checkSum);
    memcpy(writedata+16,reinterpret_cast<uint8_t*> (&checkSum),2);



    std::thread read_thread(ComRead);
    bool send_flag = true;
    while(send_flag){
//        printf("send data %02x\n",writedata[0]);
//        int nsend=write(fd,reinterpret_cast<void *>(writedata),18);
//
//        //printf("  nsend:%d  \n",nread);
//
//        if(nsend<0) {
//            printf("send  error\n");
//        }
//        else
//        {
//            printf("Send %d OK\n",nsend);
//        }

//        printf("check sum is %02x %02x\n",writedata[16],writedata[17]);
//        send_flag = false;
        sleep(12);
    }

    read_thread.join();

    close(fd);

    return 0;
}
