/**
  ******************************************************************************
  * @file           : robot-config.cpp
  * @brief          : ���û����˵�Ӳ���豸
  ******************************************************************************
  * @attention      ��
  *
  *
  ******************************************************************************
  */

#include "_includes.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;                  //����Brain
Chassis chassis;              //����chassis
Act act;                      //�����Զ�����act��action��
Speedcontrol speedcontrol;    //��������ʽpid�����ٶ�
PID pid_speed;                //�ٶȻ�pid������
PID pid_position;             //λ�û�pid������
PID pid_rotate;               //��תpid������
PID pid_pose;                 //��̬����pid������
PID pid_drunk;                //��е�۶������pid������
PID pid;                      //���ڵ���pid����

motor Serial = motor(PORT20, ratio18_1, false);               //����

// VEXcode device constructors
digital_out Catch = digital_out(Brain.ThreeWirePort.C);       //չ��
digital_out filtrate = digital_out(Brain.ThreeWirePort.A);    //ɸѡ
digital_out load = digital_out(Brain.ThreeWirePort.D);        //��β��
digital_out hand = digital_out(Brain.ThreeWirePort.E);        //��δ���ϣ�ǰ�칳��


inertial Inertial = inertial(PORT17);                          //������

vision::signature redRing = vision::signature(2, 7801, 10473, 9137, -1365, -815, -1090, 2.1, 0);
vision::signature blueRing = vision::signature (1, -4831, -3993, -4412, 3775, 5313, 4544, 2.2, 0);
vision vis = vision(PORT3, 50, redRing, blueRing);                      //�Ӿ�ʶ��

distance Distance = distance(PORT5);                         //������

optical Optical = optical(PORT11);                             //��ѧ������
rotation Drunk_rotation = rotation(PORT5, false);             //������

motor Motor_Get = motor(PORT1, ratio18_1, true);            //�ռ�����
motor Motor_Claw = motor(PORT21, ratio18_1, true);            //����׮צ��

motor Motor_Collect = motor(PORT16, ratio18_1, false);        //�׻��Ĵ�
motor Motor_Hook = motor(PORT8, ratio18_1, false);          //��׮�ṹ

motor Motor_BaseRF = motor(PORT10, ratio18_1, false);           //�����ֵ��
motor Motor_BaseRB1 = motor(PORT19, ratio18_1, true);
motor Motor_BaseRB2 = motor(PORT18, ratio18_1, false);

motor Motor_BaseLF = motor(PORT15, ratio18_1, true);            //�����ֵ��
motor Motor_BaseLB1 = motor(PORT12, ratio18_1, false);
motor Motor_BaseLB2 = motor(PORT13, ratio18_1, true);

motor_group Motor_BaseL(Motor_BaseLF, Motor_BaseLB1, Motor_BaseLB2);//����������
motor_group Motor_BaseR(Motor_BaseRF, Motor_BaseRB1, Motor_BaseRB2);//����������
      

controller Controller = controller(primary);                    //ң������

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

