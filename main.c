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
ContactPtr searchContact (char [], char [], ContactPtr []);
ContactPtr deleteContact(char [], char [], ContactPtr []);
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
            scanf("%d", &phoneNumber);
            
            ContactPtr contact = createContact(firstName, lastName, phoneNumber);
            
            int index = getIndex(contact);
            
            contacts[index] = contact;
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
                printf("Contact not found!\n");
            } else {
                printf("First name: %s\n", contact -> data.firstName);
                printf("Last name: %s\n", contact -> data.lastName);
                printf("Phone number: %d\n\n", contact -> data.phoneNumber);
            }
        } else if (select == 4){
            char firstName[50];
            char lastName[50];
            printf("Enter first name: ");
            scanf("%s", firstName);
            printf("Enter last name: ");
            scanf("%s", lastName);
            
            ContactPtr contact = searchContact(firstName, lastName, contacts);
            
            if (contact == NULL){
                printf("Contact not found!\n");
            } else {
                printf("The following contact:\n");
                printf("First name: %s\n", contact -> data.firstName);
                printf("Last name: %s\n", contact -> data.lastName);
                printf("First name: %d\n", contact -> data.phoneNumber); 
                printf("Was successfully deleted!\n");
            }
        } else if (select == 5){
            //TO DO
        } else if (select == 6){
            //TO DO           
        } else if (select == 7){
            //TO DO           
        } else if (select == 0){
                printf("Thank you!\n");
                printf("This program was developed by\n");
                printf("Ricardo Satoshi Ikeima\n");
                printf("Rongfu Li\n"); 
                printf("PROG20799 Data Structures & Algorithm Development - C\n"); 
                printf("Final Project - 14 - AUG - 2017\n");
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

    ContactPtr input = createContact(firstName, lastName, 0);
    
    int index = getIndex(input);
    ContactPtr contact = array[index];
       
    while (contact != NULL){
        if (strcmp(contact -> data.firstName, firstName) == 0 && strcmp(contact -> data.lastName, lastName) == 0){
            return contact;
        } else {
            contact = contact -> next;
        }
    }
    
    return NULL;
}

// Delete contact
ContactPtr deleteContact (char firstName[], char lastName[], ContactPtr array[]){

    ContactPtr input = createContact(firstName, lastName, 0);
    
    int index = getIndex(input);
    
    ContactPtr contact = array[index];
       
    while (contact != NULL){
        if (strcmp(contact -> data.firstName, firstName) == 0 && strcmp(contact -> data.lastName, lastName) == 0){
            array[index] = NULL;
            return contact;
        } else {
            contact = contact -> next;
        }
    }
    
    return NULL;
}