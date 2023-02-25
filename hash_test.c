
#include <stdio.h>
#include <string.h>

#include "hashing.h"

#define ALGO_SIZE 4 /* make sure to change this if you add hash algos to hash[]*/
#define MAX_MOVIES -1
#define SIZE 2000000

int collisions[ALGO_SIZE][SIZE];

/** this is a way that we can
 * cycle through the algorithms.
*/
uint32_t (*hash[])(char*) = {
    simple_hash,
    djb2,
    fnv_hash,
    jenkins_one_at_a_time_hash
    
    };


void printArray(int * array, int size) {

    for(int i = 0; i < size; i++) printf("%d ", array[i]);
    printf("\n");
}

void printCollisionsOnly(int *array, int size)
{
    int total = 0;
    int highest  = 0;
    int counter = 0;
    int load = 0;
    for (int i = 0; i < size; i++) {
        if(array[i] > 1) { 
            total += array[i];
            counter++;
            if(array[i] > highest) highest = array[i];
        }
        if(array[i] > 0) {
            load++;
        }
    }
    printf("Collisions: %d, Highest: %d, Average: %.2f, Load: %.5f\n", total, highest, 
           total / (float)counter, load / (float)SIZE);
}

int main() {

    char buffer[256];
    FILE *fp;
    fp = fopen("movie_ids_us.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int min_count = 0;

    while (fgets(buffer, sizeof(buffer), fp))
    {
        int newline_pos = strcspn(buffer, "\n"); // Find position of newline character
        if (newline_pos > 0 && buffer[newline_pos - 1] == '\r')
        { // Check for carriage return on Windows
            newline_pos--;
        }
        buffer[newline_pos] = '\0'; // Replace

        for (int i = 0; i < ALGO_SIZE; i++)
        {
            uint32_t loc = (hash[i](buffer)) % SIZE;
            collisions[i][loc]++;
        }
        if(MAX_MOVIES > 0 && min_count++ >= MAX_MOVIES) break;;
    }

    fclose(fp);
    for(int i = 0; i < ALGO_SIZE; i++) {
        if (SIZE > 200)
            printCollisionsOnly(collisions[i], SIZE);
        else printArray(collisions[i], SIZE);
    }

    return 0;
}
