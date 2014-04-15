#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
//===============================================================
//   PROGRAM:  Assignment #3
//   AUTHOR :  Cameron Hicks
//   DUE    :  4/30/2014 9:00 AM
//   DESCRIPTION:
//			This program will simulate a train terminal, by 
//			using a graph data structure.  It will need to
//			find the shortest path between two points, and 
//			optionally, the shortest time between two points.
//===============================================================
using namespace std;

// GLOBAL CONSTANT ====================================

// This is where the stations.dat file is located
string stationsFile = "stations.dat";

// this is where the trains.dat file is located
string trainsFile = "trains.dat";

const int terminalWidth = 80;
const int terminalHeight = 20;

// GLOBAL TYPE DEF  =====================================

/**@struct STATION
 *	^	This holds all the information related to a station.
 *
 * @param Number | int
 *	^	This is the number of the train station.
 *	N	This will be in the range of 0 to 99
 *
 * @param Name | String
 *	^	This is the name of the train station.
 *	N	This will have a max length of 25 characters
 *
 * @author NoremacSkich | 2014/4/14
 * 
 */

struct STATIONS{
	int Number;
	string Name;
};

/**@struct TRAINS
 *	^	This holds all the information related to a train.
 *	N	This program assumes that no train will run from one day to the next.
 *
 * @param Departure_Time | int
 *	^	This is when the train leaves the station according to the number
 *		of minutes into the day.
 *	N	There are 1440 minutes in a day.
 *
 * @param Arrival_Time | int
 *	^	This is when the train arrives at the station according to the number
 *		of minutes into the day.
 *	N	There are 1440 minutes in a day.
 *	N	This number should be greater than the departure time.
 *
 * @param Departure_Station | int
 *	^	This is the station were the train will depart from.
 *	N	There are at most 100 stations.
 *
 * @param Arrival_Station | int
 *	^	The train will arrive at this station.
 *	N	There are at most 100 stations.
 *
 * @author NoremacSkich | 2014/4/14
 * 
 */

struct TRAINS{
	int Departure_Station;
	int Arrival_Station;
	int Departure_Time;
	int Arrival_Time;
};


// ================= PROTOTYPES ========================

// ================= PROTOTYPES FOR STATIONS ========================
// this will print out all the stations.
void showStations(STATIONS stations[]);
// This will get the stations from file and return them to the stations array
void getStations(string filePath, STATIONS stations[]);

// ================= PROTOTYPES FOR TRAINS ========================
// This will print out all the id's and names for the train station
void showTrainSched(STATIONS stations[]);
// This will get the trains from file and return them to the trainSched array
void getTrains(string filePath, TRAINS trainSched[]);

// ================= PROTOTYPES FOR MISC ========================
// This shows the primary menu.
void showMainMenu(void);
// program main driver
int main(void); 
// This is a routine to print a prompt and get a user input.  This is so that 
// when something is sent to the screen, it can be seen before the screen is 
// cleared.
void myPause(void);

// This will insert a bunch of new lines to cludge a new screen.
void clearScreen(void); 

// converts an integer into a string
string convertInt(int number);

//=========================== FUNCTIONS ===========================
// ================= STATIONS ========================
/**@fun getStations(string filePath, STATIONS stations[])
 *	^	This will open up the inputed file, and return an array of stations.
 *	N	This function assumes that spaces are being used to distinguish the 
 *		station number from the station name.
 *
 * @param filePath | String
 *	^	This is the path that leads to a file with the station info.
 *
 * @param stations[] | STATIONS
 *	^	This is the array that the station data will be returned in.
 *
 * @author NoremacSkich | 2014/4/14
 *
 * @todo NoremacSkich | 2014/4/14
 *	^	Convert each line from the file into a data structure.
 *
 * @return 
 *	^	See the stations[] parameter.
 */
void getStations(string filePath, STATIONS stations[]){
		// create the file variable
	ifstream infile;
	string line;
	
	// Open the file to read the schedule contents
	infile.open("stations.dat");
	
	// Check to make sure that the file opened
	if( infile.fail() ){
		cout << "The " << stationsFile << " file is missing." << endl;
		exit(1);
	}
	
	// While there is a line to get
	while(getline(infile, line)){
		cout << line << endl;
			
	}
	
	// Close the file
	infile.close();
}
/**@fun showStations(STATIONS stations[])
 *	^	This will print out the stations and their ID to the consumer.
 * 
 * @param stations[] | STATIONS
 *	^	This array should hold the station name and their associated station 
 *		ID.
 *
 * @author NoremacSkich | 2014/4/14
 *
 */
void showStations(STATIONS stations[], int numStations){
	/*
	if(numStations > (terminalHeight - 4)){
		
	}
	cout << " " << setw(3) << stations[i].Number << ". " << setw(25) << stations[i].Name;
	*/
}
// ================= TRAINS ========================
/**@fun getTrains(string filePath, TRAINS trainSched[])
 *	^	This will open up the inputed file, and return an array of the train
 *		schedule.
 *	N	This function assumes that spaces are being used to distinguish the 
 *		arrival and departure time and station.
 *
 * @param filePath | String
 *	^	This is the path that leads to a file with the train schedule.
 *
 * @param trainSched[] | STATIONS
 *	^	This is the array that the train schedule data will be returned in.
 *
 * @author NoremacSkich | 2014/4/14
 *
 * @todo NoremacSkich | 2014/4/14
 *	^	Convert each line from the file into a data structure.
 *
 * @return 
 *	^	See the trainSched[] parameter.
 */
void getTrains(string filePath, TRAINS trainSched[]){
	
	// create the file variable
	ifstream infile;
	string line;
	
	// Open the file to read the schedule contents
	infile.open("trains.dat");
	
	// Check to make sure that the file opened
	if( infile.fail() ){
		cout << "The " << trainsFile << " file is missing." << endl;
		exit(1);
	}
	
	// While there is a line to get
	while(getline(infile, line)){
		cout << line << endl;
			
	}
	
	// Close the file
	infile.close();
}

/**@fun showTrainSched(TRAINS trainSched[])
 *	^	This will print out the stations and their ID to the consumer.
 * 
 * @param trainSched[] | TRAIN
 *	^	This array should hold the arrival and departure times for the train.
 *		They also contain the arrival and departure stations.
 *
 * @author NoremacSkich | 2014/4/14
 *
 */
void showTrainSched(STATIONS stations[]){
	
}

// ================= OTHER ========================
/**@fun showMainMenu(void)
 *	^	This will print out the main menu.
 *
 * @author NoremacSkich | 2014/4/14
 *
 */
 
void showMainMenu(void){
	cout << "Main Menu" << endl;
	
	cout << "1: List of Stations" << endl;
	cout << "2: Find Shortest Travel Time on Trains" << endl;
	cout << "3: Find Shortest Time Overall" << endl;
	cout << "4: exit" << endl;
}





/**@fun myPause(void)
 *	^	This is a routine to print a prompt and get a user input.  This is 
 *		so that when something is sent to the screen, it can be seen before 
 *		the screen is cleared
 * @author ??? | Sorting Algorithm
 *
 */
void myPause(void)
{
	int key;
	printf("\nEnter the 1 key to continue..");
	scanf("%i",&key);
	printf("\n");
}

/**@fun ClearScreen(void)
 *	^	This will insert a bunch of new lines to cludge a new screen.
 *
 * @note NoremacSkich | 2014/31/3
 *	^	Originally came from http://goo.gl/ZyMku8
 */
void clearScreen(void)
{
	cout << string( 50, '\n' );
}

/**@fun minToHour(int min)
 *	^	This will convert the inputted minutes into an hour:minute xm format
 * @param min | int
 *	^	This is the number of minutes in a day to be converted.
 *	N	This function assumes that the inputed number is no greater than 1440
 *
 * @return string
 *	^	This will return a string formated as:
 *	F	HH:MM APM
 *		Where H is hours, M is minutes, APM is either am or pm
 */
string minToHour(int minutes){
	
	string numHours = "00"; // Stores the text version of the number of hours
	string numMinutes = "00"; // Stores the text version of the minutes
	string apm = "am"; // Stores the text version of am or pm
	
	int tmpMinutes; // this is the number of minutes into an hour
	
	// This is the number of minutes into an hour
	tmpMinutes = minutes % 60;
	
	// Now find the number of hours
	int tmpHours = (minutes - tmpMinutes) / 60;
	
	// check to see if it is over 12 hours
	if(tmpHours >= 12){
		
		// If it is, we need to change the apm string.
		apm = "pm";
		
		// If the time is past noon, subtract 12 from it.
		if(tmpHours > 12){
			
			// get the noon hour
			tmpHours -= 12;
		}
	}
	
	numHours = convertInt(tmpHours);
	numMinutes = convertInt(tmpMinutes);
	
	
	string complete << numHours << ":" << numMinutes << " " << apm;
	
	return complete;
}

/**@fun convertInt(int number)
 *	^	Converts an integer into a number using standard libraries.
 * @param number | integer
 *	^	This is the number to be converted
 *
 * @returns
 *	^	A String of the number.
 *
 * @author Bazzy | 2009/2/14
 *	S	http://goo.gl/wC32J
 * 
 * @reqs <sstream>
 *
 */
string convertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

// ====== main driver ==============================
int main(void)
{
	//TRAINS trainSched[100];
	//STATIONS stations[100];
	
	//getTrains(trainsFile,trainSched);
	//getStations(stationsFile, stations);
	
	for(int i=0; i<1440; i++)
		minToHour(i);
	}
	
	if(false){
	int main_choice;

	do{
		// Clear the Screen.
		clearScreen();
		
		// Display the main menu
		showMainMenu();
		
		// Get their choice
		cin >> main_choice;
		
		// Check if input failed
		if(cin.fail()){
			// It failed, print it out
			cout << "Input Failed" << endl;
						// clear the buffer, then continue
			cin.clear();
			cin.ignore();
			myPause();

			continue;
		}
		
		switch(main_choice){
			
			
			case 1: 
				cout << "List of Stations" << endl;
				myPause();
				break; // To the main menu
				
			case 2:
				cout << "Shortest Travel Time on Trains" << endl;
				myPause();
				break; // To the main menu
				
			case 3:
				cout << "Find Shortest Time Overall" << endl;
				myPause();			
				break; // To the main menu
				
			case 4:
				cout << "End Program" << endl;
				
				break; // To the main menu
			
			default:
				cout << "oops :)" << endl;
				
		}
	}while(main_choice != 4);
	}
	// Exit the program gracefully, without errors
	return 0;
}


