#include <iostream>
#include <iomanip> // setw
#include <sstream>
using namespace std;

static int numStations = 4;

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
			

 /**@fun path(int i, int j, TRAINS p)
 *	^	This will get the stations between the two given stations
 *
 * @param shortMatrix | Integer | Array
 *	^	
 *
 * @param i | integer
 *	^	This is the starting vertex
 *
 * @param j | integer
 *	^	This is the ending vertex
 *

 * @author NoremacSkich | 2014/4/21
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
		returnString << k << ",";
		
		// get the midpoint between k -> j
		returnString << path(shortMatrix, middleMatrix, k,j);
		
		return returnString.str();
	}
	return "";
 }
 
string completePath(int shortMatrix[4][4], int middleMatrix[4][4], int i, int j){
	stringstream returnString;	// This will hold the HH:MM APM string
	
	// Check to make sure stations exist
	if(i > numStations){
		returnString << "Provided station # " << i << " doesn't exist." << endl;
		return returnString.str();
	}
	if(j > numStations){
		returnString << "Provided station # " << j << " doesn't exist." << endl;
		return returnString.str();
	}
	// See if route doesn't exist
	if(shortMatrix[i][j] == 50){
		return "Not A Route";
	}
	// is This is going to itself?
	if(middleMatrix[i][j] == 0){
		// Return Nothing
		return "To Itself";
	}
	returnString << i << ",";
	returnString << path( shortMatrix, middleMatrix, i, j );
	returnString << j << endl;
	return returnString.str();
}
// ====== main driver ==============================
int main(void)
{
	int numVertexes = 4;
	
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
		{inf,  10,  10, inf },
		{inf, inf,  30, inf },
		{inf, inf, inf,   5 },
		{inf, inf, inf, inf }
	};
	
	// This is the adjacency matrix of all shortest paths
	int shortMatrix[4][4] ={inf};
	
	// This holds the intermediate paths between stations.
	int middleMatrix[4][4] = {inf};
	
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
	
	cout << endl << endl;
	printArray(adjMatrix);
	printArray(shortMatrix);
	printArray(middleMatrix);
	int start = 0;
	int end = 0;
	
	//do{

		cout << "Start: ";
		cin >> start;
		cout << " End: ";
		cin >> end;
		
		cout << completePath( shortMatrix, middleMatrix, start, end);

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


