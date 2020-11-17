#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int random_int(){

    int rand_num[1];

    int file = open("/dev/random", O_RDONLY);

    if (file == -1)
        printf("Error %d: Error: %s\n", errno, strerror(errno));

    int err = read(file, rand_num, sizeof(rand_num));

    if (err == -1)
        printf("Error %d: Error: %s\n", errno, strerror(errno));

    close(file);

    return rand_num[0];
}

int main(){

    int rand[10];

    printf("Generating random numbers:\n");

    int i;
    for(i = 0; i < 10; i++){
        rand[i] = random_int();
        printf("\tRandom %d: %d\n", i, rand[i]);
    }

    printf("\nWriting numbers to file...\n");

    int out = open("./out", O_RDWR);

    if (out == -1)
        printf("Error %d: Error: %s\n", errno, strerror(errno));

    int new = write(out, rand, sizeof(rand));

    if (new == -1)
        printf("Error %d: Error: %s\n", errno, strerror(errno));

    printf("\nReading numbers from file...\n\n");

    int randrand[10];

    new = read(out, randrand, sizeof(randrand));

    if (new == -1)
        printf("Error %d: Error: %s\n", errno, strerror(errno));

    printf("Verification that the numbers were the same:\n");

    for (i = 0; i < 10; i++) {
        printf("\tRandom Number %d: %d\n", i, rand[i]);
    }

    close(out);

    return 0;
}