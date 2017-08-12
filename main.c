/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Ricardo Satoshi Ikeima / Rongfu Li
 *
 * Created on August 12, 2017, 8:40 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 500

typedef struct { 
    char firstName[50];
    char lastName[50];
    int phoneNumber;
} NodeData;

typedef struct node{
    NodeData data;
    struct node *next;
} Contact, *ContactPtr;

int getIndex(ContactPtr);
ContactPtr createContact(char [], char [], int);

/*
 * 
 */
int main() {

    // Create array of contacts
    ContactPtr contacts[MAX_CONTACTS + 1] = {0};
       
    int select = -1;
    
    // MENU
    while (select != 0){
        printf("--- Contact List: Main Menu ---\n");
        printf("1. Add new contact\n");
        printf("2. Edit contact\n");
        printf("3. Search for contact\n");
        printf("4. Delete contact\n");
        printf("5. Save contacts to file\n");
        printf("6. Load contacts from file\n");
        printf("7. Sort contacts\n");
        printf("0. Exit program\n\n");
        printf("   Enter your option: ");
        scanf("%d", &select);
        system("@cls||clear");
        
        if (select == 1){
            char firstName[50];
            char lastName[50];
            int phoneNumber;
            printf("Enter first name: ");
            scanf("%s", firstName);
            printf("Enter last name: ");
            scanf("%s", lastName);
            printf("Enter phone number: ");
            scanf("%s", phoneNumber);
            
            ContactPtr contact = createContact(firstName, lastName, phoneNumber);
                
            contacts[getIndex(contact)] = contact;
        } else if (select == 2){
            // TODO
        } else if (select == 3) {
            char firstName[50];
            char lastName[50];
            printf("Enter first name: ");
            scanf("%s", firstName);
            printf("Enter last name: ");
            scanf("%s", lastName);
            
            ContactPtr contact = searchContact(firstName, lastName, contacts);
            
            if (contact == NULL){
                printf("Contact not found!");
            }
        }
    }

    return (0);
}

// Enter full name and return the index
int getIndex(ContactPtr contact){
    char fullName[101];
    strcpy(fullName, contact -> data.firstName);
    strcat(fullName, " ");
    strcat(fullName, contact -> data.lastName);

    int charIndex = 0;
    int result = 0;
    
    while (fullName[charIndex] != '\0'){
        // Get char value and multiply by Weight (charIndex + 1)
        result += (int)fullName[charIndex] * (++charIndex);
    }
    
    return (result % MAX_CONTACTS) + 1;
}

// Create the contact
ContactPtr createContact(char firstName[], char lastName[], int phoneNumber){
    ContactPtr contact = (ContactPtr)malloc(sizeof(Contact));
    strcpy(contact -> data.firstName, firstName);
    strcpy(contact -> data.lastName, lastName);
    contact -> data.phoneNumber = phoneNumber;
    contact -> next = NULL;
    
    return contact;
}

// Search contact
ContactPtr searchContact (char firstName[], char lastName[], ContactPtr array[]){

    ContactPtr contact = array[getIndex(input)];
       
    while (contact != NULL){
        if (strcmp(contact -> data.firstName, firstName) != 0 && strcmp(contact -> data.lastName, lastName)){
            return contact;
        } else {
            contact = contact -> next;
        }
    }
}