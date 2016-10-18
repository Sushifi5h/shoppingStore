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
* Function: void simulationRunner(void)                     *
* Date Created: 02/10/2015                                   *
* Date Last Modified: 02/10/2015                             *
* Description: return 1 if empty return 0 if not             *
* Input parameters: struct holding pointer                   *
* Returns: 1 or 0                                            *
* Preconditions: Nothing                                     *
* Postconditions: none                                       *
*************************************************************/
void simulationRunner(void)
{
	//contains all time vars
	TimeManager allTimevars = { 0,0,{0,0,0},{0,0,0}};

	//initialized two lines
	Queue lineNormal = { NULL, NULL };//
	Queue lineExpress = { NULL, NULL };//

	//use srand to seed values
	srand((unsigned int) time(NULL));

	//get times in mins
	do {
		printf("Please give time in mins for simulation: ");
		scanf("%d", &allTimevars.runningTime);
		system("cls");
	} while (allTimevars.runningTime <= 0);

	//set arival times for customers
	allTimevars.normal.arrivalTime = randomNumberGen(1);
	allTimevars.express.arrivalTime = randomNumberGen(2);

	//announce next arivals
	printf("\nNext Customer arivving in %d mins in Normal Lane.\n", allTimevars.normal.arrivalTime);
	printf("\nNext Customer arivving in %d mins in Express Lane.\n", allTimevars.express.arrivalTime);

	
	//run till time limit
	while(allTimevars.runningTime > allTimevars.realTime) 
	{
		//check arrival time normal line
		if(!allTimevars.normal.arrivalTime)
		{
			//itterate customer number & generate service time
			allTimevars.normal.customerNumber++;
			allTimevars.normal.serviceTime = randomNumberGen(1);

			//message to say customer arived in a lane
			printf("\n\tCustomer arrived in normal line.\n (Customer Number: %d, Time Arrived: %d, Service Time: %d)\n",
				allTimevars.normal.customerNumber, allTimevars.realTime, allTimevars.normal.serviceTime);

			//put them in que
			enqueue(&lineNormal, allTimevars.normal.customerNumber, allTimevars.normal.serviceTime, allTimevars.realTime,0);

			//set arival times for customers
			allTimevars.normal.arrivalTime = randomNumberGen(1);
			printf("\nNext Customer arivving in %d mins in Normal Lane.\n", allTimevars.normal.arrivalTime);

		}

		//check arrival time express line 
		if (!allTimevars.express.arrivalTime)
		{
			//itterate customer number & generate service time
			allTimevars.express.customerNumber++;
			allTimevars.express.serviceTime = randomNumberGen(2);

			//message to say customer arived in a lane
			printf("\n\tCustomer arrived in express line.\n (Customer Number: %d, Time Arrived: %d, Service Time: %d)\n",
				allTimevars.express.customerNumber, allTimevars.realTime, allTimevars.express.serviceTime);

			//put them in que
			enqueue(&lineExpress, allTimevars.express.customerNumber, allTimevars.express.serviceTime, allTimevars.realTime,0);

			//get new customer arival and print it
			allTimevars.express.arrivalTime = randomNumberGen(2);
			printf("\nNext Customer arivving in %d mins in Express Lane.\n", allTimevars.express.arrivalTime);
		}

		//serve customer in normal line
		if (!isempty(lineNormal))
		{
			//check serivce time of front customer
			if (lineNormal.pHead->serviceTime != 0)
			{
				//decrease service time
				lineNormal.pHead->serviceTime--;

				//do check to make sure not 0
				if (lineNormal.pHead->serviceTime == 0)
				{
					//print message & deque customer 
					printf("\nDone serving customer: %d, who waited %d mins in normal line.\n",
						lineNormal.pHead->customerNumber, allTimevars.realTime - lineNormal.pHead->arivalTime);
					dequeue(&lineNormal);
				}
			}
				
			else
			{
				//print message & deque customer 
				printf("\nDone serving customer: %d, who waited %d mins in normal line.\n", 
					lineNormal.pHead->customerNumber, allTimevars.realTime - lineNormal.pHead->arivalTime);
				dequeue(&lineNormal);

				//decrease service time for next customer
				if (!isempty(lineNormal))
					lineNormal.pHead->serviceTime--;

			}
		}

		//serve customer in normal line
		if (!isempty(lineExpress))
		{
			//check serivce time of front customer
			if (lineExpress.pHead->serviceTime != 0)
			{
				//decrease service time
				lineExpress.pHead->serviceTime--;

				//check to make sure not to release now
				if ((lineExpress.pHead->serviceTime == 0))
				{
					//print message & deque customer
					printf("\nDone serving customer: %d, who waited %d mins in Express line.\n\n",
						lineExpress.pHead->customerNumber, allTimevars.realTime - lineExpress.pHead->arivalTime);
					dequeue(&lineExpress);
				}
			}

			else
			{
				//print message & deque customer
				printf("\nDone serving customer: %d, who waited %d mins in Express line.\n\n",
					lineExpress.pHead->customerNumber, allTimevars.realTime - lineExpress.pHead->arivalTime);
				dequeue(&lineExpress);

				//decrease teh service time for next 
				if (!isempty(lineExpress))
					lineExpress.pHead->serviceTime--;
			}
		}
		
		//print info for 10 mins interval
		if (!(allTimevars.realTime % 10) && (allTimevars.realTime > 2))
		{
			system("pause");
			puts("==================================================\nPrinting normal line\n==================================================");
			printQueRecursively(lineNormal.pHead);
			puts("==================================================");
			puts("Printing express line\n==================================================");
			printQueRecursively(lineExpress.pHead);
			puts("==================================================");
			system("pause");
			system("cls");

		}

		//decrease min by 1
		allTimevars.realTime++;
		allTimevars.normal.arrivalTime--;
		allTimevars.express.arrivalTime--;
		
		//check if day has passed
		if (allTimevars.realTime == 1440)
		{
			//brief message and pause
			puts("It's been a day or 1440 mins! Closing shop and clearing all lines and setting time to new day.");
			system("pause");

			
			//print que before clearing and format
			system("pause");
			puts("==================================================\nPrinting normal line\n==================================================");
			printQueRecursively(lineNormal.pHead);
			puts("==================================================");
			puts("Printing express line\n==================================================");
			printQueRecursively(lineExpress.pHead);
			puts("==================================================");
			system("pause");
			system("cls");

			//clean list 
			while (!isempty(lineNormal))
				dequeue(&lineNormal);
			while (!isempty(lineExpress))
				dequeue(&lineExpress);

			//set day real time back to 0 and subract 1440 from time entered
			allTimevars.realTime = 0;
			allTimevars.runningTime = allTimevars.runningTime - 1440;
		}
	}
	system("pause");
	printQueRecursively(lineNormal.pHead);
	system("pause");
	printQueRecursively(lineExpress.pHead);

	system("pause");

	//clean list 
	while (!isempty(lineNormal))
		dequeue(&lineNormal);
	while (!isempty(lineExpress))
		dequeue(&lineExpress);

	
}




