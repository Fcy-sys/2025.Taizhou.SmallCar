/**
  ******************************************************************************
  * @file           : include.h
  * @brief          : ����ͷ�ļ��ļ��ϣ��󲿷ֲ���������������
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INCLUDES_H
#define __INCLUDES_H

/* �ڲ����� ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <cassert>
#include <vector>
#include "v5.h"
#include "v5_vcs.h"
/* �û����� ------------------------------------------------------------------*/
#include "auto.h"
#include "manual.h"
#include "chassis.h"
#include "controller.h"
#include "user-math.h"
#include "PID.h"
#include "PIDProcess.h"
#include "robot-config.h"
#include "tools.h"
#include "initialize.h"
#include "KalmanFilter.h"
#include "Matrix.h"
#include "EncodingDisk.h"
#include "Speedcontrol.h"
#include "serial.h"

// Add missing includess
#include <stddef.h>

/* ���Ʋ���   ---------------------------------------------------------------------------*/
#define USE_MOTOR_ENCODER             //����˴������õ���Դ����������������ýǶȴ�����
// #define CASE_1
 #define CASE_2                     //ѡ�����
/* �궨��   ------------------------------------------------------------------*/


/* �ṹ����   ------------------------------------------------------------------*/


typedef struct MotionData{
 double position_x;                          //xλ��
 double position_y;                          //yλ��
 double heading_angle;                           //���������(0~360)
 double rotation_angle;                      //������ת�ǣ�-�� ~~ +�ޣ�
 double current_forward;                     //�Ƕȴ����������������ĵ�ǰ�Ƕ�
 MotionData():position_x(0.0),position_y(0.0),heading_angle(0.0),rotation_angle(0.0),current_forward(0.0){};
}MotionData;

typedef struct MainDataSTR{
  MotionData Statedata;                     //��ų�����λ����̬��Ϣ
}MainDataSTR;

/* ȫ�ֱ�������   ------------------------------------------------------------------*/
 
extern SpeedControlMode SpeedControlConfig;              //�ٶȿ���ģʽ
extern MainDataSTR MainData;                             //�����Ҫ����
extern KalmanFilter KF;                                  //�������˲���
extern const int DefaultMaxTimeMsec;                     //PIDĬ���������ʱ��
extern double ANGLE;                                     //ȫ���ƶ������ã�����ϵƫת��
extern float Chassis_velocity;                           //�����ٶ�

/* ����ȫ�ֽӿ�����   ------------------------------------------------------------------*/

void DataAnalyse();                                       //���ݷ�������
void check(float _delta);                                 //�鿴�������ݺ����������ն˲鿴����
void Thread_DataAnalyse();

#endif