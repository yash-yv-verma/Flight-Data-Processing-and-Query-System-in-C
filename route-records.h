#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

//Creating struct type for RouteRecord and declaring data members. --->
typedef struct RouteRecord_struct {
    char origin[3+1];
    char destination[4+1];
    char airline[2+1];
    int passengerCount[7];
} RouteRecord;

//Creating enum type for SearchType and declaring enum members. --->
typedef enum SearchType {
    ROUTE, ORIGIN, DESTINATION, AIRLINE
} SearchType;

//Prototypes --->
RouteRecord* createRecords(FILE* filein);
int fillRecords(RouteRecord* r, FILE* filein);
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

#endif