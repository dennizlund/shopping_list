//
//  list.h
//  shoppingList
//
//  Created by Dennis Lund on 2017-10-15.
//  Copyright © 2017 Dennis Lund. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>

typedef struct {
    char name[32];
    char unit[32];
    float amount;
}item;

typedef struct {
    item *items;
    int amountOfItems;
}itemList;

void printOptions(void);

#endif /* list_h */
