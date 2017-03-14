Required:
	aircrack-ng
	        tar xfz aircrack-ng-1.0-rc1.tar.gz
		cd aircrack-ng-1.0-rc1
		make 
		make install
		
	macchanger
	        sudo apt-get install macchanger macchanger-gtk
		
	*kali linux comes with these installed.
-Your wireless card will need to be able to use packet injection and "monitor mode" in order to run successfully. 
-My wireless card is named wlan0mon in monitor mode and wlan0 in managed mode.
	type "airmon-ng" in console to find out managed mode card name.
	type "airmon-ng start (name of managed mode card)" and type in "airmon-ng" to find out monitor mode card name.
-Change the script based on your network card and desired location to save files.
-For ethical testing only.


How it works:
	This will execute a series of aircrack commands. It will first place your wireless card in monitor mode to pick up 
	wifi signals. Then it will assign a random MAC address to your wireless card. The program will then take in your 
	targets information you provide. This will then restart the wireless card in the correct channel of your target, 
	and attempt a deauthentication attack. If it is successful, you will see "handshake captured" in the right corner of 
	the new terminal window. CTRL + C to quit. Your files should be saved in the location specified in the script.
