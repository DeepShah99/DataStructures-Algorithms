/*******************************************************************************************
* File Name :	PROG8130sec2midterm.cpp
* Description : PROG8130 Section 2 midterm starter code
*
*				I have written the code to take the supplied data and put it into a sorted
*				Singly Linked List.
*
*				Create the two functions:
*					removeDuplicates - which will delete only the nodes that have the same data in it
*					removeLastNode - will delete the second last node from list
*
*				After the program is complete use the provided function to print out the list.
*
*Author :       Deep Shah
*Date :         20th Oct 2021
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS	12					// the number of data items to be used in list

// definition of linked list data nodes
typedef struct LinkedListNode {
	struct LinkedListNode* ptrNextNode;		// pointer to next node in list (NULL if the end)
	int						NumberData;			// the number stored in node
} LinkedListNodeDef;

// prototypes
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, int NameData);
void PrintLinkedList(LinkedListNodeDef* ptrHead);
LinkedListNodeDef* removeDuplicates(LinkedListNodeDef* ptrHead);
void removeLastNode(LinkedListNodeDef* ptrHead);


// data to be used for this programming question
int iData[NUMBER_OF_DATA_ITEMS] = {
	6,
	3,
	19,
	9,
	93,
	19,
	86,
	72,
	40,
	48,
	3,
	59
};

// your output from the program should look like this when working correctly:
//Data before Linked List Operations is :
//1.      6
//2.      3
//3.      19
//4.      9
//5.      93
//6.      19
//7.      86
//8.      72
//9.      40
//10.     48
//11.     3
//12.     59
//
//Data after inserted into linked list in numeric order :
//1.      3
//2.      3
//3.      6s
//4.      9
//5.      19
//6.      19
//7.      40
//8.      48
//9.      59
//10.     72
//11.     86
//12.     93
//
//Data after processing :
//1.      3
//2.      6
//3.      9
//4.      19
//5.      40
//6.      48
//7.      59
//8.      72
//9.      86

// START OF CODE YOU ARE ALLOWED TO CHANGE

// FUNCTION      : removeDuplicates()
// DESCRIPTION   : This function will iterate through a linked list and remove all duplicate entries 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* removeDuplicates(LinkedListNodeDef* ptrHead) {

	// add your code to remove and free memory from all duplicates here
	
	//We have to use two struct nodes for the removal of duplicates. One struct is useful for traversal and another struct node is useful to skip the duplicate and point to next of next node
	LinkedListNodeDef* traverseNode = NULL; //initialize to NULL to avoid "potentially unintialized local pointer" warning
	LinkedListNodeDef* jumpNode = NULL;     //initialize to NULL to avoid "potentially unintialized local pointer" warning
	
	traverseNode = ptrHead; //traversing will start from root of the link list

	while (traverseNode != NULL && traverseNode->ptrNextNode != NULL) { 
		//it is crucial that first node and second node of LL is not null, if such is the case then there are no duplicates in the LL
		if (traverseNode->NumberData == traverseNode->ptrNextNode->NumberData) { //check if current data is equal to next data 
			jumpNode = traverseNode->ptrNextNode->ptrNextNode; //jump to next to next node by unlinking the duplicate node
			// it is crucial to save the address of next to next node otherwise the link list will be broken
			
			if (jumpNode == NULL){ //if true means link is terminating
				traverseNode->ptrNextNode = NULL; //terminate the link list by adding a NULL at the end
				break;   //break out of loop 
		}

			traverseNode->ptrNextNode = jumpNode; //unlink the duplicate node by saving this address of next to next node in traversenode
		}

		//The importance of the next if statement comes into picture when there are more than two duplicates of a node
		if (traverseNode->NumberData != traverseNode->ptrNextNode->NumberData) { //check if the current node is not equal to next node
			traverseNode = traverseNode->ptrNextNode; //traverse to nextnode
		}
	}
	return ptrHead;
}

// FUNCTION      : removeLastNode()
// DESCRIPTION   : This function will iterate through a linked list and remove/free the last entry
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : Nothing
void removeLastNode(LinkedListNodeDef* ptrHead) {
	
	//We will require two temporary struct nodes one for traversing to the end of linked list and another to point to the previous node of last node
	//The traverseNode will be useful to delete the last node
	//We also have to terminate the linked list by adding a NULL to the node before deleted node
	//For this we can use another node termed as nodeBeforeLastNode

	LinkedListNodeDef* traverseNode = NULL; //initialize to NULL to avoid "potentially unintialized local pointer" warning
	LinkedListNodeDef* nodeBeforeLastNode = NULL; //initialize to NULL to avoid "potentially unintialized local pointer" warning

	traverseNode = ptrHead; //start the traversing from root of linked list

	while (traverseNode->ptrNextNode != 0) { //traverse till one previous node of last node which is to be deleted
		nodeBeforeLastNode = traverseNode;   //traverseNode will be now equal to nodeBeforeLastNode
		traverseNode = traverseNode->ptrNextNode; //now point to next node
	}
	if (traverseNode != ptrHead) { //We have to make sure to terminate the linked list by placing a NULL in the node which is before the deleted node
		nodeBeforeLastNode->ptrNextNode = NULL;		
	}
	else {
		ptrHead = NULL;   //if traverseNode is equal to root of link list that means there is only one node in the link list
		//So delete that node by just placing a NULL in the root of list
	}
	free(traverseNode); //It is very important to free the memory for the last deleted node
	return;
}

// END OF CODE YOU ARE ALLOWED TO CHANGE

// DO NOT CHANGE ANY OF THE CODE BELOW!  

int main(void) {
	int i;

	// define linked list head
	struct LinkedListNode* ptrHead = NULL;

	// Print out the input data
	printf("Data before Linked List Operations is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++) {
		printf("%d.\t%d\n", i + 1, iData[i]);
		ptrHead = AddToLinkedList(ptrHead, iData[i]);
	}

	// now print out the list in order it is stored starting at head
	printf("\nData after inserted into linked list in numeric order:\n");
	PrintLinkedList(ptrHead);
	removeDuplicates(ptrHead);

	removeLastNode(ptrHead);

	// now print out the list in order it is stored starting at head after required operations are complete
	printf("Data after processing:\n");
	PrintLinkedList(ptrHead);

	return 0;
}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized numerically
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   int	NumberData				- Number to add to linked list 
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, int NumberData) {
	LinkedListNodeDef* ptrCurrent = ptrHead;
	LinkedListNodeDef* ptrNew = NULL;

	// allocate a new node to be added to linked list
	ptrNew = (LinkedListNodeDef*)calloc(1, sizeof LinkedListNode);
	if (ptrNew == NULL) {
		printf("calloc failure!!\n");
		exit(-1);
	}

	// load new node with data
	ptrNew->ptrNextNode = NULL;
	ptrNew->NumberData = NumberData;

	if (ptrCurrent == NULL) {		// if list is empty simply change head to be new node
		ptrHead = ptrNew;
	}
	else {
		LinkedListNodeDef* ptrLast = NULL;

		// stop traversing if we reach the end of the list
		while (ptrCurrent != NULL) {
			// check for numeric order
			if (ptrCurrent->NumberData > NumberData)
			{
				// we found where new node should go so need to link in to list
				if (ptrLast == NULL)		// if the last pointer is NULL this means no traversing happened so put on beginning
					ptrHead = ptrNew;
				else						// otherwise link it into chain between last node and current
					ptrLast->ptrNextNode = ptrNew;
				ptrNew->ptrNextNode = ptrCurrent;
				return ptrHead;
			}
			ptrLast = ptrCurrent;			// keep track of last node because sometimes it is needed to insert new data
			ptrCurrent = ptrCurrent->ptrNextNode;	// traverse to next node
		}
		if (ptrCurrent == NULL) {			// if the current pointer is NULL that means we reached the end of the list so put it there
			ptrLast->ptrNextNode = ptrNew;
		}
	}
	return ptrHead;
}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//				   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead) {
	int i = 0;
	LinkedListNodeDef* ptrCurrent = ptrHead;

	// check for empty list
	if (ptrCurrent != NULL) {
		// traverse list looking for the end printing the items out as we go
		for (i = 1; ptrCurrent != NULL; i++)
		{
			printf("%i.\t%d\n", i, ptrCurrent->NumberData);
			ptrCurrent = ptrCurrent->ptrNextNode;
		}
	}
	printf("\n");
	return;
}

