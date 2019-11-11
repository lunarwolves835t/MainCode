// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Arm                  motor         10              
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Rail                 motor         5               
// Arm                  motor         10              
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Rail                 motor         5               
// Arm                  motor         10              
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// BackRight            motor         4               
// Controller1          controller                    
// Rail                 motor         5               
// Arm                  motor         10              
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// BackLeft             motor         3               
// BackRight            motor         4               
// Controller1          controller                    
// Rail                 motor         5               
// Arm                  motor         10              
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         2               
// BackLeft             motor         3               
// BackRight            motor         4               
// Controller1          controller                    
// Rail                 motor         5               
// Arm                  motor         10              
// RightHand            motor         9               
// LeftHand             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\amayb                                            */
/*    Created:      Sat Nov 09 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
 
// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----
 
#include "vex.h"
 
using namespace vex;
 
vex::competition Competition;
vex::controller Controller;
vex::motor MotorFrontLeft = vex::motor(vex::PORT2);
vex::motor MotorFrontRight = vex::motor(vex::PORT1);
vex::motor MotorBackLeft = vex::motor(vex::PORT3);
vex::motor MotorBackRight = vex::motor(vex::PORT4);
vex::motor MotorIntakeArm = vex::motor(vex::PORT10);
vex::motor MotorIntakeLeft = vex::motor(vex::PORT9);
vex::motor MotorIntakeRight = vex::motor(vex::PORT8);
vex::motor MotorRail = vex::motor(vex::PORT5);
 


class Cont{
  public:
  void armHands(void){
        //hands
        if (Controller.ButtonA.pressing()) {
          MotorIntakeLeft.spin(vex::directionType::fwd,-50,velocityUnits::pct);
          MotorIntakeRight.spin(vex::directionType::fwd,50,velocityUnits::pct);
        }
        if (Controller.ButtonY.pressing()) {
          MotorIntakeLeft.spin(vex::directionType::fwd,50,velocityUnits::pct);
          MotorIntakeRight.spin(vex::directionType::fwd,-50,velocityUnits::pct);
        }
        //arms
        if (Controller.ButtonDown.pressing()) {
          MotorIntakeArm.stop(vex::brakeType::hold);
          MotorIntakeArm.spin(vex::directionType::fwd,100,velocityUnits::pct);
        }
        if (Controller.ButtonUp.pressing()) {
          MotorIntakeArm.stop(vex::brakeType::hold);
          MotorIntakeArm.spin(vex::directionType::fwd,-25,velocityUnits::pct); 
        }
        else {
          MotorFrontLeft.stop(vex::brakeType::coast);
          MotorFrontRight.stop(vex::brakeType::coast);
          MotorBackLeft.stop(vex::brakeType::coast);
          MotorBackRight.stop(vex::brakeType::coast);
          MotorIntakeArm.stop(vex::brakeType::hold);
        }
    
  }
  void driveBase(void){
    int ratio = 80;
    double speedRight = Controller.Axis3.position(percent)*70 - Controller.Axis1.position(percent)*100;
    speedRight /= ratio;
    MotorFrontRight.spin(directionType::fwd, speedRight, percent);
    MotorBackRight.spin(directionType::fwd, speedRight, percent);
    double speedLeft = Controller.Axis3.position(percent)*70 + Controller.Axis1.position(percent)*100;
    speedLeft /= ratio;
    MotorFrontLeft.spin(directionType::fwd, speedLeft, percent);
    MotorBackLeft.spin(directionType::fwd, speedLeft, percent);
      
  }
  void rails(void){
    //Rail.setMaxTorque(1, percentUnits::pct);
    if(Controller.ButtonA.pressing()){
    MotorRail.spin(directionType::fwd, 50, velocityUnits::pct);
    }
    if(Controller.ButtonB.pressing()){
    MotorRail.spin(directionType::rev, 500, velocityUnits::pct);
    }
    else{
      MotorRail.stop(coast);
    }
  }
}; 

class Auton{
  public:

  //wheel diamter: 4 in 
  void (void){
    MotorFrontLeft.rotateFor(.47746482982, rotationUnits::rev, 


  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  bool controll = true;
  Cont cont;
  Auton auton;
  if(controll){
    while (true) {
      cont.armHands();
      cont.driveBase();
    }
  }
  else{
    while(true){

    }
  }
}
