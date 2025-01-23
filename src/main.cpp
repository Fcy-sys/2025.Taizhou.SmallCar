#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include "_includes.h"

using namespace vex;
using std::endl;
using std::cout;
using std::fstream;


competition Competition;

int main()
{
  vexcodeInit();
// Initializing Robot Configuration. DO NOT REMOVE!
#ifdef TO_AUTO // ����TO_AUTO������Զ�ģʽ
  autonomous_task();
  manual_task();
#endif



#ifndef TO_AUTO
  Competition.autonomous(autonomous_task);
  Competition.drivercontrol(manual_task);
#endif
  while (true)
  {
    // std::cout << MainData.Statedata.position_y << std::endl;                 //�����ǰλ����Ϣ
    // std::cout << Chassis_velocity << std::endl;                 //�����ǰ�ٶ���Ϣ
    // std::cout << "Angle= " << Inertial.rotation()  << std::endl;       //�����ǰ�Ƕ���Ϣ
    //std::cout << "hue= " << Optical.hue() << std::endl;       //�����ǰ�Ƕ���Ϣ
    //std::cout << "Distance = "<<Distance.objectDistance(vex::distanceUnits::mm)<< std::endl;       //�����ǰ�Ƕ���Ϣ
    // std::cout << "Drunk = " << Drunk_rotation.position(deg) << std::endl; //�����ǰ�Ƕ���Ϣ
    // check(Motor_Claw.position(deg));
    // check(Optical.isNearObject());
    Serial_Send(MainData.Statedata.position_y, Chassis_velocity, 0, 0);

    wait(100, msec);
  }


}   