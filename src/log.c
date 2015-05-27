#include "global.h"

#define LOGFILE	"gl.log"     // all Log(); messages will be appended to this file
 
void LogErr (char *message); // logs a message; execution is interrupted

int LogCreated = 0;
 
void Log (char *message)
{
	FILE *file;
 
	if (LogCreated == 0) {
		file = fopen(LOGFILE, "w");
		LogCreated = 1;
	}
	else		
		file = fopen(LOGFILE, "a");
		
	if (file == NULL) {
		if (LogCreated == 1)
			LogCreated = 0;
		return;
	}
	else
	{
		fputs(message, file);
		fclose(file);
	}
 
	if (file)
		fclose(file);
}
