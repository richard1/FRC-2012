/**
 * @author Eric Caldwell
 *
 * This file is read by Constants and contains the variables and default values that will be stored as member
 * variables in Constants. Use it by including it in the macro definition of the functions used below.
 */

// Motors
// NOTE(patrick): PWMs 1 and 10 currently unused.
DECLARE_DOUBLE(leftDrivePwmA, 5)
DECLARE_DOUBLE(leftDrivePwmB, 4)
DECLARE_DOUBLE(rightDrivePwmA, 6)
DECLARE_DOUBLE(rightDrivePwmB, 7)
DECLARE_DOUBLE(intakePwm, 2)
DECLARE_DOUBLE(conveyorPwm, 9)
DECLARE_DOUBLE(leftShooterPwm, 3)
DECLARE_DOUBLE(rightShooterPwm, 8)
DECLARE_DOUBLE(jumblePwm, 10)

// Analog Sensors
DECLARE_DOUBLE(gyroPort, 2)
DECLARE_DOUBLE(accelerometerXPort, 5)
DECLARE_DOUBLE(accelerometerYPort, 6)
DECLARE_DOUBLE(accelerometerZPort, 7)
DECLARE_DOUBLE(poofMeterPort, 3)
DECLARE_DOUBLE(ballRangerPort, 1)

// Digital Sensors
DECLARE_DOUBLE(bumpSensorPort, 1)
DECLARE_DOUBLE(leftEncoderPortA, 2)
DECLARE_DOUBLE(leftEncoderPortB, 3)
DECLARE_DOUBLE(rightEncoderPortA, 4)
DECLARE_DOUBLE(rightEncoderPortB, 5)
DECLARE_DOUBLE(shooterEncoderPortA, 6)
DECLARE_DOUBLE(shooterEncoderPortB, 7)
DECLARE_DOUBLE(conveyorEncoderPortA, 8)
DECLARE_DOUBLE(conveyorEncoderPortB, 9)
DECLARE_DOUBLE(conveyorBallSensorPort, 11)

// Pneumatics
DECLARE_DOUBLE(compressorPressureSwitchPort, 14)
DECLARE_DOUBLE(compressorRelayPort, 8)
DECLARE_DOUBLE(pizzaWheelSolenoidUpPort, 1)
DECLARE_DOUBLE(pizzaWheelSolenoidDownPort, 4)
DECLARE_DOUBLE(hoodSolenoidPort, 6)
DECLARE_DOUBLE(intakeSolenoidUpPort, 5)
DECLARE_DOUBLE(intakeSolenoidDownPort, 7)
DECLARE_DOUBLE(brakeSolenoidOnPort, 2)
DECLARE_DOUBLE(brakeSolenoidOffPort, 3)
DECLARE_DOUBLE(shiftSolenoidPort, 8)

// Vision
DECLARE_DOUBLE(thresholdRMin, 0)
DECLARE_DOUBLE(thresholdRMax, 50)
DECLARE_DOUBLE(thresholdGMin, 0)
DECLARE_DOUBLE(thresholdGMax, 50)
DECLARE_DOUBLE(thresholdBMin, 80)
DECLARE_DOUBLE(thresholdBMax, 255)

// Driver controls
DECLARE_DOUBLE(leftJoystickPort, 1)
DECLARE_DOUBLE(rightJoystickPort, 2)
DECLARE_DOUBLE(baseLockPort, 1)
DECLARE_DOUBLE(fineControlLeftPort, 6)
DECLARE_DOUBLE(fineControlRightPort, 7)
DECLARE_DOUBLE(intakeDeployPort, 8)

// Operator controls
DECLARE_DOUBLE(operatorControlPort, 3)
DECLARE_DOUBLE(conveyorUpPort, 3)
DECLARE_DOUBLE(conveyorDownPort, 4)
DECLARE_DOUBLE(conveyorIndexPort, 5)
DECLARE_DOUBLE(presetFenderPort, 9)
DECLARE_DOUBLE(presetKeyPort, 10)
DECLARE_DOUBLE(presetBridgePort, 11)
DECLARE_DOUBLE(presetHalfCourtPort, 12)
DECLARE_DOUBLE(presetMaxPort, 13)
DECLARE_DOUBLE(shooterPort, 14)
DECLARE_DOUBLE(hoodIncrementPort, 15)
DECLARE_DOUBLE(hoodDecrementPort, 16)
DECLARE_DOUBLE(manualOverridePort, 18)
DECLARE_DOUBLE(bridgeLowererPort, 19)
DECLARE_DOUBLE(highGearPort, 2);
DECLARE_DOUBLE(quickTurnPort, 4);
DECLARE_DOUBLE(pizzaSwitchPort, 2);

// Linearization
DECLARE_DOUBLE(linearCoeffA, 4.5504)
DECLARE_DOUBLE(linearCoeffB, -5.9762)
DECLARE_DOUBLE(linearCoeffC, 2.5895)
DECLARE_DOUBLE(linearCoeffD, -0.0869)
DECLARE_DOUBLE(linearCoeffE, 0.0913)
DECLARE_DOUBLE(shooterCoeffA, 4.7658)
DECLARE_DOUBLE(shooterCoeffB, -5.8827)
DECLARE_DOUBLE(shooterCoeffC, 1.8275)
DECLARE_DOUBLE(shooterCoeffD, 0.2894)
DECLARE_DOUBLE(conveyorCoeffA, 0.5021)
DECLARE_DOUBLE(conveyorCoeffB, 0.16)
DECLARE_DOUBLE(conveyorCoeffC, 0.3228)
DECLARE_DOUBLE(conveyorCoeffD, 1.1347)

// Drive tuning
DECLARE_DOUBLE(turnSensLow, 1.1)
DECLARE_DOUBLE(turnSensHigh, 1.4)

// PID constants
DECLARE_DOUBLE(driveKP, 1.2)
DECLARE_DOUBLE(driveKI, 0.003)
DECLARE_DOUBLE(driveKD, 8)
DECLARE_DOUBLE(baseLockKP, 1.5)
DECLARE_DOUBLE(baseLockKI, 0.01)
DECLARE_DOUBLE(baseLockKD, 0)
DECLARE_DOUBLE(shooterKP, 0.1)
DECLARE_DOUBLE(shooterKI, 0.3)
DECLARE_DOUBLE(shooterKD, -0.15)
DECLARE_DOUBLE(conveyorKP, 0.002)
DECLARE_DOUBLE(conveyorKI, 0.00000006)
DECLARE_DOUBLE(conveyorKD, 0.005)

// Shooter constants
DECLARE_DOUBLE(minConveyorBallDist, 700)
DECLARE_DOUBLE(conveyorPIDThreshold, 50)
DECLARE_DOUBLE(conveyorHeight, 1440)
DECLARE_DOUBLE(conveyorPIDIncrement, 10)
DECLARE_DOUBLE(conveyorPoofWindowLow, 230)
DECLARE_DOUBLE(conveyorPoofWindowHigh, 580)

// Poofometer calibration
DECLARE_DOUBLE(poofometerLowPoofiness, 400)
DECLARE_DOUBLE(poofometerLowCorrection, 1.1)
DECLARE_DOUBLE(poofometerHighPoofiness, 500)
DECLARE_DOUBLE(poofometerHighCorrection, 1.0)
