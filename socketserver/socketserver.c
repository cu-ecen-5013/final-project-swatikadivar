#include <stdio.h>
#include <stdlib.h>
#include <time.h>			// To use time library of C
  
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int main(){
	for (int i=0;i<10;i++){
		delay(1000);
		printf("%d\n",rand()%50);
	}

	return 0;
}
