#include <iostream>
#include <iomanip> // setw
#include <sstream>
using namespace std;

static int numStations = 4;

void printStationList(int stations[4]);

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
/**@fun shortest(TRAINS a, TRAINS c, TRIANS p)
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
/**@fun path(int i, int j, TRAINS p)
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
 * @param stations[4] | integer | Array
 *	^	This is the array that contains the complete path from station (i) to 
 *		station (j)
 *
 * @param[io] stationsI | integer
 *	^	This will keep track of the current position of the station index.
 *		should be modified on each call.
 *
 * @author NoremacSkich | 2014/4/21
 * @modified NoremacSkich | 2014/4/28
 *
 */

void path(int shortMatrix[4][4], int middleMatrix[4][4], int i, int j, int stations[4], int stationsI ){
 	
 	cout << endl << "In Path, stationsI = " << stationsI << endl;
 	printStationList(stations);
 		
		// Increment the station counter
	stationsI++;
	
 	// Check if path exists, and if there is a mid path
	if(shortMatrix[i][j] != 50 && middleMatrix[i][j] !=-1){
		
		
		// This is the middle point
		int k;
		// Set k to the midpoint of i -> j
		k = middleMatrix[i][j];
		
		// Grounding Condition
		if(k==-1){
			
			// This is a direct path, exit the function
			return ;
		}
	
		// Get the midpoint between i -> k
		path(shortMatrix, middleMatrix, i,k, stations, stationsI);

		// Store the midpoint
		stations[stationsI] = k;
		
		// get the midpoint between k -> j
		path(shortMatrix, middleMatrix, k,j, stations, stationsI);
	}

 }
 
/**@fun completePath(int shortMatrix[4][4], int middleMatrix[4][4], int i, int j, int stations[4])
 *	^	This will fill in the array for the station order (stations)
 * 
 * @param shortMatrix[4][4] | integer | array
 *	^	This is the matrix containing an array of shortest paths
 * 
 * @param middleMatrix[4][4] | integer | array
 *	^	This is the matrix containing the next train to board
 * 
 * @param i | integer
 *	^	This is the starting station
 * 
 * @param j | integer
 *	^	This is the ending station
 * 
 * @param stations[4] | integer | Array
 *	^	This is the array that contains the complete path from station (i) to 
 *		station (j)
 *	N	This should be returned modified.
 *	N	This should probably be a linked list, but for now will use array
 *
 * @author NoremacSkich | 2014/4/28
 */
void completePath(int shortMatrix[4][4], int middleMatrix[4][4], int start, int end, int stations[4]){
	
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
	stations[stationI] = start;
	
	// increment the station counter
	stationI++;
	
	// Print out the station list.
	printStationList(stations);
	
	// Then find all the middle stations, and put them into the array
	path( shortMatrix, middleMatrix, start, end, stations, stationI);
	
	// Finally put the last station in the array
	stations[stationI] = end;
	
	// Print out the station list.
	printStationList(stations);
}
// Note: if the array spot was not used, then it will equal 101
void printStationList(int stations[4]){
	for(int i=0; i<4; i++){
		cout << stations[i] << ",";
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
		int stationList[4] = {101};
		for(int i=0; i<=4; i++){
			stationList[i] = 101;
		}
		// Ask for the starting and stopping stations
		cout << "Start: ";
		cin >> start;
		cout << " End: ";
		cin >> end;
		
		// Print out the station list.
		printStationList(stationList);
		
		// Get the complete path between stations
		completePath( shortMatrix, middleMatrix, start, end, stationList);
		
		// Print out the station list.
		printStationList(stationList);
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


