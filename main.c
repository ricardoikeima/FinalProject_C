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
    float phoneNumber;
} NodeData;

typedef struct node{
    NodeData data;
    struct node *next;
} Contact, *ContactPtr;

int getIndex(char [], char []);
ContactPtr createContact(char [], char [], int);
void addContact(int, ContactPtr, ContactPtr []);
void sortContacts(ContactPtr []);
ContactPtr insertContactIntoLinkList (ContactPtr, ContactPtr);
    
/*
 * 
 */
int main() {

    // Create array of contacts
    ContactPtr contacts[MAX_CONTACTS + 1] = { NULL };
       
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
        printf("9. Load contacts sample\n");
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
            scanf("%f", &phoneNumber);
            
            ContactPtr newContact = createContact(firstName, lastName, phoneNumber);
            
            int index = getIndex(firstName, lastName);
            
            addContact(index, newContact, contacts);
            
            system("@cls||clear");            
            
            printf("Contact successfully added!\n\n");
            
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
                printf("Current phone number: %.0f\n\n", contact -> data.phoneNumber);
                printf("Enter new phone number: ");
                scanf("%f", &contact -> data.phoneNumber);
                
                system("@cls||clear");
                
                printf("New phone number saved!\n\n");
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
                printf("Contact not found!\n\n");
            } else {
                system("@cls||clear");
                
                printf("First name: %s\n", contact -> data.firstName);
                printf("Last name: %s\n", contact -> data.lastName);
                printf("Phone number: %.0f\n\n", contact -> data.phoneNumber);                                           
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
                printf("First name: %.0f\n", contact -> data.phoneNumber); 
                
                system("@cls||clear");
                
                printf("Was successfully deleted!\n\n");
                
                contacts[index] = NULL;
            }
        } else if (select == 5){
            // Write file
            FILE *out = fopen("contacts.txt", "w");
            
            for(int i = 0; i <= MAX_CONTACTS; i++){
                if (contacts[i] != 0){
                    fprintf(out, "%s ", contacts[i] -> data.firstName);
                    fprintf(out, "%s ", contacts[i] -> data.lastName);
                    fprintf(out, "%0.f\n", contacts[i] -> data.phoneNumber);
                    
                    ContactPtr nextContact = contacts[i] -> next;
                    
                    while (nextContact != NULL){
                        fprintf(out, "%s ", nextContact -> data.firstName);
                        fprintf(out, "%s ", nextContact -> data.lastName);
                        fprintf(out, "%0.f\n", nextContact -> data.phoneNumber);
                        
                        nextContact = nextContact -> next;
                    }
                }
            }
            
            fclose(out);
            
            system("@cls||clear");
            
            printf("File Saved!\n");
            
        } else if (select == 6){
            ContactPtr temp = (ContactPtr) malloc(sizeof(Contact));
            
            // Clear contact list
            for(int i = 1; i <= MAX_CONTACTS; i++){
                if (contacts[i] != NULL){
                    contacts[i] = NULL;
                }
            }
            
            // Read file
            FILE *in = fopen("contacts.txt", "r");
            
            // Get name and grade until EOF
            while (fscanf(in, "%s", temp -> data.firstName) != EOF){

                fscanf(in, "%s", temp -> data.lastName);
                fscanf(in, "%f", &temp -> data.phoneNumber);
                temp -> next = NULL;
                
                int index = getIndex(temp -> data.firstName, temp -> data.lastName);
                
                addContact(index, temp, contacts);
            }
            
            fclose(in);
        } else if (select == 7){
            sortContacts(contacts);
        } else if (select == 8){
            printf("Contact List\n");
            
            for(int i = 1; i <= MAX_CONTACTS; i++){
                if (contacts[i] != NULL){
                    
                    printf("First Name: %s\n", contacts[i] -> data.firstName );
                    printf("Last Name: %s\n", contacts[i] -> data.lastName );
                    printf("Phone Number: %.0f\n\n", contacts[i] -> data.phoneNumber ); 
                    
                    ContactPtr nextContact = contacts[i] -> next;
                    
                    while (nextContact != NULL){

                        printf("First Name: %s\n", nextContact -> data.firstName );
                        printf("Last Name: %s\n", nextContact -> data.lastName );
                        printf("Phone Number: %.0f\n\n", nextContact -> data.phoneNumber );
                        
                        nextContact = nextContact -> next;
                    }
                }
            }
        } else if (select == 9){
            ContactPtr temp = (ContactPtr) malloc(sizeof(Contact));
            
            // Clear contact list
            for(int i = 1; i <= MAX_CONTACTS; i++){
                if (contacts[i] != NULL){
                    contacts[i] = NULL;
                }
            }
            
            // Read file
            FILE *in = fopen("sample.txt", "r");
            
            // Get name and grade until EOF
            while (fscanf(in, "%s", temp -> data.firstName) != EOF){

                fscanf(in, "%s", temp -> data.lastName);
                fscanf(in, "%f", &temp -> data.phoneNumber);
                temp -> next = NULL;
                
                int index = getIndex(temp -> data.firstName, temp -> data.lastName);
                
                addContact(index, temp, contacts);
            }
            
            fclose(in);
        } else if (select == 0){ // Exit program and message
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

// Add contact to contact list
void addContact(int index, ContactPtr contact, ContactPtr contacts[]){
    
    ContactPtr newContact = (ContactPtr) malloc(sizeof(Contact));
    
    strcpy(newContact -> data.firstName, contact -> data.firstName);
    strcpy(newContact -> data.lastName, contact -> data.lastName);
    newContact -> data.phoneNumber = contact -> data.phoneNumber;
    newContact ->next = contact -> next;
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

// Create a link list and print sorted contact
void sortContacts(ContactPtr contacts[]){
    int i;
    
    // New node
    ContactPtr contact = NULL;
    
    // Link list head;
    ContactPtr head = NULL;
        
    // Create link list
    for(i = 1; i <= MAX_CONTACTS; i++){
 
        if (contacts[i] != 0){
            // Allocate memory for new node
            contact = (ContactPtr)malloc(sizeof(Contact));
            
            // Create node
            strcpy(contact -> data.firstName, contacts[i] -> data.firstName);
            strcpy(contact -> data.lastName, contacts[i] -> data.lastName);
            contact -> data.phoneNumber = contacts[i] -> data.phoneNumber;
            contact -> next = NULL;
            
            if (head == NULL){// Set the new node as head
                head = contact;
            } else {
                head = insertContactIntoLinkList(head, contact);
            }
            
            // Create node for link list
            if (contacts[i] -> next != NULL){
                ContactPtr nextContact = contacts[i] -> next;
                
                while (nextContact != NULL){
                    // Allocate memory for new node
                    contact = (ContactPtr)malloc(sizeof(Contact));
                    
                    strcpy(contact -> data.firstName, nextContact -> data.firstName);
                    strcpy(contact -> data.lastName, nextContact -> data.lastName);
                    contact -> data.phoneNumber = nextContact -> data.phoneNumber; 
                    contact -> next = NULL;
                    
                    head = insertContactIntoLinkList(head, contact);
                    
                    nextContact = nextContact -> next;
                }
            }
       }
    }
    
    ContactPtr contactNext = head;
    // Print link list
    while (contactNext != NULL){
        printf("First Name: %s \n", contactNext -> data.firstName);
        printf("Last Name: %s \n", contactNext -> data.lastName);
        printf("Phone Number: %.0f \n\n", contactNext -> data.phoneNumber);
        
        contactNext = contactNext -> next;
    }
}
// Insert item into Link list
ContactPtr insertContactIntoLinkList (ContactPtr head, ContactPtr contact){
    // Flag if a contact is placed in link list
    int placed = 0;

    ContactPtr currentContact = head;
    ContactPtr nextContact = currentContact -> next;
    
    // Place item in Link List
    while (placed == 0){
        // Compare with head
        if (strcmp(head -> data.firstName, contact -> data.firstName) > 0 &&
                    strcmp(head -> data.firstName, contact -> data.firstName) > 0){
            ContactPtr temp = contact;
            temp -> next = head; 
            head = contact;
            placed = 1;
        } else if (nextContact == NULL){
            currentContact -> next = contact;
            placed = 1;
        } else if (strcmp(nextContact -> data.firstName, contact -> data.firstName) > 0 &&
                    strcmp(nextContact -> data.firstName, contact -> data.firstName) > 0) {
            currentContact -> next = contact;
            contact -> next = nextContact;
            placed = 1;
        } else {
            currentContact = nextContact;
            nextContact = currentContact -> next;
        }
    }
    
    return head;
}