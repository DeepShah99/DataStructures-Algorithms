/*******************************************************************************
* File Name          : hashAssignmentV3.cpp
* Description        : Implemenation of a hash skelleton
*
* Author:              PROG8130 / Deep Shah (Student Id - 8750086)
* Date:                Dec 13th, 2021
******************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int putIntoHashTable(char* ptrInputData, unsigned int bufferLength);    // function to add to hash table
unsigned int getFromHashTable(char* ptrOutputData, unsigned int bufferLength);   // function to retrieve data from hash table

#define INPUT_BUFFER_SIZE         200             // local buffer used for adding data to the hash table (there is no reason in this assignment to change this value)

#define HASH_SIZE    10                          // size of hash table to be used (for testing I suggest making this number much lower)

												  // data structure used to keep track of hashed data
struct myHashStruct {
	char* ptrBuffer = NULL;                       // pointer to data stored in hash (you will need to malloc space for string to be stored)
	struct myHashStruct* ptrNextHashData = NULL;  // pointer to next item in this hash bucket (or NULL if no more)
};

struct myHashStruct* myHash[HASH_SIZE];           // create an empty hash table structure (note this is basically an arrary of linked list heads)

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];

	// initialize the hash table to empty one
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if ((myHash[i] = (struct myHashStruct*)calloc(1, sizeof(struct myHashStruct))) == NULL)
		{
			printf("calloc failed!\n");
			return(-1);
		}
	}

	// add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// get strings from the console and place in hash until nothing entered
		scanf_s("%199s", inputBuffer, INPUT_BUFFER_SIZE);
		inputBuffer[INPUT_BUFFER_SIZE - 1] = '\0';

		// stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
			break;

		if (putIntoHashTable(inputBuffer, strlen(inputBuffer)) == HASH_SIZE)
			printf("Error putting into hash table\n");
	}

	// check if data is in hash table
	while (1)
	{
		unsigned int hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// get strings from the console and check if in hash table
		scanf_s("%199s", inputBuffer, INPUT_BUFFER_SIZE);
		inputBuffer[INPUT_BUFFER_SIZE - 1] = '\0';

		// stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
			break;

		if ((hashIndexNumber = getFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
			printf("%s not found in hash table\n", inputBuffer);
		else
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
	}

	return 0;
}

// FUNCTION      : myHashFunction
// DESCRIPTION   :
//   Calculate a hash value to use in storing the data into the hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//
// RETURNS       :
//   Hash value calculated ( HASH_SIZE on failure)

unsigned int myHashFunction(char* ptrInputBuffer)
{
	unsigned int calculatedHashValue = 0;

	// add code to create a hashed value here!!!
	int sumSDBM = 0;                              //Reference - Class notes
	while (sumSDBM = *ptrInputBuffer++)
	{
		calculatedHashValue = sumSDBM + (calculatedHashValue << 6) + (calculatedHashValue << 16) - calculatedHashValue;
	}
	//printf("The summation of SDBM is %d\n", calculatedHashValue);

	// make sure if hash value is bigger than the table size, the value wraps
	return calculatedHashValue % HASH_SIZE;
}

// FUNCTION      : putIntoHashTable
// DESCRIPTION   :
//   Put the supplied data into a hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//   bufferLength   - how many characters are in the buffer being put into the hash table
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int putIntoHashTable(char* ptrInputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrInputData); //get the hash value from myHashFunction for the user input data
	myHashStruct* temp = NULL, * newNode = NULL;  //newNode is used for inserting elements at start and at end of a linked list while temp is used to traverse till end of linked list 
    
	printf("The hashValue for '%s' is %d\n",ptrInputData, hashValue);

	newNode = (myHashStruct*)malloc(sizeof(myHashStruct)); //dynamic memory allocation for newNode
	                                                       //Reference - https://www.youtube.com/watch?v=hJbDwpSdGkM&t=1052s
	if (newNode) {                                         //condition to check if we are not referencing a null pointer
		if ((newNode->ptrBuffer = (char*)malloc(strlen(ptrInputData) + 1)) == NULL) {
			return HASH_SIZE;                              //malloc failed
		}
		strcpy_s(newNode->ptrBuffer, bufferLength + 1, ptrInputData); //copy the string to buffer pointed by newNode
		newNode->ptrNextHashData = NULL;                   //make sure to terminate the end of LinkList by a null 

	}

	if (myHash[hashValue]->ptrBuffer == NULL)              //check if this string is the first element of link list 
	{
		myHash[hashValue] = newNode;                       //if yes, then place the data part of newNode at beginning of required index of the hash table
	}
	else
	{

		for (temp = myHash[hashValue]; temp->ptrNextHashData != NULL; temp = temp->ptrNextHashData); //traverse till end of linked list
		temp->ptrNextHashData = newNode; //put the address of newNode into address pointed by temp 

	}


	// check if the value is in the hash
	// add code to put data into the hash table!!!

	return hashValue;                                      //return hashValue on successful addition of a node to a linked list
}

// FUNCTION      : getFromHashTable
// DESCRIPTION   :
//   Read as much data as there is room for from the hash table
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from hash table
//   bufferLength    - maxiumum number of characters that can be read
//
// RETURNS       :
//   Hash value used ( return HASH_SIZE value on failure)

unsigned int getFromHashTable(char* ptrOutputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrOutputData);  //get the hash value from myHashFunction for the user input data

	myHashStruct* temp;                                      //temp structure used to traverse till end
	if (myHash[hashValue]->ptrBuffer != NULL && ptrOutputData != NULL) {   //enter only if data at a required index and user input data is not Null 
		for (temp = myHash[hashValue]; temp != NULL; temp = temp->ptrNextHashData)
		{
			if (strcmp(temp->ptrBuffer, ptrOutputData) == 0) //strcmp returns zero if both strings matches
			{
				return hashValue;                            //return hashValue if we found a match after traversing
			}
		}
	}

	// check if the data is in the hash table here!!!

	return HASH_SIZE;                                        //return Hash size if match not found (return type is unsigned int that is why we can not return -1)
}

// end code *     *     *   
