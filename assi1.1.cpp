#include <iostream>
//#include <string>
#include <sstream>
using namespace std;

/*******************************************
  Author  : Cameron Hicks
  Program : Memory Manager
  Due Date: Feb 13th  11:00 AM (CST)
  Course  : CSC 300 Data Structures
*******************************************/
bool debug2 = false;
// GLOBAL DATA STRUCTURES =======================
typedef struct FREE_NODE * FREEPTR;
typedef struct ALLOCNODE * ALLOCPTR;

struct FREE_NODE  // FREE LIST NODES
{
  int start_byte;
  int end_byte;
  int size;
  
  FREEPTR next;
};
struct ALLOCNODE // ALLOCTADED LIST NODES
{
  int start_byte;
  int end_byte;
  int size;
  int id;
  
  ALLOCPTR next;
};
// ======   GLOBAL DATA =========================
FREEPTR  freelist = NULL;  // the FREE link list
ALLOCPTR alloclist = NULL; // the ALLOCATED link list
int total_memory_managed = 0; // the amount of memory managed

//======   PROTOTYPES ===========================
//--- test only ---
void dump_freelist(void);
void dump_alloclist(void);

//--- utility ---
void free_zeros(void);
void printFree(FREEPTR printlink);
void printAlloc(ALLOCPTR printlink);

//--- interface ---
void init_memory_manager(const int amount);
int allocate_memory(const int job, const int amount);
void release_memory(const int job);
int total_free(void);
int total_allocated(void);
int largest_free(void);
int job_allocated(const int job);
void report_memory(void);
void report_jobs(void);

//======= TESTING ONLY FUNCTIONS ====================
void dump_freelist(void)
{ FREEPTR curLink = freelist; // temp pointer to list
  cout << "==================" << endl;
  cout << "  FREE LIST DUMP  " << endl;
  cout << "==================" << endl;
  cout << "Start : End : Size " << endl;
  while (curLink !=NULL)
  {
    cout << curLink->start_byte << " : ";
	cout << curLink->end_byte << " : ";
	cout << curLink->size << endl;
	curLink = curLink->next; //move pointer to next node (or NULL)
  }
}
//----------------------
void dump_alloclist(void)
{ ALLOCPTR curLink = alloclist; // temp pointer to list
  cout << "========================" << endl;
  cout << "  ALLOCATED LIST DUMP  " << endl;
  cout << "========================" << endl;
  cout << "Start : End : Size : ID" << endl;
  
  while (curLink !=NULL)
  {
    cout << curLink->start_byte << " : ";
	cout << curLink->end_byte << " : ";
	cout << curLink->size << " : ";
	cout << curLink->id << endl;
	curLink = curLink->next; //move pointer to next node (or NULL)
  }
}
/*
ALLOCPTR curLink = alloclist; // temp pointer to list
FREEPTR curLink = freelist; // temp pointer to list

while (curLink !=NULL)
{
	curLink->start_byte << " : ";
	curLink->end_byte << " : ";
	curLink->size << " : ";
	curLink->id << endl;
	curLink = curLink->next; //move pointer to next node (or NULL)
}
*/


//======= UTILITY FUNCTIONS ====================
void log(string statement, bool local=false){
	bool debug = true;
	if(debug && local){
		cout << endl << statement << endl << endl;
	}
}

void free_zeros(void){
	bool debug=false;
	log("free_zeros function", debug);
	
	log("Checking for links in chain", debug);
	//Check for links in the chain
	if(freelist==NULL){
		log("There are no links", debug);
		return;
	}
	log("There are links", debug);
	
	log("Creating Pointers", debug);
	FREEPTR curLink = freelist; // this is the link that we are dealing with
	FREEPTR prevLink = freelist; // this is the last link that we dealt with
	
	
	log("going into while loop", debug);
	while (curLink !=NULL)
	{
		log("Checking if link size is zero", debug);
		// if this link is empty
		if(curLink->size == 0){
			log("Link size is zero", debug);
			
			log("Special Cases", debug);
			
			if(curLink == prevLink){
				log("This is the first link in chain", debug);
				
				if(curLink == prevLink){
					log("Is it also the last link in the chain?", debug);
					if(curLink->next == NULL){
						
						log("Yes, unlinking link from chain", debug);
						freelist = NULL;
						
						log("removing the link", debug);
						delete curLink;
						
						log("exiting the loop", debug);
						break;
					}else
					// Or is it just the first?
					if(curLink->next != NULL){
						log("No, just the first.", debug);
						
						log("remove the link from the chain", debug);
						freelist = curLink->next;
						
						log("delete the link", debug);
						delete curLink;
						
						log("Get back to beginning of chain", debug);
						curLink = freelist;
						prevLink = freelist;
						//break;					
					}
				}
				
			} else
			
			// Link is in the middle
			if(prevLink != NULL && curLink->next !=NULL){
				log("The link is in the middle", debug);
				
				log("Unhook the link from the chain", debug);
				prevLink->next = curLink->next;
				
				
				log("Dispose of link", debug);
				delete curLink;
				
				log("Get back to the chain", debug);
				curLink = prevLink;
			
			} else
			
			// Last link in the chain
			if(curLink->next == NULL){
				log("This is the last link in the chain", debug);
				
				log("unhook link from chain", debug);
				prevLink->next == NULL;
				
				log("Dispose of link", debug);
				delete curLink;
				
				log("Since this is the last link, we can break out", debug);
				break;
			}
		}
		log("Link size is not zero", debug);
		
		log("Moving to next link in chain", debug);
		prevLink = curLink;			// Keep pointer to current link
		curLink = curLink->next;	// Move to next link
	}
	log("end free_zeros", debug);
}

void clumpFree(void){
	bool debug = true;
	log("enterng clumpFree(void)", debug);
	
	FREEPTR prevLink = freelist;
	FREEPTR curLink = freelist;
	
	log("Is free list NULL?", debug);
	if(freelist == NULL){
		log("Yes, exiting the clumpFree(void)", debug);
		return;
	}
	
	log("Nope, parsing the free list for clumping", debug);
	while(curLink==NULL){
		
		log("Is this the last link?", debug);
		if(curLink->next == NULL){
			log("Yes, exiting the loop", debug);
			// Kinda hard to clump together a single link . . .
			break;
		}
		
		log("No, can we clump the previous and next links together?", debug);
		if(prevLink->end_byte = curLink->start_byte + 1){
			
			log("Yes, but are we looking at the same link?", debug);
			if(prevLink == curLink){
				log("Yes, this shouldn't happen", debug);
			}
			
			log("No, clumping the links", debug);
			prevLink->end_byte = curLink->end_byte;
			prevLink->size += curLink->size;
			prevLink->next = curLink->next;
			delete curLink;
			
			log("curLink need to point to something!", debug);
			// have it point to the previous link, just in case there are many
			// sections in a row that need to be clumped together 
			curLink = prevLink; 
		}
		
		log("Move to next link", debug);
		prevLink = curLink;
		curLink = curLink->next;
	}
}

void allocSortInsert(ALLOCPTR newLink){
	bool debug = false;
	bool debug3 = false;
	
	ALLOCPTR curLink = alloclist; // temp pointer to list
	ALLOCPTR prevLink = alloclist; // temp pointer to list
	
	log("Entering allocSortInsert");
		if(debug3){
		dump_freelist();
		dump_alloclist();
	}
	log("Is list null?", debug);
	if( curLink == NULL ){
		log("It's null, adding to list", debug);
		alloclist = newLink;
		newLink->next = NULL;
	}else{
		// this will also cover the 1 link scenario
		log("No, parsing the chain", debug);
		while ( curLink != NULL )
		{

			log("Does the link go before the current link?", debug);
			if(newLink->end_byte < curLink->start_byte){
				
				log("Yes. Is this the first link?", debug);
				if(curLink == alloclist){
					
					log("Yes, inserting at the front", debug);
					alloclist = newLink;
					newLink->next = curLink;
					prevLink = newLink;
				}else{
					log("No, Is this the last link in the chain?", debug);
					if(curLink->next == NULL){
						log("Yes, adding it to the end", debug);
						curLink->next = newLink;
						newLink->next = NULL;
					}else{
						log("No, we are in the middle of the list", debug);
						prevLink = curLink;
						curLink=curLink->next;
						prevLink->next = newLink;
						newLink->next = curLink;
						prevLink = newLink;
					}
				}
					
				log("Breaking out of loop", debug);
				break;
			}
			log("Is this the last link?", debug);
			if(curLink->next == NULL){
				
				log("Yes, Now does the link go at the end?", debug);
				if(curLink->end_byte < newLink->start_byte){
					
					log("Yes, inserting link at the end", debug);
					curLink->next = newLink;
					newLink->next = NULL;
					log("Breaking the loop", debug);
					break;
				}
			}
			log("No, moving on to next link", debug);
			prevLink = curLink;
			curLink = curLink->next; //move pointer to next node (or NULL)
		}
	}
	if(debug3){
		dump_freelist();
		dump_alloclist();
	}
	
	
	log("Exiting allocSortInsert function", debug);
	return;
}

void freeSortInsert(FREEPTR newLink){
	
	bool debug = true;
	bool debug3 = true;
	
	FREEPTR curLink = freelist; // temp pointer to list
	FREEPTR prevLink = freelist; // temp pointer to list
	
	log("Entering freeSortInsert Function", debug);
	
	if(debug3){
		dump_freelist();
		dump_alloclist();
	}
	
	log("Is list null?", debug);
	if( curLink == NULL ){
		log("It's null, adding to list", debug);
		freelist = newLink;
		newLink->next = NULL;
	}else
	{

		log("No, parsing the chain", debug);
		while ( curLink != NULL )
		{
			log("Does the link go before the current link?", debug);
			if(newLink->end_byte < curLink->start_byte){
				
				log("Yes. Is this the first link?", debug);
				if(curLink == freelist){
					
					log("Yes, inserting at the front", debug);
					freelist = newLink;
					newLink->next = curLink;
					prevLink = newLink;
				}else{
					//log("No, Is this the last link in the chain?", debug);
					//if(curLink->next == NULL){
						//log("Yes, adding it to the end", debug);
						//prevLink->next = newLink;
						//newLink->next = NULL;
					//}else{
						log("No, we are in the middle of the list", debug);
						newLink->next = curLink;
						prevLink->next = newLink;
						/*
						prevLink = curLink;
						curLink=curLink->next;
						prevLink->next = newLink;
						newLink->next = curLink;
						prevLink = newLink;*/
				}
				log("Breaking out of loop", debug);
				break;
			}else
			//log("No, is this the last link?", debug);
			if(curLink->next == NULL){
				
				log("No, Now does the link go at the end?", debug);
				if(curLink->end_byte < newLink->start_byte){
					
					log("Yes, inserting link at the end", debug);
					curLink->next = newLink;
					
					newLink->next = NULL;
					
					log("Breaking the loop", debug);
					break;
				}
			}

			log("No, moving on to next link", debug);
			prevLink = curLink;
			curLink = curLink->next; //move pointer to next node (or NULL)
		}
	}
	if(debug3){
		dump_freelist();
		dump_alloclist();
	}
	
	
	log("Exiting freeSortInsert function", debug);
	return;
}

void printFree(FREEPTR printlink){
	bool debug = false;
	
	log("Entering printFree(printlink)", debug);
	
	log("Create '## - ##' part", debug);
	ostringstream memblock;
	memblock << printlink->start_byte << " - " << printlink->end_byte;
	
	log("Now add the padding and put 'FREE' at the end", debug);
	cout.width(25); 
	cout << left << memblock.str() << "FREE" << endl;
	
	log("Exiting printFree(printlink)", debug);
}

void printAlloc(ALLOCPTR printlink){
	bool debug = false;
	
	log("Entering printAlloc(printlink)", debug);
	
	log("Create '## - ##' part", debug);
	ostringstream memblock;
	memblock << printlink->start_byte << " - " << printlink->end_byte;
	
	log("Now add the padding and put 'FREE' at the end", debug);
	cout.width(25); 
	cout << left << memblock.str() << printlink->id << endl;
	
	log("Leaving printAlloc(printlink)", debug);
}

void deallocate(ALLOCPTR toDelete){
	bool debug = false;
	bool debug3 = false;
	log("deallocate function", debug);
	
	if(debug){
		cout << "Removing"<< endl;
		cout << toDelete->start_byte << " : ";
		cout << toDelete->end_byte << " : ";
		cout << toDelete->size << " : ";
		cout << toDelete->id << endl;
	}
	
	log("Grab pertinent Info from node", debug);
	int start = toDelete->start_byte;
	int end = toDelete->end_byte;
	int size = toDelete->size;
	
	log("Delete the current node", debug);
	delete toDelete;
	
	log("Create Free list Node", debug);
	FREE_NODE * newFree;
	newFree = new FREE_NODE;
	
	log("Add The Attributes", debug);
	newFree->size = size;
	newFree->start_byte = start; 
	newFree->end_byte = end;
	
	log("Add to Free list", debug);
	freeSortInsert(newFree);
	
	//FREEPTR ftmp = freelist;
	//newFree->next = ftmp;
	//freelist = newFree;
	
	
	if(debug3){
		dump_freelist();
		dump_alloclist();
	}
	log("end deallocate", debug);
}

//======= INTERFACE FUNCTIONS ==================
/* @fun init_memory_manager(const int amount)
 *		^	Set the initial data structures for the Memory Manager. 
 * 
 * @param amount | const int 
 * 		^	the number of bytes to be managed 	
 * 
 * @return void
 * 
 * @note
 * 		^	Should set up lists and set the total_memory_managed 
 * 			variable
 */
void init_memory_manager(const int amount)
{
  total_memory_managed = amount;
  // set up the freelist linked list
  freelist = new FREE_NODE;
  freelist -> size = amount;
  freelist -> start_byte = 0;
  freelist -> end_byte = amount -1;
  freelist -> next = NULL;
  // set up the alloclist linked list
  alloclist = NULL;
}
//----------------------
/**@fun allocate_memory(const int job, const int amount)
 * 	^	reflect allocation of memory to a particular job
 * 
 * @param job | const int 
 * 	^	the id of the user (can assume positive integer value) 	
 * 
 * @param amount | const int
 * 	^	then number of bytes asked to allocate
 * 
 * @return int
 * 	^	the number of bytes actually allocated
 * 
 * @note Krebsbach
 *	^	Special Case 1 : amount <= 0 : return 0
 *	^	Special Case 2 : amount > total_memory_managed : return 0
 *	^	Special Case 3 : amount > largest_free() : return 0
 * 
 */
int allocate_memory(const int job, const int amount)
{
	bool debug = false;
	bool debug3 = false;
	
	FREEPTR curLink = freelist; // temp pointer to list
	bool success = false; // Did we allocate the memory?
	
	log("allocate_memory", debug);
	
	log("Is the number less than zero?", debug);
	if(amount<=0){
		
		log("yes, returning zero", debug);
		return 0;
	}
	
	log("No, checking if bigger than allocated memory", debug);
	if(total_memory_managed < amount){
		log("Yes, returning zero");
		return 0;
	}
	
	log("No, now try to allocate it", debug);
	//if(debug){
		cout << endl << "Allocating " << amount << " blocks for job " << job << endl << endl;
	
	
	log("Allocating . . .", debug);
	while (curLink !=NULL )
	{
		// If we found a suitable size
		if(curLink->size >= amount){
			
			log("Modifying Free Node", debug);
			curLink->size -= amount;
			curLink->end_byte -= amount;
			
			log("Creating a new link", debug);
			ALLOCNODE * newLink;
			newLink = new ALLOCNODE;
			
			//===================================
			log("Initializing the link", debug);
			//===================================
			newLink->size = amount;
			newLink->id = job;
			newLink->start_byte = curLink->size;
			newLink->end_byte = newLink->start_byte + amount - 1;
			
			log("Attaching to chain . . .", debug);
			allocSortInsert(newLink);
			
			log("We are successful", debug);
			success=true;
			
			log("Breaking out of loop", debug);
			break;
		}
		
		log("Moving on to next link", debug);
		curLink = curLink->next;
		
	}
	if(debug3){
		cout << endl << "Start : End : Size " << endl;
		cout << curLink->start_byte << " : ";
		cout << curLink->end_byte << " : ";
		cout << curLink->size << endl;
		cout << endl;
		dump_alloclist();
		dump_freelist();
	}
	log("Removing any links of size Zero", debug);
	//===============================
	// Remove any links of size Zero
	//===============================
	free_zeros();
	
	if(success){
		log("Enough Memory", debug);
		log("Exiting function", debug);
		return amount;// return amount of memory allocated
	}else{
		log("Not Enough Memory", debug);
		log("Exiting function", debug);
		return 0;// return 0 if not able to allocate
	}
	
	
}

 /**@fun void release_memory(const int job); 
  * 	^	reflect the dealloction of ALL memory held by a particular job 
  * 
  * @param job | const int
  * 	^	the job whose memory to deallocate
  */ 
void release_memory(const int job){ 
	bool debug = true;
	bool debug2 = false;
	bool debug3 = false;
	
	log("Entering release_memory(job)", debug);
	ALLOCPTR curLink = alloclist; 	// temp pointer to list
	ALLOCPTR lastLink = alloclist;	// temp pointer to previous value
	

	
	if(debug3){
		cout << endl << "Removing jobs with ID of " << job << endl << endl;
	}
	if(alloclist == NULL){
		log("Alloc List Null", debug);
		return;
	}

	// Is this list empty?
	while (curLink !=NULL){
		
		if(debug){
			cout << "Checking:"<< endl;
			cout << curLink->start_byte << " : ";
			cout << curLink->end_byte << " : ";
			cout << curLink->size << " : ";
			cout << curLink->id << endl;
		}
		log("Is this link the job that we are looking for?", debug);
		if(curLink->id == job){
			
			log("Yes, Is this the first link?", debug);
			if(curLink == alloclist){
				
				log("Yes, is this also the last link?", debug);
				if(curLink->next == NULL){
					
					log("Yes, removing the link from the chain", debug);
					alloclist = NULL;
					
					log("Remove and add to free list", debug);
					deallocate(curLink);
					
					log("Since that was only link, we can exit the loop", debug);
					break;
				}else
				if(curLink->next != NULL){
					log("No, it's just the first link, removing link from chain", debug);
					alloclist = curLink->next;
					
					log("Remove the link, and add to free list", debug);
					deallocate(curLink);
						
					log("Redefine the last and current links", debug);
					curLink = alloclist; 	// temp pointer to list
					lastLink = alloclist;	// temp pointer to previous value

					//break;					
				}
			}else
			
			if(curLink->next == NULL){
				log("no, this is the last link", debug);
				lastLink->next = NULL;
				deallocate(curLink);
			}else
			
			//============================================================
			//log("Is it in the middle?", debug);
			//============================================================
			if(curLink->id == job){
				log("No, this link is in the middle", debug);
				//=====================================================
				log("Yes, removing link from allocated chain", debug);
				//=====================================================
				lastLink->next = curLink->next;	
				
				//===================================
				log("Add link to Free Chain",debug);
				//===================================
				deallocate(curLink);
				//break;
			}else{
				cout << "should never happen" << endl;
			}
			
		}

		
		//==================================
		log("No, moving on to the next link", debug);
		//==================================
		lastLink = curLink;			// Keep the last pointer
		curLink = curLink->next;	//move pointer to next node (or NULL)
	}
}

/**@fun int total_free(void)
 *	^	compute the total number of bytes not allocated
 * 
 * @return int
 *	^	the amount of total free bytes
 */
int total_free(void){
  	FREEPTR curLink = freelist; // temp pointer to list
	int freeTotal = 0;
	
	while (curLink != NULL)
	{
		freeTotal+=curLink->size;
		curLink = curLink->next; //move pointer to next node (or NULL)
	}
	return freeTotal; // return amount of free memory
}

/**@fun int total_allocated(void)
 *	^	compute the total number of bytes allocated
 * 
 * return int
 *	^	the amount of total allocated bytes
 * 
 */
int total_allocated(void){
  	ALLOCPTR curLink = alloclist; // temp pointer to list
	int allocTotal = 0;
	
	while (curLink != NULL)
	{
		allocTotal+=curLink->size;
		curLink = curLink->next; //move pointer to next node (or NULL)
	}   
   return allocTotal; //return amount of allocated memory
};

/**@fun int largest_free(void)
 * 	^	find the largest available free block of memory
 * 
 * @return int
 *	^	the amount of free memory in the block 
 */
int largest_free(void){
	bool debug = true;
	log("Create a free pointer", debug);
	FREEPTR curLink = freelist; // temp pointer to list
	int largest = 0;
	
	log("Traverse the chain", debug);
	while (curLink !=NULL)
	{
		log("Checking if this is the largest", debug);
		if(largest <= curLink->size){
			log("Not the largest, changing . . .", debug);
			largest = curLink->size;
		}else{
			log("It isn't the largest", debug);
		}
		log("Moving on to next link", debug);
		curLink = curLink->next; //move pointer to next node (or NULL)
	}
	log("returning the largest free block of memory", debug);
	return largest;
}

/**@fun job_allocated(const int job)
 *	^	compute the total amount of memory allocated to a particular job
 * @param job | const int
 *	^	The number of the job
 * @return int
 * 	^	The total amount of memory allocated to the job
 */
int job_allocated(const int job){
  	bool debug = false;
	log("Create a Allocated pointer", debug);
	ALLOCPTR curLink = alloclist; // temp pointer to list
	int total = 0; // keep track of total
	
	log("Traverse the chain", debug);
	while (curLink != NULL){
		
		log("Checking if this is the right job", debug);
		if(job == curLink->id){
			
			log("Right job, adding to total", debug);
			total += curLink->size;
		}else{
			
			log("Not the right job", debug);
		}
		
		log("Move on to the next link", debug);
		curLink = curLink->next; //move pointer to next node (or NULL)
	}
	log("Returning the number of blocks allocated to the job", debug);
	return total; // return amount of allocated memory
}

/**@fun void report_memory(void)
 *	^	Report the use of the continuous memory usage
 *
 * @note Krebsbach
 *	^	See Report Formats 2014 document for format
 *		^	Memory Block	JOB
 *		^	0 - 9			5
 *		^	10 - 50			1
 *		^	51 - 53			FREE
 *		^	54 - 75			1
 *		^	76 - 100		FREE
 *
 */
void report_memory(void){
	bool debug = true;
	log("Entering report_memory", debug);
	
	FREEPTR curFree = freelist;
	FREEPTR prevFree = freelist;
	
	ALLOCPTR curAllo = alloclist;
	ALLOCPTR prevAllo = alloclist;
	
	
	log("Is either list null?", debug);
	if(alloclist == NULL && freelist == NULL){
		log("Both lists are NULL");
		// ????
	}
	if(alloclist == NULL){
		log("Alloc list is null");
	}else
	if(freelist == NULL){
		log("Free list is null");
	}else{
		log("No, both lists have something");
	}
	
	
	log("Which list has the start byte?", debug);
	if(alloclist->start_byte == 0){
		log("The allocated list has the start byte", debug);
		
		
	}else 
	if(freelist->start_byte == 0){
		log("The free list has the start byte", debug);
	
	}else{
		log("Neither list has a start byte of 0", debug);
	}
	
	log("Print out the header", debug);
	cout.width(25); 
	cout << left << "Memory Block" << "JOB" << endl;
	
	log("Print out the line", debug);
	printFree(freelist);
	printAlloc(alloclist);
	
	log("exiting report_memory", debug);
 }
 

 
/**@fun void report_jobs(void)
 *	^ Report the memory blocks used by each job
 *
 * @note Krebsbach
 * 	^	See Report Formats 2014 document for format
 * 		^	JOB 	Memory Usage 
 *		^	1 		10 – 50  54 – 75  200 – 240 
 *		^	5 		1 – 9  101 – 134 
 *		^	3 		180 – 184  185 – 192
 * 
 */
void report_jobs(void){
    // STUB
}
//==========  MAIN =============================

int main(void)
{
	init_memory_manager(256);
	

	allocate_memory(1,10);	
	allocate_memory(2,20);
	cout << endl << "Now Delete 1" << endl;
	release_memory(2);

	allocate_memory(3,30);
	allocate_memory(4,40);
	allocate_memory(3,30);
	allocate_memory(4,40);
	allocate_memory(3,30);
	allocate_memory(4,40);

	dump_freelist();
	dump_alloclist();
	
	cout << endl << "release memory 3" << endl;
	release_memory(3);
	
	cout << endl << "release memory 1" << endl;
	release_memory(1);
	
	dump_freelist();
	dump_alloclist();
	
	cout << endl << "Memory for job 4 " << job_allocated(4) << endl;
	cout << endl << "Free Total: " << total_free() << endl;
	cout << "Alloc Total: " << total_allocated() << endl;

	report_memory();
	return 0;
}
