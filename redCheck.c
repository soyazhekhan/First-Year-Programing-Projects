void waitOnPress();

void gyroReset()
{
	while(getGyroRate(S2) != 0)
	{}
	resetGyro(S2);
}

void rotateRobot(int angle)
{
	gyroReset();
	wait1Msec(50);
	motor[motorA] = 10;
	motor[motorD] = -10;

	while(SensorValue[S2] > -angle)
	{}

	motor[motorA] = motor[motorD] = 0;
}

task main()
{
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);
	SensorType[S2] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Ultrasonic;
	wait1Msec(50);

	displayString(2, "Group 13, Thursday, 11:30");
	waitOnPress();

	motor[motorA] = motor[motorD] = 25;
	while (SensorValue[S3]!= (int)colorRed)
	{}
	motor[motorA] = motor[motorD] = 0;
	rotateRobot(90);

	while(SensorValue[S1] == 0)
	{
		if(SensorValue[S4] < 120)
			rotateRobot(360);
	}
	while(SensorValue[S1] == 1)
	{}
}

void waitOnPress()
{
	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
}
