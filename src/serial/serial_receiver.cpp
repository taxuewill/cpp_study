//
// Created by will on 2022/4/15.
//

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
#include <time.h>
#include <sys/time.h>
#include <vector>

using namespace std;

//const string kSerialDevice("/dev/ttyS3");
const string kSerialDevice("/dev/ttyUSB1");

std::vector<uint64_t> time_delay_list(1100);

char buffer[1024];
int fd = 0;
int fd2 = 0;
int cnt = 1000,hz=0;


//bool open_port(int & fd){
//    int temp = open(kSerialDevice.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
//    if(temp == -1){
//        cout<<"Can't Open Serial Port"<<endl;
//        return false;
//    }else{
//        cout<<"Open Serial Port Success"<<endl;
//        fd = temp;
//        return true;
//    }
//}

bool open_port(int & fd,const std::string& dev_name){
//    int temp = open(dev_name.c_str(), O_RDWR|O_NOCTTY|O_NDELAY|O_ASYNC);
    int temp = open(dev_name.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
    if(temp == -1){
        cout<<"Can't Open Serial Port "<<dev_name<<endl;
        return false;
    }else{
        cout<<"Open Serial Port Success "<<dev_name<<endl;
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

int32_t HostSerialRecvOnePack()
{


    //TODO SQ: pre-alloc these variables in class.
    uint8_t buf[250] = {0}; //TODO... rtk data max data 128?
    uint8_t * ptr = buf;
    int32_t len = 0;
    int32_t remain_len = 0;
    int32_t read_len = 0;
    int32_t data_len = 0;
    int recv_state = 0;
    uint8_t data_buf[255] = {0};
    int receive_times = 0;
    // data_buf = NULL;
    int i = 0;
    fd_set rd_fdset;
    struct timeval dly_tm;
    while(receive_times<cnt) {


        fd_set rd_fdset;
        FD_ZERO(&rd_fdset);
        FD_SET(fd, &rd_fdset);
        struct timeval dly_tm;
        dly_tm.tv_sec  = 1;
        dly_tm.tv_usec = 0;
        // char buf[256];
        // int temp = 0;
        i++;
        int ret = select(fd+1, &rd_fdset, NULL, NULL, &dly_tm);
        /* wait timeout */
        if (ret == 0) {
            // err_cnt++;
             printf("\n%d times : wait data timeout.\n", i);
            // goto begin_next_test;
            continue;
        }

        /* select error */
        if (ret < 0) {
            // err_cnt++;
            // printf("select(%s) return %d. [%d]: %s \n", argv[PT_DEV_PORT], ret, errno, strerror(errno));
            // goto begin_next_test;
            continue;

        }


        //TODO SQ: use a switch-case pattern state machine. Use enum as state ID.
        //TODO SQ: seprate implement state in funstions.
        if(recv_state == 0) {
            memset(data_buf,0,200);
            //TODO SQ: use a wapper serial::read(uint8_t* buf, int len), to datapt differnt read / mock read methods.
            len = read(fd, buf, 1);
            if(len == 1) {
                if(buf[0] == 0x5A) {
                    recv_state = 1;
                    //gettimeofday(&g_sendtime2, NULL);
                    // printf("recv 5A\n");
                }
                else {
                    printf( "%s: recv not 5A but is %02x\n",__FUNCTION__,buf[0]);
                    recv_state = 0;
                }
            }
            else {
                //TODO: this trace can abstract to macro.
                //TracePrint(GetTrace(*serial_interface), TraceLevelWarning, "error byte %d\n", recv_state);
                recv_state = 0;
                // if(serial_interface->serial_recv_terminate == 1){
                //     // TracePrint(GetTrace(*serial_interface), TraceLevelWarning, "read(fd) exit\n");
                //     return -1;
                // }
            }
        }
        else if(recv_state == 1) {
            len = read(fd, buf, 1);
            if(len == 1) {
                if(buf[0] == 0xA5) {
                    recv_state = 2;
                    printf("recv start: 5A A5\n");
                }
                else {
                    recv_state = 0;
                    printf( "error byte %d\n", recv_state);
                    // TracePrint(GetTrace(gControlDataSync), TraceLevelVerbose, "%s: recv not A5\n",__FUNCTION__);
                }
            }
            else {
                printf("error byte %d\n", recv_state);
                recv_state = 0;
            }
        }
        else if(recv_state == 2) {
            len = read(fd, buf, 1);
            if(len == 1) {
                recv_state = 3;
            }
            else {

                printf("error byte %d\n", recv_state);
                recv_state = 0;
            }
        }
        else if(recv_state == 3) {
            remain_len = 4;
            read_len = 0;
            head_read:  len = read(fd, &buf[1+read_len], remain_len);
            if(len >= 0) {
                remain_len -= len;
                read_len += len;
                if(remain_len == 0) {
                    recv_state = 4;
                    printf("recv data5:%x %x %x %x %x\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
                }
                else {
                    goto head_read; //TODO SQ Don't use goto (NOT even continue!). use standard state machine.
                }
            }
            else {
                recv_state = 0;
                printf("error byte %d, len error %d:%d\n", recv_state, len, remain_len);
            }
        }
        else if(recv_state == 4) {
            //remain_len = buf[0] + 2;
            remain_len = buf[0];
            data_len = remain_len;
            read_len = 0;

            //TODO SQ: use static memory.
            // auto data = malloc(data_len + 6);

            {
                data_read:  len = read(fd, &data_buf[read_len], remain_len);
                if(len >= 0) {
                    remain_len -= len;
                    read_len += len;
                    if(remain_len == 0) {
                        recv_state = 5;
                        printf(" read_data:\n 5A A5 ");
                        for(i=0; i<5; i++){
                            printf(" %x ",buf[i]);
                        }
                        for(i = 0; i < read_len; i++)
                            printf(" %x ",data_buf[i]);
                        printf("\n");
                    }
                    else {
                        goto data_read; //TODO SQ Don't use goto (NOT even 'continue'!). use standard state machine.
                    }
                }
                else {
                    printf("error byte %d, len short %d:%d\n", recv_state, len, remain_len);
                    perror("read:\n");
                    recv_state = 0;
                    // free(data_buf);
                    // data_buf = NULL;
                }
            }
        }
        else if(recv_state == 5) {
            remain_len = 2;
            read_len = 0;
            cs_read:    len = read(fd, &buf[5 + read_len], remain_len);
            if(len >= 0) {
                remain_len -= len;
                read_len += len;
                if(remain_len == 0) {   //todo optimize use buf instead of temp_buffer
                    uint16_t recv_checksum = ((uint16_t) buf[6]) << 8 | (uint16_t) buf[5];
                    uint8_t temp_buffer_size = 5+buf[0];
                    u_int8_t temp_buffer[temp_buffer_size];
                    memcpy(temp_buffer,buf,5);
                    memcpy(temp_buffer+5,data_buf,data_len);
                    uint16_t checksum = GetCrc16(temp_buffer,temp_buffer_size);
                    if (checksum == recv_checksum) {
                        receive_times++;
                        recv_state = 0;
                        printf("checksum ：%x,%x right checksum:%d,recv_checksum:%d,receive_times:%d\n",buf[5],buf[6],checksum,recv_checksum,receive_times);
                        // continue;
                    } else {
                        printf("Checksum error!\n");
                        // TracePrint(GetTrace(gControlDataSync), TraceLevelVerbose, "%s: Checksum error!\n",__FUNCTION__);
                        recv_state = 0;
                        // free(data_buf);
                        // data_buf = NULL;
                    }
                }
                else {
                    goto cs_read;  //TODO SQ: Don't use goto (NOT even continue!). use standard state machine.
                }
            }
            else {
                printf("Checksum %d len error %d:%d\n", recv_state, len, remain_len);
                // TracePrint(GetTrace(gControlDataSync), TraceLevelVerbose, "%s: Checksum error len=0!\n",__FUNCTION__);
                recv_state = 0;
                // free(data_buf);
                // data_buf = NULL;
            }
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

int GetTimeOfDay(struct timeval *tv){

    gettimeofday(tv,NULL);

}

#define MAX_BASIC_FRM_SZ 0x81 //TODO... rtk data max data 128?

#if 1
#pragma pack(1)
typedef struct StampedBasicFrame_{
    uint32_t type_id;                 //数据类型编号，此时为index
    int32_t data_len;                //有效数据长度,如 imu acc 6byte一个包，imu gyro 6byte一个包，如果imu一起传，则是12byte；ticks 左和右一个包，16byte；
    uint64_t timestamp;               //Linux时间戳
    char  data[MAX_BASIC_FRM_SZ];     //具体数值
} StampedBasicFrame;
#pragma pack()
#endif

//------------MOWER INDEX---------------------
//寄存器地址定义
#define COMM_MOWER_SPEED_WX				0x01	//底盘速度，w(rad/s)，精度同v(m/s)
#define COMM_MOWER_SPEED_VX				0x02    //底盘速度，v(m/s)，如1m/s ，发送1000
#define COMM_MOWER_CHASSIS_TICKS_L		0x04	//0x04--0x07，ticks，频率20hz
#define COMM_MOWER_CHASSIS_TICKS_R		0x08	//0x08--0x0b，ticks，频率20hz

#define COMM_MOWER_CHASSIS_ERROR		0x0C	//底盘报错信息：底盘错误码，出错时上报

#define COMM_MOWER_CHASSIS_ACC_X		0x0E	//IMU：所有加速度 x 的原始数据，频率100hz
#define COMM_MOWER_CHASSIS_ACC_Y		0x0F	//IMU：所有加速度 y 的原始数据，频率100hz
#define COMM_MOWER_CHASSIS_ACC_Z		0x10	//IMU：所有加速度 z 的原始数据，频率100hz
#define COMM_MOWER_CHASSIS_GYRO_X		0x11	//IMU：所有陀螺仪 x 的原始数据，频率100hz
#define COMM_MOWER_CHASSIS_GYRO_Y		0x12	//IMU：所有陀螺仪 y 的原始数据，频率100hz
#define COMM_MOWER_CHASSIS_GYRO_Z		0x13	//IMU：所有陀螺仪 z 的原始数据，频率100hz

#define COMM_MOWER_CHASSIS_VERSION      0x14	//
#define COMM_MOWER_CHASSIS_EMERGENCY    0x15    //底盘急停信息：急停信号，底盘触发；上层调用和底盘主动上报2种情况
// #define COMM_MOWER_BMS_CHARGE           0x16	//BMS charge
// #define COMM_MOWER_EYE_BMS_CAPACITY     0x17	//BMS capacity,0%-100%
// #define COMM_MOWER_EYE_POWER_OFF     	0x18	//shutdown,底盘发给rk的
#define COMM_MOWER_BASE_TIMESTAMP     	0x18	//主控当前的时间的时间戳 ref:BaseTimeStamp.msg
#define COMM_MOWER_BUMPER               0x19    //bumper
#define COMM_MOWER_RTK                  0x21    //rtk
#define COMM_MOWER_MAP_CONTROL          0x23    //planner对感知地图操作的指令
#define COMM_MOWER_EFLS_POSE            0x28    //融合位姿，包括cov
#define COMM_MOWER_BU_INFO              0x25    //收到业务请求之后的返回，收到一次请求code就返回一次结果


////wiki not define BAT info
#define COMM_MOWER_BAT_VOLTAGE          0x1A    //voltage of battery
#define COMM_MOWER_BAT_CURRENT          0x1B    //current of battery
#define COMM_MOWER_BAT_PERCENT          0x1C    //remain electric quantulity of battery
#define COMM_MOWER_BAT_ERR_CODE         0x1D    //error of battery
#define COMM_MOWER_BAT_TEMP             0x1E    //temperature of battery
#define COMM_MOWER_LOCAL_MAP_STATE      0x61    //localmap的启动状态
#define COMM_MOWER_MODE_ERROR_CODE      0x66    //感知错误
#define COMM_MOWER_BU_CODE              0x0B    //业务控制指令

#define COMM_MOWER_LOCAL_SIMPLE_MAT     0x9D    //感知生成的地图数据


#define COMM_MOWER_MODE					0x8A	//遥控模式：写0x07表示进入遥控模式,注意：千万不要写入别的数据

//#define MOWER_BIT_ERROR_RATE_CMD			0xFA	//测试误码率使用,上层不需要关心

#pragma pack(1)
typedef struct MowerBaseTimestampData_ {
    uint64_t timestamp;
    uint16_t index;
}MowerBaseTimestampData;
#pragma pack()

enum parameter_type {
    PT_PROGRAM_NAME = 0,
    // PT_DEV_PORT,
    // PT_DEV_BAUDRATE,
    PT_CYCLE,
    PT_DATA_SIZE,
    PT_HZ,
    PT_NUM,
};



int main(int argc, char **argv) {


    int i = 0, temp = 0, ret = -1;
    int read_size = 0, write_size = 0;

    int baudrate;

    char *data_buf = NULL;
    char *receive_buf = NULL;
    char uart_port[16] = {0};
    char buf[256];
    int data_size = 0;



    cout<<"Serial Receiver Test"<<endl;


    if(!open_port(fd,kSerialDevice)){
        return 0;
    }

    if(HostSerialConfig(fd,B57600)<0){
        close(fd);
        perror("set_opt error");
        return 1;
    }else{
        cout<<"set Config success fd:"<<fd<<endl;
    }


    size_t my_size = data_size;
    uint8_t writedata[my_size+9+1];
    writedata[0] = 0x5A;
    writedata[1] = 0xA5;

    writedata[2] = my_size;//len

    writedata[3] = 0x20 ;  //src
    writedata[4] = 0x1C ;  //dst
    writedata[5] = 0x03; //cmd
    writedata[6] = 0;    //index

    writedata[7] = 0x00;    //time  data?
    writedata[8] = 0x00;

    writedata[9] = 0x00;
    writedata[10] = 0x00;
    writedata[11] = 0x00;
    writedata[12] = 0x00;
    writedata[13] = 0x00;
    writedata[14] = 0x00;

    writedata[15] = 0x00;
    writedata[16] = 0x00;

    writedata[17] = 0x00;//check sum
    writedata[18] = 0x00;

//    for(int i=15;i< my_size+7;i++){
//        writedata[i] = i-15;
//    }

    for(int i=7;i< my_size+7;i++){
        writedata[i] = i-7;
    }

    writedata[my_size + 9] = '\n';


    struct timeval tv;
    gettimeofday(&tv,NULL);
    uint64_t time_now = (tv.tv_sec * 1000*1000 + tv.tv_usec)/1000;
    printf("time_now:%ld,tv_sec:%ld\n",time_now,tv.tv_sec);
    printf("time_now:size :%d\n",sizeof(time_now));
//    memcpy(&writedata[7],&time_now,sizeof(time_now));

    uint16_t checkSum = siCheckSum(writedata +2,my_size+7);
    printf("check sum is %d\n",checkSum);

    memcpy(writedata+my_size+7,reinterpret_cast<uint8_t*> (&checkSum),2);

    // MowerBaseTimestampData test_data;

    // std::thread read_thread(ComRead, data_size);
    std::thread read_thread(HostSerialRecvOnePack);

    bool send_flag = true;
    int n_times = 0;


    read_thread.join();

    close(fd);

    return 0;
}

