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
/*
  while (true) {
    if (axis2Ratio == true) {
      MotorFrontLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
      MotorFrontRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
      MotorBackLeft.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
      MotorBackRight.spin(vex::directionType::fwd,axis2Ratio,velocityUnits::pct);
    }
    else if (axis1Ratio == true) {
      MotorFrontLeft.spin(vex::directionType::fwd,-axis1Ratio,velocityUnits::pct);
      MotorFrontRight.spin(vex::directionType::fwd,axis1Ratio,velocityUnits::pct);
      MotorBackLeft.spin(vex::directionType::fwd,axis1Ratio,velocityUnits::pct);
      MotorBackRight.spin(vex::directionType::fwd,-axis1Ratio,velocityUnits::pct);
    }
 
  }
  */
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);
  // test things here
  Brain.Screen.print(Controller.Axis1.value());
}