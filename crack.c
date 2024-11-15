#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int strcomp(const void *a,const void *b);


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    char line[HASH_LEN + 1];
    int numberofhash = 0;

    FILE *file1 = fopen(argv[1],"r");

    if (file1 == NULL){
        printf("no able to read file %s\n", argv[1]);
        exit(1);
    }

    // capacity for array
    int capacity = 1000;

    // allocating the memory for the array
    char **array = (char **) malloc(capacity * sizeof(char *));
    if(array == NULL){
        printf("memory failed\n");
        exit(1);
    }

    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);

    while(fgets(line,sizeof(line),file1) != NULL){

        //Trim newline.
		char *nl = strchr(line,'\n');
        if(nl) *nl = '\0';

        // reallocating the memory
        if (numberofhash >= capacity){
            capacity *= 2;
            char **temp = (char **) realloc (array, capacity * sizeof(char *));
            if (temp == NULL){
                printf("memory failed");
                free(array);
                exit(1);
            }
            array = temp;
        }

       // memory for each string
        array[numberofhash] = (char *)malloc((strlen(line) + 1) * sizeof(char));
        if (array[numberofhash] == NULL){
            printf("memory failed");
            free(array[numberofhash]);
            exit(1);
        }
        //copying the line into the array
        char *str = strcpy(array[numberofhash],line);

        numberofhash++;
    }
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(array,size,sizeof(char**),strcomp);

    /*//for testig porposes printing the array after sorting 
    for (int i = 0; i < numberofhash; i++) {
        printf("Hash %d: %s\n", i + 1, array[i]);
        free(array[i]);
    }*/

    // TODO
    // Open the password file for reading.
    FILE *file2 = fopen(argv[2],"r");

    if (file2 == NULL){
        printf("no able to read file %s\n", argv[2]);
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search. 

    //password variable
    char passW[PASS_LEN];
    int hashesfound = 0;

    while(fgets(passW,PASS_LEN,file2)){

        //trimming the new line character
        char *nl = strchr(passW,'\n');
        if(nl) *nl = '\0';

        // Hash the password.
        char *hash = md5(passW, strlen(passW));

        //array search
        char *found = substringSearchAA(passW, hashes, size);

        if(found){
            hashesfound++;
            printf("Hashes Found %d: %s\n",hashesfound , found);
        }

    }
    
    // TODO
    // When done with the file:
    //   Close the file
    fclose(file1);
    fclose(file2);

    //   Display the number of hashes found.

    //   Free up memory.
    free(array);
    free(array[numberofhash]);
}

// string compare function
int strcomp(const void *a,const void *b){

    char **aa = (char **)a;
    char **bb = (char **)b;

    return strcmp(*aa, *bb);
    
}
