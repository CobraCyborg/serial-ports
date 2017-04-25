#include <stdio.h>
#include <windows.h>

int main(void)
{
	char SerialPort[15] = "";

	for (int i = 0; i < 256; ++i)
	{
		sprintf(SerialPort, "\\\\.\\COM%d", i);
		
		HANDLE Port = CreateFile(
                  SerialPort,
                  GENERIC_READ | GENERIC_WRITE,
                  0,
                  NULL,
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL,
                  NULL);

		if (Port != INVALID_HANDLE_VALUE)
			puts(SerialPort);
	}
	return 0;
}