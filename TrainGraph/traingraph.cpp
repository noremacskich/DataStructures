#include <iostream>
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
void showStations(STATIONS stations[]){
	
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

// ====== main driver ==============================
int main(void)
{
	TRAINS trainSched[100];
	STATIONS stations[100];
	
	getTrains(trainsFile,trainSched);
	getStations(stationsFile, stations);
	
	/*
	int main_choice;

	do{
		// Clear the Screen.
		clearScreen();
		
		// Display the main menu
		
		
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

				
				
				break; // To the main menu
				
				
			case 2:
				
				
				
				break; // To the main menu
				
				
			case 3:
				
									
				break; // To the main menu
				
				
				
			case 4:
				cout << "End Program" << endl;
				
				break; // To the main menu
			
				
				
				
			default:
				cout << "oops :)" << endl;
		}
	}while(main_choice != 4);
	*/
	// Exit the program gracefully, without errors
	return 0;
}


