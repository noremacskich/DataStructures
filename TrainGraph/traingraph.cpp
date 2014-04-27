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

// Store the number of stations
int numStations = 0;

// Store the number of trains
int numTrains = 0;

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
 * @param Travel_Time | int
 *	^	This is how long the train ride is.
 *	N	This is calculated by subtracting departure time from arrival time.
 *
 * @author NoremacSkich | 2014/4/14
 * @modified NoremacSkich | 2014/4/22
 *
 */

struct TRAINS{
	int Departure_Station;
	int Arrival_Station;
	int Departure_Time;
	int Arrival_Time;
	int Travel_Time;
	string DT_String;
	string AT_String;
};


// ================= PROTOTYPES ========================

// ================= PROTOTYPES FOR STATIONS ========================

// this will print out all the stations.
void showStations(string stations[]);

// This will get the stations from file and return them to the stations array
void getStations(string filePath, string stations[]);

// ================= PROTOTYPES FOR TRAINS ========================

// This will print out all the id's and names for the train station
void showTrainSched(string stations[]);

// This will get the trains from file and return them to the trainSched array
void getTrains(string filePath, TRAINS trainSched[]);

// This prints out the 2 column station info
string printSingleStation(string stationList[], int stationNumber);

// ================= PROTOTYPES FOR FLOYD'S ALGORITHM ========================

void shortest(TRAINS a, TRAINS c, TRAINS p);
 
void path(int i, int j, TRAINS p);
// ================= PROTOTYPES FOR MISC ========================

// This shows the primary menu.
void showMainMenu(void);

// program main driver
int main(void); 
// converts teh minutes into a string like: 08:00 AM
string minToHour(int minutes);
// This is a routine to print a prompt and get a user input.  This is so that 
// when something is sent to the screen, it can be seen before the screen is 
// cleared.
void myPause(void);

// This will insert a bunch of new lines to cludge a new screen.
void clearScreen(void); 

// converts an integer into a string
string convertInt(int number);

// print out the train info
void printTrainInfo(TRAINS trainSched[], int trainID);
//=========================== FUNCTIONS ===========================

/**@fun shortest(TRAINS a, TRAINS c, TRIANS p)
 *	^	This calculates the shortest path between two stations based on the 
 *		path of the trains
 *	I	This is based on Floyd's Algorithm
 *
 * @param a | TRAINS
 *	^	The Adjacency Matrix
 *
 * @param c | TRAINS
 *	^	The Adjacency Matrix of shortest paths
 *
 * @param p | TRAINS
 *	^	This holds all the stations between the two stations
 *
 * @author NoremacSkich | 2014/4/21
 * @modified NoremacSkich | 2014/4/25
 */

 void shortest(TRAINS a, TRAINS c, TRAINS p){
/*	
	int i;
	int j;
	int k;
	int infinity = 500;
	
	// Copy a into c
	for(i=0; i<infinity; i++){
		for(j=0; j<infinity; i++){
			a[i,j].Travel_Time = c[i,j].Travel_Time;
			p[i,j].Travel_Time = 0; // set p to zero
		}
	}
	
	// Set distance to self as 0
	for(i=0; i<infinity; i++){
		a[i,i].Travel_Time = 0;
	}
	
	// Compute the shortest paths
	for(k=0; k<infinity; k++){
		for(i=0; i<infinity; i++){
			for(j=0; j<infinity; j++){
				if(a[i,k].Travel_Time + a[k,j].Travel_Time < a[i,j].Travel_Time){
					a[i,j].Travel_Time = a[i, k].Travel_Time + a[k,j].Travel_Time;
					p[i,j].Travel_Time = k; // record the middle path
				}
			}
		}
	}
	
*/	
}
void fillMatrix(STATIONS stationList[], TRAINS trainList[]){
	//MATRIX floyds[numStations, numStations];
	
	//floyds[train.departureStation, train.arrivalStation].infinity = false;
	//floyds[train.departureStation, train.arrivalStation].cost = #;
	
}
/**@fun path(int i, int j, TRAINS p)
 *	^	This will get the stations between the two given stations
 *
 * @param i | integer
 *	^	???
 *
 * @param j | integer
 *	^	???
 *
 * @param p | TRAINS | Array
 *	^	
 * @author NoremacSkich | 2014/4/21
 *
 */

void path(int i, int j, TRAINS p){
/*	int k;
	// Set k to the midpoint of i -> j
	k = p[i, j];
	
	// Grounding Condition
	if(k==0){
		
		// This is a direct path, exit the function
		return;
	}
	
	// Get the midpoint between i -> k
	path(i,k);
	
	// process the midpoint
	cout << k;
	
	// get the midpoint between k -> j
	path(k,j);
*/
}

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
 * @modified NoremacSkich | 2014/4/27
 *
 * @return 
 *	^	See the stations[] parameter.
 */
void getStations(string filePath, string stationlist[]){
	// using array of strings for stations
	// create the file variable
	ifstream infile;
	string line;
	int debug = false;
	// Open the file to read the schedule contents
	infile.open("stations.dat");
	// this gets rid of the number
	int number;
	int i=0;
	
	// While there is a line to get, and there fewer than 100 records
	while(!infile.eof()){
		
		// Store the Number
		infile >> number;
		
		// Store the Name
		getline(infile, stationlist[i]);
		
		// This removes the first character in the string
		// from http://goo.gl/4dg3Lh
		//stationlist[i].Name = stationlist[i].Name.substr(1).append(stationlist[i].Name.substr(0,1));
		
		// Goto next spot in the array.
		i++;
	}
	i--;
	numStations = i;
	
	if(debug){
		cout << "Number of records read in: " << i << endl;
	}
	// Close the file
	infile.close();
}

/**@fun printShortTime(string startStation, string endStation)
 *	^	This prints out the shortest time screen
 *	
 * @author NoremacSkich | 2014/4/21
 *
 */
void printShortTime(string startStation, string endStation){
	
	cout << "REPORT 1: Shortest time riding on Trains." << endl;
	//cout << "To go from " << startStation << " to " << endStation << "you will need to ride on trains for " << endl;
	//cout << numHours << " hours and " << numMinutes << " minutes." << endl;
	
	cout << "You will take the following trains:" << endl;
	
	// This is where the printRoute function will be called.
	
	
	cout << "END OF REPORT" << endl;
	
}

/**@fun printRoute()
 *	^	This will print out the intermediate stations
 *
 * @author NoremacSkich | 2014/4/21
 *
 */
void printRoute(TRAINS trainInfo){
	
	// The contents for this come from the P array
	//cout << trainInfo.routeString << endl;

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
 * @param startRec | Integer
 *	^	This is record that the first column starts on.
 *
 * @author NoremacSkich | 2014/4/14
 * @modified NoremacSkich | 2014/4/17
 * @modified NoremacSkich | 2014/4/21
 * 
 * @bugs NoremacSkich | 2014/4/17
 *	1	an start record of zero crashes the program
 *	2	the number of rows needs to be lower than half of the 
 *		number of stations, otherwise program will crash
 *	3	Negative numbers do nothing for the row count
 *	4	Negative numbers for the startRec will crash the program.
 */
void showStations(string stationList[], int numRows, int startRec){
	// Things to know:
	//		Number of rows to print out, this is the column height
	//		The list of stations
	//		The starting record
	
	// This is the current line.
	int currentLine = 0;
	
	// This fixes the problem of records being off by 1, but not quite
	// sure what is causing that in the first place.
	startRec--;
	
	// Print out the header info quick and dirty
	cout << "  ID  Name                        ID  Name                      " << endl;
	cout << " ---  -------------------------- ---  --------------------------" << endl;
	
	//Print out lines until the page is done.
	while(currentLine <= numRows){
		
		// Print out the station for the first column, then a space
		cout << printSingleStation(stationList, (currentLine + startRec)) << " ";
		
		// Next print out the 2nd column by adding together the current line
		// that is currently being displayed, and the number of rows in a column
		// (columnHeight) and add one.
		cout << printSingleStation(stationList, (numRows + currentLine + startRec + 1)) << endl;
		
		// Increment to the next line.
		currentLine++;
	}


}
/**@fun printSingleStation(STATIONS stationList[], int stationNumber)
 *	^	This will print out the station number and name.  If there isn't a
 *		a station associated with the stationNumber, then it will return 32
 *		space characters.
 *
 * @param stationList[] | STATIONS
 *	^	This is the list of stations
 *
 * @param stationNumber | Integer
 *	^	This is the station ID that this function will print.
 * 
 * @note NoremacSkich | 2014/4/17
 *	^	This will output: ###. XXXXX
 *	^	There is no new line character.
 *	^	This will print out 32 spaces if the station doesn't exist
 *
 * @author NoremacSkich | 2014/4/22
 *
 */
string printSingleStation(string stationList[], int stationNumber){
	
	// Create a string
	stringstream stationColumns;
	
	if( stationNumber < numStations ){ 
		
		// Print out the station number
		stationColumns << " " << right << setw(3) << stationNumber << ". ";
		
		// Print out the station name
		stationColumns << left << setw(25) << stationList[stationNumber];
		
	}else{
		// Print out  a blank line
		stationColumns << setw(31) << " ";
	}	
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
 * @modified NoremacSkich | 2014/4/22
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
	while(!infile.eof()){
		// for some reason, not stopping at last line, reads in a blank record,
		// then stops.
		// Store the train info
		infile >> trainSched[i].Departure_Station;
		infile >> trainSched[i].Arrival_Station;
		infile >> trainSched[i].Departure_Time;
		infile >> trainSched[i].Arrival_Time;
		
		// Set the travel time.
		trainSched[i].Travel_Time = trainSched[i].Arrival_Time - trainSched[i].Departure_Time;
		trainSched[i].DT_String = minToHour(trainSched[i].Departure_Time);
		trainSched[i].AT_String = minToHour(trainSched[i].Arrival_Time);
		
		// Show the train info
		printTrainInfo(trainSched, i);
		
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

void printTrainInfo(TRAINS trainSched[], int trainID){
	// being lazy
	int i = trainID;
	
	cout << "DS: \"" << trainSched[i].Departure_Station << "\"" << endl;
	cout << "AS: \"" << trainSched[i].Arrival_Station << "\"" << endl;
	cout << "DT: \"" << trainSched[i].Departure_Time << "\"" << endl;
	cout << "AT: \"" << trainSched[i].Arrival_Time << "\"" << endl;
	
	// Set the travel time.
	cout << "Travel_Time: \"" << trainSched[i].Travel_Time << "\"" << endl;
	cout << "DT_String: \"" << trainSched[i].DT_String << "\"" << endl;
	cout << "AT_String: \"" << trainSched[i].AT_String << "\"" << endl;
	cout << "-------------------" << endl;
	
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
void showTrainSched(string stations[]){
	
	// Place to store the starting Station
	int startStation = 0;
	int endStation = 0;
	
	// Show the options
	showStations(stations, 49, 1);
	
	// Ask for Starting station
	cout << "What station do you want to start at?" << endl;
	cin >> startStation;
	
	cout << "Where do you wish to go?" << endl;
	cin >> endStation;
	
	// Calculate the route
	
	// clear the screen
	
	// Print out the Report
	
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
	// Sanitize / initialize the Array
	for(int i = 0; i<100; i++){
		trainSched[i].Departure_Station = -1;
		trainSched[i].Arrival_Station = -1;
		trainSched[i].Departure_Time = -1;
		trainSched[i].Arrival_Time = -1;
		trainSched[i].Travel_Time = -1;
		trainSched[i].DT_String = "-";
		trainSched[i].AT_String = "-";
	}
	// Create the station list array
	string stationlist[100];
	
	cout << "getStations" << endl;
	// Populate the stations array
	getStations(stationsFile, stationlist);
	
	cout << "getTrains" << endl;
	// Populate the train array
	getTrains(trainsFile, trainSched);
	
	cout << "Show Stations" << endl;
	showStations(stationlist, 5, 1);
	
	
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
				showStations(stations, 49, 1);
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


