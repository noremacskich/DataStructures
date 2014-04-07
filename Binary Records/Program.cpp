#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
//===============================================================
//   PROGRAM:  Assignment #2
//   AUTHOR :  Cameron Hicks
//   DUE    :  N/A
//   DESCRIPTION:
//          This program wil be used to create a test file of records to
//    be used in Assignment #2 (Spring 2014)
//===============================================================
using namespace std;

// GLOBAL CONSTANT ====================================
const int MAXNAME = 31; // Empl names 30 in length + 1, can have spaces
const int MAXLINE = 81; // Emply data line from text file  80 in length +1, comma delimited : Don't need this, only reading from data file

char TEXT_FILENAME[] = "a2.txt"; //text file name : Don't Need anymore
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
int main(void); // program main driver
void mainMenu(void); // This is the main menu
void empView(void); // Enter ID Number to view employee
void empList(void); // This lists out the employees in ascending order
void empEditId(void); // This will allow user to select an employee ID to edit
bool menuContinue(void); // This will ask user if s/he wants to continue
void myPause(void); // This waits for the user input
void clearScreen(void); // Quick and dirty clear screen function
void testread(void);  // testing only!! reading text lines from file
void create_data_file(void); // Process records and create the binary file
void read_binary_file(void); // testing only!!  look at what is in the Binary file
EMPL_TYPE parse_record_line(char line[]); // parse a line into a record
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
	while (i<=count)
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
 
/**@sort_index(INDEX_TYPE index[], int count)
 *	^	This will sort the list in Ascending Order
 *
 * @param index[] | INDEX_TYPE
 *	^	this is the index to sort
 *	R	This will modify inputed list.
 *
 * @param count | Constant Integer
 *	^	This is the total number of records in the index
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

/**@build_index(INDEX_TYPE i[], int & c)
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
		
	// .eof() end of file
	// .fail read somehow failed
	while(!infile.fail() && !infile.eof()){
		
		// Store the employee ID
		i[c].key = temp_emp.emplid;
		
		// Store the index location
		i[c].RID = c;
		
		// Increase the index location
		c++;
		
		// Already at the next record, automatically does this.
		infile.read( (char *) &temp_emp, sizeof(temp_emp) );
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
 *	^	This will be the primary menu for the user to interact with
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
 *	^	This menu screen allows the user to enter the employee ID number to view
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
 *	^	This menu screen allows the user to enter the employee ID that they 
 *		wish to edit.
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
 *	^	This will display the 2nd page of the edit employee menu
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
 *	^	This menu screen allows the user to print out a list of employees 
 *		by id or name.
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

/**@fun menuContinue()
 *	^	This will ask the user if they wish to continue.  It will ask a max of
 *		20 times for the correct input, before it will quit the program.
 * 
 * @return Bool
 * 	T	This will return the user to the main menu
 *	F	This will exit the program
 */
bool menuContinue(void){
	
	// Variables
	string next;
	int ground = 0;
	
	// Ask them if they wish to continue
	cout << "Do you wish to continue? (Y/N) : ";
	
	// This will ask them 20 times for the correct input (Y, y, N, n).
	while(ground<20){
				
		// Store, then clear cin
		cin >> next;
		cin.clear();
		
		// Check the input
		if(next.find("Y")!=string::npos || next.find("y")!=string::npos)
			return true;
		if(next.find("N")!=string::npos || next.find("n")!=string::npos)
			return false;
		
		// Ask them again, if they are wrong.
		cout << "Please enter (Y/N) : ";
		
		// Increment this so this while loop isn't infinite.
		ground++;
	}
	
	// if they reach the ground, quit the program
	return false;
}//menuContinue

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
	int empID = 5;
	int rid = 0;
	
	// Test the get RID
	rid = get_RID(empID, index, count);
	cout << "RID: " << rid << endl;
	
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
	EMPL_TYPE empl_rec; // This is the employee record currently being used

	do{
		// Clear the Screen.
		clearScreen();
		
		// Display the main menu
		mainMenu();
		
		// Get their choice
		cin >> main_choice;
		
		switch(main_choice){
			
			
			case 1: 
				// Clear the Screen.
				clearScreen();
				
				// Print the Employee Menu
				empView();
				
				// Store then sanitize their input
				cin >> emplid_num;
				cin.clear();
				
				// Now Sanitize the input
				
				// If user presses 4, it means they want to go back to main
				// menu
				if(emplid_num==4){
					break; // To the main menu
				}
				
				// call the function to handle the logic
				empl_rec = get_employee(get_RID(emplid_num, index, count));
				
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
				
				// Display the Edit Employee Menu, Page 1
				empEditId();
				
				// Store then sanitize the input
				cin >> empID;
				cin.clear();
				
				// Sanitize the input
				
				
				// Do they want to go back?
				if(empID==0){
					break; // To the main menu
				}
				
				// We now have the employee ID to lookup
				// Function to lookup the department number of employee
				empl_rec = get_employee(get_RID(empID, index, count));
			
				// Clear the Screen.
				clearScreen();
				
				// Now Display the jEdit Employee Menu, Page 2
				empEditDep(empl_rec.emplid, empl_rec.dept_num);
				
				// Store then sanitize the cin buffer
				cin >> depNum;
				cin.clear();
		
				// Sanitize the input
				
				// Check to see if they wish to go back to main menu
				if(depNum==0){
					break; // To the main menu
				}
				
				// This is the function that changes the department number.
				empl_rec.dept_num = depNum;
				
				// Write out the changes to file
				set_employee(empl_rec, get_RID(empID, index, count));
				
				// Display the changes
				
				
				// Pause to let user look at output
				myPause();
				
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
					cin.clear(); // Clear the cin buffer
				
					//Perform action based on their choice
					switch (empID){
						case 1:
							sort_index(index, count);
							print_Ascending(index, count);
							
							// Pause to let user look at output
							myPause();
							
							break;
						case 2:
							cout << "Order by Name" << endl;
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


	/*testread();  // see what is read form the text file
	
	create_data_file(); // create the binary file
	
	read_binary_file( );  // look at what is inside the binary file
	*/
	return 0;
}

// ====== testread ======================================
void testread(void)
{
	char input_line[MAXLINE];
	
	ifstream empl_infile;  		// declare file variable for input
	empl_infile.open(TEXT_FILENAME); // assign physical file to FV and open
	
	cout << "====== TEXT FILE CONTENT  ========" << endl;
	while(!empl_infile.get(input_line,MAXLINE).eof())  // attempt to read next line up to maxline characters
	{
		cout << input_line << endl;
		
		empl_infile.ignore(256,'\n');  // clear any char remaining on taht line
	}
	cout << "==================================" << endl;
	empl_infile.close(); // close the file
}	

// ====== parse_record_line (down and dirty way :) ====================
EMPL_TYPE parse_record_line(char line[])
{
	// the line parameter is one text line from the text file as a C string
	EMPL_TYPE parsed_record;
	int i = 0;
	int j = 0;
	
	char temp_arg[MAXLINE];
	//arg 1
	while(line[i] != ',') //build temp_arg up to comma
	{
		temp_arg[j] = line[i];
		i++; j++;
	}
     
	i++; // move by the comma
	temp_arg[j] = '\0'; // make tem_arg a C string
	parsed_record.dept_num = atoi(temp_arg); // atoi() convert char string to integer 
	// and assign to dept_num in record
	//arg 2
	j = 0;
	while(line[i] != ',') // build argument up to comma
	{
		temp_arg[j] = line[i];
		i++; j++;
	}
     
	i++;  // move by the comma
	temp_arg[j] = '\0';	 // make temp_arg a C String
	strcpy(parsed_record.name,temp_arg); //copy C string to name C string in record
	
	// arg 3
	j=0;
	while(line[i] != ',') // build argument up to comma
	{
		temp_arg[j] = line[i];
		i++; j++;
	}
	i++;
	temp_arg[j] = '\0';  // make temp_arg a C String
	parsed_record.age = atoi(temp_arg);  // atoi() convert char to integer
	// assign to age in record
	//arg 4;
	j=0;
	while(line[i] != '\0')
	{
		temp_arg[j] = line[i];
		i++; j++;
	}
	temp_arg[j] = '\0';  // make temp_arg a C string
	parsed_record.emplid = atoi(temp_arg); // atoi() convert char to integer
	// assign to emplid in record	
	
	return parsed_record;  // return the filled record
	
}
// ====== create_data_file=========================
void create_data_file(void)
{
	char input_line[MAXLINE];
	ifstream empl_infile;    // assign the file variable for input
	empl_infile.open(TEXT_FILENAME); // open the file
	
	EMPL_TYPE empl_rec; //record to be filled and then written out
	fstream empl_outfile; // assign file variable for output
	empl_outfile.open(BIN_FILENAME,ios::out|ios::binary); // open file an se mode for Binary file
	// output  and input(to not truncate)
	
	while (!empl_infile.get(input_line,MAXLINE).eof()) // attempt to get a line from text file
	{
		empl_infile.ignore(256,'\n');  // move past more than 81 characters if they exist on line
		empl_rec = parse_record_line(input_line); //parse the text line into a record
		empl_outfile.write((char *) &empl_rec, sizeof(empl_rec)); // write the record out to the Binary file
	}
	
	empl_infile.close();  // close the text file
	empl_outfile.close(); // close the binary file
}
// ====== read_binary_file ============================
void read_binary_file(void)
{
	EMPL_TYPE   empl_rec;  // record to be read into from file
	fstream empl_infile;   // file variable (no mode set)
	empl_infile.open(BIN_FILENAME,ios::in|ios::binary); // open binary file for reading
	empl_infile.read((char *) &empl_rec,sizeof(empl_rec)); //attempt to read in a record
	cout << endl;
	cout << "===== BINARY FILE CONTENT =================" << endl;
	while (!empl_infile.eof())  // while the last thing read was not the End Of File marker
	{
		cout << "Dept: " << empl_rec.dept_num;
		cout << "  Name: " << empl_rec.name;
		cout << "  age : " << empl_rec.age;
		cout << "  emplid : " << empl_rec.emplid << endl;
		
		empl_infile.read((char *) &empl_rec,sizeof(empl_rec));  // attempt to read in the next record
	}
	cout << "==========================================" << endl;
	empl_infile.close(); // close the file
}



