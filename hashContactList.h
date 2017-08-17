/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hash.h
 * Author: Ricardo Satoshi Ikeima
 *
 * Created on August 14, 2017, 1:41 PM
 */

#include <stdlib.h>

#ifndef HASHCONTACTLIST_H
#define HASHCONTACTLIST_H

typedef struct node{
    NodeData data;
    struct node *next[NUMBER_OF_LINKED_LIST];
    // index 0 -> Pointer to next contact. Used in full name hash table
    // index 1 -> Pointer to next contact. Used in phone number hash table
    // index 2 -> Pointer to next contact (sorted by first name)
    // index 3 -> Pointer to next contact (sorted by last name)
    // index 4 -> Pointer to next contact (sorted by phone number)
} Contact, *ContactPtr;

ContactPtr linkedListHead[NUMBER_OF_LINKED_LIST] = { NULL };
// index [0] = Full name hash table linked list
// index [1] = Phone number hash table linked list
// index [2] = Linked list ordered by first name
// index [3] = Linked list ordered by last name
// index [4] = Linked list ordered by phone number


int getIndexFullName(ContactPtr);
int getIndexPhoneNumber(ContactPtr);
ContactPtr createContact();
void addContactFullName(ContactPtr, ContactPtr []);
void addContactPhoneNumber(ContactPtr, ContactPtr []);
void removeContactFullName(ContactPtr, ContactPtr []);
ContactPtr getContactFullName(ContactPtr, ContactPtr []);
ContactPtr getContactPhoneNumber(ContactPtr, ContactPtr []);
void addSortedLinkedList (ContactPtr);
ContactPtr addContactLinkedList(int, ContactPtr, ContactPtr);
ContactPtr removeContactLinkedList(int, ContactPtr, ContactPtr);

// Enter full name and return the index
int getIndexFullName(ContactPtr contact){
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

// Enter phone number and return the index
int getIndexPhoneNumber(ContactPtr contact){
    int charIndex = 0;
    int result = 0;
    char phoneNumber[11];
    
    strcpy(phoneNumber, contact -> data.phoneNumber);
    
    while (phoneNumber[charIndex] != '\0'){
        // Get char value and multiply by Weight (charIndex + 1)
        result += (int)phoneNumber[charIndex] * (++charIndex);
    }
    
    return (result % MAX_CONTACTS) + 1;
}

// Create the contact
ContactPtr createContact(){
    char firstName[50];
    char lastName[50];
    
    printf("Enter first name: ");
    scanf("%s", firstName);
    printf("Enter last name: ");
    scanf("%s", lastName);
    
    ContactPtr contact = (ContactPtr)malloc(sizeof(Contact));
 
    if (contact != NULL){
        strcpy(contact -> data.firstName, firstName);
        strcpy(contact -> data.lastName, lastName);
        //contact -> data.phoneNumber = NULL;
    
        for (int i = 0; i < NUMBER_OF_LINKED_LIST; i++){
            contact -> next[i] = NULL;
        }
    } else {
        printf("Memory could not be allocated");
    }

    return contact;
}

// Add contact to full name hash table
void addContactFullName(ContactPtr newContact, ContactPtr contacts[]){
    int index = getIndexFullName(newContact);
        
    // Space is empty
    if (contacts[index] == NULL){
        contacts[index] = newContact;
    } else { // We have a collision!
        // Add contact to linked list
        contacts[index] = addContactLinkedList(INDEX_FOR_FULL_NAME_HASH_TABLE, newContact, contacts[index]);
    }
}

// Add contact to phone number hash table
void addContactPhoneNumber(ContactPtr newContact, ContactPtr contacts[]){
    int index = getIndexPhoneNumber(newContact);
        
    // Space is empty
    if (contacts[index] == NULL){
        contacts[index] = newContact;
    } else { // We have a collision!       
        // Add contact to linked list
        contacts[index] = addContactLinkedList(INDEX_FOR_PHONE_NUMBER_HASH_TABLE, newContact, contacts[index]);
    }
}

// Remove contact from full name hash table
void removeContactFullName(ContactPtr contact, ContactPtr contacts[]){
    int index = getIndexFullName(contact);
    
    // If the contact is the first item
    if (strcmp(contacts[index] -> data.firstName, contact -> data.firstName) == 0 
                    && strcmp(contacts[index] -> data.lastName, contact -> data.lastName) == 0){
            contacts[index] = contacts[index] -> next[INDEX_FOR_FULL_NAME_HASH_TABLE];
    } else { // We have a collision!
        // Add contact to linked list
        removeContactLinkedList(INDEX_FOR_FULL_NAME_HASH_TABLE, contact, contacts[index]);
    }
}

// Remove contact from phone number hash table
void removeContactPhoneNumber(ContactPtr contact, ContactPtr contacts[]){
    int index = getIndexPhoneNumber(contact);
    
    // If the contact is the first item
    if (strcmp(contacts[index] -> data.phoneNumber, contact -> data.phoneNumber) == 0){
        contacts[index] = contacts[index] -> next[INDEX_FOR_PHONE_NUMBER_HASH_TABLE];
    } else { // We have a collision!
    removeContactLinkedList(INDEX_FOR_PHONE_NUMBER_HASH_TABLE, contact, contacts[index]);    
    }
}

// Get contact by Full name
ContactPtr getContactFullName(ContactPtr newContact, ContactPtr contacts[]){
    int index = getIndexFullName(newContact);

    ContactPtr contact = contacts[index];
    
    while (contact != NULL){
        if (strcmp(contact -> data.firstName, newContact -> data.firstName) == 0 
                && strcmp(contact -> data.lastName, newContact -> data.lastName) == 0){
            break;
        } else {
            contact = contact -> next[INDEX_FOR_FULL_NAME_HASH_TABLE];
        }
    }
    
    return contact;
}

// Get contact by phone number
ContactPtr getContactPhoneNumber(ContactPtr newContact, ContactPtr contacts[]){
    int index = getIndexPhoneNumber(newContact);

    ContactPtr contact = contacts[index];
    
    while (contact != NULL){
        if (strcmp(contact -> data.phoneNumber, newContact -> data.phoneNumber) == 0){
            break;
        } else {
            contact = contact -> next[INDEX_FOR_PHONE_NUMBER_HASH_TABLE];
        }
    }
    
    return contact;
}

// Add to sorted linked list
void addSortedLinkedList (ContactPtr newContact){
    // Add contact to each linked list
    for (int i = INDEX_FOR_FIRST_NAME_SORTING; i < NUMBER_OF_LINKED_LIST; i++){
        linkedListHead[i] = addContactLinkedList(i, newContact, linkedListHead[i]);
    }  
}

ContactPtr addContactLinkedList(int i, ContactPtr contact, ContactPtr head){

    // First, verify head
    if (head == NULL){
        return contact;
    } else if (i == INDEX_FOR_PHONE_NUMBER_SORTING
                && strcmp(head -> data.phoneNumber, contact -> data.phoneNumber) > 0){
        
        contact -> next[i] = head;
        return contact;
        
    } else if ( (i == INDEX_FOR_FIRST_NAME_SORTING || i == INDEX_FOR_FULL_NAME_HASH_TABLE)
                && ((strcmp(head -> data.firstName, contact -> data.firstName) > 0) 
                    || (strcmp(head -> data.firstName, contact -> data.firstName) == 0 // Same first name
                    && strcmp(head -> data.lastName, contact -> data.lastName) > 0))) {
        
            contact -> next[i] = head;
            return contact;

    } else if (i == INDEX_FOR_LAST_NAME_SORTING
                && ((strcmp(head -> data.lastName, contact -> data.lastName) > 0) 
                    || (strcmp(head -> data.lastName, contact -> data.lastName) == 0 // Same last name
                    && strcmp(head -> data.firstName, contact -> data.firstName) > 0))) {
            
            contact -> next[i] = head;
            return contact;      
    } else if (head -> next[i] == NULL) { // There is no next
        
        head -> next[i] = contact;
        return head;
        
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> next[i];
        ContactPtr nextContact = currentContact -> next[i];

        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (i == INDEX_FOR_PHONE_NUMBER_SORTING
                    && strcmp(nextContact -> data.phoneNumber, contact -> data.phoneNumber) > 0){
                
                contact -> next[i] = nextContact;
                currentContact -> next[i] = contact;
                
                return head;
                
            } else if ( (i == INDEX_FOR_FIRST_NAME_SORTING || i == INDEX_FOR_FULL_NAME_HASH_TABLE)
                && ((strcmp(nextContact -> data.firstName, contact -> data.firstName) > 0) 
                    || (strcmp(nextContact -> data.firstName, contact -> data.firstName) == 0 // Same first name
                    && strcmp(nextContact -> data.lastName, contact -> data.lastName) > 0))) {
            
                contact -> next[i] = nextContact;
                currentContact -> next[i] = contact;
                
                return head;
                
            } else if (i == INDEX_FOR_LAST_NAME_SORTING
                        && ((strcmp(nextContact -> data.lastName, contact -> data.lastName) > 0) 
                            || (strcmp(nextContact -> data.lastName, contact -> data.lastName) == 0 // Same last name
                            && strcmp(nextContact -> data.firstName, contact -> data.firstName) > 0))) {

                contact -> next[i] = nextContact;
                currentContact -> next[i] = contact;
                
                return head;
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> next[i];
            }
        }

        if (nextContact == NULL){
            currentContact -> next[i] = contact;
        } 
        
        return head;
    }
}

// Remove from sorted linked list
void removeSortedLinkedList (ContactPtr contact){
    // Add contact to each linked list
    for (int i = INDEX_FOR_FIRST_NAME_SORTING; i < NUMBER_OF_LINKED_LIST; i++){
        linkedListHead[i] = removeContactLinkedList(i, contact, linkedListHead[i]);
    }  
}

ContactPtr removeContactLinkedList(int i, ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if ( strcmp(head -> data.firstName, contact -> data.firstName) == 0
            && strcmp(head -> data.lastName, contact -> data.lastName) == 0
            && strcmp(head -> data.phoneNumber, contact -> data.phoneNumber) == 0) {
        head = head -> next[i];
        return head;
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> next[i];
        ContactPtr nextContact = currentContact -> next[i];

        while (nextContact != NULL){    
            // Compare with the next
            if ( strcmp(nextContact -> data.firstName, contact -> data.firstName) == 0 // Same first name
                        && strcmp(nextContact -> data.lastName, contact -> data.lastName) == 0 // Same last name
                        && strcmp(nextContact -> data.phoneNumber, contact -> data.phoneNumber) == 0) { // Same phone number
                
                currentContact -> next[i] = nextContact -> next[i];
                return head;
                        
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> next[i];
            }
        }
    }
}
#endif /* HASHCONTACTLIST_H */

