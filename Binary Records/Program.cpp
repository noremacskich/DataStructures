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

// =================   PROTOTYPES ========================
int main(void); // program main driver
void mainMenu(void); // This is the main menu
void empView(void); // Enter ID Number to view employee
void empList(void); // This lists out the employees in ascending order
void empEditId(void); // This will allow user to select an employee ID to edit
bool menuContinue(void); // This will ask user if s/he wants to continue
void clearScreen(void); // Quick and dirty clear screen function
void testread(void);  // testing only!! reading text lines from file
void create_data_file(void); // Process records and create the binary file
void read_binary_file(void); // testing only!!  look at what is in the Binary file
EMPL_TYPE parse_record_line(char line[]); // parse a line into a record
//========================================================

// FUNCTIONS
/************** [myPause] ******************************
* myPause() 
*
* returns:   nothing
* ******************************************/

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
	cout << "Please enter your selection from the menu [1-3]" << endl;
	
	// Space
	cout << endl << endl;
	
	// Ask for and store the input, then clear the cin buffer
	cout << "Please enter the Employee ID number : ";


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
	// Variables
	int main_choice;
	int emplid_num;
	int empID;
	int depNum=-99;

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
				
				// Grab their choice
				cin >> emplid_num;
				
				// If user presses 4, it means they want to go back to main
				// menu
				if(emplid_num==4){
					break; // To the main menu
				}
				
				// call the function to handle the logic
				cout << "Looked up Employee " << emplid_num << "." << endl;
				
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
				
				// Do they want to go back?
				if(empID==0){
					break; // To the main menu
				}
				
				// We now have the employee ID to lookup
				// Function to lookup the department number of employee
				depNum=55;
							
				// Clear the Screen.
				clearScreen();
				
				// Now Display the jEdit Employee Menu, Page 2
				empEditDep(empID, depNum);
				
				// Store then sanitize the cin buffer
				cin >> depNum;
				cin.clear();
		
				// Check to see if they wish to go back to main menu
				if(depNum==0){
					break; // To the main menu
				}
				
				// This is the function that changes the department number.
				cout << "New Department Number " << depNum <<endl;
				
				// Pause to let user look at output
				myPause();
				
				break; // To the main menu
				
				
			case 3:
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
							cout << "Order by ID" << endl;
							
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



