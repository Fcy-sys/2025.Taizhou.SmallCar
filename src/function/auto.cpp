#include "_includes.h"
// #define Competition
#define REDSIDE
// #define BLUESIDE
// #define CALIBRATION_ROTATE
// #define CALIBRATION_STRAIGHT
// #define CALIBRATION_DISTANCE

void rotate_test();
void straight_test();
void Competition_route();
void Skill_route();
void IN()
{
    spinning_state = 1;
    Motor_Collect.spin(forward);
    Motor_Get.spin(forward);
}

void OUT()
{
    spinning_state = 2;
    Motor_Collect.spin(reverse);
    Motor_Get.spin(reverse);
}

/// @brief 设置陀螺仪角度
/// @param Heading,Rotation 
void set_angle(int Heading, int Rotation)
{
    Inertial.setHeading(Heading,degrees);
    Inertial.setRotation(Rotation,degrees);
}


// #define FILE_RECORD
// #define DEBUG
int default_time = 1500;
/// @brief 自动模式的任务
void autonomous_task()
{   
    auto_init();
    thread debug(Thread_DataAnalyse);

    #ifdef Competition
    Competition_route();
    #endif

    #ifndef Competition
    Skill_route();
    #endif

    #ifdef CALIBRATION_ROTATE
    rotate_test();
    #endif

    #ifdef CALIBRATION_STRAIGHT
    straight_test();
    #endif

    #ifdef CALIBRATION_DISTANCE
    act.distance(160, 70, 0, 2500);
    #endif   
}

void Competition_route()
{
    thread Kasi(Thread_Kasi);
       #ifdef REDSIDE
    thread Filtrate(Thread_FiltrateTask_BLUE);

    //开始钩桩
    task_hook_flag = 1;
    act.Straight_2(105, 95, 15, 920);//前进钩桩
    task_hook_flag2 = 1;
    act.Straight_2(-60, 55, 15, 1300);//拉桩倒退
    task_hook_flag2 = 0;
    task_Hook();
    task_hook_flag3 = 1;
    act.Rotate(170, 70, 1500);//旋转且收回钩子
    act.Straight_2(-63, 40, 200 , 1300);//反向夹桩
    CATCH();//夹
    act.Rotate(147, 70, 2000);   //160,70,1400
    Ringin();//收
    act.Straight_2(132, 30, 175, 3000);//开始收环

    //开始清理角落环
    int angle_coner = 240;//角落角度
    act.Rotate(angle_coner, 60, 1200);
    act.Straight(80, 35 , angle_coner, 1600);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-40, 25 , angle_coner, 1400);

    //开始挂联队桩
    act.Rotate(90, 50, 1300);
    act.distance(160, 70, 90, 2500);
    act.Rotate(180, 40, 2000);
    act.Straight(45, 40, 180, 1600);
    Motor_Claw.spinTo(-750,deg,true);
    act.Straight(-50, 50, 180, 1100);
    act.Rotate(0, 50, 1100);
    task_claw_flag = 1;
    act.Straight(60, 30, 0, 2000);

    
    printf("DONE\n");
    #endif

    #ifdef BLUESIDE
    wait(10,msec);
    Motor_Hook.spinTo(-700,deg,false);
    Motor_Get.spin(reverse, 40, pct);   
    #endif
}

void Skill_route()
{
    IN();                           //开履带
    keep_red_flag = 1;
    act.Straight_2(85, 72, -90);    //吃第一个环, keep住
    act.Straight(-70, 25, -90);     //去夹桩
    CATCH();                        //夹桩
    thread Kasi(Thread_Kasi);       //若一开始就打开该线程可能会导致第一个环keep不住


    act.Rotate(0);                  //去吃第二个环
    IN();                           //开履带
    act.Straight(60, 60, 0);        //吃中线上的红环
    act.Straight(-37, 40, 0);       //退回，防止碰到联队桩旁边的两个环
    act.Rotate(180);                //掉头，准备吃第三个环
    act.Straight(85, 80, 180);      //直走吃第三个环

    act.Rotate(135);                //转向角落
    act.Straight(50, 60,135);       //吃角落环
    act.Rotate(100, 20);            //转一下，防止吃不到
    act.Straight(30, 80, 90, 350);  //吃掉角落环
    act.Rotate(-47);                //转角度，准备放桩和下一步的角度
    CATCH();                        //放桩

    //————————————————————————————————————————————放下第一个桩，过半场————————————————————————————————————————————//

    act.Straight_2(80, 80, 0, 5000);
    act.Straight(140, 80, 0, 5000);
    act.Rotate(160);
    act.Straight_2(-45, 30, 90);
    CATCH();                        //夹到第二个桩

    act.Rotate(90);
    act.Straight(55, 40, 90);
    act.Straight_2(-47, 68, 0);
    
    act.Straight(85, 40, 0);
    act.Rotate(90);
    act.Straight(65, 90, 90);

    act.Rotate(45);
    act.Straight(70, 60, 45);
    wait(1000,msec);

    act.Straight(-30, 20, 45);

    act.Straight(35, 20, 45);
    act.Rotate(80);
    act.Straight(30, 80, 90, 350);
    act.Rotate(225);
    CATCH();


    wait(2000,sec);


    printf("DONE\n");
}

void straight_test()
{
    CATCH();
    Ringin();
    wait(100,msec);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
}

void rotate_test()
{
    wait(10,msec);
    act.Rotate(90, 60 ,1500);
}

void DebugEnd()
{
    exit(0);
}


