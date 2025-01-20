/**
  ******************************************************************************
  * @file           : analyse.cpp
  * @brief          : ���ڷ������ݣ�����������������ʾ�ڵ�����Ļ��
  ******************************************************************************
  * @attention      ����Ҫ����ʹ��
  *
  *
  ******************************************************************************
  */
#include "_includes.h"


void Analyse_Rotates();
void Main_DataShow();
void Analyse_Inertial();
void Analyse_Velocity();
float Chassis_velocity = 0.0;



MainDataSTR MainData;


void check(float _delta)                            //�鿴����
{
    std::cout << _delta << std::endl;      
}


/// @brief ���ݷ���
void DataAnalyse()
{
    static int temp_count = 0; // ���ڿ���������ʾ��Ƶ��
    if (temp_count == 50)
    {
        //  Controller_DataShow();
        //printf("------------------\n"); 
        // Rotates_DataShow();
        // Arm_DataShow();
        // Inertial_DataShow();
        //Main_DataShow();
        temp_count = 0;
    }
    temp_count++;
    Analyse_Rotates();
    Analyse_Inertial();
    Analyse_Velocity();
    //Analyse_Position();
}

/// @brief ���ݷ����߳�
void Thread_DataAnalyse()
{
    while (true)
    {
        DataAnalyse();
        this_thread::sleep_for(10);
    }
}

/// @brief �Ƕȴ�������������ʾ
void Analyse_Rotates()
{
#ifdef USE_MOTOR_ENCODER    
    int num = 6;
    double deg_motor[num];
    deg_motor[0] = Motor_BaseRF.position(rotationUnits::deg);
    deg_motor[1] = Motor_BaseLF.position(rotationUnits::deg);
    deg_motor[2] = Motor_BaseLB1.position(rotationUnits::deg);
    deg_motor[3] = Motor_BaseLB2.position(rotationUnits::deg);
    deg_motor[4] = Motor_BaseRB1.position(rotationUnits::deg);
    deg_motor[5] = Motor_BaseRB2.position(rotationUnits::deg);

    double deg_wheel[num/2];
    deg_wheel[0] = (deg_motor[0] + deg_motor[1]) / 2;
    deg_wheel[1] = (deg_motor[2] + deg_motor[3]) / 2;
    deg_wheel[2] = (deg_motor[4] + deg_motor[5]) / 2;
    
    double max = MaxElement(deg_motor,num);
    double min = MinElement(deg_motor,num);
    double result = (SumElement(deg_motor,num) - max - min)/(num - 2);
    MainData.Statedata.position_y = result / 6.27;
#endif

#ifndef USE_MOTOR_ENCODER
    double theta =  Inertial.heading() * M_PI / 180;

    double RF = Angle_SensorRF.position(rotationUnits::deg);
    double LF = Angle_SensorLF.position(rotationUnits::deg);

    MainData.Statedata.position_y = -(RF * sin(theta + ANGLE)  - LF * cos(theta + ANGLE)) * 0.0535;
    MainData.Statedata.position_x = -(- RF * cos(theta + ANGLE) - LF * sin(theta + ANGLE)) * 0.0535;
    
#endif
}

void Analyse_Velocity()
{
    int num = 6;
    double velocity_motor[num];
    velocity_motor[0] = Motor_BaseRF.velocity(velocityUnits::pct);
    velocity_motor[1] = Motor_BaseLF.velocity(velocityUnits::pct);
    velocity_motor[2] = Motor_BaseLB1.velocity(velocityUnits::pct);
    velocity_motor[3] = Motor_BaseLB2.velocity(velocityUnits::pct);
    velocity_motor[4] = Motor_BaseRB1.velocity(velocityUnits::pct);
    velocity_motor[5] = Motor_BaseRB2.velocity(velocityUnits::pct);
    double max = MaxElement(velocity_motor,num);
    double min = MinElement(velocity_motor,num);
    double result = (SumElement(velocity_motor,num) - max - min)/(num - 2);
    Chassis_velocity = result;
}

/// @brief ����Ҫ�����е������ǽǶȽ��и���
void Analyse_Inertial()
{
    MainData.Statedata.heading_angle = Inertial.heading(vex::rotationUnits::deg);
    MainData.Statedata.rotation_angle = Inertial.rotation(vex::rotationUnits::deg);
}

/// @brief ��Ҫ������ʾ
void Main_DataShow()
{
    printf("@ position_x: %.3f , position_y:%.3f\n", 
    MainData.Statedata.position_x,
    MainData.Statedata.position_y
    );    
}


/// @brief �ֱ�������ʾ
void Controller_DataShow()
{
    //Controller.Screen.print("volt:%.3f,vel:%d", Motor_BaseLB.voltage(vex::volt), Motor_BaseLB.velocity(vex::rpm));
    printf("volt:%.3f , vel:%.3f\n", Motor_BaseLB1.voltage(vex::volt), Motor_BaseLB2.velocity(vex::rpm));
    //Controller.Screen.newLine();
}
