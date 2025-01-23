#include "_includes.h"

//������������������������������������������������������������������ֹ��ܺ�����������������������������������������������������������������������������������������������������������//

int sign(float x) {                              //���ź�����ȡ�����ķ���
    return x < 0 ? -1 : x == 0 ? 0 : 1;
}

bool Red()                                      //������ɫ����true
{
   vis.takeSnapshot(redRing);
   int objectArea=vis.largestObject.height*vis.largestObject.width;//��ȡ���Ŀ�����
   if(vis.largestObject.exists&& objectArea >2000 )
     return true;
   else 
     return false;
}

bool Blue()                                     //������ɫ����true
{
   vis.takeSnapshot(blueRing);
   int objectArea=vis.largestObject.height*vis.largestObject.width;//��ȡ���Ŀ�����
   if(vis.largestObject.exists&& objectArea >2000 )
     return true;
   else 
     return false;
}

//��������������������������������������������������Ҫ��¼���ݵı����������־λ�ȡ�������������������������������������������//
int spinning_state = 0;     //�׻��Ĵ����ռ����ֵ�״̬��0��ֹͣ��1����ת��2�Ƿ�ת
bool catch_flag = 0;        //��׮���׼����־λ
bool hand_flag = 0;         //ǰ�칳�����׼����־λ
bool shift = 1;             //�Ĵ����ٱ�־λ
bool keep_flag = 0;         //�Ĵ�ͣ����־λ      
bool light1_state = 0;      //����1��־λ

void Keep()
{
    if(keep_flag)
    {
        keep_flag = 0;
    }
    else if(!keep_flag)
    {
        keep_flag = 1;
    }
}

void Ringin()
{   
   if(spinning_state == 0 || spinning_state == 2)
     {
        Motor_Get.spin(forward);
        Motor_Collect.spin(forward);
        spinning_state = 1;
     }
    else if(spinning_state == 1)
    {
        Motor_Get.stop();
        Motor_Collect.stop();
        spinning_state = 0;
    }
}

void Ringout()
{
    if(spinning_state == 0 || spinning_state == 1)
     {
        Motor_Get.spin(reverse,40,pct);
        Motor_Collect.spin(reverse,40,pct);
        spinning_state = 2;
     }
    else if(spinning_state == 2)
    {
        Motor_Get.stop();
        Motor_Collect.stop();
        spinning_state = 0;
    }
} 

void Collect_stop()
{
    Motor_Collect.stop();
    spinning_state = 0;
}

void GOT() //���¹��ӹ�׮
{
    if(hand_flag)
    {
        Motor_Hook.spinTo(0, deg, false);
        hand_flag = 0;
    }
    else if(!hand_flag)
    {
        Motor_Hook.spinTo(-280, deg, false);
        hand_flag = 1;
    }
}

void CATCH() {
    if(catch_flag)
    {
        Catch.set(false);
        catch_flag = 0;
    }
    else if(!catch_flag)
    {
        Catch.set(true);
        catch_flag = 1;
    }
}

void wait_ring()
{
    chassis.Move_free(15,0);
    chassis.Move();
    for(int i = 0; i < 260; i++)
    {
       if(Red()||Blue())
       {
           break;
       }
       wait(10,msec);
    }
    chassis.Stop_brake();
}

void keep_red()
{
    for(int i = 0; i < 300; i++)
    {
        if(Red())
        {
            Collect_stop();
            break;
        }
        wait(10,msec);
    }
}

void keep_blue()
{
   for(int i = 0; i < 300; i++)
    {
        if(Blue())
        {
            Collect_stop();
            break;
        }
        wait(10,msec);
    } 
}

void Catch_lamp()
{  
        if(catch_flag )
        {
            load.set(true);
            light1_state = 1;
        }
        else if(!catch_flag )
        {
            load.set(false);
            light1_state = 0;
        }
    
  
}

void Filtrate()
{   
        Optical.setLightPower(50,percent);
        Optical.setLight(ledState::on);
        if (Blue())
        {
           filtrate.set(false);
           wait(200,msec);
           
        }
        if(Red())
        {
            filtrate.set(true);
            wait(250,msec);
            filtrate.set(false);
        }
}

void Filtrate2()
{
    int objectArea=vis.largestObject.height*vis.largestObject.width;//��ȡ���Ŀ�����
    // std::cout<<objectArea<<std::endl;
    if(vis.largestObject.exists&&objectArea > 7000)
    {
        std::cout<<"Done"<<std::endl;
        filtrate.set(true);
        wait(350,msec);
        filtrate.set(false);
    }
}

void Filtrate3()
{
    int objectArea=vis.largestObject.height*vis.largestObject.width;//��ȡ���Ŀ�����
    // std::cout<<objectArea<<std::endl;
    if(vis.largestObject.exists&&objectArea > 2000)
    {
        std::cout<<"Done"<<std::endl;
        filtrate.set(true);
        wait(420,msec);
        filtrate.set(false);
    }
}

void Wall_set()
{
    Motor_Claw.spinTo(1290, deg, false);
    for(int i = 0; i < 150; i++)
    {
        
            float degree = Motor_Claw.position(deg)/5 + 180;
            act.Drunk(degree*2);
        
        wait(10,msec);
    }
    Motor_Hook.stop();
}

void Team_set()
{
    Motor_Claw.spinTo(600, deg, false);
    for(int i = 0; i < 200; i++)
    {
        if(300 <= Motor_Claw.position(deg) && Motor_Claw.position(deg) <= 600)
        {
            float degree = Motor_Claw.position(deg)/5 + 300;
            act.Drunk(degree);
        }
        wait(10,msec);
    }
    Motor_Hook.stop();
}

void Arm_return()
{
   Motor_Claw.spinTo(10,deg, false);
   Motor_Hook.spinTo(-30,deg, false);
}

void Arm_up()
{
    Motor_Claw.spin(forward);
   if(Motor_Claw.position(deg) >= 800)
    {
        float degree = Motor_Claw.position(deg)/5 + 180;
        act.Drunk(degree*2);
    }
    else if((400 <= Motor_Claw.position(deg)) && (Motor_Claw.position(deg) <= 800))
    {
        float degree = Motor_Claw.position(deg)/5+300;
        act.Drunk(degree*2);
    }
    if(Motor_Claw.position(deg) <= 400)
    {
        Motor_Hook.spinTo(0, deg,false);
    }
}
void Arm_down()
{
    
    if(Motor_Claw.position(deg) >= 800)
    {
        Motor_Claw.spin(reverse);
        float degree = Motor_Claw.position(deg)/5 + 230;
        act.Drunk(degree*2);
    }
    else if((400 <= Motor_Claw.position(deg)) && (Motor_Claw.position(deg) <= 800))
    {
        Motor_Claw.spin(reverse);
        float degree = Motor_Claw.position(deg)/5+300 ;
        act.Drunk(degree*2);
    }
    if(Motor_Claw.position(deg) <= 500&&Motor_Claw.position(deg) >= 10)
    {
        Motor_Claw.spin(reverse);
        Motor_Hook.spinTo(0, deg,false);
    }
    else if(Motor_Claw.position(deg) <= 10)
    {
       Motor_Claw.spinTo(-10, deg);
       Motor_Hook.spin(reverse,80,pct);
       Motor_Hook.setPosition(-30,deg);
       Motor_Claw.setPosition(0,deg);
    }
}

void Remove()
{
    Motor_Claw.spinTo(1300,deg,false);
    Motor_Hook.spinTo(500,deg,true);
    wait(500,msec);
    Motor_Claw.spinTo(1290, deg, false);
    for(int i = 0; i < 100; i++)
    {
        
            float degree = Motor_Claw.position(deg)/5 + 150;
            act.Drunk(degree*2);
        
        wait(10,msec);
    }
    Motor_Hook.stop();
}

void Collect_shift()
{
    if(shift == 1)
    {
        Motor_Collect.setVelocity(25,pct);
        shift = 0;
    }
    else if(shift == 0)
    {
        Motor_Collect.setVelocity(100,pct);
        Ringout();
        Ringout();
        shift = 1;
    }
}


void Thread_FiltrateTask()
{
    Optical.objectDetectThreshold(90);
    while (true)
    {
        Filtrate();
        this_thread::sleep_for(10);
    }
}

void Thread_FiltrateTask_RED()
{
    while (true)
    {
        vis.takeSnapshot(redRing);
        Filtrate2();
        this_thread::sleep_for(10);
    }
}

void Thread_FiltrateTask_BLUE()
{
   
    while (true)
    {
        vis.takeSnapshot(blueRing);
        Filtrate3();
        this_thread::sleep_for(10);
    }
}

void Thread_ControllerTask()
{
    while (true)
    {
        controller_task();
        this_thread::sleep_for(10);
    }
}

void Thread_Kasi()
{
    while(true)
    {
        if (spinning_state == 1 )
        {
            if(Motor_Collect.velocity(pct) < 2)

               {
                    wait(1000, msec);
                    if(Motor_Collect.velocity(pct) < 2)
                    {Motor_Collect.spin(reverse, 100, pct);
                    wait(200,msec);
                    Motor_Collect.spin(forward, 100, pct);
                    wait(200,msec);}
                }
        }
        this_thread::sleep_for(10);

    }
}

void Thread_Keep()
{
    while(true)
    {
        if(keep_flag)
        {
            keep_blue();
            keep_flag = 0;
        }
        this_thread::sleep_for(10);
    }
    
}

// void Thread_CatchTask()
// {
//     while (true)
//     {
//         CATCH();
//         this_thread::sleep_for(10);
//     }
// }

