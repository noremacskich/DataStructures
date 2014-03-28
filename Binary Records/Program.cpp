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
void empEditDep(int empID); // This will allow user to edit the department number of employee
void testread(void);  // testing only!! reading text lines from file
void create_data_file(void); // Process records and create the binary file
void read_binary_file(void); // testing only!!  look at what is in the Binary file
EMPL_TYPE parse_record_line(char line[]); // parse a line into a record
//========================================================

// FUNCTIONS
/**@fun mainMenu(void)
 *	^	This will be the primary menu for the user to interact with
 * 
 */
void mainMenu(void){
	
	int menuChoice = -99;
	
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
	
	// Ask for input
	cout << "Please enter your selection from the menu [1-4] : __";
	cin >> menuChoice;
	
	switch (menuChoice){
		case 1:
			empView();
			break;
		case 2:
			empEditId();
			break;
		case 3:
			empList();
			break;
		case 4:
			cout << "End Program" << endl;
			exit;
			break;
		default:
			cout << "Default" << endl;
			mainMenu();
	}
}// mainMenu

/**@fun empView(void)
 *	^	This menu screen allows the user to enter the employee ID number to view
 *
 */
 void empView(void){
	
	// Variables
	int empID=-99;
	
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
	
	// Ask for input
	cout << "Please enter the Employee ID number: __";
	
	cin >> empID;
	
	// Do they want to go back?
	if(empID==0){
		mainMenu();
	}else{
		// Lookup the Employee
		cout << "employee lookup" << endl;
	}

} // empView

/**@fun empEditId(void)
 *	^	This menu screen allows the user to enter the employee ID that they wish to edit
 *
 */
 void empEditId(void){
	
	// Variables
	int empID=-99;
	
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
	
	// Ask for input
	cout << "Please enter the Employee ID number: __";
	
	cin >> empID;
	
	// Do they want to go back?
	if(empID==0){
		return;
	}else{
		// Edit the department number
		cout << "Enter Employee ID" << endl;
		empEditDep(empID);
	}
	
	// Lookup Employee department number
	int depNum = 55; //empLookup(empid);
	
	// Title
	cout << "EDIT" << endl;
	cout << "EMPLOYEE DEPARTMENT NUMBER cont." << endl;
	
	// Space
	cout << endl << endl;
	
	// Description
	cout << "Employee: " << empID << endl;
	cout << endl;
	cout << "Current Department Number: " << depNum << endl;
	cout << endl;
	cout << "To change the department number you will need to " << endl;
	cout << "enter the new department number" << endl;
	cout << endl;
	cout << "To return to MAIN MENU : enter the number 0" << endl;
	
	// Space
	cout << endl << endl;
	
	// Ask for input
	cout << "Please enter the NEW department number: __";
	
	cin >> empID;
	
	// Do they want to go back?
	if(empID==0){
		return;
	}else{
		// Change the department number.
		cout << "New Department Number" << endl;
	}

} // empEditDep

/**@fun empList(void)
 *	^	This menu screen allows the user to print out a list of employees by id or name.
 *
 */
 void empList(void){
	
	// Variables
	int empID=-99;
	
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
	
	// Ask for input
	cout << "Please enter the Employee ID number: __";
	
	cin >> empID;
	
	// Do they want to go back?
	if(empID==3){
		return;
	}else if(empID==2){
		// Order by ID
		cout << "Order by ID" << endl;
	}else if(empID==3){
		// Order by Name
		cout << "Order by Name" << endl;
	}else{
		// Do Nothing
		cout << "Not an option" << endl;
	}

} // empList

/**@fun menuContinue()
 *	^	This will ask the user if they wish to continue
 * @return Bool
 * 
 */
bool menuContinue(){
	
	// Variables
	bool next = false;
	
	// Ask for input
	cout << "Do you wish to continue? (Y/N)";
	
	// Store input
	cin >> next;
	
	if(next){
		mainMenu();
	}
 }
// ====== main driver ==============================
int main(void)
{
	do{
		mainMenu();
		
	}while(menuContinue());
	
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



