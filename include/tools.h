#ifndef TOOLS_H
#define TOOLS_H
#include "robot-config.h"
int sign(float);

bool Red();                     //Optical��غ���
bool Blue();
void keep_red();
void keep_blue();
void wait_ring();

void Ringin();                  //�����غ���
void Ringout();
void Collect_stop();
void Keep();

void Filtrate();                //������غ���
void CATCH();
void GOT();

void Arm_return();              //��е����غ���������׮��
void Arm_up();
void Arm_down();
void Remove();
void Wall_set();
void Team_set();

void Catch_lamp();              //��β�ƺ���
void Collect_shift();           //�Ĵ����ٺ���

void Thread_FiltrateTask();     //�̺߳���   
void Thread_FiltrateTask_RED();
void Thread_FiltrateTask_BLUE();
void Thread_Keep();
void Thread_Kasi();



#endif