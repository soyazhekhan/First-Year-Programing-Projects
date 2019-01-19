#include "PC_FileIO.c"

void writeRGB(TFileHandle fout, string paper, long redValue, long greenValue, 
long blueValue)
{
	writeTextPC(fout, paper);
	writeCharPC(fout, ' ');
	writeLongPC(fout, redValue);
	writeCharPC(fout, ' ');
	writeLongPC(fout, greenValue);
	writeCharPC(fout, ' ');
	writeLongPC(fout, blueValue);
	writeEndlPC(fout);
}

task main()
{
	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "RGB.txt");
	if(!fileOkay)
	{
		displayString(2, "ERROR!");
		wait1Msec(5000);
	}
	else
	{
		SensorType[S3] = sensorEV3_Color;
		wait1Msec(50);
		SensorMode[S3] = modeEV3Color_Color;
		wait1Msec(50);

		long redValue = 0, greenValue = 0, blueValue = 0;

		getColorRGB(S3, redValue, greenValue, blueValue);
		getColorRGB(S3, redValue, greenValue, blueValue);

		bool done = false;

		while(!done)
		{
			while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight) 
			&& !getButtonPress(buttonEnter))
			{}

			if(getButtonPress(buttonEnter))
			{
				done = true;
			}

			else
			{
				getColorRGB(S3, redValue, greenValue, blueValue);
				string color = "";
				if (getButtonPress(buttonLeft))
				{
					color = "Pink";
					while (getButtonPress(buttonLeft)){}
				}
				else
				{
					color = "Orange";
					while (getButtonPress(buttonRight)){}
				}
				writeRGB(fout, color, redValue, greenValue, blueValue);
			}

			while (getButtonPress(buttonLeft) || getButtonPress(buttonRight) 
			|| getButtonPress(buttonEnter))
			{}
		}
	}
	closeFilePC(fout);
}
