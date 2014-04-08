#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
//===============================================================
//   PROGRAM:  Assignment #2
//   AUTHOR :  Cameron Hicks
//   DUE    :  4/8/2014 11:01 AM
//   DESCRIPTION:
//          This program wil be used to create a test file of records to
//    be used in Assignment #2 (Spring 2014)
//===============================================================
using namespace std;

// GLOBAL CONSTANT ====================================
const int MAXNAME = 31; // Empl names 30 in length + 1, can have spaces
char BIN_FILENAME[] = "empl.dat";// binary file name


// GLOBAL TYPE DEF  =====================================

// employee structure def
// Needs to be exactly the same as the program that created the binary files
struct EMPL_TYPE
{
	int dept_num;
	char name[MAXNAME];
	int age;
	int emplid;		// is a unique key for indexing
};

// This is the array that will hold the employee records
struct INDEX_TYPE{
	int key; // will be the emplid
	int RID; // location of record in the file
};

// =================   PROTOTYPES ========================
// program main driver
int main(void); 

// This prints out employee info in ascending order
void print_Ascending(INDEX_TYPE index[], const int count); 

// This will sort the index in Ascending Order
bool sort_index(INDEX_TYPE index[], const int count); 

// This will lookup the record id value based on employee id parameter
int get_RID(int employeeID, INDEX_TYPE index[], int count); 

// This will update the employee record
void set_employee(EMPL_TYPE empl, const int RID);

// This will get the employee info from the data file based on the RID
EMPL_TYPE get_employee(const int RID);

// This populates the index array, and record count
void build_index(INDEX_TYPE i[], int & c);

// This is a routine to print a prompt and get a user input.  This is so that when something is 
// sent to the screen, it can be seen before the screen is cleared.
void myPause(void);

// This will print out the text for the main menu.
void mainMenu(void);

// This will print out the text for viewing the employee
void empView(void);

// This will print out the text for the first page of editing the department ID.
void empEditId(void); 

// This will print out the second page for editing the department ID.
void empEditDep(int impId, int depNum);

// This prints out the text for the sorting employees menu.
void empList(void);

// This will insert a bunch of new lines to cludge a new screen.
void clearScreen(void); 

//========================================================

// FUNCTIONS
/**@fun print_Ascending(INDEX_TYPE index[], int count)
 *	^	This prints out employee info in ascending order
 *
 * @param index[] | INDEX_TYPE
 *	^	this is the index that is to be printed out
 *
 * @param count | Integer
 *	^	This is how many records there are in the index
 *
 */
void print_Ascending(INDEX_TYPE index[], const int count){
	// create the file variable
	fstream infile;
	
	// Open the file to read the stored binary
	infile.open(BIN_FILENAME, ios::in|ios::binary);
	
	// Check to make sure that file was opened
	if(infile.fail()){
		cout << "The empl.dat file is missing" << endl;
		exit(0);
	}

	// Create a Temporary Employee Record
	EMPL_TYPE empl_rec;
	
	int i = 0;
	
	// Print out the header
	cout << "===== Sorted Binary File Contents =================" << endl;
	
	// Loop through employees, stop when count reaches 0
	while (i<count)
	{
		// Get to the record position
		// record position * record size, starting location
		infile.seekg(index[i].RID * sizeof(EMPL_TYPE), ios::beg);
		
		// attempt to read in the employee data
		infile.read((char *) &empl_rec,sizeof(empl_rec));
		
		// display the employee data
		cout << "Dept: " << empl_rec.dept_num;
		cout << "  Name: " << empl_rec.name;
		cout << "  age : " << empl_rec.age;
		cout << "  emplid : " << empl_rec.emplid << endl;
		

		// Increment the current count
		i++;
	}
	cout << "==========================================" << endl;

	// close the file
	infile.close();
}
 
/**@fun sort_index(INDEX_TYPE index[], int count)
 *	^	This will sort the index in Ascending Order
 *
 * @param index[] | INDEX_TYPE
 *	^	this is the index to sort
 *	R	This will modify inputed list.
 *
 * @param count | Constant Integer
 *	^	This is the total number of records in the index
 *
 * @return Boolean
 *	T	The index has been sorted
 *	F	This should never happen
 *
 * @note NoremacSkich | 2014/4/7
 *	^	This function does not write the sorted changes to the file.
 */
bool sort_index(INDEX_TYPE index[], const int count)
{	
	INDEX_TYPE tmpIndex;
	
	for(int i = 0; i < count; i++){
		for( int j = 0; j < count - 1; j++)
		{
			if(index[j].key > index[j+1].key){
				tmpIndex = index[j];
				index[j]= index[j+1];
				index[j+1] = tmpIndex;
			}
		}
	}
	
	return true;
}

/**@get_RID(int employeeID, INDEX_TYPE index[])
 *	^	This will lookup the record id value based on employee ID parameter
 *
 * @param employeeID | Integer
 *	^	This is the employee ID to lookup
 *
 * @param index[] | INDEX_TYPE
 *	^	This is the index with which we use to lookup the record ID
 *
 * @param count | Integer
 *	^	This is the number of records in the current index.
 *
 * @return Integer
 *	^	This will return the record id.  If it doesn't find the employee, it
 *		will return a -99
 *	D	-99
 */
int get_RID(int employeeID, INDEX_TYPE index[], int count){

	// Need a counter for number of records processed
	int i=0;
	
	while(i <= count){
		// Check to see if this is employee
		if(index[i].key == employeeID){
			// If so, return the RID
			return index[i].RID;
		}
		
		// If not, increment the counter
		i++;
	}
	
	// Not found, return -99
	return -99;
	
}

/**@set_employee(EMPL_TYPE empl, const int RID)
 *	^	This will update the employee record
 *
 * @param empl | EMPL_TYPE
 *	^	This is the employee record that you wish to update
 *
 * @param RID | constant Integer
 *	^	This is the position of the employee record you wish to update
 *
 * @note NoremacSkich | 2014/4/7
 *	^	The class put together this function.
 */
void set_employee(EMPL_TYPE empl, const int RID)
{

	// create the file variable
	fstream infile;

	// Assign variable to file stream, and open it in the right mode
	// Need ios::in, otherwise you loose all info in the data
	infile.open (BIN_FILENAME, ios::in|ios::out|ios::binary);
	
	// Check to make sure that the file opened
	if(infile.fail()){
		cout << "The empl.dat file is missing" << endl;
		exit(1);
	}
	
	// seekg and seekp use same pointer for file manipulation
	// record position * record size, starting location
	infile.seekg(RID * sizeof(EMPL_TYPE), ios::beg);
	
	// typecast
	// where you want it, how many bytes do you want?
	infile.write((char *) &empl, sizeof(EMPL_TYPE)); 
	
	// close the file
	infile.close();

}

/**@fun get_employee(const int RID)
 *	^	This will get the employee info from the data file based on the RID
 *
 * @return EMPL_TYPE
 *	^	This will return the employee object
 *
 * @note NoremacSkich | 2014/4/7
 *	^	The class put together this function.
 */
EMPL_TYPE get_employee(const int RID)
{

	// create the file variable
	fstream infile;
	
	// Open the file to read the stored binary
	infile.open(BIN_FILENAME, ios::in|ios::binary);
	
	// Check to make sure that the file opened
	if(infile.fail()){
		cout << "The empl.dat file is missing" << endl;
		exit(1);
	}
	
	// Create a Temporary Employee Record
	EMPL_TYPE temp;
	
	// Get to the record position
	// record position * record size, starting location
	infile.seekg(RID * sizeof(EMPL_TYPE), ios::beg);
	
	// typecast
	// where you want it, how many bytes do you want?
	infile.read((char *) &temp, sizeof(EMPL_TYPE)); 
	
	// close the file
	infile.close();
	
	// return the employee record
	return temp;
}

//int count; // the number of items in the index
// i[] - pass in as a pointer

/**@fun build_index(INDEX_TYPE i[], int & c)
 *	^	This populates the index array, and record count
 *
 * @param i[] | INDEX_TYPE
 *	^	This passes in an blank index array through a pointer
 *	R	This will return a filled in array.
 *
 * @param c | int &
 *	^	This variable will hold the total number of records
 *	R	This will return the total number of records
 *
  * @note NoremacSkich | 2014/4/7
 *	^	The class put together this function.
 */
void build_index(INDEX_TYPE i[], int & c){
	
	// Create a temporary record holder
	EMPL_TYPE temp_emp;
	
	// create file variable
	fstream infile;
	
	// Open the File for input as an binary file
	infile.open(BIN_FILENAME, ios::in|ios::binary);
	
	// Check to make sure that the file opened correctly
	// C++ doesnt throw an error if it can't open a file, it sets a flag 
	// instead
	// Check to make sure that the file opened
	if(infile.fail()){
		cout << "The empl.dat file is missing" << endl;
		exit(1);
	}
	
	// Bring in the record
	// "Prime the Pump"
	// sizeof() is an other operator, will get the size of input
	// Typecast (char *) 
	infile.read( (char *) & temp_emp, sizeof(temp_emp) );
	
	c = 0;
	
	int j = 0;
	// .eof() end of file
	// .fail read somehow failed
	while(!infile.fail() && !infile.eof() && j != 100){
		
		// Store the employee ID
		i[c].key = temp_emp.emplid;
		
		// Store the index location
		i[c].RID = c;
		
		// Increase the index location
		c++;
		
		// Already at the next record, automatically does this.
		infile.read( (char *) &temp_emp, sizeof(temp_emp) );
		
		j++;
	}
	
	// Close the file
	infile.close();
	
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

/**@fun mainMenu(void)
 *	^	This will print out the text for the main menu.
 * 
 */
void mainMenu(void){
	
	// The title
	cout << "Main Menu" << endl;
	
	// Space
	cout << endl << endl;
	
	// The options
	cout << "1) VIEW an Employee" << endl;
	cout << "2) EDIT an Employee's Department Number" << endl;
	cout << "3) LIST all Employees" << endl;
	cout << "4) END THE PROGRAM" << endl;
	
	// Space
	cout << endl << endl;
	
	// Ask for and store the input, then clear the cin buffer
	cout << "Please enter your selection from the menu [1-4] : ";

}// mainMenu

/**@fun empView(void)
 *	^	This will print out the text for viewing the employee
 *
 */
void empView(void){
	
	// Title
	cout << "VIEW EMPLOYEE" << endl;
	
	// Space
	cout << endl << endl;
	
	// Description
	cout << "To view an Employee record you will need to" << endl;
	cout << "enter their Employee ID number." << endl;
	cout << endl;
	cout << "To return to MAIN MENU : enter the number 0" << endl;
	
	// Space
	cout << endl << endl;
	
	// Ask for impID
	cout << "Please enter the Employee ID number : ";
	
} // empView

/**@fun empEditId(void)
 *	^	This will print out the text for the first page of editing the department ID.
 *
 */
 void empEditId(void){

	// Title
	cout << "EDIT" << endl;
	cout << "EMPLOYEE DEPARTMENT NUMBER" << endl;
	
	// Space
	cout << endl << endl;
	
	// Description
	cout << "To EDIT an Employee Department number you will need to" << endl;
	cout << "enter the Employee ID number." << endl;
	cout << endl;
	cout << "To return to MAIN MENU : enter the number 0" << endl;
	
	// Space
	cout << endl << endl;
	
	// Ask for and store the input, then clear the cin buffer
	cout << "Please enter the Employee ID number : ";
	
 }

 /**@fun empEditDep(int impNum, int depNum)
 *	^	This will print out the second page for editing the department ID.
 *	
 * @var impId | Integer
 *	^	This is the employee ID
 *
 * @var depNum | Integer
 *	^	This is the employee's department Number.
 *
 */
void empEditDep(int impId, int depNum){

		// Title
		cout << "EDIT" << endl;
		cout << "EMPLOYEE DEPARTMENT NUMBER cont." << endl;
		
		// Space
		cout << endl << endl;
		
		// Description
		cout << "Employee: " << impId << endl;
		cout << endl;
		cout << "Current Department Number: " << depNum << endl;
		cout << endl;
		cout << "To change the department number you will need to " << endl;
		cout << "enter the new department number" << endl;
		cout << endl;
		cout << "To return to MAIN MENU : enter the number 0" << endl;
		
		// Space
		cout << endl << endl;
		
		// Ask for and store the input, then clear the cin buffer
		cout << "Please enter the NEW department number : ";

} // empEditDep

/**@fun empList(void)
 *	^	This prints out the text for the sorting employees menu.
 *
 */
 void empList(void){
	
	// Title
	cout << "LIST ALL EMPLOYEES" << endl;
	
	// Space
	cout << endl << endl;
	
	// Description
	cout << "You may list all employees ordered in several different" << endl;
	cout << "ways.  All will be in ascending order." << endl;
	cout << "1) List ordered by Employee ID Number" << endl;
	cout << "2) List ordered by Employee Name {sorry not available}" << endl;
	cout << "3) Return to MAIN MENU" << endl;
	cout << endl;
	cout << "Please enter your selection from the menu [1-3] : " << endl;
	
} // empList

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
	
	INDEX_TYPE index[100];
	int count;
	
	// Has the index been sorted?
	bool indexSorted = false;
	// Build the index
	build_index(index, count);
	
	// Test the build index
	//cout << index[1].key << endl;
	/*
	int empID = 100;
	int rid = 0;
	
	cout << "RID: " << rid << endl;
	cout << "count: " << count << endl;
	// Test the get RID
	rid = get_RID(empID, index, count);
	cout << "RID: " << rid << endl;
	cout << "count: " << count << endl;
	
	
	
	// Test the get employee
	EMPL_TYPE empl_rec;
	empl_rec = get_employee(rid);
	
	// Display what we got.
	cout << "Dept: " << empl_rec.dept_num;
	cout << "  Name: " << empl_rec.name;
	cout << "  age : " << empl_rec.age;
	cout << "  emplid : " << empl_rec.emplid << endl;
	
	// Test the write employee
	
	// Change a Value
	empl_rec.age = 4;
	
	// store it into the data file	
	set_employee(empl_rec, rid);
	cout << "Restart to See if age of " << empl_rec.name << " is " << empl_rec.age << endl;
	// Restart program to see if worked
	
	
	// Print out current list
	cout << "Current List" << endl;
	for (int i=0; i<count; i++)
		cout << index[i].key << " " << index[i].RID << endl;
	
	// Sort the list
	sort_index(index, count);
	
	// Print out New list
	cout << "Sorted List" << endl;
	for (int i=0; i<count; i++)
		cout << index[i].key << " " << index[i].RID << endl;
	
	print_Ascending(index, count);
	*/
	
	
	// Variables
	int main_choice;
	int emplid_num;
	int empID;
	int depNum=-99;
	int rid = -100;
	EMPL_TYPE empl_rec; // This is the employee record currently being used

	do{
		// Clear the Screen.
		clearScreen();
		
		// Display the main menu
		mainMenu();
		
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
				// Clear the Screen.
				clearScreen();
				
				// Print the Employee Menu
				empView();
				
				// Store then sanitize their input
				cin >> emplid_num;
				
				// Sanitize the input
				if(cin.fail()){
					
					// It failed, print it out
					cout << "Input Failed, Going to main menu" << endl;
					
					// clear the buffer, then continue
					cin.clear();
					cin.ignore();
					myPause();
					break;
				}

				// If user presses 4, it means they want to go back to main
				// menu
				if(emplid_num==4){
					break; // To the main menu
				}
				
				// Get the rid based on employee ID
				rid = get_RID(emplid_num, index, count);
				
				// Check to make sure that employee exists
				if(rid<0){
					cout << "Employee doesn't exist" << endl;
					// Pause to let user look at output
					myPause();
					break; // to the main menu
				}
				
				empl_rec = get_employee(rid);
				
				// Display what we got.
				cout << "Dept: " << empl_rec.dept_num;
				cout << "  Name: " << empl_rec.name;
				cout << "  age : " << empl_rec.age;
				cout << "  emplid : " << empl_rec.emplid << endl;
				
				// Pause to let user look at output
				myPause();
				
				// Return to main menu
				break;
				
				
			case 2:
				// Clear the Screen.
				clearScreen();
				cin.clear();
				cin.ignore();
				// Display the Edit Employee Menu, Page 1
				empEditId();
				
				// Store then sanitize the input
				cin >> empID;
				cin.clear();
				
				// Sanitize the input
				if(cin.fail()){
					
					// It failed, print it out
					cout << "Input Failed, Going to main menu" << endl;
										
					// clear the buffer, then continue
					cin.clear();
					cin.ignore();
					myPause();
					break;
				}
				
				// Do they want to go back?
				if(empID==0){
					break; // To the main menu
				}
				
				// Get the rid based on employee ID
				rid = get_RID(empID, index, count);
				
				// Check to make sure that employee exists
				if(rid<0){
					cout << "Employee doesn't exist" << endl;
					// Pause to let user look at output
					myPause();
					break; // to the main menu
				}
				
				// We now have the employee ID to lookup
				// Function to lookup the department number of employee
				empl_rec = get_employee(rid);
			
				// Clear the Screen.
				clearScreen();
				
				// Now Display the jEdit Employee Menu, Page 2
				empEditDep(empl_rec.emplid, empl_rec.dept_num);
								
				// Store then sanitize the cin buffer
				cin >> depNum;
				cin.clear();
		
				// Sanitize the input
				if(cin.fail()){
					
					// It failed, print it out
					cout << "Input Failed, Going to main menu" << endl;
										
					// clear the buffer, then continue
					cin.clear();
					cin.ignore();
					myPause();
					break;
				}
				
				// Check to see if they wish to go back to main menu
				if(depNum==0){
					break; // To the main menu
				}
				
				// This is the function that changes the department number.
				empl_rec.dept_num = depNum;
				
				// Get the rid based on employee ID
				rid = get_RID(empID, index, count);
				
				// Check to make sure that employee exists
				if(rid<0){
					cout << "Employee doesn't exist" << endl;
					// Pause to let user look at output
					myPause();
					break; // to the main menu
				}
				
				// Write out the changes to file
				set_employee(empl_rec, rid);
				
				break; // To the main menu
				
				
			case 3:
				
				// This is a new menu, so need another do while loop
				do{
					
					// Clear the Screen.
					clearScreen();
					
					// Display the employee List Menu
					empList();
					
					// Take their menu choice
					cin >> empID;
					
					// Sanitize the input
					if(cin.fail()){
						
						// It failed, print it out
						cout << "Input Failed, Going back to employee list menu" << endl;
												
						// clear the buffer, then continue
						cin.clear();
						cin.ignore();
						myPause();
						// Reset empID
						empID = 0;
						continue;
					}

					//Perform action based on their choice
					switch (empID){
						case 1:
							if(!indexSorted){
								indexSorted = sort_index(index, count);
							}
							print_Ascending(index, count);
							
							// Pause to let user look at output
							myPause();
							
							break;
						case 2:
							cout << "This Feature is not available" << endl;
							// Pause to let user look at output
							myPause();
							break;
						case 3: 
							break; // To the main menu
						default:
							cout << "Wrong Input" << endl;
					}
				}while(empID != 3);
					
				break;
				
				
				
			case 4:
				cout << "End Program" << endl;
				
				break;
			
				
				
				
			default:
				cout << "oops :)" << endl;
		}
	}while(main_choice != 4);
	
	// Exit the program gracefully, without errors
	return 0;
}


