#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

int main(int argc, char *argv[]){//This function ties the whole project together.

    //If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    if(argc < 2){
        printf("ERROR: Missing file name");
        return -1;
    }
    //Print out Opening <filename>... before you call fopen().
    printf("Opening %s...", argv[1]);
    FILE* infile = fopen(argv[1], "r");

    //If it does not open, print out ERROR: Could not open file and end the program.
    if(infile == NULL){
        printf("ERROR: Could not open file");
        return -1;
    }


    //Call createRecords(), which will read through the file once to find the total number of lines/records in the file.
    //Create pointer out of what createRecords return
    RouteRecord* r = createRecords(infile);

    /*Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has.*/
    int numLines = fillRecords(r, infile);
    int userNum;
    /*Close the file.*/
    fclose(infile);

    /*an infinite loop*/
    while(1) {

        /*Call printMenu()*/
        printMenu();
        /*Ask the user to input a value for the menu*/
        scanf("%d", &userNum);

        /*A switch/case statement to handle all the menu options*/
        char key1[3+1];//key1 Variable
        char key2[3+1];//key2 Variable

        switch(userNum){//This control statement calls the function respective to the userNum.
            case 1://when userNum is 1
                printf("Enter origin: ");//key1
                scanf("%s", key1);
                printf("Enter destination: ");//key2
                scanf("%s", key2);
                printf("\nSearching by route...\n");
                searchRecords(r, numLines, key1, key2, ROUTE);
                break;
            case 2://when userNum is 2
                printf("Enter origin: ");//key1
                scanf("%s", key1);
                printf("\nSearch by origin...\n");
                searchRecords(r, numLines, key1, "NULL\0", ORIGIN);
                break;
            case 3://when userNum is 3
                printf("Enter destination: ");//key1
                scanf("%s", key1);
                printf("\nSearching by destination...\n");
                searchRecords(r, numLines, key1, "NULL\0", DESTINATION);
                break;
            case 4://when userNum is 4
                printf("Enter airline: ");//key2
                scanf("%s", key2);
                printf("\nSearch by airline...\n");
                searchRecords(r, numLines, "NULL\0", key2, AIRLINE);
                break;
            case 5://when userNum is 5
                free(r);//HERE WE FREE THE ARRAY USING FREE METHOD.
                printf("Good-bye!");
                return 0;

            default://when neither match
                printf("Invalid choice.");

        }

    }


    return 0;
}