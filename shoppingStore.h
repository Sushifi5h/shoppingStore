/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 122, Fall  2016; Lab Section 5                                               *
* Programming Assignment: Programming Assignment 2					                       *
* Date: January 29, 2016                                                                   *
* Description: Writing a program that is a Digital music manager						   *
*******************************************************************************************/
//Gaurd Code
#ifndef SHOPPINGSTORE_H
#define SHOPPINGSTORE_H

//elminate unwanted errors
#define _CRT_SECURE_NO_WARNINGS

//include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//struct to store info
typedef struct queueNode
{
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime;   // Random time; varies between express and normal lanes; units in minutes
	int arivalTime;   //arival time from main clock
	int totalTime;     // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes

	struct queueNode *pNext; //
} QueueNode;

//hold pointers to head and tail
typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
}Queue;

//generic timers for two lines
typedef struct customerTimers
{
	int arrivalTime;
	int customerNumber;
	int serviceTime;
} CustomerTimers;

//struct for holding time
typedef struct timeManager
{
	int realTime; //starts from 1 easier time management
	int runningTime; //run simulation while real < RunningTIme

	//timers for lines
	CustomerTimers express;
	CustomerTimers normal;
} TimeManager;

//prototypes for databases
QueueNode* makeNode(int customerNumber, int serviceTimes, int arivalTime, int totalTime); //make node
int printQue(Queue line); //print queue
int enqueue(Queue *line, int customerNumber, int serviceTime, int arivalTime, int totalTime); // put in que
int dequeue(Queue *line);//remove first from que
int isempty(Queue line);//check to see if empty
int randomNumberGen(int line);//will give back number to line entered
int printQueRecursively(QueueNode *queue); //recursively print que
int totalTimeCalculator(QueueNode *head, int serviceTime);//manage total service time

//prototypes for simulation
void simulationRunner(void);//will hold all logic





#endif /*SHOPPINGSTORE_H*/