#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)      //Saving contacts structure to the file
{
    FILE *fptr;                            //File pointer decleration
    fptr = fopen("contact.csv","w");         //opening file in write mode
    if(fptr == NULL)
    {
        printf("\033[1;31mCSV File doesn't exists\n\033[0m");
        return;
    }

    fprintf(fptr,"%d\n",addressBook->contactCount);  //printing contact count in the file

    for (int i=0;i < addressBook->contactCount;i++)  //printing contacts in the file
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)    //Loading contacts file to structure
{
    FILE *fptr;                                //File pointer decleration
    fptr=fopen("contact.csv","r");           //Opening file in Read mode
    if(fptr==NULL)
    {
        printf("\033[1;31m\n==========> CSV File doesn't exits! <==========\n\033[0m");
        printf("While Saving the contact file will be created.\n");
        return;
    }

    fscanf(fptr," %d",&addressBook->contactCount);      //Reading contact count from file to structure

    for (int i=0;i < addressBook->contactCount;i++)     //Reading contacts from file to structure
    {
        fscanf(fptr," %[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}
