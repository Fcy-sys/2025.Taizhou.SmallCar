#include "_includes.h"


//����ʽPID���Ƶ���ٶȣ��������Զ�ʵ�ִ���PID���������������ֶ�������/ɲ��������ͷ��β��
//���ڼ��٣���ǰɲ�������ɲ���������ͬ������Ӧ�ֱ����
//��Ҫ���ڲ���I��P���Ƴ�����Dûɶ�ã����㼴��

/// @brief ���ٲ�ά�������ٶ�
/// @param �����ٶȣ���������
/// @return ��ǰӦ�����������ٶ�����
double Speedcontrol::speed_up(double speed)              
{
    pid.init(&pid_speed, 3.0, 4.0, 0 ,20);
    double speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}


double Speedcontrol::brake(double speed)
{
    pid.init(&pid_speed, 0.3, 0.55, 0, 10);    //0.038  0.055
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief ��ǰ�ٶȵ�ɲ��
/// @param �����ٶȣ���������
/// @return ��ǰӦ�����������ٶ�����
double Speedcontrol::brake_1(double speed)
{
    pid.init(&pid_speed, 0.5, 0.7, 0, 15);
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief �����ٶȵ�ɲ��
/// @param �����ٶȣ���������
/// @return ��ǰӦ�����������ٶ�
double Speedcontrol::brake_2(double speed)
{
    pid.init(&pid_speed, 0.3, 0.75, 0, 20);
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief ��������ת���ٶ�
/// @param �����ٶȣ���������
/// @return ��ǰӦ�����������ٶ�
double Speedcontrol::adjust(double speed)
{
    pid.init(&pid_speed, 0.3, 1, 0, 30);
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief �������ã��ɿ��Ƶ����ٶ�
/// @param �����ٶȣ���������,���Ҳ�ѡ��(LΪ��RΪ��)
/// @return ��ǰӦ�����������ٶ�����
double Speedcontrol::soft_drive(double speed, char side)                 
{
    float side_speed = 0;
    pid.init(&pid_speed, 0.019, 0.04, 0 ,2);
    if (side == 'L')
    {
        side_speed = (Motor_BaseLB2.velocity(pct) + Motor_BaseLB1.velocity(pct) + Motor_BaseLF.velocity(pct)) / 3;
    }
    else if (side == 'R')
    {
        side_speed = (Motor_BaseRB2.velocity(pct) + Motor_BaseRB1.velocity(pct) + Motor_BaseRF.velocity(pct)) / 3;
    }
    double speedDev = pid.PID_Incremental(&pid_speed, speed, side_speed);
    return speedDev;
}