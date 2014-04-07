#include <stdio.h>   // C header files
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <string.h>

#include <cstring>  // using c-string methods
#include <cstdlib>  // exit() ...

/******************************************************************
*   This program is used to do time trials on sort algortihms.
*   It is designed to allow for simple inclusion of additional sorts.
*******************************************************************/

/****************[ Global Constants]****************/
const int CLEAR_LINES = 20;//  # of blank lines used to clear the screen
const int MIN_MENU = 0; //    
const int MAX_MENU = 5; // # of menu options  {MODIFY WHEN NEEDED!!!}
const int MAX_LEVELS=300;   // Used by quicksort() for partitioning
/****************[ Global Variables ]****************/
// This is the file path to the data file. This gets concatanated to later when
// the program parameters are read from the command line.
char file_path[300] = ""; 

int DATA_COUNT=0;     // Number of integers in the file

// Array of numbers
int *data;	          

/***************[ Prototypes ]********************/
void exeTime(timeb *begin, timeb *total);


void saveFile(void);
void myPause(void);
int loadData(char filename[]);

void bubbleSort(void);
void quickSort(int *arr, int elements);
void insertionSort(void);
void selectionSort(void);

void myPause(void);
void myclear(void);
int menu(void);
void dumpData(bool dump, int dumpBeg, int dumpCnt);
int getArgs(int count, char *args[], int *beg, int *cnt, char fileName[], bool *dump);
int main(int argc, char *argv[]);

/**************[exeTime] **********************************
* This function is used to time various part of
* the program. 
*
*To start the timming, pass in the
* address of the BEGIN variable and pass in a
* NULL in the TOTAL location. To end the timing
* and get the total time taken, pass in the address
* of the BEGIN variable again, and pass in the
* address of the TOTAL variable.  The total time
* taken will be passed back in the TOTAL variable.
* NOTE:  Although this function does an excellent 
* job of keeping track of the time, it does depend 
* upon the deprecated function ftime().  I haven't 
* found a good substitute yet.
*
*      ins:      none
*      outs:     none
*      in-outs:  begin - address of start variable
*                total - address of total variable
*      returns:  none
************************************************/
void exeTime(timeb *begin, timeb *total)
{
	timeb end;
	
	if (total == NULL)
	{
		ftime(begin);
	}
	else
	{
		ftime(&end);
		total->time = end.time-begin->time;
		
		if(end.millitm >= begin->millitm)
		{
			total->millitm=end.millitm-begin->millitm;
		}
		else
		{
			total->time--;
			total->millitm=begin->millitm-end.millitm;
		}
	}
}

/************* [loadData] **********************************
* loadData() loads the integers from a file 
* into an array.  The first integer read from
* the file is the number of integers found in 
* the file.  The rest of the data are the 
* integers used for the sort functions.
*
* filename : IN : filename to open
* returns:   0 for success
*	      -1 for failure
* *********************************************/
int loadData(char filename[])
{
	FILE *iFile;
	int i;
	int datum;
	
	char fullname[500];
	
	strcpy(fullname,file_path);
	strcat(fullname,filename);  //  add filename  to path
	// open the file
	if ((iFile=fopen(fullname,"r"))==NULL)
	{
		printf("Error opening %s\n",fullname);
		myPause();
		return -1;
	}
	
	// Grab the number of data items in the file
	fscanf(iFile,"%i",&DATA_COUNT);
	//printf("DATA COUNT IS : %i \n",DATA_COUNT);  //*** K-BACH ADDITION
	//myPause();                                   //*** K_BACH ADDITION
	// Allocate the array on HEAP based upon the DATA_COUNT
	data=new int [DATA_COUNT];
	// check for eoor in allocation
	if (data==NULL)
	{
		printf("Error allocating array\n");
		myPause();
		return -1;
	}
	// Read in numbers and put them into the array
	for (i=0;i<DATA_COUNT;i++) 
	{
		fscanf(iFile,"%i",&datum);
		data[i]=datum;
	}
	// close the file
	fclose(iFile);
	return 0;
}

/*********** [bubbleSort ] **********************************
* bubbleSort() is an elementry sorting routine
* that compares two items and swaps them. It 
* takes the first data item, compares it to
* the next one.  If one is larger, they swap.
* As it moves through the array, it compares 
* the next one to all in the array. 
*
* returns:   nothing
* *******************************************/
void bubbleSort(void)
{
	int i;
	int j;
	int tmp;
	
	// copy data into a temp array to allow more than 1 algorithm use per 
	// program
	int *tmpdata;
	tmpdata=new int [DATA_COUNT];
	for(i=0; i<DATA_COUNT; i++){
		tmpdata[i] = data[i];	
	}
	//------------
	
	// Outer loop 
	for (i=0;i<DATA_COUNT-1;i++)
	{
		// Inner loop to compare against
		for(j=0;j<DATA_COUNT-1-i;j++)
		{
			// check to see if we need to swap
			if (tmpdata[j+1] < tmpdata[j])
			{
				//Perform swap
				tmp=tmpdata[j];
				tmpdata[j]=tmpdata[j+1];
				tmpdata[j+1]=tmp;
			}
		}
	}
	
	// cleanup temp data
	delete []tmpdata;
	//-----------
}

/********************[ quickSort] ***********************
* quickSort() is a very efficient sorting routine
* that partitions its data.  This acts as a 
* 'divide and conquer' system. Each section is
* divided in half.  This is not a recursive
* algorithm.
*
* This public-domain C implementation by Darel Rex Finley.
*  	http://alienryderflex.com/quicksort/
* 	No Fail heading
*
* Example calls:
*    quickSort(&myArray[0],5); // sorts elements 0, 1, 2, 3, and 4
*    quickSort(&myArray[3],5); // sorts elements 3, 4, 5, 6, and 7
*
*  *array:    pointer to array of data : IN
*  elements:  number of elements in array.
*******************************************************/
void quickSort(int *arr, int elements) 
{
	int piv;
	int beg[MAX_LEVELS];
	int end[MAX_LEVELS];
	int i=0;
	int L,R;
	int swap;
	
	// copy data into a temp array to allow more than 1 algorithm use per 
	// program
	int *tmpdata;
	tmpdata=new int [DATA_COUNT];
	for(i=0; i<DATA_COUNT; i++){
		tmpdata[i] = data[i];	
	}
	//------------
	
	// need to reset i
	i=0;
	
	beg[0]=0; 
	end[0]=elements;
	while (i>=0) 
	{
		L=beg[i]; 
		R=end[i]-1;
		if (L<R) 
		{
			piv=tmpdata[L];
			while (L<R) 
			{
				while (tmpdata[R]>=piv && L<R) 
					R--; 
				if (L<R) 
					tmpdata[L++]=tmpdata[R];
				while (tmpdata[L]<=piv && L<R) 
					L++; 
				if (L<R) 
					tmpdata[R--]=tmpdata[L]; 
			}
			tmpdata[L]=piv; 
			beg[i+1]=L+1; 
			end[i+1]=end[i]; 
			end[i++]=L;
			if (end[i]-beg[i] > end[i-1]-beg[i-1]) 
			{
				swap=beg[i]; 
				beg[i]=beg[i-1]; 
				beg[i-1]=swap;
				swap=end[i]; 
				end[i]=end[i-1]; 
				end[i-1]=swap; 
			}
		}
		else {
			i--; 
		}
	}
	
	// cleanup temp data
	delete []tmpdata;
	//-----------
}
// =============================================================
/********* [ Insertion Sort]******************************
* 
* Psuedo
*    for i:= 2 to n do
*       move A[i] forward to the position j <= i such that
*               A[i] < A[k] for j <= k < i, and
*	         either A[i] >= A[j-1] or j = 1
*
*
********************************************************/			 
void insertionSort(void)
{
	int i;
	int j;
	int value;
	
	// copy data into a temp array to allow more than 1 algorithm use per 
	// program
	int *tmpdata;
	tmpdata=new int [DATA_COUNT];
	for(i=0; i<DATA_COUNT; i++){
		tmpdata[i] = data[i];	
	}
	//------------
	
	for(i=1; i<DATA_COUNT;i++)
	{
		value = tmpdata[i];	  
		j=i-1;	  
		while ((j>= 0) && (tmpdata[j] > value))
		{
			tmpdata[j+1]=tmpdata[j];
			j=j-1;
		}
		tmpdata[j+1]=value;
     }
     
     // cleanup temp data
	delete []tmpdata;
	//-----------
}
// =========================================================
void selectionSort(void)
{
	int i;
	int j;
	int min;
	int t;
	
	// copy data into a temp array to allow more than 1 algorithm use per 
	// program
	int *tmpdata;
	tmpdata=new int [DATA_COUNT];
	for(i=0; i<DATA_COUNT; i++){
		tmpdata[i] = data[i];	
	}
	//------------
	
	for (i=0; i< DATA_COUNT; i++)
	{ 
		min=i;
		for (j=i; j < DATA_COUNT; j++)
		{
			if (tmpdata[min] > tmpdata[j])
				min=j;
			t=tmpdata[min];
			tmpdata[min]=tmpdata[i];
			tmpdata[i]=t;
		}// for
	}//for 
	
	// cleanup temp data
	delete []tmpdata;
	//-----------
}// selectionSort

/************** [myPause] ******************************
* myPause() is a routine to print a prompt
* and get a user input.  This is so that
* when something is sent to the screen,
* it can be seen before the screen is
* cleared
*
* returns:   nothing
* ******************************************/
void myPause(void)
{
	int key;
	printf("\nEnter the 1 key to continue..");
	scanf("%i",&key);
	printf("\n");
}

/**************[ clear] ******************************
* my_clear() is a function to clear the screen
* using a platform agnostic algorithm:  send
* several carriage returns to the screen.
*
* returns:   nothing
* ******************************************/
void myclear(void)
{
	int i;
	for (i=0;i<CLEAR_LINES;i++)
	{
		printf("\n");
	}
}

/************** [menu]  *********************************
* menu() displays a menu of the choices that 
* the user may make.  It also gets the choice 
* that the user makes ensuring that the key
* is correct before exiting and passing the
* choice back.
*
* returns:   user choice as key
* *********************************************/
int menu(void)
{
	int key=-1; // menu value picked
	while ((key < MIN_MENU) || (key > MAX_MENU))
	{
		myclear();
		printf("***********************************\n");
		printf("*      Big O demo using sorts     *\n");
		printf("*---------------------------------*\n");
		printf("* Bubble Sort complexity = N^2    *\n");
		printf("* Quick Sort complexity = N*logN  *\n");
		// Add new stuff                                                                                              //** K-BACH MODIFICATIONS
		printf("* Insertion Sort =   N^2          *\n");
		printf("* Selection Sort =   N^2          *\n");
		//    printf("* Comparisons for 200,000 nums:   *\n");
		//    printf("*   Bubble Sort = 40,000,000,000  *\n");
		//    printf("*   Quick Sort  =      1,060,206  *\n");
		printf("***********************************\n");
		printf(" 1. Bubble Sort \n");
		printf(" 2. Quick Sort\n");
		printf(" 3. Insertion Sort\n");
		printf(" 4. Selection Sort\n");	
		printf(" 5. Sort With All\n");
		// if more menu item added then update global constant MAX_MENU
		printf(" 0. Exit \n\n\n");
		printf(" Enter a choice: ");
		scanf("%i",&key);
	}
	return key;
}

/*****************************************************
* dumpData() allows the user to dump a specific part
* of the array to see if it is sorted.
*
* This will check to see if it needs to dump first. If
* it is supposed to dump, it will dump the array 
* starting at data[dumpBeg] and dump the next dumpCnt
* numbers.
*
* dump: true=we dump, false=we don't dump.
* dumpBeg: The array index to start dumping.
* dumpCnt: The quantity of numbers to dump.
*****************************************************/
void dumpData(bool dump, int dumpBeg, int dumpCnt)
{
	int i;
	
	if (dump == true)
	{
		for(i=0;i<dumpCnt;i++)
		{
			printf("%i\n",data[dumpBeg+i]);
		}
	}
}

/***************************************************
* getArgs() parses the command line arguments using
* the getopt() function.  Expected arguments back:
*    numEls:	Number random numbers desired
*    fileName: The file to store the data
*    modNum:	The modulos number determining upper
*		bound on the random numbers
*    sort:	boolean determinging if the array
*		should be sorted before storing.
* IN: count	number of arguments (from argc)
* IN: args[]	Actual arguments (argv[])
***************************************************/
int getArgs(int count, char *args[], int *beg, int *cnt, 
	char fileName[], bool *dump)
{
	int c;
	bool b=false;
	bool e=false;
	int index=1;
	int dummy;
	
	if (count <2)
	{
		printf("Too few arguments\n");
		printf( "%s  -f <infile> [-d -b <begin> -c <count>]\n",args[0]);
		printf("Options mean:\n");
		printf("    -f = Input file of integers\n");
		printf("    -d = dump specified integers\n");
		printf("    -b = begin = array index to start dumping\n");
		printf("    -c = quantity to dump\n");
		return -1;
	}
	while (index < count)
	{
		// printf("arg=%s\n",args[index]);  // **** K-BACH  MODIFICATION
		// Check for the input file option
		if ((strncmp(args[index],"-f",2))==0)
		{
			strncpy(fileName, args[index+1],15);
			index=index+1;
		}
		// Check for the dump option
		else if ((strncmp(args[index],"-d",2))==0)
		{
			*dump=true;
		}
		// Check for starting array index for dump
		else if ((strncmp(args[index],"-b",2))==0) 
		{
			*beg=atoi(args[index+1]);
			b=true;
			index=index+1;
		} 
		// Check for the quantity to dump
		else if ((strncmp(args[index],"-c",2))==0)
		{
			*cnt=atoi(args[index+1]);
			e=true;
			index=index+1;
		}
		else {
			printf("%s: invalid option\n",args[index]);
			exit(-1);
		}
		index++;
	}
	if (*dump == true)
		if ((b && e) == false)
		{
			printf("If dumping, both begining number and quantity are required\n");
			return -1;
		}
		return 0;
}

/********** [main] **************************************
* main() is the main driver for any C/C++ program.
* This one takes in one command line arguement 
* which is the data file that the program used
* to fill the array for sorting.
*
* argc:  IN: number of command line arguements
* argv:  IN: Array of strings containing the 
*	      command line arguements
* returns: exit status (usually 0)
* *********************************************/
int main(int argc, char *argv[])
{
	// argc - the number of arguments on the comand line 
	//   not counting the program name
	// argv[] - array of cstrings holding all the arguments 
	//   on the command line
	
	int key=-1;         // menu value returned
	
	timeb begin;        // holds beginning time of sort
	timeb total;        // holds total time of sort
	
	int dummy;          // used in switch to allow defualt:
	
	char fName[300]={0}; // The path to the data file
	
	int pkey;           // this version of quicksort always returnsd true
	bool status;        // so pkey and status not need at this time
	
	int dumpBeg=0;
	int dumpCnt=0;
	
	bool dump=false;
	
	if (getArgs(argc, argv, &dumpBeg, &dumpCnt, fName,&dump) < 0)
	{
		return -1;
	}
	//	printf("dumpBeg=%d,dumpCnt=%i,fName=%s\n",dumpBeg,dumpCnt,fName);  // *** K_BACH MODIFICATION
	
	// Load data into the array once, copy array for each algorithm test
	if ((loadData(fName)) == -1)
		return -1;
	
	// perform menu and function until 0 is selected
	while (key != 0)
	{
		// get menu pick
		key=menu();
		// process menu pick
		switch (key)
		{
		case 0:
	          // end the program
	          exit(EXIT_SUCCESS);
	     case 1:
			// Start the timer
			exeTime(&begin,NULL);
			// Run the sort
			bubbleSort();
			// Stop timer
			exeTime(&begin,&total);
			// display stats
			printf("\nBubble sort sorted %d numbers in %d sec %d millisec\n",
				DATA_COUNT, total.time,total.millitm);
			break;
		case 2:
			// Start timer
			exeTime(&begin,NULL);
			// Run the sort
			quickSort(&data[0],DATA_COUNT);
			// Stop the timer
			exeTime(&begin,&total);
			// Check for failure on quick sort routine
			printf("\nQuick sort sorted %i numbers in %i sec %i millisec\n",
				DATA_COUNT, total.time,total.millitm);
			break;
		case 3:
			// Start the timer
			exeTime(&begin,NULL);
			// Run the sort
			insertionSort();
			// Stop timer
			exeTime(&begin,&total);
			// display stats
			printf("\nInsertion sort sorted %d numbers in %d sec %d millisec\n",
				DATA_COUNT, total.time,total.millitm);
			break;	  
		case 4:
			// Start the timer
			exeTime(&begin,NULL);
			// Run the sort
			selectionSort();
			// Stop timer
			exeTime(&begin,&total);
			// display stats
			printf("\nSelection sort sorted %d numbers in %d sec %d millisec\n",
				DATA_COUNT, total.time,total.millitm);
			break;	  
			// If more sorts added then add more cases and also update menu function 
		case 5:
			// Test all sorts at once
			
			// Clear the Screen
			myclear();
			
			// First Display the number of numbers in the file
			printf("Total numbers in file: %i\n", DATA_COUNT);
			
			//=======================
			// First the bubble sort
			//=======================
			
			// Start the timer
			exeTime(&begin,NULL);
			// Run the sort
			bubbleSort();
			// Stop timer
			exeTime(&begin,&total);
			// display stats
			printf("\nBubble Sort : %d millisecs\n",
				total.time * 100 + total.millitm);
			
			//=====================
			// Then the Quick sort
			//=====================
			
			// Start timer
			exeTime(&begin,NULL);
			// Run the sort
			quickSort(&data[0],DATA_COUNT);
			// Stop the timer
			exeTime(&begin,&total);
			// Check for failure on quick sort routine
			printf("\nQuick Sort : %d millisecs\n",
				total.time * 100 + total.millitm);
			
			//================================
			// Followed by the Insertion Sort
			//================================
			
			// Start the timer
			exeTime(&begin,NULL);
			// Run the sort
			insertionSort();
			// Stop timer
			exeTime(&begin,&total);
			// display stats
			printf("\nInsertion Sort : %d millisecs\n",
				total.time * 100 + total.millitm);
			
			//=================================
			// Then finally the Selection Sort
			//=================================
			
			// Start the timer
			exeTime(&begin,NULL);
			// Run the sort
			selectionSort();
			// Stop timer
			exeTime(&begin,&total);
			// display stats
			printf("\nSelection Sort : %d millisecs\n",
				total.time * 100 + total.millitm);
			
			
		default:
			// needed to prevent the compiler from complaining about
			// having a default with nothing in it.
			dummy=1;
		}

		myPause();
	}
	// Free the data from the HEAP
	dumpData(dump,dumpBeg,dumpCnt);
	// moved delete data after the loop
	delete []data;
	return EXIT_SUCCESS;  // or  1;
	
}

