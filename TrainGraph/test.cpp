#include <iostream>
#include <iomanip> // setw
#include <sstream>
using namespace std;

static int numStations = 4;

void printVerticesList(string verticesList[100]);
void pathToTable(string verticesList[100], string trainpath);
void printArray(int myarray[4][4]);
void shortest(int adjMatrix[4][4], int shortMatrix[4][4], int middleMatrix[4][4], int numVertexes, int inf);
string path(int shortMatrix[4][4], int middleMatrix[4][4], int i, int j );
void completePath(int shortMatrix[4][4], int middleMatrix[4][4], int start, int end, string verticesList[100]);

void printArray(int myarray[4][4]){
	
	cout << "    0   1   2   3" << endl;
	for(int i=0; i<4; i++){
		cout << i << " ";
		for(int j=0; j<4; j++){
			cout << setw(3) << myarray[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
/**@fun shortest(int adjMatrix[4][4], int shortMatrix[4][4], int middleMatrix[4][4], int numVertexes, int inf)
 *	^	This calculates the shortest path between two stations based on the 
 *		path of the trains
 *	I	This is based on Floyd's Algorithm
 *
 * @param adjMatrix | TRAINS
 *	^	The Adjacency Matrix, this is the matrix with all known values
 *
 * @param shortMatrix | TRAINS
 *	^	The Short Matrix, aka the cost matrix.  This is the computed list of
 *		shortest paths.
 *
 * @param middleMatrix | TRAINS
 *	^	This will hold the station with the next train to get to destination.
 *
 * @param numVertexes | Integer
 *	^	This is the number of stations there are.
 *
 * @param inf | Integer
 *	^	This is what the infinity value is.
 *
 * @author NoremacSkich | 2014/4/21
 * @modified NoremacSkich | 2014/4/25
 * @modified NoremacSkich | 2014/4/28
 *
 */
void shortest(int adjMatrix[4][4], int shortMatrix[4][4], int middleMatrix[4][4], int numVertexes, int inf){

	// Copy adjacency matrix into the shortest path matrix
	for(int i=0; i<numVertexes; i++){
		for(int j=0; j<numVertexes; j++){
			shortMatrix[i][j] = adjMatrix[i][j];
			middleMatrix[i][j] = -1; // set p to 
		}
	}

	// Set distance to self as 0
	for(int i=0; i<numVertexes; i++){
		middleMatrix[i][i] = 0;
	}

	// Compute the shortest paths
	for(int k=0; k<numVertexes; k++){
		for(int i=0; i<numVertexes; i++){
			for(int j=0; j<numVertexes; j++){
				if( shortMatrix[i][k] + shortMatrix[k][j] < shortMatrix[i][j] ){ // works
					shortMatrix[i][j] = shortMatrix[i][k] + shortMatrix[k][j];// works
					middleMatrix[i][j] = k; // record the middle path
				}
			}
		}
	}
}
/**@fun path(int shortMatrix[4][4], int middleMatrix[4][4], int i, int j )
 *	^	This will get the stations between the two given stations
 *
 * @param shortMatrix | Integer | Array
 *	^	This is the matrix with all the computed shortest paths
 * 
 * @param middleMatrix | Integer | Array
 *	^	This will hold the station with the next train to get to destination.
 *
 * @param i | integer
 *	^	This is the starting vertex
 *
 * @param j | integer
 *	^	This is the ending vertex
 *
 * @author NoremacSkich | 2014/4/21
 * @modified NoremacSkich | 2014/4/28
 *
 * @reverted NoremacSkich | 2014/4/28
 *
 */

string path(int shortMatrix[4][4], int middleMatrix[4][4], int i, int j ){
 	stringstream returnString;	// This will hold the HH:MM APM string
 	
 	// Check if path exists, and if there is a mid path
	if(shortMatrix[i][j] != 50 && middleMatrix[i][j] !=-1){

		// This is the middle point
		int k;
		// Set k to the midpoint of i -> j
		k = middleMatrix[i][j];
		
		// Grounding Condition
		if(k==-1){
			
			// This is a direct path, exit the function
			return "";
		}
	
		// Get the midpoint between i -> k
		returnString << path(shortMatrix, middleMatrix, i,k);
		
		// process the midpoint
		returnString << k << " ";
		
		// get the midpoint between k -> j
		returnString << path(shortMatrix, middleMatrix, k,j);
		
		return returnString.str();
	}
	return "";
 }
 
/**@fun completePath(int shortMatrix[4][4], int middleMatrix[4][4], int start, int end, string verticesList[100])
 *	^	This will fill in the array for the station order (stations)
 * 
 * @param shortMatrix | integer | array[4][4]
 *	^	This is the matrix containing an array of shortest paths
 * 
 * @param middleMatrix | integer | array [4][4]
 *	^	This is the matrix containing the next train to board
 * 
 * @param start | integer
 *	^	This is the starting station
 * 
 * @param end | integer
 *	^	This is the ending station
 * 
 * @param verticesList | integer | Array[100]
 *	^	This is the array that contains the complete path from station (i) to 
 *		station (j)
 *	N	This should be returned modified.
 *	N	This should probably be a linked list, but for now will use a string
 *
 * @author NoremacSkich | 2014/4/28
 */
void completePath(int shortMatrix[4][4], int middleMatrix[4][4], int start, int end, string verticesList[100]){
	stringstream returnString;	// This will hold the HH:MM APM string
	
	// Check to make sure stations exist
	if(start > numStations){
		// starting station doesn't exist
		return ;
	}
	
	if(end > numStations){
		// ending station doesn't exist
		return ;
	}
	
	// See if route doesn't exist
	if(shortMatrix[start][end] == 50){
		// there is no route between the starting and stopping stations
		return ;
	}
	
	// is This is going to itself?
	if(middleMatrix[start][end] == 0){
		// The starting and stopping stations are the same
		return ;
	}
	
	// initialize the stations index value (stationI)
	int stationI = 0;
	
	// Set the first element in the array, in this case, the first station
	returnString << start << ",";
	
	// Then find all the middle stations, and put them into the string
	returnString << path( shortMatrix, middleMatrix, start, end);
	
	// Finally put the last station in the array
	returnString << end;
	
	// create the table from the string
	pathToTable(verticesList, returnString.str());
	
	// Print out the station list.
	printVerticesList(verticesList);
}

void pathToTable(string verticesList[100], string trainpath){
	stringstream stream;
	stream << trainpath;
	for(int i=0;i<=100;i++){
		// If there is no more numbers, break the loop early
		if(stream.rdbuf()->in_avail() == 0){
			break;
		}
		stream >> verticesList[i];
	}
}

// Note: if the array spot was not used, then it will equal 101
void printVerticesList(string verticesList[100]){
	for(int i=0; i<100; i++){
		// Short Circuit the readout
		if(verticesList[i] == "101"){
			break;
		}
		// Print out the station ID
		cout << verticesList[i] << ",";
	}
	cout << endl;
}
// ====== main driver ==============================
int main(void)
{
	int numVertices = 4;
	
	// this is what we are using for infinity
	int inf = 50;
	/*
	A -> C -> D
	|    ^
	V    |
	B ---+
	*/
	// This is the adjacency matrix of known values
	// inf means there doesn't exist an path between the two points
	int adjMatrix[4][4] = 
	{
		{inf,  10,  30, inf },
		{inf, inf,  10, inf },
		{inf, inf, inf,   5 },
		{inf, inf, inf, inf }
	};
	
	// This is the adjacency matrix of all shortest paths
	int shortMatrix[4][4] ={inf};
	
	// This holds the intermediate paths between stations.
	int middleMatrix[4][4] = {inf};
	
	// Run the variation of floyds algorithm
	shortest(adjMatrix, shortMatrix, middleMatrix, numVertices, inf);
	// put some space
	cout << endl << endl;
	
	// print out the arrays
	printArray(adjMatrix);
	printArray(shortMatrix);
	printArray(middleMatrix);
	
	// initialize the starting and ending stations
	int start = 0;
	int end = 0;
	
	//do{
		// Initialize the starting list
		string verticesList[100];
		for(int i=0; i<100; i++){
			verticesList[i] = "101";
		}
		// Ask for the starting and stopping stations
		cout << "Start: ";
		cin >> start;
		cout << " End: ";
		cin >> end;
				
		// Get the complete path between stations
		completePath( shortMatrix, middleMatrix, start, end, verticesList);
		
		// Print out the station list.
		printVerticesList(verticesList);
		cout << endl << endl;
		
		printArray(adjMatrix);
		printArray(shortMatrix);
		printArray(middleMatrix);
	
	//}while(start != 50);
	
	
	
	
	/*
	for(int k=0; k<4; k++){
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				myarray[i][k] += 1;
				myarray[k][j] += 3;
				myarray[i][j] += 5;
				printArray(myarray);
				myarray[i][k] = 0;
				myarray[k][j] = 0;
				myarray[i][j] = 0;
				
			}
		}
	}*/
	
	return 0;
}


