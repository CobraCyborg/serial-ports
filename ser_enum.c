#include <stdio.h>
#include <windows.h>

int main(void)
{
	char portname[15] = "";

	for (int i = 0; i < 256; ++i)
	{
		sprintf(portname, "\\\\.\\COM%d", i);
		//puts(portname);
		HANDLE Port = CreateFile(
                  portname,
                  GENERIC_READ | GENERIC_WRITE,
                  0,
                  NULL,
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL,
                  NULL);
		if (Port != INVALID_HANDLE_VALUE)
			puts(portname);
	}
	return 0;
}