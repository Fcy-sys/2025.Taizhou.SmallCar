#include "_includes.h"

using namespace vex;
SpeedControlMode SpeedControlConfig = SPEED_CONTROL; 
double ANGLE = M_PI / 4; // 45��
float speedL = 0, speedR = 0;       //����������ģʽ˫������
float forward_ratio = 1;
float rotate_ratio = 0.5;  


void Chassis::Move_free(double x, double r)
{
    Motor_speed[0] = x + r ;
    Motor_speed[1] = x - r ;
}   

void Chassis::Move() // �˶��ϳ�ִ��
{
    if (SpeedControlConfig == VOLT_CONTROL)      //���õ�ѹ����ģʽ(VOLT_CONTROL)
    {
        Motor_BaseL.spin(vex::forward, Motor_speed[0] * 12.0 / 100.0, vex::volt);
        Motor_BaseR.spin(vex::forward, Motor_speed[1] * 12.0 / 100.0, vex::volt);
    }
    else if(SpeedControlConfig == SOFT_CONTROL) //��������������ģʽ��SOFT_CONTROL��
    {
        int temp = 0;
        temp = speedcontrol.soft_drive(Motor_speed[0], 'L');
        speedL += temp;
        temp = speedcontrol.soft_drive(Motor_speed[1], 'R');
        speedR += temp;
        Motor_BaseL.spin(vex::forward, speedL , vex::pct);
        Motor_BaseR.spin(vex::forward, speedR , vex::pct);
        
    }
    else                                         //�����ٶȿ���ģʽ(SPEED_CONTROL)
    {
        Motor_BaseL.spin(vex::forward, Motor_speed[0] , vex::pct);
        Motor_BaseR.spin(vex::forward, Motor_speed[1] , vex::pct);
    }
}


void chassis_task()             //��������
{
    float brake_speed = 0;                                  //����ɲ��ʱ�ĵ����ٶ�
    double speed_y = Controller.Axis4.position(pct);        //��ȡ�ֱ�ֵ
    double speed_x = Controller.Axis3.position(pct);
    double speed_r = Controller.Axis1.position(pct);
    if (
        fabs(speed_x) >= 10 || 
        fabs(speed_y) >= 10 ||
        fabs(speed_r) >= 10)                                 //����ҡ����������ֹҡ�����޲���״̬��Ư��
    {
        if (fabs(speed_r) > 90) rotate_ratio = 0.7;         //��ҡ���������ת��ϵ�����ɸ��ݲ�����ϰ��ʹ��               
        else rotate_ratio = 0.45;
        
        chassis.Move_free(speed_x * forward_ratio,
                          speed_r * rotate_ratio);          //�����ٶ�д���ٶ�����
    }
    else
    {     
        if(Chassis_velocity > 30)
        {
            brake_speed = Chassis_velocity;
            brake_speed +=speedcontrol.brake_1(0);
            chassis.Move_free(brake_speed ,0);
        }
        else if(Chassis_velocity < -30)
        {
            brake_speed = Chassis_velocity;
            brake_speed +=speedcontrol.brake_2(0);
            chassis.Move_free(brake_speed ,0);
        }
        else 
        {
             chassis.Stop_brake();
        }
    }
    chassis.Move(); // �˶�ִ��
}



/// @brief ����������ֹͣģʽ��ǿ��ɲ��
void Chassis::Stop_brake()
{
    Motor_BaseL.stop(brake);
    Motor_BaseR.stop(brake);
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}

void Chassis::Stop_hold()
{
    Motor_BaseL.stop(hold);
    Motor_BaseR.stop(hold);
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}

void Chassis::Stop_coast()
{
    Motor_BaseL.stop(coast);
    Motor_BaseR.stop(coast);
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}


/// @brief ������·�������ĵ����˶�������������ֱ�����������߳���ǽ���ߣ�����ÿ���ߵĲ�һ����   
/// @param ����Ŀ��Ƕ�
//�����ǰ�汾�������ٶȻ���ϣ������ʵ�ֵ���ת��Ŀ�����δ����
void Chassis::Move_Curve(float angle)
{
    double hope = 0;
    double fit_value = 0;                                                                                            // ����ֵ
    pid.init(&pid_pose, 0.5, 0.2, 1, 70, 3, 1);
    hope = pid.PID_Absolute(&pid_pose, angle, Inertial.rotation(rotationUnits::deg));                           //��������ֵ
    fit_value = hope;//+= speedcontrol.adjust(hope);
    Motor_speed[0] += fit_value;
    Motor_speed[1] -= fit_value;
}


void Chassis::Move_withfit(float angle)
{
    double hope = 0;
    double fit_value = 0;                                                                                            // ����ֵ
    pid.init(&pid_pose, 0.05, 0.2, 0.6, 4, 3, 0.5);
    hope = pid.PID_Absolute(&pid_pose, angle, Inertial.rotation(rotationUnits::deg));                           //��������ֵ
    fit_value = hope;//+= speedcontrol.adjust(hope);
    Motor_speed[0] += fit_value;
    Motor_speed[1] -= fit_value;
}


int Chassis::stop_Monitor()             //ûɶ�ã�
{
    if (Controller.ButtonUp.RELEASED == 0 && Controller.ButtonDown.RELEASED == 0 && Controller.ButtonLeft.RELEASED == 0 && Controller.ButtonRight.RELEASED == 0)
    {
        return 1;
    }
    return 0;
}
Chassis::Chassis()  //���̳�ʼ��
{
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}

void Thread_ChassisTask()
{
    while (true)
    {
        chassis_task();
        this_thread::sleep_for(10);
    }
}