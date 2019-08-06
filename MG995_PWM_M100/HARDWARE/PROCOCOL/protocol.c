#include "protocol.h"
#include "usart.h"
#include "i2c.h"

DEF_RE_RECEIVE receive_data;
DEF_RE_RECEIVE i2c_receive_data;
uint8_t check[20];
int16_t pack_motor[2]= {0};
int16_t pack_motor_outdoor[4]={0};

void RECEIVE_PACK(unsigned char data)
{
    //校验和
    static unsigned char sum_check=0;
    //数据计数
    static unsigned char data_num=0;
   // printf("receive_back");
   // printf("%d",data);
    switch(receive_data.state)
    {
    //包头1
    case HEADER1:
        if(data==0xB5)
        {
        //    printf("0xB5\n");
            receive_data.state = HEADER2;
            sum_check += data;
        }
        else
        {
            receive_data.state=HEADER1;
            data_num = 0;
        }
        //sum_check = 0;
        break;

    //包头2
    case HEADER2:
        if(data==0x5B)
        {
         //      printf("0x5B\n");
            receive_data.state = CMDID1;
            sum_check += data;

        }
        else
        {
            receive_data.state=HEADER1;
            data_num = 0;
        }
        //sum_check = 0;

        break;

    //ID
    case CMDID1:
        if(data==0x01)
        {
           // printf("0x01");
            //	pack[0]=data;
            receive_data.state=LENGTH1;
            receive_data.Cmd_ID = data;
            sum_check += data;

        }
        else
        {
            receive_data.state=HEADER1;
            sum_check=0;
        }
        break;

    //长度
    case LENGTH1:
        //	printf("0x01");
        //	pack[1]=data;
        receive_data.Length = data;
        receive_data.state = DATA1;
        sum_check += data;

        break;

    //数据
    case DATA1:
      //  printf("0x01");
        //	printf("%d\n",data);
        receive_data.Re_Data [data_num++] = data;
        check[data_num + 3] = data;
        sum_check+=data;
        if(data_num==receive_data.Length)
        {
            receive_data.state=CHECK1;
        }
      //  printf("%d",sum_check);
        break;



    //校验
    case CHECK1:
        if(data == sum_check % 0xff)
        {
         //   printf("14");
//            pack_motor[0] = ((receive_data.Re_Data[0]<<8)| (receive_data.Re_Data[1]));
//            pack_motor[1] = ((receive_data.Re_Data[2]<<8)| (receive_data.Re_Data[3]));
            pack_motor[0] = receive_data.Re_Data[0];
          //  printf("%d",pack_motor[0]);
            pack_motor[1] = receive_data.Re_Data[1];
        }
        receive_data.state = END;
        data_num = 0;
        sum_check=0;
        break;

    //包尾
    case END:
        if(data == 0xBB)
        {
            receive_data.state = HEADER1;
            data_num = 0;
            sum_check=0;
        }
        break;

    }
}

void I2C_PACK(unsigned char data)
{
    static unsigned char i2c_sum_check=0;
    static unsigned char i2c_data_num=0;
     switch(i2c_receive_data.state)
    {
    //包头1
    case HEADER1:
        if(data==0xB5)
        {
        //    printf("0xB5\n");
            i2c_receive_data.state = HEADER2;
            i2c_sum_check += data;
        }
        else
        {
            i2c_receive_data.state=HEADER1;
            i2c_data_num = 0;
        }
        //sum_check = 0;
        break;

    //包头2
    case HEADER2:
        if(data==0x5B)
        {
         //      printf("0x5B\n");
            i2c_receive_data.state = CMDID1;
            i2c_sum_check += data;

        }
        else
        {
            i2c_receive_data.state=HEADER1;
            i2c_data_num = 0;
        }
        //sum_check = 0;

        break;

    //ID
    case CMDID1:
        if(data==0x01)
        {
           // printf("0x01");
            //	pack[0]=data;
            i2c_receive_data.state=LENGTH1;
            i2c_receive_data.Cmd_ID = data;
            i2c_sum_check += data;

        }
        else
        {
            i2c_receive_data.state=HEADER1;
            i2c_sum_check=0;
        }
        break;

    //长度
    case LENGTH1:
        //	printf("0x01");
        //	pack[1]=data;
        i2c_receive_data.Length = data;
        i2c_receive_data.state = DATA1;
        i2c_sum_check += data;

        break;

    //数据
    case DATA1:
      //  printf("0x01");
        //	printf("%d\n",data);
        i2c_receive_data.Re_Data [i2c_data_num++] = data;
       //i2c_check[data_num + 3] = data;
        i2c_sum_check+=data;
        if(i2c_data_num==i2c_receive_data.Length)
        {
            i2c_receive_data.state=CHECK1;
        }
      //  printf("%d",sum_check);
        break;



    //校验
    case CHECK1:
        if(data == i2c_sum_check % 0xff)
        {
         //   printf("14");
//            pack_motor[0] = ((receive_data.Re_Data[0]<<8)| (receive_data.Re_Data[1]));
//            pack_motor[1] = ((receive_data.Re_Data[2]<<8)| (receive_data.Re_Data[3]));
            pack_motor_outdoor[0] = i2c_receive_data.Re_Data[0];
          //  printf("%d",pack_motor[0]);
            pack_motor_outdoor[1] = i2c_receive_data.Re_Data[1];
        }
        i2c_receive_data.state = END;
        i2c_data_num = 0;
        i2c_sum_check=0;
        break;

    //包尾
    case END:
        if(data == 0xBB)
        {
            i2c_receive_data.state = HEADER1;
            i2c_data_num = 0;
            i2c_sum_check=0;
        }
        break;

    }
    
    
}
