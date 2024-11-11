#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    char line[HASH_LEN + 1];
    int hashesFound = 0;

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

    while(fgets(line,sizeof(line),file1) != NULL){

        //Trim newline.
		char *nl = strchr(line,'\n');
        if(nl) *nl = '\0';


        // reallocating the memory
        if (hashesFound >= capacity){
            capacity *= 2;
            char **temp = (char **) realloc (array, capacity * sizeof(char *));
            if (temp == NULL){
                printf("memory failed");
                free(array);
                exit(1);
            }
            array = temp;
        }

         // meomyry for each string
        array[hashesFound] = (char *)malloc((strlen(line) + 1) * sizeof(char));

        //copying the line into the array
        strcpy(array[hashesFound],line);

        hashesFound++;

    }

    for (int i = 0; i < hashesFound; i++) {
        printf("Hash %d: %s\n", i + 1, array[i]);
        free(array[i]);
    }  

    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    //char **hashes = loadFile(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.

    //qsort(array,size,sizeof(char **),strcmp);

    // TODO
    // Open the password file for reading.
    FILE *file2 = fopen(argv[2],"r");

    if (file1 == NULL){
        printf("no able to read file %s\n", argv[2]);
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search.
    

    // TODO
    // When done with the file:
    //   Close the file
    fclose(file1);
    fclose(file2);
    //   Display the number of hashes found.
    //printf("%d Haseshes found",hashesFound);
    //   Free up memory.
    free(array);
}
