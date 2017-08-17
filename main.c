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
#include <ctype.h>

#define MAX_CONTACTS 500
#define FLUSH while (getchar() != '\n')
#define NUMBER_OF_LINKED_LIST 5
#define INDEX_FOR_FULL_NAME_HASH_TABLE 0
#define INDEX_FOR_PHONE_NUMBER_HASH_TABLE 1
#define INDEX_FOR_FIRST_NAME_SORTING 2
#define INDEX_FOR_LAST_NAME_SORTING 3
#define INDEX_FOR_PHONE_NUMBER_SORTING 4


typedef struct { 
    char firstName[50];
    char lastName[50];
    char phoneNumber[11];
} NodeData;

#include "hashContactList.h"

int getIndex(char [], char []);
void importSampleFile(ContactPtr [], ContactPtr []);
ContactPtr searchContact (int, ContactPtr [], ContactPtr []);
int searchMenu();
/*
 * 
 */
int main() {

    // Create array of contacts - Hash calculated with Full Name
    ContactPtr contactsFullName[MAX_CONTACTS + 1] = { NULL };
    
    // Create array of contacts - Hash calculated with Phone Number
    ContactPtr contactsPhoneNumber[MAX_CONTACTS + 1] = { NULL };
    
    for (int i = 0; i < NUMBER_OF_LINKED_LIST; i++){
        linkedListHead[i] = NULL;
    }
    
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
        printf("9. Load sample list\n");
        printf("0. Exit program\n\n");
        printf("   Enter your option: ");
        scanf("%d", &select);
        
        system("@cls||clear");
        if (isdigit(select + '0')){
            if (select == 1){
                
                ContactPtr contact = createContact();
                // Get contact number;
                printf("Enter phone number: ");
                scanf("%s", contact -> data.phoneNumber);
                
                // Verify if contact exists
                ContactPtr verifyName = getContactFullName(contact, contactsFullName);
                
                ContactPtr verifyPhone = getContactPhoneNumber(contact, contactsPhoneNumber);
                
                // Verify if contact already exist
                if (verifyName != NULL){
                    system("@cls||clear");
                    
                    printf("Contact already exist!\n"); 
                } else if (verifyPhone != NULL){ // Verify if phone number already exist
                    system("@cls||clear");
                    
                    printf("Phone number already exist!\n"); 
                } else {

                
                    // Add contact to FullName Hash Table
                    addContactFullName(contact, contactsFullName);
                    
                    // Add contact to Phone Number Hash Table
                    addContactPhoneNumber(contact, contactsPhoneNumber);
                    
                    // Add to sorted linked list
                    addSortedLinkedList(contact);
                            
                    system("@cls||clear");            

                    printf("Contact successfully added!\n\n");
                }
                
            } else if (select == 2){ // Edit Contact
                int selectSearch = -1;
                
                while (selectSearch != 0){
                    printf("--- Contact List: Edit ---\n");
                
                    selectSearch = searchMenu();
                
                    if (selectSearch != 0){

                        // Get contact
                        ContactPtr oldContact = searchContact(selectSearch, contactsFullName, contactsPhoneNumber);
                        
                        if (oldContact == NULL){ // No contact found
                            printf("Contact not found!\n\n");
                        } else { // Print Contact
                            system("@cls||clear");
                            
                            printf("First name: %s\n", oldContact -> data.firstName);
                            printf("Last name: %s\n", oldContact -> data.lastName);
                            printf("Phone number: %s\n\n", oldContact -> data.phoneNumber);
                                                        
                            ContactPtr contact = createContact();
                            // Get contact number;
                            printf("Enter phone number: ");
                            scanf("%s", contact -> data.phoneNumber);

                            // Remove contact from FullName Hash Table
                            removeContactFullName(oldContact, contactsFullName);

                            // Remove contact from Phone Number Hash Table
                            removeContactPhoneNumber(oldContact, contactsPhoneNumber);

                            // Remove from sorted linked list
                            removeSortedLinkedList(oldContact);

                            free(oldContact);
                                
                            // Verify if contact exists
                            ContactPtr verifyName = getContactFullName(contact, contactsFullName);

                            ContactPtr verifyPhone = getContactPhoneNumber(contact, contactsPhoneNumber);

                            // Verify if contact already exist
                            if (verifyName != NULL){
                                system("@cls||clear");

                                printf("Contact already exist!\n"); 
                            } else if (verifyPhone != NULL){ // Verify if phone number already exist
                                system("@cls||clear");

                                printf("Phone number already exist!\n"); 
                            } else {
                                // Add contact to FullName Hash Table
                                addContactFullName(contact, contactsFullName);

                                // Add contact to Phone Number Hash Table
                                addContactPhoneNumber(contact, contactsPhoneNumber);

                                // Add to sorted linked list
                                addSortedLinkedList(contact);

                                system("@cls||clear");            

                                printf("Contact was successfully edited!\n\n");
                            }
                        }
                    }
                }
            } else if (select == 3) { // Search for a contact
                int selectSearch = -1;
                
                while (selectSearch != 0){
                    printf("--- Contact List: Search ---\n");
                
                    selectSearch = searchMenu();
                
                    if (selectSearch != 0){

                        // Get contact
                        ContactPtr contact = searchContact(selectSearch, contactsFullName, contactsPhoneNumber);

                        if (contact == NULL){ // No contact found
                            printf("Contact not found!\n\n");
                        } else { // Print Contact
                            system("@cls||clear");
                            
                            printf("First name: %s\n", contact -> data.firstName);
                            printf("Last name: %s\n", contact -> data.lastName);
                            printf("Phone number: %s\n\n", contact -> data.phoneNumber);
                        }
                    }
                }        
                    
            } else if (select == 4){ // Delete contact
                int selectSearch = -1;
                
                while (selectSearch != 0){
                    printf("--- Contact List: Delete ---\n");
                
                    selectSearch = searchMenu();
                
                    if (selectSearch != 0){

                        // Get contact
                        ContactPtr contact = searchContact(selectSearch, contactsFullName, contactsPhoneNumber);

                        if (contact == NULL){ // No contact found
                            printf("Contact not found!\n\n");
                        } else { // Print Contact
                            system("@cls||clear");
                            
                            printf("First name: %s\n", contact -> data.firstName);
                            printf("Last name: %s\n", contact -> data.lastName);
                            printf("Phone number: %s\n\n", contact -> data.phoneNumber);
                            
                            // Remove contact from FullName Hash Table
                            removeContactFullName(contact, contactsFullName);

                            // Remove contact from Phone Number Hash Table
                            removeContactPhoneNumber(contact, contactsPhoneNumber);

                            // Remove from sorted linked list
                            removeSortedLinkedList(contact);
                            
                            free(contact);
                            
                            printf("Contact was successfully deleted!\n\n");
                        }
                    }
                }
            } else if (select == 5){
                // Write file
                FILE *out = fopen("contacts.txt", "w");
                
                ContactPtr currentContact = linkedListHead[INDEX_FOR_FIRST_NAME_SORTING];
                
                while (currentContact != NULL){
                    fprintf(out, "%s ", currentContact -> data.firstName);
                    fprintf(out, "%s ", currentContact -> data.lastName);
                    fprintf(out, "%s\n", currentContact -> data.phoneNumber);

                    currentContact = currentContact -> next[INDEX_FOR_FIRST_NAME_SORTING];
                }

                fclose(out);

                system("@cls||clear");

                printf("File Saved!\n");

            } else if (select == 6){
                ContactPtr temp = (ContactPtr) malloc(sizeof(Contact));

                // Clear contact list
                for(int i = 1; i <= MAX_CONTACTS; i++){
                    if (contactsFullName[i] != NULL){
                        contactsFullName[i] = NULL;
                    }
                }
                
                char firstName[50];
                
                // Read file
                FILE *in = fopen("contacts.txt", "r");

                    // Get name and grade until EOF
                    while (fscanf(in, "%s", firstName) != EOF){
                        ContactPtr temp = (ContactPtr) malloc(sizeof(Contact));

                        strcpy(temp -> data.firstName, firstName);
                        fscanf(in, "%s", temp -> data.lastName);
                        fscanf(in, "%s", temp -> data.phoneNumber);

                        for (int i = 0; i < NUMBER_OF_LINKED_LIST; i++){
                            temp -> next[i] = NULL;
                        }

                     // Add contact to Full Name Hash Table list
                     addContactFullName(temp, contactsFullName);

                     // Add contact to Phone Number Hash Table
                     addContactPhoneNumber(temp, contactsPhoneNumber);

                     // Add to sorted linked list
                     addSortedLinkedList(temp);
                 }

                fclose(in);
            } else if (select == 7){
                int selectSorting = -1;
                
                while ( selectSorting != 0){
                    printf("--- Contact List: Sort ---\n");
                    printf("1. Sort by first name\n");
                    printf("2. Sort by last name\n");
                    printf("3. Sort by phone number\n");
                    printf("0. Return\n\n");
                    printf("   Enter your option: ");
                    scanf("%d", &selectSorting);
                    
                    if ( selectSorting == 1
                            || selectSorting == 2
                            || selectSorting == 3){
                        
                        int index;
                        
                        // Convert option according to array index
                        switch (selectSorting){
                            case 1 : index = INDEX_FOR_FIRST_NAME_SORTING; break;
                            case 2 : index = INDEX_FOR_LAST_NAME_SORTING; break;
                            case 3 : index = INDEX_FOR_PHONE_NUMBER_SORTING; break;
                        }
                        
                        ContactPtr printContact = linkedListHead[index];

                        while (printContact != NULL){                            
                            printf("First Name: %s\n", printContact -> data.firstName );
                            printf("Last Name: %s\n", printContact -> data.lastName );
                            printf("Phone Number: %s\n\n", printContact -> data.phoneNumber );

                            printContact = printContact -> next[index];
                        }
                    } else if ( selectSorting != 0){ // Invalid option
                        system("@cls||clear");
                        printf("Invalid Option!\n");
                        FLUSH;
                    } else { // Back to main menu
                        system("@cls||clear");
                    }
                }


            } else if (select == 8){ // List all contacts
                printf("Contact List\n");
                int counter = 1;
                for(int i = 1; i <= MAX_CONTACTS; i++){
                    if (contactsFullName[i] != NULL){
                        printf("Contact number: %d\n", counter++);
                        printf("First Name: %s\n", contactsFullName[i] -> data.firstName );
                        printf("Last Name: %s\n", contactsFullName[i] -> data.lastName );
                        printf("Phone Number: %s\n\n", contactsFullName[i] -> data.phoneNumber ); 

                        ContactPtr nextContact = contactsFullName[i] -> next[INDEX_FOR_FULL_NAME_HASH_TABLE];

                        while (nextContact != NULL){
                            printf("Contact number: %d\n", counter++);
                            printf("First Name: %s\n", nextContact -> data.firstName );
                            printf("Last Name: %s\n", nextContact -> data.lastName );
                            printf("Phone Number: %s\n\n", nextContact -> data.phoneNumber );

                            nextContact = nextContact -> next[INDEX_FOR_FULL_NAME_HASH_TABLE];
                        }
                    }
                }
            } else if (select == 9){
                
                importSampleFile(contactsFullName, contactsPhoneNumber);

            } else if (select == 0){ // Exit program and message
                    printf("Thank you!\n");
                    printf("This program was developed by\n");
                    printf("Ricardo Satoshi Ikeima\n");
                    printf("Rongfu Li\n"); 
                    printf("PROG20799 Data Structures & Algorithm Development - C\n"); 
                    printf("Final Project - 14 - AUG - 2017\n");
            } else {
                printf("Invalid Option!\n");
                FLUSH;
                select = -1;
            }
        } else {
            printf("Invalid Option!\n");
            FLUSH;
            select = -1;
        }
    }
    return (0);
}

int searchMenu(){
    int selectSearch = -1;
                
    while ( selectSearch != 0){
        printf("1. Search by name\n");
        printf("2. Search by phone number\n");
        printf("0. Return\n\n");
        printf("   Enter your option: ");
        scanf("%d", &selectSearch);
        
        if (selectSearch == 1 || selectSearch == 2){
            return selectSearch;
        } else if ( selectSearch != 0){ // Invalid option
                system("@cls||clear");
                printf("Invalid Option!\n");
                FLUSH;
        } else { // Back to main menu
            system("@cls||clear");
            return selectSearch;
        }
    }
    
    return selectSearch;
}

ContactPtr searchContact (int selectSearch, ContactPtr contactsFullName[], ContactPtr contactsPhoneNumber[]){

    ContactPtr contact;
    char phoneNumber[11];

    if (selectSearch == 1) {
        ContactPtr newContact = createContact();

        contact = getContactFullName(newContact, contactsFullName);

        return contact;
    } else if (selectSearch == 2){

        contact = (ContactPtr)malloc(sizeof(Contact));

        // Get contact number;
        printf("Enter phone number: ");
        scanf("%s", contact -> data.phoneNumber);

        contact = getContactPhoneNumber(contact, contactsPhoneNumber);

        return contact;
    }
}
void importSampleFile(ContactPtr contactsFullName[], ContactPtr contactsPhoneNumber[]){

    char firstName[50];

    // Read file
    FILE *in = fopen("sample.txt", "r");

    // Get name and grade until EOF
    while (fscanf(in, "%s", firstName) != EOF){
        ContactPtr temp = (ContactPtr) malloc(sizeof(Contact));
            
        strcpy(temp -> data.firstName, firstName);
        fscanf(in, "%s", temp -> data.lastName);
        fscanf(in, "%s", temp -> data.phoneNumber);
        
        for (int i = 0; i < NUMBER_OF_LINKED_LIST; i++){
            temp -> next[i] = NULL;
        }
        
        // Add contact to Full Name Hash Table list
        addContactFullName(temp, contactsFullName);
        
        // Add contact to Phone Number Hash Table
        addContactPhoneNumber(temp, contactsPhoneNumber);
                    
        // Add to sorted linked list
        addSortedLinkedList(temp);
    }

    fclose(in);    
}

// TODO Validation
// TODO SORTING By phone number and By Name