#include "_includes.h"

using std::vector;
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！喘噐堪笥宥佚！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！//

uint8_t buffet[8] = {0};
void Serial_Send(float data0, float data1, float data2, float data3)              //窟僕汽倖方象
{
    vector<float> data{data0, data1, data2, data3};
    uint8_t* point;
    for(int i = 0; i < 4; i++)
    {
      point = Float2Byte(data[i]);
      if(i == 3)
      {
        point[7] = '\n';
      }
      vexGenericSerialTransmit(Serial.index(), point, 8);
    }
}

uint8_t* Float2Byte(float f)
  {
    if (f < 0)
    {
      f = -f;
      buffet[0] = '-';
    }
    else
    {
      buffet[0] = '+';
    }
    int hundred = f / 100;
    int ten = (f - hundred * 100) / 10;
    int one = f - hundred * 100 - ten * 10;
    int decimal = (f - hundred * 100 - ten * 10 - one) * 10;
    int decimal2 = (f - hundred * 100 - ten * 10 - one - decimal * 0.1) * 100;
    
    char hundred_c = hundred + '0';
    char ten_c = ten + '0';
    char one_c = one + '0';
    char decimal_c = decimal + '0';
    char decimal2_c = decimal2 + '0';

    buffet[1] = hundred_c;
    buffet[2] = ten_c;
    buffet[3] = one_c;
    buffet[4] = '.';
    buffet[5] = decimal_c;
    buffet[6] = decimal2_c;
    buffet[7] = ',';
    
    return buffet;
  }