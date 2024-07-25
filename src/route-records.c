//
// Created by Yash Verma on 4/10/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"//Calling header file

RouteRecord* createRecords(FILE* infile){//This method returns RouteRecord pointer.
    char firstChar[50];
    int lineCount = 0;
    int i;
    int j;

    while(fgets(firstChar, 50, infile) != NULL){//This loop parses through the csv to know how many lines.
        lineCount++;//Increment
    }
    lineCount = lineCount - 1;//Because the first line needs to be ignored we do minus 1.

    RouteRecord* rec = (RouteRecord*)malloc(lineCount * sizeof(RouteRecord));//This is creating the struct array with respective memory needed.

    for(j = 0; j < lineCount; j++){//this nested for loop initializes all values of the array to 0.
        for(i = 0; i < 6; i++){
            rec[j].passengerCount[i] = 0;
        }
    }
    rewind(infile);//Brings the cursor back to the top of the csv file.
    return rec;//returns the pointer of type RouteRecord.
}

int fillRecords(RouteRecord* r, FILE* infile){//This function returns the index which goes back into the parameter of recursive calls.
    //This call returns the indexNum where the three strings appear in the array. If it doesn't find, -1.
    char wholeLine[50];
    char origin[3+1];
    char destination[3+1];
    char airline[2+1];
    char passType[10+1];
    int monthNum = 0;
    int passenCount = 0;
    int length = 0;
    int currIndex = 0;

    while(fgets(wholeLine, 50, infile) != NULL){//This loop counts the number of lines there are
        length++;
    }
    length = length - 1;//Length - 1 because the first line is garbage
    rewind(infile);//Brings the cursor back to the top of csv file
    fgets(wholeLine, 50, infile);//This reads the first line which we want to ignore.


    while(fgets(wholeLine, 50, infile) != NULL){//This loop goes till the file ends.

        sscanf(wholeLine, "%d,%[^,],%[^,],%[^,],%[^,],%d", &monthNum, origin, destination, airline, passType, &passenCount);//This parses the variable wholeLine to their respective variables.

        int ret = findAirlineRoute(r, length, origin, destination, airline, 0);//This call returns the indexNum where the three strings appear in the array. If it doesn't find, -1.

        if(ret == -1){//if the return value is -1
            strcpy(r[currIndex].origin, origin);//copy respective origin
            strcpy(r[currIndex].destination ,destination);//copy respective destination
            strcpy(r[currIndex].airline, airline);//copy respective airline
            r[currIndex].passengerCount[monthNum - 1] = passenCount;//copy respective passenger count
            currIndex++;//increment currIndex
        }
        else{
            r[ret].passengerCount[monthNum - 1] += passenCount;
        }

    }
    printf("\nUnique routes operated by airlines: %d\n", currIndex);
    return currIndex;//return
}


int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx){//This function returns the currIndex if matched else returns -1
    // base case
    if(curIdx >= length) {
        return -1;//When it goes beyond array bound.
        // check origin, dest, airline match
    } if(strcmp(r[curIdx].origin, origin) == 0 && strcmp(r[curIdx].destination, destination) == 0 && strcmp(r[curIdx].airline, airline) == 0){
        return curIdx;//Returns the currIdx if the origin, destination, and airlines match
    } else {
        // recursive call
        return findAirlineRoute(r, length, origin, destination, airline, ++curIdx);//Calls the function with the next index.
    }
}


void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st){//This function prints the flight info and statistics.
    int i = 0;
    int j = 0;
    int caseCounter = 0;
    int totalPassengers = 0;
    int monhtlyPass[6] = {0};
    for(i = 0; i < length; i++){//This loop going from 0 to length - 1.

        switch(st){//This switch statement is taking in enum type
            case ROUTE:
                if((strcmp(r[i].origin, key1) == 0) && (strcmp(r[i].destination, key2) == 0)){
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    caseCounter += 1;
                    for(j = 0; j < 6; j++){
                        totalPassengers = totalPassengers + r[i].passengerCount[j];
                        monhtlyPass[j] += r[i].passengerCount[j];
                    }
                }
                break;

            case ORIGIN:
                if((strcmp(r[i].origin, key1) == 0)){
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    caseCounter += 1;
                    for(j = 0; j < 6; j++){
                        totalPassengers = totalPassengers + r[i].passengerCount[j];
                        monhtlyPass[j] += r[i].passengerCount[j];
                    }
                }
                break;

            case DESTINATION:
                if((strcmp(r[i].destination, key1) == 0)){
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    caseCounter += 1;
                    for(j = 0; j < 6; j++){
                        totalPassengers = totalPassengers + r[i].passengerCount[j];
                        monhtlyPass[j] += r[i].passengerCount[j];
                    }
                }
                break;

            case AIRLINE:
                if((strcmp(r[i].airline, key2) == 0)){
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    caseCounter += 1;
                    for(j = 0; j < 6; j++){
                        totalPassengers = totalPassengers + r[i].passengerCount[j];
                        monhtlyPass[j] += r[i].passengerCount[j];
                    }
                }
                break;

        }
    }
    printf("\n%d matches were found.\n", caseCounter);//Prints all the stats
    printf("\nStatistics\n");
    printf("Total Passengers:\t%d\n", totalPassengers);
    int k = 0;
    for(k = 0; k < 6; k++){
        printf("Total Passengers in Month %d:\t%d\n", k+1, monhtlyPass[k]);
    }
    int avg = totalPassengers / 6;
    printf("\nAverage Passenger Per Month:\t%d\n", avg);

}


void printMenu(){//This function prompts the user what they want to do.
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Destination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}