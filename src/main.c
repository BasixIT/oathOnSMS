/*

 OATHonSMS

 connects liboath.0 with smsd to send out your tokens via sms.

 Description: includes the main(...) function and essential methods

 */

#include "global.h"
#include "mysql.h"
#include "helper.c"
#include "log.c"

char* generateToken(char *mobileNumber, char *serverName);
int sendToken(char *mobileNumber, char *serverName);
void listSeeds();
void addSeed();
void generateSeed();
int createSMS();

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

struct config configuration;

void main(int argc, char *argv[]) {

	// Read from config file, see config.c
	configuration = get_config(FILENAME);

	char* command = argv[1];

	if (strcmp(command,"genToken") == 0){
		char* temp = "";
		if (argc == 4)
		{
			temp = generateToken(argv[2],argv[3]);
			if (strlen(temp) != 0)
			{
				printf("Token: %s \n", temp);
			}
			else
			{
				printf("No seed found \n");
			}
		}
		else
			printf("Argumentcount invalid \n");
	}
	else if (strcmp(command,"sendToken") == 0){
		int val;
		if (argc == 4)
		{
			val = sendToken(argv[2],argv[3]);
			if (val == 1)
			{
				printf("Token send \n");
			}
			else
				printf("Token could not be send \n");
		}
		else
			printf("Argumentcount invalid \n");
	}
	else if (strcmp(command,"list") == 0){
		listSeeds();
	}
	/*else if (strcmp(command,"genSeed") == 0){
		generateSeed();
	}*/
	else if (strcmp(command,"help") == 0){
		printHelp();
	}
	else{
		printf("ERROR: Unkown command \n\n");
		printHelp();
	}


}

int sendToken(char* mobileNumber, char* serverName){
	char* token = "";
	token = generateToken(mobileNumber, serverName);

	if (strlen(token) != 6)
		return -1;

	char header[60] = "To: ";
	strcat(header, mobileNumber);
	strcat(header, "\nFlash: yes\nAlphabet: ISO\nPriority: High\n\n");

	char text[140] = "Your token for \'";
	strcat(text, serverName);
	strcat(text, "\' is ");
	strcat(text, token);

	char sms[200] = "";
	strcat(sms, header);
	strcat(sms, text);
	
	int create;
	create = createSMS(sms);
	
	return 1;
}

int createSMS(char* content){
	char path[80] = "";

	char *filenamePtr;

	rand_string(filenamePtr, 10);

	strcat(path, configuration.smsoutpath);
	strcat(path, filenamePtr);

	FILE *fp;
	fp = fopen(path, "w+");
	fputs(content, fp);
	fclose(fp);

	return 1;
}

void generateSeed(){
	char *filenamePtr;
	//rand_hexstring(filenamePtr, 20);
	//printf("%p \n", filenamePtr);
}

char* generateToken(char* mobileNumber, char* serverName) {
    printf("Checking if seed exists for %s and server %s \n",mobileNumber,serverName);

	char query[100] = "";
	strcat(query, "SELECT seed FROM oath_users WHERE number = '");
	strcat(query, mobileNumber);
	strcat(query, "' and server = '");
	strcat(query, serverName);
	strcat(query, "'");

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, configuration.dbserver, configuration.dbuser, configuration.dbpassword, configuration.dbname, 0, NULL,
			0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	/* send SQL query */
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);

	char seed[50] = "";
	while ((row = mysql_fetch_row(res)) != NULL)
		strcat(seed,row[0]);
	
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);

	if (strlen(seed) != 0)
	{
		char call[20] = "oathtool --totp ";
		strcat(call, seed);

        FILE *pipein_fp;
        char readbuf[80];

        /* Create one way pipe line with call to popen() */
        if (( pipein_fp = popen(call, "r")) == NULL)
        {
                perror("popen");
                exit(1);
        }

 		char* token = "";

        /* Processing loop */
        while(fgets(readbuf, 80, pipein_fp))
		{
			if (strlen(readbuf) != 0)
				token = readbuf;
		}

        /* Close the pipes */
        pclose(pipein_fp);
		trim(token);

		return token;
	}
	return "";
}


void listSeeds() {
	char *query = "SELECT * FROM oath_users";

	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, configuration.dbserver, configuration.dbuser, configuration.dbpassword, configuration.dbname, 0, NULL,
			0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	/* send SQL query */
	if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);
	/* output table name */
	printf("OATH Users in database:\n");
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s | %s | %s | %s | %s | %s \n", row[0], row[1], row[2], row[3], row[4], row[5]);
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
}

// WIP
void addSeed() {
	printf("Please enter user's data (* means requirred)\n");
	char* name;
	printf("*Name: ");
	scanf("%s",name);

	char* telnumber;
	printf("*Number: ");
	scanf("%s",telnumber);

	char* server;
	printf("*Servername: ");
	scanf("%s",server);
	
	char* seed;
	printf("*Seed: ");
	scanf("%s",seed);
	
	char* parameters;
	printf("Parameters: ");
	scanf("%s",parameters);
	
	printf("User added:\n Name: %s | Number: %s | Servername: %s | Seed: %s | Params: %s \n", name, telnumber, server, seed, parameters);
}
