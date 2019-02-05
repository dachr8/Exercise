//mall.c -- Use the Queue interface
//Compile with queue.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h" //Change the typedef of the Item

#define MIN_PER_HR 60.0

bool newcustomer(double x);  //Are there new customers coming
Item customertime(long when); //Set customer parameters


int main(void) {
	Queue line;
	Item tmp;               //New customer data
	int hours, perhour;     //Simulated hours, average number of customers per hour
	long cyclelimit;        //Counter limit
	long turnaways = 0;     //Number of customers rejected due to queue full
	long customers = 0;     //Number of customers joining the queue
	long served = 0;        //Number of customers who consulted Sigmund during the simulation
	long sum_line = 0;      //Cumulative total queue length
	int wait_time = 0;      //Time from current to Sigmund free time
	double min_per_cust;    //Average time of arrival of customers
	long line_wait = 0;     //Queue cumulative wait time

	InitializeQueue(&line);
	srand((unsigned int)time(0));
	puts("Case Study: Sigmund Lander's Advice Booth");
	puts("Enter the number of simulation hours:");
	scanf("%d", &hours);
	cyclelimit = MIN_PER_HR * hours;
	puts("Enter the average number of customers per hour:");
	scanf("%d", &perhour);
	min_per_cust = MIN_PER_HR / perhour;

	for (long cycle = 0; cycle < cyclelimit; ++cycle) {
		if (newcustomer(min_per_cust)) {
			if (QueueIsFull(&line))
				++turnaways;
			else {
				tmp = customertime(cycle);
				EnQueue(tmp, &line);
				++customers;
			}
		}
		if (wait_time <= 0 && !QueueIsEmpty(&line)) {
			DeQueue(&tmp, &line);
			wait_time = tmp.processtime;
			line_wait += cycle- tmp.arrive;
			++served;
		}
		if (wait_time > 0)
			--wait_time;
		sum_line += QueueItemCount(&line);
	}

	if (customers) {
		printf("customers accepted: %ld\n", customers);
		printf("  customers served: %ld\n", served);
		printf("         turnaways: %ld\n", turnaways);
		printf("average queue size:%.2f\n", (double)sum_line / cyclelimit);
		printf(" average wait time:%.2f minutes\n", (double)line_wait / served);
	} else
		puts("Np customers!");
	EmptyTheQueue(&line);
	puts("Bye!");

	return 0;
}

//x is the average time the customer arrives (unit: minute)
//Return true if a customer arrives within 1 minute
bool newcustomer(double x) {
	if (x*rand() / RAND_MAX < 1)
		return true;
	else
		return false;
}

//when is the time of arrival of the customer
//This function returns an Item structure, the time the customer arrived is set to when
//The consultation time is set to a random number of 1~3
Item customertime(long when) {
	Item cust;

	cust.processtime = 1 + rand() % 3;
	cust.arrive = when;

	return cust;
}
