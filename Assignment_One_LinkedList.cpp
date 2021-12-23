
/*******************************************************************************************
* File Name          : Assignment_One_LinkedLists.c
* Description        : Prog8130 - Assignment 1: Linked Lists
*   This program uses linked lists to hold and print a list of words
*   organized by index number assosciated with each word. Each word can
*   consist of maximum 30 characters.
*
* Author:              Deep Shah
* Date:                5th Oct2021
********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS   10			// the number of data items to be used in list
#define MAX_Length 30                       // a word can have maximum 30 characters 
int pos = 0;                                // position of linked list

typedef struct {                            // struct data type with char for words and integer for indices
	char name[MAX_Length];
	int index;
} inputData;


typedef struct LinkedListNode {             // struct data type for LinkList 
	struct LinkedListNode* ptrNextNode;     // The pointer variable is of struct data type
	char NameData[MAX_Length];              // This will store words
} LinkedListNodeDef;


// prototypes
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex);
void PrintLinkedList(LinkedListNodeDef* ptrHead);
void insertAtBeg(void);
void insertAtEnd(void);
void insertAtMid(int index);


LinkedListNodeDef* ptrHead = NULL;            // defining linked list head
LinkedListNodeDef* newNode = NULL;            //newnode for the LinkList

//my last four digits of student id is 0086
inputData iData[10] = {
		{ "orange", 5 },
		{ "airplane", 3 },
		{ "fish", 6 },
		{ "water", 3 },
		{ "carrot", 8 },
		{ "milk", 9 },
		{ "kiwi", 4 },
		{ "butter", 6 },
		{ "allan", 9 },
		{ "chocolate", 6 }
};
//end of data for assignment

// Correct order after inserting into list is:
// 1. orange
// 2. airplane
// 3. water
// 4. kiwi
// 5. fish
// 6. chocolate
// 7. butter
// 8. carrot
// 9. milk
// 10. allan
int main() {
	int i;
   // Print out the input data
	printf("Data before Linked List is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
		printf("%s , %d\n", iData[i].name, iData[i].index);

	// inserting the data into Linked List
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
		ptrHead = AddToLinkedList(ptrHead, iData[i].name, iData[i].index);

	PrintLinkedList(ptrHead);
}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead - variable to store address of ptrHead
//                 char *NameData - Array of Characters with data 
//                 int DataIndex - Index of data
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex)
{
	
	pos++;  //Incrementing the position of link list
    newNode = (LinkedListNodeDef*)malloc(sizeof(LinkedListNodeDef)); //Typecasting is done on malloc as it gives a void pointer address
	
	strcpy_s(newNode->NameData, NameData); //copying the NameData to newNode one by one
	newNode->ptrNextNode = NULL; //the next pointer of new node is set to NULL

	if (pos == 1)
	{
		ptrHead = newNode; //if position of link list is one then first node will be the head of the list
	}
	else
	{
		if (DataIndex == 0 || DataIndex == 1)  //if index is 0 or 1 insert in the beginning of list
		{
			insertAtBeg();
		}
		else if (DataIndex >= pos) //if index of data is greater than current position of LL then insert that data to end of LL
		{
			insertAtEnd();
		}
		else                       //insert at a specific position of link list
		{
			insertAtMid(DataIndex);

		}
	}
	return ptrHead;
}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead) {
	LinkedListNodeDef* temp = ptrHead;
	printf("Correct order after inserting into list is :\n");
	while (temp != NULL)   //Repeat the loop till tail of LL points to Null
	{
		for (int i = 1; i <= NUMBER_OF_DATA_ITEMS; i++)
		{
			printf("%d . %s \n", i, temp->NameData);
			temp = temp->ptrNextNode;
		}
	}

}

// FUNCTION      : insertAtBeg()
// DESCRIPTION   : Function to insert data at the beginning of the link list 
// PARAMETERS    : None
// RETURNS       : None
void insertAtBeg() {
	newNode->ptrNextNode = ptrHead;
	ptrHead = newNode;
}

// FUNCTION      : insertAtEnd()
// DESCRIPTION   : Function to insert data at the end of the link list 
// PARAMETERS    : None
// RETURNS       : None
void insertAtEnd() {
	LinkedListNodeDef* temp = ptrHead;

	while (temp->ptrNextNode != NULL)
	{
		temp = temp->ptrNextNode;
	}
	temp->ptrNextNode = newNode;
}

// FUNCTION      : insertAtMid(int index)
// DESCRIPTION   : Function to insert data at a specific position of the link list 
// PARAMETERS    : int index - pass the index of the struct data type
// RETURNS       : none
void insertAtMid(int index) {
	LinkedListNodeDef* temp = ptrHead;
	for(int i = 0; i != index - 2; i++)
	{
		temp = temp->ptrNextNode;
	}

	newNode->ptrNextNode = temp->ptrNextNode; 
	temp->ptrNextNode = newNode;
}
