/*

 OATHonSMS

 Helper methods

 */

#include "global.h"

void trim(char* s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

void *rand_string(char *s, const int len)
{
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
 	int i;
	srand(time(NULL));
    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
 
    s[len] = 0;
}

void *rand_hexstring(char *s, const int len)
{
    static const char alphanum[] = "ABCDEFabcdef0123456789";
 	int i;
	srand(time(NULL));
    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
 
    s[len] = 0;
}

void logDate(){
	char buff[20];
    struct tm *sTm;

    time_t now = time (0);
    sTm = gmtime (&now);

    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    printf ("%s | ", buff);
}

void printHelp()
{
	printf("\n******************************************************* \n");
	printf("HELP\n\n");
	printf("Usage: ./main COMMAND ARGS \n\n");
	printf("Commands: \n");
	printf("- genToken $Number$ $Servername$ \n");
	printf("  Generate a token and display it \n");
	printf("- sendToken $Number$ $Servername$ \n");
	printf("  Generate a token and send it to the number \n");
	//printf("- genSeed \n");
	//printf("  Generates a hex-seed with 20 chars \n");
	printf("- list \n");
	printf("  List all data \n");
	printf("Formats: \n");
	printf("- Number: International Format (e.g 491785569971 ) \n");
	printf("- Servername: Only chars, no whitespace allowed (e.g MAIN ) \n");
	printf("******************************************************* \n");
}
