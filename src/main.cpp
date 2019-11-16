
 
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
  //works: arms, drivebase, rails
  //doesn't work: hands
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
    int ratio = 250; //increase to make drive slower
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
    MotorRail.setMaxTorque(90, percentUnits::pct);
    if(Controller.ButtonX.pressing()){
    MotorRail.spin(directionType::fwd, 30, velocityUnits::pct);
    }
    else if(Controller.ButtonB.pressing()){
    MotorRail.spin(directionType::fwd, -30, velocityUnits::pct);
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
    MotorBackLeft.setVelocity(50, velocityUnits::pct);
    MotorBackRight.setVelocity(50, velocityUnits::pct);
    MotorFrontLeft.setVelocity(50, velocityUnits::pct);
    MotorFrontRight.setVelocity(50, velocityUnits::pct);
    MotorFrontLeft.rotateFor(revo, rotationUnits::rev, false);
    MotorFrontRight.rotateFor(-revo, rotationUnits::rev, false);
    MotorBackLeft.rotateFor(revo, rotationUnits::rev, false);
    MotorBackRight.rotateFor(-revo, rotationUnits::rev);
  }

  void turnn(int direc){  //direc = -1 || 1
    const double vel = 50;
    MotorFrontLeft.spin(fwd, -vel, velocityUnits::pct);
    MotorFrontRight.spin(fwd, -vel, velocityUnits::pct);
    MotorBackRight.spin(fwd, -vel, velocityUnits::pct);
    MotorBackLeft.spin(fwd, -vel, velocityUnits::pct);
    task::sleep(100); //increase this to increase turn
    MotorBackLeft.stop();
    MotorBackRight.stop();
    MotorFrontLeft.stop();
    MotorFrontRight.stop();
  }

  void pickup(int num){
    for(int i = 0; i < num; i++){
      MotorIntakeLeft.spin(fwd, 100, velocityUnits::pct);
      MotorIntakeRight.spin(fwd, -100, velocityUnits::pct);
      task::sleep(500);
      move(5.5);
      MotorIntakeRight.stop();
      MotorIntakeLeft.stop();
    
    
    
    
    }
  }

  void dropoff(int num){
    MotorRail.rotateFor(fwd, .5, rev);
    for(int i = 0; i < num; i++){
      MotorIntakeLeft.spin(fwd, -30, velocityUnits::pct);
      MotorIntakeRight.spin(fwd, 30, velocityUnits::pct);
      task::sleep(500);
      MotorIntakeLeft.stop();
      MotorIntakeRight.stop();
      MotorRail.rotateFor(fwd, -.5, rev);
    }
  }


  void instructions(void){
    move(23.5); //23.5
    pickup(4);
    turnn(-1);
    // move(12);
    // turnn(-1);

  }
};

void autonomous(void){
  Auton auton;
  MotorFrontRight.setVelocity(50, percentUnits::pct);
  MotorFrontLeft.setVelocity(50, percentUnits::pct);
  MotorBackRight.setVelocity(50, percentUnits::pct);
  MotorBackLeft.setVelocity(50, percentUnits::pct);
  auton.instructions();
}

void usercontrol(void){
  Cont cont;
  while(true){
    cont.hands();
    cont.driveBase();
    cont.rails();
    cont.arms();
    vex::task::sleep(20);
  }
}

void pre_auton(){
  MotorIntakeArm.setMaxTorque(100, pct);
  MotorIntakeArm.setVelocity(100, pct);
    MotorIntakeArm.rotateFor(2, rotationUnits::rev);
    
    MotorIntakeArm.rotateFor(-2, rotationUnits::rev);
    MotorIntakeArm.rotateFor(2, rotationUnits::rev);
    
    MotorIntakeArm.rotateFor(-1.65, rotationUnits::rev);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  pre_auton();
  // tell the competition code what to run for the autonomous period
  // while(true){
  //   usercontrol();
  // }
  // autonomous();
  Competition.autonomous( autonomous );
  // tell the competition code what to run for the driver control period
  Competition.drivercontrol( usercontrol );
  
  //Prevent main from exiting with an infinite loop.
  while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }
}
