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

int getIndex(char [], char []);
ContactPtr createContact(char [], char [], int);
void addContact(int, ContactPtr, ContactPtr []);

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
        printf("8. List contacts\n");
        printf("0. Exit program\n\n");
        printf("   Enter your option: ");
        scanf("%d", &select);
        //system("@cls||clear");
        
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
            
            ContactPtr newContact = createContact(firstName, lastName, phoneNumber);
            
            int index = getIndex(firstName, lastName);
            
            addContact(index, newContact, contacts);
            
        } else if (select == 2){
            char firstName[50];
            char lastName[50];
            printf("Enter first name: ");
            scanf("%s", firstName);
            printf("Enter last name: ");
            scanf("%s", lastName);
            
            int index = getIndex(firstName, lastName);
            
            ContactPtr contact = contacts[index];
            
             if (contact == NULL){
                printf("Contact not found!\n");       
            } else {
                printf("Current phone number: %d\n\n", contact -> data.phoneNumber);
                printf("Enter new phone number: ");
                scanf("%d", &contact -> data.phoneNumber);
                printf("New phone number saved!\n");
            }
            
        } else if (select == 3) {
            char firstName[50];
            char lastName[50];
            printf("Enter first name: ");
            scanf("%s", firstName);
            printf("Enter last name: ");
            scanf("%s", lastName);
            
            int index = getIndex(firstName, lastName);
            
            ContactPtr contact = contacts[index];
            
            while (contact != NULL){
                if (strcmp(contact -> data.firstName, firstName) == 0 && strcmp(contact -> data.lastName, lastName) == 0){
                    break;
                } else {
                    contact = contact -> next;
                }
            }
            
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
            
            int index = getIndex(firstName, lastName);
            
            ContactPtr contact = contacts[index];
            
            if (contact == NULL){
                printf("Contact not found!\n");
            } else {
                printf("The following contact:\n");
                printf("First name: %s\n", contact -> data.firstName);
                printf("Last name: %s\n", contact -> data.lastName);
                printf("First name: %d\n", contact -> data.phoneNumber); 
                printf("Was successfully deleted!\n");
                
                contacts[index] = NULL;
            }
        } else if (select == 5){
            // Write file
            FILE *out = fopen("contacts.txt", "w");
            
            for(int i = 1; i <= MAX_CONTACTS; i++){
                if (contacts[i] != 0){
                    fprintf(out, "%s ", contacts[i] -> data.firstName);
                    fprintf(out, "%s ", contacts[i] -> data.lastName);
                    fprintf(out, "%d\n", contacts[i] -> data.phoneNumber);
                    
                    ContactPtr nextContact = contacts[i] -> next;
                    
                    while (nextContact != NULL){
                        fprintf(out, "%s ", nextContact -> data.firstName);
                        fprintf(out, "%s ", nextContact -> data.lastName);
                        fprintf(out, "%d\n", nextContact -> data.phoneNumber);
                        
                        nextContact = nextContact -> next;
                    }
                }
            }
            
            fclose(out);
            
            printf("File Saved!\n");
            
        } else if (select == 6){
            ContactPtr contact = (ContactPtr) malloc(sizeof(Contact));
            
            ContactPtr contacts[MAX_CONTACTS + 1] = {0};
            // Read file
            FILE *in = fopen("contacts.txt", "r");
            
            // Get name and grade until EOF
            while (fscanf(in, "%s", contact -> data.firstName) != EOF){

                fscanf(in, "%s", contact -> data.lastName);
                fscanf(in, "%d", &contact -> data.phoneNumber);
                
                int index = getIndex(contact -> data.firstName, contact -> data.lastName);
                
                addContact(index, contact, contacts);
            }
            
            fclose(in);
        } else if (select == 7){
            //TO DO   
        } else if (select == 8){
            printf("Contact List\n");
            
            for(int i = 1; i <= MAX_CONTACTS; i++){
                if (contacts[i] != 0){
                    printf("First Name: %s\n", contacts[i] -> data.firstName );
                    printf("Last Name: %s\n", contacts[i] -> data.lastName );
                    printf("Phone Number: %d\n\n", contacts[i] -> data.phoneNumber ); 
                    
                    ContactPtr nextContact = contacts[i] -> next;
                    
                    while (nextContact != NULL){
                        printf("First Name: %s\n", nextContact -> data.firstName );
                        printf("Last Name: %s\n", nextContact -> data.lastName );
                        printf("Phone Number: %d\n\n", nextContact -> data.phoneNumber );
                        
                        nextContact = nextContact -> next;
                    }
                }
            }
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
int getIndex(char firstName[], char lastName[]){
    char fullName[101];
    strcpy(fullName, firstName);
    strcat(fullName, " ");
    strcat(fullName, lastName);

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

void addContact(int index, ContactPtr newContact, ContactPtr contacts[]){
    if (contacts[index] == NULL){
        contacts[index] = newContact;              
    } else { // We have a collision!
        ContactPtr currentContact = contacts[index];

        // Verify the first item. If the new contact is lower, store it as first and move the current to next
        if (strcmp(currentContact -> data.firstName, newContact -> data.firstName) > 0 &&
                strcmp(currentContact -> data.firstName, newContact -> data.firstName) > 0) {
                newContact -> next = currentContact;
                contacts[index] = newContact;
        } else { // Get the next one and compare
            ContactPtr nextContact = currentContact -> next;

                // Create a sorted link list
                while (nextContact != NULL){
                    if (strcmp(nextContact -> data.firstName, newContact -> data.firstName) > 0 &&
                        strcmp(nextContact -> data.firstName, newContact -> data.firstName) > 0) {
                        currentContact -> next = newContact;
                        newContact -> next = nextContact;
                        break;
                    } else {
                        currentContact = nextContact;
                        nextContact = currentContact -> next;
                    }
                }

            if (currentContact == NULL){ // If there is no next, store new contact as next
                currentContact -> next = newContact;
            }
        }
    }
}