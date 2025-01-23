#ifndef CHASSIS_H_
#define CHASSIS_H_

//�����ۺ��Դ���λ�ڴ˴��������������ڲ������궨�壬����
#include "PID.h"
#include "PIDProcess.h"
#include "robot-config.h"


void chassis_task();           //��������
void Thread_ChassisTask();     //�����߳� 
class Chassis
{
private:
    double Motor_speed[2];//LF��LB��RF��RB,ֵΪ�ٷֱ�
public:
    Chassis();//���̳�ʼ��
    double angle = 0;
    double speed_x = 0;
    double speed_y = 0;
    double speed_r = 0;

    void Move_free(double x, double r);//�����ƶ�д�������ٶ�
    
    int stop_Monitor();//�ֱ�����ֹͣ�źż��

    void Move();//�˶�ִ�к���

    void Stop_brake();
    void Stop_coast();
    void Stop_hold();//ֹͣ
    
    void Move_Curve(float angle);//��������
    void Move_withfit(float angle);//ֱ������
};

typedef enum
{
    SPEED_CONTROL,//�ٶȿ��Ƶ���
    VOLT_CONTROL,//��ѹ���Ƶ���
    SOFT_CONTROL//(������)�ٶ�-��ѹ���Ƶ���
} SpeedControlMode;//�����˶�����ģʽ

#endif