#include "auto/TurnCommand.h"

#include "subsystems/Drive.h"
#include "subsystems/Pid.h"
#include "util/PidTuner.h"

TurnCommand::TurnCommand(Drive* drive, double angle, double timeout) {
  SetTimeout(timeout);
  angle_ = angle;
  drive_ = drive;
  oldAngle_ = 0;
  Constants* constants = Constants::GetInstance();
  turnPid_ = new Pid(&constants->turnKP, &constants->turnKI, &constants->turnKD);
}

void TurnCommand::Initialize() {
  drive_->ResetGyro();
  oldAngle_ = drive_->GetGyroAngle();
  AutoCommand::Initialize();
}

bool TurnCommand::Run() {

  if(timer_->Get() > timeout_) {
    angle_*=-1;
    timer_->Reset();
    Constants* constants = Constants::GetInstance();
    constants->LoadFile();
  }
  
  double curAngle = drive_->GetGyroAngle();
  double power = turnPid_->Update(angle_, curAngle);
  drive_->SetLinearPower(-power, power);
  printf("Curr Angle: %f, Power: %f\n", drive_->GetGyroAngle(), power);
  PidTuner::PushData(angle_, curAngle, power *100);

  /*
  if (curAngle - angle_ < 1.0 && curAngle - oldAngle_ < .1) { // Make this better
    return true;
  }
  oldAngle_ = curAngle;

  return TimeoutExpired();
  */
  return false;
}
