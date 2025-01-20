/**
  ******************************************************************************
  * @file           : initialize.cpp
  * @brief          : ��ʼ��Ӳ��,�Լ���Ӳ�����õ���ʼ״̬
  ******************************************************************************
  * @attention      ��
  *
  *
  ******************************************************************************
  */
#include "_includes.h"



/// @brief �ܳ�ʼ��
void vexcodeInit(void){
    serial_init();
    Inertial.calibrate();
    std::cout << "calibrated!" << std::endl;
    while (Inertial.isCalibrating());
    std::cout << "calibrated2!" << std::endl;
    Controller.Screen.print("GO!");

    angle_sensor_init();
    Motor_Get.setStopping(vex::brakeType::coast);
    Motor_Get.setVelocity(85,vex::velocityUnits::pct);
}


/// @brief �Զ�ģʽ��ʼ��
void auto_init(){
    angle_sensor_init();
    inertial_init();
    Motor_BaseL.setStopping(brakeType::brake);    
    Motor_BaseR.setStopping(brakeType::brake);
    Motor_Hook.setStopping(brakeType::hold);
    Motor_Claw.setStopping(brakeType::brake);

    Motor_Collect.setVelocity(90,pct);
    Motor_Get.setVelocity(80,pct);
    Motor_Claw.setVelocity(100,pct);
    Motor_Hook.setVelocity(70,pct);

    Motor_Claw.resetPosition();

   

    std::vector<double> x0 = {0, 0}; // ��ʼ״̬����
    Matrix P0({{1, 0}, {0, 1}}); // ��ʼЭ�������
    KF.initialize(x0,P0);
}

/// @brief �ֶ�ģʽ��ʼ��
void manual_init(){
    angle_sensor_init();
    inertial_init();
    Drunk_rotation.resetPosition();
    Motor_Claw.setPosition(0,deg);
    Motor_Hook.setPosition(0,deg);

    Motor_BaseL.setStopping(brakeType::coast);    
    Motor_BaseR.setStopping(brakeType::coast);
    Motor_Hook.setStopping(brakeType::hold);

    Motor_Collect.setVelocity(80,pct);
    Motor_Get.setVelocity(100,pct);
    Motor_Claw.setVelocity(70,pct);
    Motor_Hook.setVelocity(100,pct);

    Motor_Hook.setStopping(brakeType::hold);
    Motor_Claw.setStopping(brakeType::hold);
} 

/// @brief ��ʼ���Ƕȴ�����
void angle_sensor_init(){
    Motor_BaseL.resetPosition();
    Motor_BaseR.resetPosition();
}

/// @brief ��ʼ��������
void inertial_init()
{
    Inertial.resetRotation();
    Inertial.resetHeading();
}

/// @brief ���ڳ�ʼ��
void serial_init(){
    int BAUDRATE = 19200;
    vexGenericSerialEnable(Serial.index(), 0);
    vexGenericSerialBaudrate(Serial.index(), BAUDRATE);
}