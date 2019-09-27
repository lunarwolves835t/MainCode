/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\yashk                                            */
/*    Created:      Sun Sep 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;
//Necessary delcarations here
vex::brain Brain;
vex::competition Competition;
vex::controller Controller;
vex::motor MotorFrontLeft = vex::motor(vex::PORT1);
vex::motor MotorFrontRight = vex::motor(vex::PORT2);
vex::motor MotorBackLeft = vex::motor(vex::PORT3);
vex::motor MotorBackRight = vex::motor(vex::PORT4);
//Global variables here
int axis1Ratio = ((Controller.Axis1.value()/127)*100);
int axis2Ratio = ((Controller.Axis2.value()/127)*100);
int axis3Ratio = ((Controller.Axis3.value()/127)*100);
int axis4Ratio = ((Controller.Axis4.value()/127)*100);



// All real code here
void autonomous() {

}

void drivercontrol() {
// mecanum drive

  while (true) {

  axis1Ratio = ((Controller.Axis1.value()/127)*100);
  axis2Ratio = ((Controller.Axis2.value()/127)*100);
  axis3Ratio = ((Controller.Axis3.value()/127)*100);
  axis4Ratio = ((Controller.Axis4.value()/127)*100);

    
      MotorFrontLeft.spin(vex::directionType::fwd,axis1Ratio,velocityUnits::pct);
      MotorFrontRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
      MotorBackLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
      MotorBackRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
      if (Controller.Axis1.value() == 0) {
      MotorFrontLeft.stop();
      MotorFrontRight.stop();
      MotorBackLeft.stop();
      MotorBackRight.stop();
      }
    

 
  }

}

float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);
  // test things here
  while(true){
    int Axis1N = static_cast<int>(clamp(Controller.Axis1.value(), -127, 127));

    Brain.Screen.clearScreen();
    Brain.Screen.print(Axis1N);
    Brain.Screen.newLine();
  }
}