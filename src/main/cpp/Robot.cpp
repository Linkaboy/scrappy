//FIRST Robotics Competition 2020: Team 8023
//Robot Control Software v0.0.0

//RoboRIO docs: https://www.ni.com/pdf/manuals/374474a.pdf

/*ToDO (? - unconfirmed feature or idea):
 * -implement control configuration system
 * -implement launcher speed profile system
 * -implement game-related control stuff
 * -research and plan configuration file loader using a USB flash drive
 * -implement teamwork things, such as deciding on a stable workflow (Updating a changelog, GitHub?)
 * -move all of these comments to a documentation file?
 */

/*Motors:
  * Drive system:
  *  -m 0, 1
  *  -+/-?
  * Intake:
  *  -m 2
  *  -+/-?
  * Launcher
  *  -m 3, 4
  *  -3 speed profiles
  *  -+/-?
  * Hook
  *  -m 5
  *  -moves up and down
  *  -toggle-controlled?
  *  -+/-?
  */

/*Notes:
 * -Loading data from an SD card or USB stick mounted on the chassis would be much faster than trasmitting it through the robot control network
 * -JSON or ini could be a good way to load anonymous control command data
 * -If a motor has to be replaced and it somehow gets reveresed, it may be easier to create and use a polarity configuration for that motor in the control config file
 * -Version formatting: (v)rewrite.featureAdditions.Patches: i.e. v1.2.3 if the software has been rewritten 1 time, had 2 new features added since creation (v0.0.0), and 3 bug
 *    fixes or "patches" since creation
 * -When to update the changelog:
 *    -When a new feature has been fully implemented
 *    -When a bug has been fixed
 * -Maybe we can use ini to load control and motor profile settings and use JSON to "script" timed actions
 * -It may make more sense to tell a robot to drive n inches than it is to tell it to drive for x minutes. Both methods may have to take power supply into account unless
 *    the motor controllers are good at regulating voltage
 * -Apparently aomething called path weaver exists which uses JSON. Probably part of WPILib?
 */

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>

class Robot : public frc::TimedRobot {
 private:
  //Motors and drive
  frc::PWMVictorSPX mA{0}; //drive L, two motors
  frc::PWMVictorSPX mB{1}; //drive R, two motors
  frc::PWMVictorSPX mC{2}; //intake
  frc::PWMVictorSPX mD{3}; //flywheel L
  frc::PWMVictorSPX mE{4}; //flywheel R
  frc::PWMVictorSPX mF{5}; //hook
  frc::DifferentialDrive drive{mA, mB};

  //IO
  frc::Joystick stick{0};
  frc::LiveWindow &lw = *frc::LiveWindow::GetInstance();

  //Misc
  frc::Timer timer;

 public:
  Robot() {
    drive.SetExpiration(0.1);
    timer.Start();
  }

  void AutonomousInit() override {
    timer.Reset();
    timer.Start();
  }

  void AutonomousPeriodic() override {
    //perhaps implement an easily reprogrammable command system here, maybe a state machine? The script can be loaded from a file on a USB stick mounted on the robot
  }

  void TeleopInit() override {
    //init control scheme here. Maybe load the control scheme from a file on a USB stick mounted on the robot?
  }

  void TeleopPeriodic() override {
    //update motors and other components with joystick input data and sensor data
    drive.ArcadeDrive(stick.GetY(), stick.GetZ());
  }

  void TestPeriodic() override {} //dunno what this does
};

#ifndef RUNNING_FRC_TESTS
int main() {return frc::StartRobot<Robot>();}
#endif
