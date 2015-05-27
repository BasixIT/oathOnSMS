#include "global.h"

#define FILENAME "config.cfg"
#define MAXBUF 1024
#define DELIM "="

struct config
{
   char dbserver[MAXBUF];
   char dbuser[MAXBUF];
   char dbpassword[MAXBUF];
   char dbname[MAXBUF];
   char smsoutpath[MAXBUF];
};

struct config get_config(char *filename)
{
    struct config configstruct;
    FILE *file = fopen (filename, "r");

    if (file != NULL)
    {
        char line[MAXBUF];
        int i = 0;

        while(fgets(line, sizeof(line), file) != NULL)
        {
            char *cfline;
            cfline = strstr((char *)line,DELIM);
            cfline = cfline + strlen(DELIM);

            if (i == 0)
			{
                memcpy(configstruct.dbserver,cfline,strlen(cfline));
				trim(configstruct.dbserver);
			}
            else if (i == 1)
			{
                memcpy(configstruct.dbuser,cfline,strlen(cfline));
				trim(configstruct.dbuser);
			}
            else if (i == 2)
			{
                memcpy(configstruct.dbpassword,cfline,strlen(cfline));
				trim(configstruct.dbpassword);
			}
            else if (i == 3)
			{
                memcpy(configstruct.dbname,cfline,strlen(cfline));
				trim(configstruct.dbname);
			}
            else if (i == 4)
			{
            	memcpy(configstruct.smsoutpath,cfline,strlen(cfline));
				trim(configstruct.smsoutpath);
			}
          
            i++;
        } // End while
    } // End if file
   
    fclose(file);   
   
    return configstruct;
}
