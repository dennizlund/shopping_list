//
//  main.c
//  shoppingList
//
//  Created by Dennis Lund on 2017-10-15.
//  Copyright © 2017 Dennis Lund. All rights reserved.
//


#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#define MAX_SIZE_NAME 32

int addItemFromUser(itemList *pMyList);
void clearBuffer(void);
float inputController(char tempArray[MAX_SIZE_NAME]);
void printList(itemList *pMyList);
void removeNewLine(itemList *pMyList);
item *allocItemMemory(itemList *pMyList);
void getUserItemFields(char *pName, char *pUnit, float *amount);
void assignItem(item *pItem, char *name, char *unit, float amount);
void removeItem(itemList *pMylist);
void changeItem(itemList *pMyList);
int *getSearchIndex(itemList *pMyList);
void saveToBinFile(itemList *pMyList);
void loadFromBinFile(itemList *pMyList);

int main(int argc, const char * argv[]) {
    
    itemList myList;
    myList.items = NULL;
    myList.amountOfItems = 0;                     // Sätter antal varor till 0.
                                                  // itemList pekaren är satt till den som skapats.
                                                  // En int variabel som representerar antal varor i shopping listan.
    int userChoice = 0, endLoop = 0;
    
    
    
    
    do{
        printOptions();
        scanf("%d", &userChoice);
        clearBuffer();
        switch (userChoice) {
            case 1:
                addItemFromUser(&myList);
                break;
            case 2:
                printList(&myList);
                break;
            case 3:
                removeItem(&myList);
                break;
            case 4:
                changeItem(&myList);
                break;
            case 5:
                saveToBinFile(&myList);
                break;
            case 6:
                loadFromBinFile(&myList);
                break;
            case 7:
                endLoop = 1;
                break;
            default:
                printf("Choice does not exist, please try again. \n");
                break;
        }
    } while (endLoop == 0);
    
    
    return 0;
}

void printOptions(){
    printf("1: Add item\n");
    printf("2: Print list\n");
    printf("3: Remove an item\n");
    printf("4: Change an item\n");
    printf("5: Save shopping list\n");
    printf("6: Load shopping list\n");
    printf("7: Exit program\n\n");
    
    printf("Your choice: ");
}

int addItemFromUser(itemList *pMyList){

    item* pItem = allocItemMemory(pMyList);
    
    char name[MAX_SIZE_NAME], unit[MAX_SIZE_NAME];
    float amount;
    
    getUserItemFields(name,unit,&amount);
    assignItem(pItem,name,unit,amount);
    
    
    return 1;
}

void getUserItemFields(char *pName, char *pUnit, float *amount){
    
    long lenght = 0;
    char tempArray[MAX_SIZE_NAME];
    
    printf("Type item name: \n");
    fgets(pName, MAX_SIZE_NAME, stdin);
    lenght = strlen(pName) -1;
    pName[lenght] = '\0';
    
    
    printf("Type item unit: \n");
    fgets(pUnit, MAX_SIZE_NAME, stdin);
    lenght = strlen(pUnit) - 1;
    pUnit[lenght] = '\0';
    
    printf("Type amount of item: \n");
    fgets(tempArray, MAX_SIZE_NAME, stdin);
    
    while(inputController(tempArray) == 0){
        fgets(tempArray, MAX_SIZE_NAME, stdin);
    }
    
    *amount = inputController(tempArray);
}

item *allocItemMemory(itemList *pMyList) {
    int amountOfItems = pMyList->amountOfItems;
    item *pTempMem = NULL;
    if(pMyList->amountOfItems == 0){                            // Om det är första varan, så används malloc.
        pTempMem = (item*)malloc(sizeof(item));
        if(pTempMem==NULL){
            printf("Failed to allocate memory, shutting off.\n");
            return NULL;
        }
        else{
            pMyList->items = pTempMem;
            pMyList->amountOfItems++;
            return pMyList->items;
        }
    }
    else{                                                       // Om det är fler än 1 vara, realloc.
        pTempMem = (item*)realloc(pMyList->items, sizeof(item) * amountOfItems+1);
        if(pTempMem == NULL){
            printf("Failed to allocate memory, shutting off.\n");
            return NULL;
        }
        else{
            pMyList->items = pTempMem;
            pMyList->amountOfItems++;
            return &pMyList->items[amountOfItems];
        }
    }
    
    

}

float inputController(char tempArray[MAX_SIZE_NAME]){                            // Kollar användarens inmatning.
    int i;
    float correctValue;
    
    for(i = 0; tempArray[i] != '\0'; i++){
        if(tempArray[0] == '\n'){
            printf("You have to type an amount, please try again: \n");
        }
        if(tempArray[i] == '-'){                                    // Om första tecknet är ett - avbryt inmatning.
            printf("Amount has to be positvite, please try again: \n");
            return 0;
        }
        if(tempArray[0] == '0'){                                    // Om första tecknet är noll - avbryt inmatning.
            printf("Amount has to be bigger than 0, please try again: \n");
            return 0;
        }
        if(isalpha(tempArray[i]) != 0){                             // Om något tecken är en bokstav avbryt inmatning.
            printf("Amount contains only numbers, please try again: \n");
            return 0;
        }
        
    }
    correctValue = atof(tempArray);                                 // Omvandlar strängen till en float.
    
    return correctValue;
}

void clearBuffer(){
    while(getchar() != '\n');
}

void printList(itemList *pMyList){   //Skriver ut listan av varor.
    
    int amountOfItems = pMyList->amountOfItems;
    
    int i = 0, index = 1;
    
    if(amountOfItems == 0){
        printf("\n\nYour shoppinglist is empty...\n\n\n");
    }
    printf("***************************************\n\n");
    if(amountOfItems == 1){
        printf("Your list contains %d item\n\n", amountOfItems);
    }
    else
    {
        printf("Your list contains %d items\n\n", amountOfItems);
    }
    
    for(i = 0; i < amountOfItems; i++)                  // Skriver ut alla varor.
    {
        printf("%d. ", index++);
        printf("%.2f\t",pMyList->items[i].amount);
        printf("%-10s\t", pMyList->items[i].unit);
        printf("%-18s\n", pMyList->items[i].name);
        
    }
    printf("\n");
}

void removeNewLine(itemList *pMyList){                       // Funktionen underlättar utskriften.
    
    int amountOfItems = pMyList->amountOfItems;
    
    long lastIndexOfName = strlen(pMyList->items[amountOfItems].name) -1;       // Sparar sista index av namn strängen
    long lastIndexOfType = strlen(pMyList->items[amountOfItems].unit) -1;       // Sparar sista indet av typ strängen
    pMyList->items[amountOfItems].name[lastIndexOfName] = '\0';                 // Ersätter den med \0
    pMyList->items[amountOfItems].unit[lastIndexOfType] = '\0';                 // Ersätter den med \0
}

void removeItem(itemList *pMylist){
    
    int amountOfItems = pMylist->amountOfItems, i;
    char searchString[MAX_SIZE_NAME];
    int *index = NULL;
    long lenght = 0;
    
    printf("Type the name of the item you want to remove: \n");
    fgets(searchString, MAX_SIZE_NAME, stdin);
    lenght = strlen(searchString) -1;
    searchString[lenght] = '\0';
    
    for(i = 0; i<amountOfItems; i++){
        if(strcmp(searchString, pMylist->items[i].name) == 0){
            printf("Found item\n\n");
            index = &i;
            break;
        }
        
    }
    if(index == NULL){
        printf("Did not find item.\n\n");
        return;
    }
    while(*index < amountOfItems -1){
        
    item *foundItem = &pMylist->items[*index];
    *foundItem = pMylist->items[++*index];
    
    }
    
    pMylist->amountOfItems--;
    pMylist->items = (item*)realloc(pMylist->items, amountOfItems * sizeof(item));
    
}

void assignItem(item *pItem, char *name, char *unit, float amount){
    
    strcpy(pItem->name, name);
    strcpy(pItem->unit, unit);
    pItem->amount = amount;
    
    
}


void getUserAmountField( float *amount) {
    char tempArray[MAX_SIZE_NAME];
    
    printf("Type amount of item: \n");
    fgets(tempArray, MAX_SIZE_NAME, stdin);

    while((*amount = inputController(tempArray)) == 0){
        fgets(tempArray, MAX_SIZE_NAME, stdin);
    }
}


void changeItem(itemList *pMyList){
    int *index;
    index = getSearchIndex(pMyList);
    getUserAmountField(&pMyList->items[*index].amount);
}

int *getSearchIndex(itemList *pMyList){
    
    int amountOfItems = pMyList->amountOfItems, i;
    char searchString[MAX_SIZE_NAME];
    int *index = NULL;
    long lenght = 0;
    
    printf("Type the name of the item you want to change: \n");
    fgets(searchString, MAX_SIZE_NAME, stdin);
    lenght = strlen(searchString) -1;
    searchString[lenght] = '\0';
    
    for(i = 0; i<amountOfItems; i++){
        if(strcmp(searchString, pMyList->items[i].name) == 0){
            printf("Found item\n\n");
            index = &i;
            printf("Item deleted\n\n");
            return index;
        }
        
    }
    if(index == NULL){
        printf("Did not find item.\n\n");
        return NULL;
    }
    return NULL;
}

void saveToBinFile(itemList *pMyList){
    
    char nameOfFile[MAX_SIZE_NAME];
    int amountOfItems = pMyList->amountOfItems;
    
    printf("Type filename: \n");
    fgets(nameOfFile, MAX_SIZE_NAME, stdin);
    
    FILE *fp;
    
    fp = fopen(nameOfFile, "wb");
    
    fwrite(&pMyList->amountOfItems, sizeof(int), 1, fp);
    fwrite(pMyList->items, sizeof(item), amountOfItems, fp);
    
    fclose(fp);
    
    
}

void loadFromBinFile(itemList *pMyList){
    
    char nameOfFile[MAX_SIZE_NAME];
    
    printf("Type filename: \n");
    fgets(nameOfFile, MAX_SIZE_NAME, stdin);
    
    FILE *fp;
    
    fp = fopen(nameOfFile, "rb");
    
    fread(&pMyList->amountOfItems, sizeof(int), 1, fp);
    
    pMyList->items = (item*)malloc(pMyList->amountOfItems * sizeof(item));
    
    fread(pMyList->items, sizeof(item), pMyList->amountOfItems, fp);
    
    
}

void saveToTextFile(itemList *pMyList){
    
    
}
