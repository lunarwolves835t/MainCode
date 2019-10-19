using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackLeft;
extern motor BackRight;
extern motor UpArms;
extern motor RightArm;
extern motor LeftArm;
extern motor Rails;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );