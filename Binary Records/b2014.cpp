#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
//===============================================================
//   PROGRAM:  PRE-WORK for Assignment #2
//   AUTHOR :  your name
//   DUE    :  N/A
//   DESCRIPTION:
//          This program wil be used to create a test file of records to
//    be used in Assignment #2 (Spring 2014)
//===============================================================
using namespace std;

// GLOBAL CONSTANT ====================================
const int MAXNAME = 31; // Empl names 30 in length + 1, can have spaces
const int MAXLINE = 81; // Emply data line from text file  80 in length +1, comma delimited

char TEXT_FILENAME[] = "a2.txt"; //text file name
char BIN_FILENAME[] = "empl.dat";// binary file name

// GLOBAL TYPE DEF  =====================================

// employee structure def
struct EMPL_TYPE
{
	int dept_num;
	char name[MAXNAME];
	int age;
	int emplid;		// is a unique key for indexing
};

// =================   PROTOTYPES ========================
int main(void); // program main driver
void testread(void);  // testing only!! reading text lines from file
void create_data_file(void); // Process records and crerate the binary file
void read_binary_file(void); // testing only!!  look at what is in the Binary file
EMPL_TYPE parse_record_line(char line[]); // parse a line into a record
//========================================================

// FUNCTIONS

// ====== main driver ==============================
int main(void)
{
	
	testread();  // see what is read form the text file
	
	create_data_file(); // create the binary file
	
	read_binary_file( );  // look at what is inside the binary file
	
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
	// make temp_arg a C String
	temp_arg[j] = '\0';  
	// atoi() convert char to integer
	parsed_record.age = atoi(temp_arg);  
	// assign to age in record
	//arg 4;
	j=0;
	while(line[i] != '\0')
	{
		temp_arg[j] = line[i];
		i++; j++;
	}
	// make temp_arg a C string
	temp_arg[j] = '\0';  
	// atoi() convert char to integer
	parsed_record.emplid = atoi(temp_arg); 
	// assign to emplid in record	
	
	return parsed_record;  // return the filled record
	
}
// ====== create_data_file=========================
void create_data_file(void)
{
	char input_line[MAXLINE];
	
	// assign the file variable for input
	ifstream empl_infile;    
	
	// open the file
	empl_infile.open(TEXT_FILENAME); 
	
	//record to be filled and then written out
	EMPL_TYPE empl_rec; 
	
	// assign file variable for output
	fstream empl_outfile; 
	
	// open file an se mode for Binary file
	// output  and input(to not truncate)
	empl_outfile.open(BIN_FILENAME,ios::out|ios::binary); 
	
	// attempt to get a line from text file
	while (!empl_infile.get(input_line,MAXLINE).eof()) 
	{
		// move past more than 81 characters if they exist on line
		empl_infile.ignore(256,'\n');  
		//parse the text line into a record
		empl_rec = parse_record_line(input_line); 
		// write the record out to the Binary file
		empl_outfile.write((char *) &empl_rec, sizeof(empl_rec)); 
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


