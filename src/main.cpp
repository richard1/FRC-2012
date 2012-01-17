#include "main.h"

MainRobot::MainRobot() {
  constants_ = Constants::GetInstance();
  leftDriveMotors_ = new Victor(constants_->leftMotorPort);
  rightDriveMotors_ = new Victor(constants_->rightMotorPort);
  drivebase_ = new Drive(leftDriveMotors_, rightDriveMotors_);
  leftJoystick_ = new Joystick(constants_->leftJoystickPort);
  rightJoystick_ = new Joystick(constants_->rightJoystickPort);
  controls_ = new ControlBoard(leftJoystick_, rightJoystick_);
}

void MainRobot::TeleopPeriodic() {

}
