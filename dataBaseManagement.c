/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 122, Fall  2016; Lab Section 5                                               *
* Programming Assignment: Programming Assignment 2					                       *
* Date: January 29, 2016                                                                   *
* Description: Writing a program that is a Digital music manager						   *
*******************************************************************************************/

//local libaries
#include "shoppingStore.h"

/*************************************************************
* Function: QueueNode* makeNode(int, int, int)               *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: calls malloc                                  *
* Input parameters: 3 ints                                   *
* Returns: Node with data                                    *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
QueueNode* makeNode(int customerNumber, int serviceTimes, int arivalTime,int totalTime)
{
	//local vars
	QueueNode *temp = NULL;

	temp = (QueueNode *)malloc(sizeof(QueueNode));

	if (temp != NULL)
	{
		//set data and pNext
		temp->customerNumber = customerNumber;
		temp->serviceTime = serviceTimes;
		temp->arivalTime = arivalTime;
		temp->totalTime = totalTime;
		temp->pNext = NULL;
	}

	return temp;
}

/*************************************************************
* Function: void printQue(Queue line)                        *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: print queue                                   *
* Input parameters: Queue phead                              *
* Returns: nothing                                           *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
int printQue(Queue queue)
{
	//set pCur and success
	int success = 0;
	QueueNode* pCur = queue.pHead;
	

	if (pCur != NULL)
	{
		while (pCur != NULL)
		{
			/* check to see is not empty */
			printf("Customer Number: %d\n"
				"Service Time: %d\n"
				"Arrival Time: %d\n"
				"Total Time: %d\n", pCur->customerNumber, pCur->serviceTime, 
				pCur->arivalTime,pCur->totalTime);

			//itterate pCur
			pCur = pCur->pNext;
		}

		//set success
		if (success == 0)
			success = 1;
	}
	return success;
}

int printQueRecursively(QueueNode *queue)
{
	//local var
	int success = 0;

	//if qhead is not empty
	if (queue != NULL)
	{
		//print list
		printf("Customer Number: %d\n"
			"Service Time: %d\n"
			"Arival Time: %d\n"
			"Total Time: %d\n", queue->customerNumber, queue->serviceTime, 
			queue->arivalTime ,queue->totalTime);
		//recursively print next
		printQueRecursively(queue->pNext);

		if (success == 0)
			success = 1;
	}

	return success;
}

/*************************************************************
* Function: int enqueue(Queue *line)                         *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: add to queue                                  *
* Input parameters: address line                             *
* Returns: nothing                                           *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
int enqueue(Queue *line, int customerNumber, int serviceTime, int arivalTime,int totalTime)
{
	//local var
	int success = 0;
	QueueNode *temp = NULL;

	//make node get totalTime by calling a function
	temp = makeNode(customerNumber, serviceTime, arivalTime, totalTimeCalculator(line->pHead, serviceTime));

	if (temp != NULL)
	{
		//memory was allocated
		success = 1;
		//so the list is empty
		if (line->pHead == NULL)
		{
			//que is empty
			line->pHead = line->pTail = temp;
		}
		else {
			//que is not empty
			line->pTail->pNext = temp;
			line->pTail = temp;
		}
	}
	return success;
}

/*************************************************************
* Function: int denqueue(Queue *line)                        *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: remove from front queue                       *
* Input parameters: address line                             *
* Returns: nothing                                           *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
int dequeue(Queue *line)
{
	//local var
	QueueNode *pCur = NULL;

	//set pCur to head
	pCur = line->pHead;

	if (line->pHead == line->pTail)
	{
		line->pHead = line->pTail = NULL;
	}else{
		line->pHead = line->pHead->pNext;
	}
	//free memoery
	free(pCur);

	return 1;
}

/*************************************************************
* Function: int isempty(Queue line)                          *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: return 1 if empty return 0 if not             *
* Input parameters: struct holding pointer                   *
* Returns: 1 or 0                                            *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
int isempty(Queue line)
{
	//local var
	int empty = 1;
	//check empty
	if (line.pHead !=NULL)
		empty = 0;
	//return if empty
	return empty;
}

/*************************************************************
* Function: int randomNumberGen(1 or 2)                      *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: return 1 if empty return 0 if not             *
* Input parameters: struct holding pointer                   *
* Returns: 1 or 0                                            *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
int randomNumberGen(int line)
{
	//local var
	int randNum = 0;

	if (line == 1)
		randNum = ((rand() % 6)) + 3;
	else if(line == 2)
		randNum = (rand() % 5) + 1;
	
	return randNum;
}

/*************************************************************
* Function: int totalTimeCalculator(Quenode *head)           *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: will trivse list and give back the total time *
* Input parameters: head holding pointer                     *
* Returns: totalTime                                         *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
int totalTimeCalculator(QueueNode *head, int serviceTime)
{
	//local vars
	int totalServiceTime = 0;
	QueueNode *pCur = NULL;

	//set pCur
	pCur = head;

	//go through line
	while (pCur != NULL)
	{
		//keep adding service time		
		totalServiceTime += pCur->serviceTime;

		//itterate
		pCur = pCur->pNext;
	}

	return totalServiceTime + serviceTime;
}