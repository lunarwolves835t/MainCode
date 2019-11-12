
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
vex::motor MotorFrontRight = vex::motor(vex::PORT10);
vex::motor MotorBackLeft = vex::motor(vex::PORT3);
vex::motor MotorBackRight = vex::motor(vex::PORT4);
vex::motor MotorIntakeArm = vex::motor(vex::PORT1);
vex::motor MotorIntakeLeft = vex::motor(vex::PORT9);
vex::motor MotorIntakeRight = vex::motor(vex::PORT8);
vex::motor MotorRail = vex::motor(vex::PORT5);
 


class Cont{
  public:
  void arms(void){
        //arms
        if (Controller.ButtonDown.pressing()) {
          // MotorIntakeArm.stop(vex::brakeType::brake);
          MotorIntakeArm.spin(vex::directionType::rev,60,velocityUnits::pct);
        }
        else if (Controller.ButtonUp.pressing()) {

          MotorIntakeArm.spin(vex::directionType::fwd,50,velocityUnits::pct); 
        }
        else {
          
          MotorIntakeArm.stop(vex::brakeType::hold);
        }
    
  }
  void hands(void){
        if (Controller.ButtonA.pressing()) {
          MotorIntakeLeft.spin(vex::directionType::fwd,-20,velocityUnits::pct);
          MotorIntakeRight.spin(vex::directionType::fwd,20,velocityUnits::pct);
        }
        else if (Controller.ButtonY.pressing()) {
          MotorIntakeLeft.spin(vex::directionType::fwd,100,velocityUnits::pct);
          MotorIntakeRight.spin(vex::directionType::fwd,-100,velocityUnits::pct);
        }
        else{
          MotorIntakeLeft.stop(vex::brakeType::hold);
          MotorIntakeRight.stop(vex::brakeType::hold);
        }
  }
  void driveBase(void){
    int ratio = 200;
    double speedRight = Controller.Axis1.position(percent)*70 - Controller.Axis3.position(percent)*100;
    speedRight /= ratio;
    MotorFrontRight.spin(directionType::fwd, speedRight, percent);
    MotorBackRight.spin(directionType::fwd, speedRight, percent);
    double speedLeft = Controller.Axis1.position(percent)*70 + Controller.Axis3.position(percent)*100;
    speedLeft /= ratio;
    MotorFrontLeft.spin(directionType::fwd, speedLeft, percent);
    MotorBackLeft.spin(directionType::fwd, speedLeft, percent);
      
  }
  void rails(void){
    //Rail.setMaxTorque(1, percentUnits::pct);
    MotorRail.setMaxTorque(100, percentUnits::pct);
    if(Controller.ButtonX.pressing()){
    MotorRail.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else if(Controller.ButtonB.pressing()){
    MotorRail.spin(directionType::fwd, -100, velocityUnits::pct);
    }
    else{
      MotorRail.stop(coast);
    }
  }
}; 

class Auton{
  public:
  

  //wheel diamter: 4 in 
  void move(double dist){
    const double circum = 4 * 3.1415;
    double revo = dist/circum;
    MotorFrontLeft.rotateFor(revo, rotationUnits::rev, false);
    MotorFrontRight.rotateFor(revo, rotationUnits::rev, false);
    MotorBackLeft.rotateFor(revo, rotationUnits::rev, false);
    MotorBackRight.rotateFor(revo, rotationUnits::rev);
  }

  void turnn(int direc){  //direc = 1 || -1
    const double vel = 50;
    MotorFrontLeft.spin(fwd, vel, velocityUnits::pct);
    MotorFrontRight.spin(fwd, -vel, velocityUnits::pct);
    MotorBackRight.spin(fwd, -vel, velocityUnits::pct);
    MotorBackLeft.spin(fwd, vel, velocityUnits::pct);
  }

  void pickup(int num){
    for(int i = 0; i < num; i++){
      MotorIntakeLeft.spin(fwd, 100, velocityUnits::pct);
      MotorIntakeRight.spin(fwd, 100, velocityUnits::pct);
      move(5.5);
    }
  }

  void instructions(void){
    move(23.5);
    pickup(4);
    turnn(-1);
    move(12);
    turnn(-1);

  }
};

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  bool controll = false;
  Cont cont;
  Auton auton;
  if(controll){
    while (true) {
      cont.hands();
      cont.driveBase();
      cont.rails();
      cont.arms();
    }
  }
  else{
    while(true){
      MotorFrontRight.setVelocity(50, percentUnits::pct);
      MotorFrontLeft.setVelocity(50, percentUnits::pct);
      MotorBackRight.setVelocity(50, percentUnits::pct);
      MotorBackLeft.setVelocity(50, percentUnits::pct);
      auton.instructions();
    }
  }
}
