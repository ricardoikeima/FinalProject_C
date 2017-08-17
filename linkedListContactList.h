/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   linkedListContactList.h
 * Author: Ricardo Satoshi Ikeima
 *
 * Created on August 14, 2017, 1:46 PM
 */
#include <stdlib.h>

#include "hashContactList.h"

#ifndef LINKEDLISTCONTACTLIST_H
#define LINKEDLISTCONTACTLIST_H
/*
ContactPtr addContactSortedByFirstName(ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if (strcmp(head -> data.firstName, contact -> data.firstName) > 0
            && strcmp(head -> data.lastName, contact -> data.lastName) > 0){
        contact -> nextFirstName = head;
        return contact;
    } else if (head -> nextFirstName == NULL) { // There is no next
        head -> nextFirstName = contact;
        return head;
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> nextFirstName;
        ContactPtr nextContact = currentContact -> nextFirstName;
        
        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (strcmp(nextContact -> data.firstName, contact -> data.firstName) > 0){
                contact -> nextFirstName = nextContact;
                currentContact -> nextFirstName = contact;
                return head;
            } else if (strcmp(nextContact -> data.firstName, contact -> data.firstName) == 0){ // Same first name
                if (strcmp(nextContact -> data.lastName, contact -> data.lastName) > 0){ // Compare last name
                    contact -> nextFirstName = nextContact;
                    currentContact -> nextFirstName = contact;
                    return head;
                } else {
                    currentContact = nextContact;
                    nextContact = currentContact -> nextFirstName;
                }
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> nextFirstName;
            }
        }
        
        if (nextContact == NULL){
            currentContact -> nextFirstName = contact;
            return head;
        }
    
    }
}

ContactPtr addContactSortedByLastName(ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if (strcmp(head -> data.lastName, contact -> data.lastName) > 0
            && strcmp(head -> data.firstName, contact -> data.firstName) > 0){
        contact -> nextLastName = head;
        return contact;
    } else if (head -> nextLastName == NULL) { // There is no next
        head -> nextLastName = contact;
        return head;
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> nextLastName;
        ContactPtr nextContact = currentContact -> nextLastName;
        
        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (strcmp(nextContact -> data.lastName, contact -> data.lastName) > 0){
                contact -> nextLastName = nextContact;
                currentContact -> nextLastName = contact;
                return head;
            } else if (strcmp(nextContact -> data.lastName, contact -> data.lastName) == 0){ // Same first name
                if (strcmp(nextContact -> data.firstName, contact -> data.firstName) > 0){ // Compare first name
                    contact -> nextLastName = nextContact;
                    currentContact -> nextLastName = contact;
                    return head;
                } else {
                    currentContact = nextContact;
                    nextContact = currentContact -> nextLastName;
                }                
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> nextLastName;
            }
        }
        
        if (nextContact == NULL){
            currentContact -> nextLastName = contact;
            return head;
        }
    
    }
}

ContactPtr addContactSortedByPhoneNumber(ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if (strcmp(head -> data.phoneNumber, contact -> data.phoneNumber) > 0){
        contact -> nextPhoneNumber = head;
        return contact;
    } else if (head -> nextPhoneNumber == NULL) { // There is no next
        head -> nextPhoneNumber = contact;
        return head;
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> nextPhoneNumber;
        ContactPtr nextContact = currentContact -> nextPhoneNumber;
        
        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (strcmp(nextContact -> data.phoneNumber, contact -> data.phoneNumber) > 0){
                contact -> nextPhoneNumber = nextContact;
                currentContact -> nextPhoneNumber = contact;
                return head;
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> nextPhoneNumber;
            }
        }
        
        if (nextContact == NULL){
            currentContact -> nextPhoneNumber = contact;
            return head;
        }
    
    }
}

ContactPtr removeContactSortedByFirstName(ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if (strcmp(head -> data.firstName, contact -> data.firstName) == 0
            && strcmp(head -> data.lastName, contact -> data.lastName) == 0){
        head = contact -> nextFirstName;
        
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> nextFirstName;
        ContactPtr nextContact = currentContact -> nextFirstName;
        
        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (strcmp(nextContact -> data.firstName, contact -> data.firstName) == 0 // Same first name
                && strcmp(nextContact -> data.lastName, contact -> data.lastName) == 0){ // Same last name
                    currentContact -> nextFirstName = contact -> nextFirstName;
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> nextFirstName;
            }
        }   
    }
    return head;
}

ContactPtr removeContactSortedByLastName(ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if (strcmp(head -> data.firstName, contact -> data.firstName) == 0
            && strcmp(head -> data.lastName, contact -> data.lastName) == 0){
        head = contact -> nextLastName;
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> nextLastName;
        ContactPtr nextContact = currentContact -> nextLastName;
        
        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (strcmp(nextContact -> data.firstName, contact -> data.firstName) == 0 // Same first name
                && strcmp(nextContact -> data.lastName, contact -> data.lastName) == 0){ // Same last name
                    currentContact -> nextLastName = contact -> nextLastName;
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> nextLastName;
            }
        }   
    }
    
    return head;
}


ContactPtr removeContactSortedByPhoneNumber(ContactPtr contact, ContactPtr head){
    
    // First, verify head
    if (strcmp(head -> data.phoneNumber, contact -> data.phoneNumber) == 0){
        head = contact -> nextPhoneNumber;
    } else {
        // Ok, Let's compare with the others nodes
        ContactPtr currentContact = head -> nextPhoneNumber;
        ContactPtr nextContact = currentContact -> nextPhoneNumber;
        
        while (nextContact != NULL){    
            // If the new contact is greater than the next, we will push it in front of it
            if (strcmp(nextContact -> data.phoneNumber, contact -> data.phoneNumber) == 0){ // Same phone number
                    currentContact -> nextPhoneNumber = contact -> nextPhoneNumber;
            } else {
                currentContact = nextContact;
                nextContact = currentContact -> nextPhoneNumber;
            }
        }   
    }
    
    return head;
}*/


#endif /* LINKEDLISTCONTACTLIST_H */

