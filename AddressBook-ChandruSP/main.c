/*
Documentaion:-

Name        : Chandru SP
Discription : AddressBook with content of Name, phone number and mail-id

*/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice;                       //integer variable decleraion for choice
    AddressBook addressBook;                   //Structure decleration
    initialize(&addressBook);                  // Initialize function call

    do {
        printf("\n\033[1;34mAddress Book Menu:\033[0m\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);                   //Reading Choice
        
        switch (choice) {
            case 1:
                createContact(&addressBook);    //Create contact function call
                break;
            case 2:
                searchContact(&addressBook);    //Search contact function call
                break;
            case 3:
                editContact(&addressBook);      //Edit contact function call
                break;
            case 4:
                deleteContact(&addressBook);    //Delete contact function call
                break;
            case 5:         
                listContacts(&addressBook);     //List contact function call
                break;
            case 6:
                printf("\033[1;32mSaving the contacts...\n\033[0m");
                saveContactsToFile(&addressBook); //save contact function call
                break;
            case 7:
                printf("\033[1;32m..... Exiting .....\n\033[0m");
                loadContactsFromFile(&addressBook); //Load contact function call
                break;
            default:
                printf("\033[1;31mInvalid choice. Please try again.\n\033[0m");
        }
        
    } while (choice != 7);
    
       return 0;
}
