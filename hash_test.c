
#include <stdio.h>

#include "hashing.h"

#define ALGO_SIZE 4
#define MAX_MOVIES 5

int collisions[ALGO_SIZE];

/** this is a way that we can
 * cycle through the algorithms.
*/
uint32_t (*hash[])(const char*) = {
    simple_hash,
    djb2,
    fnv_hash,
    jenkins_one_at_a_time_hash};


int main() {


    for(int i = 0; i < ALGO_SIZE; i++) {
        printf("%u\n", hash[i]("hello"));


    }



}
