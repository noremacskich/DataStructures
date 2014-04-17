#include <iostream>
#include <iomanip> // setw
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

// This prints out the 2 column station info
string printSingleStation(STATIONS stationList[], int stationNumber);
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
void getStations(string filePath, STATIONS stationlist[]){
		// create the file variable
	ifstream infile;
	string line;
	
	// Open the file to read the schedule contents
	infile.open("stations.dat");
	
	int i=0;
	
	// While there is a line to get, and there fewer than 100 records
	while(!infile.eof() && i < 100){
		
		// Store the Number
		infile >> stationlist[i].Number;
		
		// Store the Name
		getline(infile, stationlist[i].Name);
		
		// This removes the first character in the string
		// from http://goo.gl/4dg3Lh
		stationlist[i].Name = stationlist[i].Name.substr(1).append(stationlist[i].Name.substr(0,1));
		
		// Goto next spot in the array.
		i++;
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
 * @param numRows | Integer
 *	^	This is the number of rows that needs to be printed
 *
 * @param startRecord | Integer
 *	^	This is record that the first column starts on.
 *
 * @reqs terminalHeight
 *	^	Tells me what the height of the terminal is.
 *
 * @author NoremacSkich | 2014/4/14
 *
 */
void showStations(STATIONS stationList[], int numStations){
	// Things to know:
	//		Number of rows to print out, this is the column height
	//		The list of stations
	//		The starting record
	
	// This is the number of columns that can be displayed at once
	int pageColumnCount = 2;
	
	// The number of lines that are being used by other parts of the gui
	int interfaceLines = 5;
	
	// This computes the number of items that can be in each list
	int columnHeight = terminalHeight - interfaceLines;
	
	// This calculates the number of rows that will be on the last column.
	int leftovers = numStations % columnHeight;
	
	// this calculates the number of columns that will be needed to be displayed
	int columnCount = (numStations - leftovers) / columnHeight;
	
	// If there were leftovers, then we need to add an additional column
	if(leftovers > 0){
		// Then add one more column
		columnCount++;
	}
	
	int currentPage = 1;
	// This is the starting record for the current page
	int startRecord = currentPage * columnHeight * 2;
	
	// This is the current line.
	int currentLine = 0;
	
	//Print out lines until the page is done.
	while(currentLine <= columnHeight){
		// Print out the station for the first column, then a space
		cout << printSingleStation(stationList, (currentLine)) << " ";
		// Next print out the 2nd column by adding together the current line
		// that is currently being displayed, and the number of rows in a column
		// (columnHeight) and add one.
		cout << printSingleStation(stationList, (columnHeight + currentLine + 1)) << endl;
		// Increment to the next line.
		currentLine++;
	}
	
	
	// For now print out the stations one by one
	for(int i=0; i<numStations; i++){
		
	}

}
/**@fun printSingleStation(STATIONS stationList[], int stationNumber)
 *	^	This will print out the station number and name
 *
 * @param stationList[] | STATIONS
 *	^	This is the list of stations
 *
 * @param stationNumber | Integer
 *	^	This is the station ID that this function will print.
 * @note NoremacSkich | 2014/4/17
 *	^	This will output: ###. XXXXX
 *		There is no new line character.
 */
string printSingleStation(STATIONS stationList[], int stationNumber){
	stringstream stationColumns;
	stationColumns << " " << right << setw(3) << stationList[stationNumber].Number << ". ";
	stationColumns << left << setw(25) << stationList[stationNumber].Name;
	/*
	// Test the single station list input
	for(int i=0; i<100; i++){
		cout << printSingleStation( stationlist, i ) << endl;
	}
	*/
	return stationColumns.str();
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
	
	int i=0;
	
	// While there is a line to get, and there fewer than 100 records
	while(!infile.eof() && i < 100){
		// Store the train info
		infile >> trainSched[i].Departure_Station;
		infile >> trainSched[i].Arrival_Station;
		infile >> trainSched[i].Departure_Time;
		infile >> trainSched[i].Arrival_Time;
		
		// Goto next spot in the array.
		i++;
	}
	
	/*
	// See if print out the train data
	for(int i=0; i<100; i++){
		cout << trainSched[i].Departure_Station << "| : |";
		cout << trainSched[i].Arrival_Station  << "| : |";
		cout << trainSched[i].Departure_Time  << "| : |";
		cout << trainSched[i].Arrival_Time  << "| : |" << endl;
	}
	*/
	
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
 *
 * @param min | int
 *	^	This is the number of minutes in a day to be converted.
 *	N	This function assumes that the inputed number is no greater than 1440
 *
 * @return string
 *	^	This will return a string formated as:
 *	F	HH:MM APM
 *		Where H is hours, M is minutes, APM is either am or pm
 *
 * @reqs <sstream>, <iomanip>
 *
 * @author NoremacSkich | 2014/4/15
 *
 */
string minToHour(int minutes){
	
	int tmpMinutes = 0;			// this is the number of minutes into an hour
	int tmpHours = 0;			// this is the number of hours into a day
	string apm = "am";			// Stores the text version of am or pm
	stringstream returnString;	// This will hold the HH:MM APM string
	
	// Calculate the number of minutes into an hour.
	tmpMinutes = minutes % 60;
	
	// Now calculate the number of hours into the day.
	tmpHours = (minutes - tmpMinutes) / 60;
	
	// Check to see if we are past noon
	if(tmpHours >= 12){
		
		// If it is, we need to change the apm string.
		apm = "pm";
		
		// If the time is past noon, subtract 12 from it.
		if(tmpHours > 12){
			// get the noon hour
			tmpHours -= 12;
		}
		
	// If it isn't noon, check to make sure that it isn't midnight
	}else	
	
	// Check to see if it is midnight
	if(tmpHours < 1){
		// Since it is midnight, we need to change the 00 to 12
		tmpHours = 12;
	}
	
	// Now build the HH:MM APM string
	
	// first input the number of hours into the day
	returnString << setfill('0') << setw(2) << tmpHours;
	
	// followed by the colon
	returnString << ":";
	
	// then input the number of minutes into an hour
	returnString << setfill('0') << setw(2) << tmpMinutes;
	
	// Finally add a space and wether it is am or pm.
	returnString << " " << apm;
	
	/*
	// Test for the minToHour Funciton
	for(int i=0; i<1440; i += 1){
		cout << minToHour(i) << endl;
	}
	*/
	
	
	// Now, return a string with the contents of the stream
	return returnString.str();
}

/**@fun convertInt(int number)
 *	^	Converts an integer into a number using standard libraries.
 *
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
 * @note NoremacSkich | 2014/4/15
 *	^	This is depreciated, unless I find another use for it.
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
	// Create the train Schedule array
	TRAINS trainSched[100];
	// Create the station list array
	STATIONS stationlist[100];
	
	// Populate the stations array
	getStations(stationsFile, stationlist);
	
	// Populate the Train Schedule
	getTrains(trainsFile, trainSched);
	
	// Show the stations
	showStations(stationlist, 100);
	
	
	
	/*
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
	*/
	// Exit the program gracefully, without errors
	return 0;
}


