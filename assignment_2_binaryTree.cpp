/*******************************************************************************************
* File Name       : assignment_2_binaryTree.cpp
* Description     : Implement a binary search tree and print the data of the nodes using recursive inorder traversal
*                   and morris inorder traversal
* Author          : Deep Shah (Student Id - 8750086)
* Date            : 17th Oct 2021
********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
struct nodeData {
	char name[30];				// character string of the data being stored in the node
	struct nodeData* left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
	struct nodeData* right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
};

// My last four digits of student id are 0086
const char* inputData[12] = {
		{ "alnfi"},
		{ "qkhqt"},
		{ "tydkv"},
		{ "yqdwe"},
		{ "ppbfw"},
		{ "buhnm"},
		{ "xmobb"},
		{ "echjr"},
		{ "sqyfk"},
		{ "vbnms"},
		{ "ggvxi"},
		{ "nwxfb"}
};

// The correct sorted order using a binary tree is:
//      alnfi
//      buhnm
//      echjr
//      ggvxi
//      nwxfb
//      ppbfw
//      qkhqt
//      sqyfk
//      tydkv
//      vbnms
//      xmobb
//      yqdwe

struct nodeData* head = NULL;  // head of the binary tree
int i;

//prototypes
void addToBinaryTree(const char* newString);
void printBinaryTreeRecursion(struct nodeData* head);
void printBinaryTreeNonRecursion(struct nodeData* head);

int main() {
	printf("Data to be stored in binary search tree are\n");
	for (i = 0; i < 12;i++) {
		printf("%s\n", inputData[i]);
		if (i == 11) {
			printf("\n\n");
		}
	}

	// put all the data into the binary tree
	for (i = 0; i < 12;i++) {
		addToBinaryTree(inputData[i]);
	}

	// print the entire tree.  It should come out in alphabetical order because of the way it was stored in the tree
	printf("Sorted data using iterative approach is\n");
	printBinaryTreeRecursion(head);
	printf("\n\n");

	printf("Sorted data using non-iterative approach is\n");
	printBinaryTreeNonRecursion(head);

	return 0;
}

// FUNCTION      : addToBinaryTree
// DESCRIPTION   : This function will store the data in newNode into a binary tree according to alphabetical order
// PARAMETERS    : newString - the string that is to be stored in the binary tree in alphabetica order
// RETURNS       : Nothing
void addToBinaryTree(const char* newString) {

	struct nodeData* newNode = NULL, * traversalNode = NULL;
	newNode = (struct nodeData*)malloc(sizeof(struct nodeData)); //dynamic memory allocation and type casting for the newNode 

	if (newNode) {  //check if we are not referncing a NULL pointer
		strcpy_s(newNode->name, newString);
		newNode->left = NULL;
		newNode->right = NULL;
		if (i == 0)
			head = newNode;  //the first element will be the root of the binary search tree
		else {
			traversalNode = head; //start traversing from the root of the binary search tree 
			while (1) {
				if (strcmp(newNode->name, traversalNode->name) > 0) { //if the newNode is greater than traversalNode then place the node to right 
					//traverse till there is a NULL at the right of the traversalNode so that we can place the newNode to the right
					if (traversalNode->right == NULL) {
						traversalNode->right = newNode;
						break;
					}
					else {
						traversalNode = traversalNode->right;
					}
				}
				else {  //if the newNode is less than or equal to traversalNode then place the node to left
					//traverse till there is a NULL at the left of the traversalNode so that we can place the newNode to the left
					if (traversalNode->left == NULL) {
						traversalNode->left = newNode;
						break;
					}
					else {
						traversalNode = traversalNode->left;
					}
				}
			}
		}
	}

}

// FUNCTION      :  printBinaryTreeRecursion
// DESCRIPTION   :  This function will print the entire binary tree out.  
// PARAMETERS    :  struct nodeData* head - root of the binary search tree
// RETURNS       :  Nothing
void printBinaryTreeRecursion(struct nodeData *head) {
	//for inorder traversal we follow this sequence for the recursion - left root right
	if (head == 0) {                    //when root is NULL return back to the calling function
		return;
	}
	printBinaryTreeRecursion(head->left);  //first traverse to left node of tree
	printf("%s\n", head->name);            //print the root or subroot node
	printBinaryTreeRecursion(head->right); //traverse to right node of tree
}


// FUNCTION      :  printBinaryTreeNonRecursion
// DESCRIPTION   :  This function will print the entire binary tree out.  
// PARAMETERS    :  struct nodeData* head - root of the binary search tree
// RETURNS       :  Nothing
void printBinaryTreeNonRecursion(struct nodeData* head) {
    //this inorder non recursive printing is done via morris inorder traversal 
	struct nodeData* currentNode = head;
	struct nodeData* predecessorNode;

	while (currentNode != NULL)
	{
		if (currentNode->left == NULL)
		{
			printf("%s\n", currentNode->name);
			currentNode = currentNode->right;
		}
		else
		{
		
			predecessorNode = currentNode->left;       //obtain the inorder predecessor
			while (predecessorNode->right != NULL
				&& predecessorNode->right != currentNode)
			{
				predecessorNode = predecessorNode->right;
			}

			
			if (predecessorNode->right == NULL)        //create a virtual link between predecessor and the current node
			{
				predecessorNode->right = currentNode;
				currentNode = currentNode->left;
			}

			
			else                                       //break the virtual link and print the current node
			{
				predecessorNode->right = NULL;
				printf("%s\n", currentNode->name);
				currentNode = currentNode->right;
			}
		}
	}
}


