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

//Global variables and methods here
float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}
int axis2Value = static_cast<int>(clamp(Controller.Axis2.value(), -127, 127));
int axis1Value = static_cast<int>(clamp(Controller.Axis1.value(), -127, 127));
int axis1Ratio = ((axis1Value/127)*100);
int axis2Ratio = ((axis2Value/127)*100);



void mecanum() {
  //up down side side
  MotorFrontLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
  MotorFrontRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
  MotorBackLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
  MotorBackRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
  MotorFrontLeft.spin(vex::directionType::fwd,axis1Ratio,velocityUnits::pct);
  MotorFrontRight.spin(vex::directionType::fwd,-axis1Ratio,velocityUnits::pct);
  MotorBackLeft.spin(vex::directionType::fwd,-axis1Ratio,velocityUnits::pct);
  MotorBackRight.spin(vex::directionType::fwd,axis1Ratio,velocityUnits::pct);
  //diagonal movements
  if ((axis2Value > 0 && axis1Value > 0) || (axis2Value < 0 && axis1Value < 0)) {
    MotorFrontLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
    MotorFrontRight.spin(vex::directionType::fwd,0,velocityUnits::pct);
    MotorBackLeft.spin(vex::directionType::fwd,0,velocityUnits::pct);
    MotorBackRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
  } 
  if ((axis2Value < 0 && axis1Value > 0) || (axis2Value > 0 && axis1Value < 0)) {
    MotorFrontLeft.spin(vex::directionType::fwd,0,velocityUnits::pct);
    MotorFrontRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
    MotorBackLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
    MotorBackRight.spin(vex::directionType::fwd,0,velocityUnits::pct);
  }
  if (axis2Value == 0 && axis1Value == 0) {
    MotorFrontLeft.stop(vex::brakeType::coast);
    MotorFrontRight.stop(vex::brakeType::coast);
    MotorBackLeft.stop(vex::brakeType::coast);
    MotorBackRight.stop(vex::brakeType::coast);
  }  
}

void intake() {

}

void rail() {

}

void autonomous() {
//3.5 rotations

}

void drivercontrol() {
  while (true) {
    mecanum(); 
    intake();
    rail();
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.print(axis2Value);
    Brain.Screen.newLine();
  }
}


