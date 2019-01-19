task main()
{
	displayString(2, "Tuesday, 12:30 pm, Group #13");
	SensorType[S4] = sensorEV3_Ultrasonic;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	int numBlues = 0;
	float largestRed = -1, sizeRed = 0;

	while(!getButtonPress(buttonEnter))
	{}

	while(getButtonPress(buttonEnter))
	{}

	motor[motorA] = motor[motorD] = 25;
	while (SensorValue[S3] == (int)colorWhite)
	{}

	while(SensorValue[S3] != (int)colorWhite)
	{
		motor[motorA] = motor[motorD] = 25;

		if(SensorValue[S3] == (int)colorBlue)
		{
			numBlues++;
			while (SensorValue[S3] == (int)colorBlue)
			{
				if(SensorValue[S4] <30)
				{
					motor[motorA] = motor[motorD] = 10;
				}
				else
				{
					motor[motorA] = motor[motorD] = 25;
				}
			}
		}

		if(SensorValue[S3] == (int)colorRed)
		{
			nMotorEncoder[motorA] = 0;
			while (SensorValue[S3] == (int)colorRed)
			{
				sizeRed = nMotorEncoder[motorA]*2.75*PI/180;
			}
			if (sizeRed > largestRed)
			{
				largestRed = sizeRed;
			}
		}
	}

	motor[motorA] = motor[motorD] = 0;
	displayString(4, "Number of Blues: %d", numBlues);
	displayString(6, "Largest Red: %.2f cm", largestRed);
	wait1Msec(5000);
}
