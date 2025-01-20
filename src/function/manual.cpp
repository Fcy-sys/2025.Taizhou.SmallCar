/**
  ******************************************************************************
  * @file           : manual.cpp
  * @brief          : �ֶ�ģʽ
  ******************************************************************************
  * @attention      ��
  *
  *
  ******************************************************************************
  */

#include "_includes.h"

void manual_init();

void manual_task()          //�ֶ�ģʽ����
{
    manual_init();
    thread controller_thread = thread(Thread_ControllerTask);//����һ��My_Controller�߳�
    thread keep_thread = thread(Thread_Keep); 
    thread analyse_thread = thread(Thread_DataAnalyse);//����һ��My_Chassis�߳�
    thread chassis_thread = thread(Thread_ChassisTask);//����һ��My_Chassis�߳�
    thread filtrate = thread(Thread_FiltrateTask_BLUE);
    while (true)
    {
        chassis_task();
        this_thread::sleep_for(10);
    }
}

