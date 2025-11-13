#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void sort(AddressBook *addressBook)                       //For sorting the Name
{
    Contact temp;                            //Temp structure to swap and sort the contact

    for (int j = 0 ; j < addressBook->contactCount-1 ; j++)
    {
        for (int i = 0 ; i < addressBook->contactCount-j-1 ; i++)
        {
            int cmp = strcmp(addressBook->contacts[i].name,addressBook->contacts[i+1].name);

            if (cmp>0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[i+1];     //Swaping the name
                addressBook->contacts[i+1] = temp;
            }

        }
        
    }
}

int name_valid(char val_name[])                           //Name validation
{
    for (int i = 0 ; val_name[i] ; i++)      
    {
        if (!(isupper(val_name[i]) || islower(val_name[i]) || val_name[i]==' ' || (val_name[i]=='.')))
        {
            printf("\033[1;31m::::::::::Name invalid!, Retry!::::::::::\n\n\033[0m");
            return 0;
        }
    }
    return 1; 
}

int num_valid(char val_num[],AddressBook *addressBook)    //Number validation
{
    int count = 0;

    if (strlen(val_num) == 10)            //number length validation
        {

           for (int i = 0 ; val_num[i] ;i++)
            {

                if (!(val_num[i] >= '0' && val_num[i] <= '9'))          //numeric validation
                {
                    printf("\033[1;31m::::::::::Invalid number!, Retry!::::::::::\n\n\033[0m");
                    return 0;
                }
                count++;

            }

        }
        else 
        {
            printf("\033[1;31m::::::::::Invalid number!, Retry!::::::::::\n\n\033[0m");
            return 0;
        }
        
        for (int i = 0 ; i < addressBook->contactCount ; i++)
        {
            if (strcmp(addressBook->contacts[i].phone,val_num)==0)    //uniq validation
            {
                count=0;
                break;
            }
        }

        if (!count)
        {
            printf("\n\033[1;31m============>The number is alredy exists<============\n\033[0m");
            return 0;
        }
        return 1;

}

int email_valid(char val_email[],AddressBook *addressBook)//Email id validation
{
    int count = 0,at=0;                 //variable decleration
    int len = strlen(val_email);

        for (int i = 0 ; i < len ; i++)
        {
            if (val_email[i]=='@')         //Validating @
            {
                at++;

                if(!i || val_email[i+1] == '.')
                {
                    count=+2;
                    break;
                }

                if(at > 1)
                {
                    count++;
                    break;
                }

            }
        }
        char str[20] = ".com";

        if (!(strstr(val_email,str)))          //Validation .com
        {
            printf("\033[1;31m::::::::::Invalid mailid!,Try again.::::::::::\n\n\033[0m");
            return 0;
        }

        for (int i = 0; val_email[i] != '.' ; i++)    //Alpha numeric validation
        {
            if (!(islower(val_email[i]) || isdigit(val_email[i]) || val_email[i] == '@' || val_email[i] == '_'))
            {
                count++;
                break;
            }
        
        }

        for (int i = 0 ; i < addressBook->contactCount ; i++)       //Uniq validation
        {
            if (!strcmp(addressBook->contacts[i].email,val_email))
            {
                count=1;
                break;
            }
        }

        if (count==1)
        {
            printf("\033[1;31m\n============>The email is alredy exists<============\n\033[0m");
            return 0;
        }

        if(!count)
            return 1;
        else
            printf("\033[1;31m::::::::::Invalid mailid!,Try again.::::::::::\n\n\033[0m");
            return 0;
}

void listContacts(AddressBook *addressBook)               //listing contacts
{
    if (addressBook->contactCount)
    {
        sort(addressBook);                                //Sorting before listing
        printf("\n-----------------------------------------------------------------------\n");
        printf("\033[1;34m%-5s %-20s %-15s %-30s\033[0m\n", "SNO", "Name", "Phone", "Email");
        printf("-----------------------------------------------------------------------\n");
        for (int i = 0 ; i < addressBook->contactCount ; i++)
        {
            printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
    else
    {
        printf("\033[1;31m\n==========> Address Book is Empty <==========\n\033[0m");
    }  
}

void initialize(AddressBook *addressBook)                 //Initialization
{
    addressBook->contactCount = 0;           //Seting contact count 0
    sort(addressBook);                      //Sorting
    loadContactsFromFile(addressBook);      // Load contacts from file during initialization
}

void saveAndExit(AddressBook *addressBook)                //saving contacts to file
{
    sort(addressBook);                    //Sorting
    saveContactsToFile(addressBook);     // Save contacts to file
    exit(EXIT_SUCCESS);                  // Exit the program
}

void createContact(AddressBook *addressBook)              //Creating Contact
{
    char sname[50];      
    char snum[20];                          //String Variable Decleration
    char semail[50];
    int count;

    do
    {
        
        printf("Enter your name : ");
        scanf(" %[^\n]",sname);            //Reading name 
        getchar();

        if (name_valid(sname))             //Name validation
        {
           break;
        }

    } while (1);  

    do
    {
        
        printf("Enter your phone number : ");
        scanf("%s",snum);                           //Reading phone number

        if (num_valid(snum,addressBook))            //Phone number validation
        {
            break;
        }    

    } while (1);
    
    do
    {

        printf("Enter your email-id : ");         //Reading mail id
        scanf("%s",semail);
        
        if(email_valid(semail,addressBook))          //mail validation
        {
            break;
        }
 
    } while (1); 

    //Saving contacts to the structure

    strcpy(addressBook->contacts[addressBook->contactCount].name,sname);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,snum);
    strcpy(addressBook->contacts[addressBook->contactCount].email,semail);
    addressBook->contactCount++;

    printf("\n\033[1;32mContact created successfully.\033[0m\n");

    sort(addressBook);              //Sorting contact
}

void searchContact(AddressBook *addressBook)              //Search contact
{
    int op,count=0;                         //Variable decleration

    do
    {
        printf("\n\033[1;34mSearch options:\033[0m\n");
        printf("1.Name  :\n");
        printf("2.phone :\n");
        printf("3.Email :\n");
        printf("4.Exit  :\n");
        printf("\nEnter a option : ");
        scanf("%d",&op);                   //Option for switch case

        switch (op)
        {

        case 1:
            char sname[50];
            int arr_name[100];
            printf("\nEnter your name : ");
            scanf(" %[^\n]",sname);        //Reading name

            if (!name_valid(sname))        //Validating
            {
                break;
            }

            for (int i = 0; i < addressBook->contactCount ; i++)   //Comparing for similar names
            {
                if (!(strcmp(sname,addressBook->contacts[i].name)))
                {
                    arr_name[count] = i;
                    count++;
                }
            }

            if (count <= 1)                 
            {
                if(count == 0)
                {
                    printf("\033[1;31m==========> Contact not found! <==========\033[0m\n\n");
                    break;
                }

                //Printig contact if found
                printf("\n\033[1;32m==========> Contact found. <==========\n\n\033[0m");
                printf("Name   :%s\n",addressBook->contacts[arr_name[0]].name);
                printf("phone  :%s\n",addressBook->contacts[arr_name[0]].phone);
                printf("email  :%s\n",addressBook->contacts[arr_name[0]].email);
            }
            else
            {
                printf("\033[1;34m\n==========> Below %d names are simillar.<==========\n\033[0m",count);
                printf("\n-----------------------------------------------------------------------\n");
                printf("\033[1;34m%-5s %-20s %-15s %-30s\n\033[0m", "SNO", "Name", "Phone", "Email");
                printf("-----------------------------------------------------------------------\n");
                for (int i = 0 ; i < count ; i++)    //Printing if names are similar
                {
                    printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[arr_name[i]].name,addressBook->contacts[arr_name[i]].phone,addressBook->contacts[arr_name[i]].email);
                }

                printf("\nWhich one you prefered.\n");
                printf("Select the choise below and Find the conduct!\n");

                //If names are similar, searching for correct one
                do
                {
                    int ch;
                    printf("1.Index\n");
                    printf("2.Phone Number\n");
                    printf("3.Email id\n");
                    printf("4.Exit\n");
                    printf("Enter the choise:");
                    scanf("%d",&ch);                 //Reading choise for switch case

                    switch(ch)
                    {
                        case 1:

                            //Printing the contact using index
                            int indx;
                            printf("Enter index number : ");
                            scanf("%d",&indx);
                            printf("\n\033[1;32m==========> Contact found. <==========\n\n\033[0m");
                            printf("Name   :%s\n",addressBook->contacts[arr_name[indx-1]].name);
                            printf("phone  :%s\n",addressBook->contacts[arr_name[indx-1]].phone);
                            printf("email  :%s\n",addressBook->contacts[arr_name[indx-1]].email);
                            break;

                        case 2:

                            //Printing the contact using number
                            char s_num[20];
                            printf("Enter phone number : ");
                            scanf("%s",s_num);

                            for (int i = 0 ; i < count ; i++)
                            {
                                if(!(strcmp(s_num,addressBook->contacts[arr_name[i]].phone)))
                                {
                                    printf("\n\033[1;32m==========> Contact found. <==========\n\n\033[0m");
                                    printf("Name   :%s\n",addressBook->contacts[arr_name[i]].name);
                                    printf("phone  :%s\n",addressBook->contacts[arr_name[i]].phone);
                                    printf("email  :%s\n",addressBook->contacts[arr_name[i]].email);
                                }
                            }
                            break;

                        case 3:

                            //Printing the contact using mail
                            char s_email[50];
                            printf("Enter email id : ");
                            scanf("%s",s_email);

                            for (int i = 0 ; i < count ; i++)
                            {
                                if(!(strcmp(s_email,addressBook->contacts[arr_name[i]].email)))
                                {
                                    printf("\n\033[1;32m==========> Contact found. <==========\n\n\033[0m");
                                    printf("Name   :%s\n",addressBook->contacts[arr_name[i]].name);
                                    printf("phone  :%s\n",addressBook->contacts[arr_name[i]].phone);
                                    printf("email  :%s\n",addressBook->contacts[arr_name[i]].email);
                                    //printf("1. %s      %s       %s\n",addressBook->contacts[arr_name[i]].name,addressBook->contacts[arr_name[i]].phone,addressBook->contacts[arr_name[i]].email);
                                }
                            }
                            break;

                        default:
                            printf("\033[1;31m\n==========> Please enter valid choise! <==========\n\033[0m");

                    }
                }while(!4);
            }
            break;
        
        case 2:

            char snum[20];
            printf("Enter phone number : ");
            scanf("%s",snum);                  //Reading phone number

            for (int i = 0 ; i < addressBook->contactCount ; i++)
            {
                //Printing contact
                if(!(strcmp(snum,addressBook->contacts[i].phone)))
                {
                    printf("\n\033[1;32m==========> Contact found. <==========\n\n\033[0m");
                    printf("Name   :%s\n",addressBook->contacts[i].name);
                    printf("phone  :%s\n",addressBook->contacts[i].phone);
                    printf("email  :%s\n",addressBook->contacts[i].email);
                    break;
                }
                else
                {
                    printf("\033[1;31m==========> Contact not found! <==========\033[0m\n\n");
                    break;
                }

            }
            break;
        
        case 3:

            char semail[50];
            printf("Enter phone number : ");
            scanf("%s",semail);                   //Reading mail id

            for (int i = 0 ; i < addressBook->contactCount ; i++)
            {
                //Printing contact
                if(!(strcmp(semail,addressBook->contacts[i].phone)))
                {
                    printf("\n\033[1;32m==========> Contact found. <==========\n\n\033[0m");
                    printf("Name   :%s\n",addressBook->contacts[i].name);
                    printf("phone  :%s\n",addressBook->contacts[i].phone);
                    printf("email  :%s\n",addressBook->contacts[i].email);
                    break;
                }
                else
                {
                    printf("\033[1;31m==========> Contact not found! <==========\033[0m\n\n");
                    break;
                }

            }
            break;

        default:
            printf("\033[1;31mInvaild option! Please enter valid option\n\033[0m");
            break;
        }

    } while (!4);
    
}

void editContact(AddressBook *addressBook)                //Edit contact
{
    int op,ret;

    do
    {
        printf("\033[1;34m\nEdit options:\n\033[0m");
        printf("1.Name  :\n");
        printf("2.phone :\n");
        printf("3.Email :\n");
        printf("4.Exit  :\n");
        printf("\nEnter a option : ");
        scanf("%d",&op);             //Reading option for editing

        int indx=0;
        switch(op)
        {        
               
            case 1:

                //Editing name
                char sname[50];
                listContacts(addressBook);    //Lisitng contact
                printf("\nGive the index number of name : ");
                scanf("%d",&indx);               //Reading index for name
                printf("Enter new name:");
                scanf(" %[^\n]",sname);          //Reading new name

                if (name_valid(sname))           //Name validating and editing
                {
                    strcpy(addressBook->contacts[indx-1].name,sname);
                    printf("Name: %s\n", addressBook->contacts[indx-1].name);
                    printf("\033[1;32m\n==========>Name changed successefully<==========\n\033[0m");
                }

                break;

            case 2:

                //Editing number
                char snum[20];
                listContacts(addressBook);                 //Lisitng contact
                printf("Give the index number of number:\n");
                scanf("%d",&indx);                            //Reading index for number
                printf("Enter new number:");
                scanf(" %[^\n]",snum);                        //Reading new number

                if (num_valid(snum,addressBook))              //Number validating and editing
                {
                    strcpy(addressBook->contacts[indx-1].phone,snum);
                    printf("\033[1;32m\n==========>Number changed successefully<==========\n\033[0m");
                }

                break;

            case 3:

                //Editing email
                char semail[50];
                listContacts(addressBook);                  //Lisitng contact
                printf("Give the index number of email:\n");
                scanf("%d",&indx);                             //Reading index for email
                printf("Enter new email:");
                scanf(" %[^\n]",semail);                       //Reading new mail

                if (email_valid(semail,addressBook))           //email validating and editing
                {
                    strcpy(addressBook->contacts[indx-1].email,semail);
                    printf("\033[1;32m\n==========>Email changed successefully<==========\n\033[0m");
                }

                break;

            default :
                printf("\033[1;31mEnter valid choise!\n\033[0m");
                break;     
        }
        
    } while (!4);

}

void deleteContact(AddressBook *addressBook)              //Delete contact
{
    int op,count = 0;                           //Variable Decleration

    do
    {
        printf("\033[1;34m\nDelete By:\n\033[0m");
        printf("1.Name  :\n");
        printf("2.phone :\n");
        printf("3.Email :\n");
        printf("4.Exit  :\n");
        printf("\nEnter a option : ");
        scanf("%d",&op);                       //Reading option for delete contact

        switch (op)
        {

        case 1:

            //Delete by name
            char sname[50];
            int arr_name[100];
            printf("\nEnter your name : ");
            scanf(" %[^\n]",sname);           //Reading name from user

            if (!name_valid(sname))           //Name validating
            {
                break;
            }

            for (int i = 0 ; i < addressBook->contactCount ; i++)     //Comparing name in addressbook for similar names
            {
                if (!(strcmp(sname,addressBook->contacts[i].name)))
                {
                    arr_name[count] = i;
                    count++;                                      //Counting similar names
                }
            }

            if (count <= 1)
            {
                if(count == 0)                     //If no contact foun printing description
                {
                    printf("\033[1;31m\n==========> Name not found! <==========\n\033[0m");
                    break;
                }
                addressBook->contactCount--;
                printf("1. %s      %s       %s\n",addressBook->contacts[arr_name[0]].name,addressBook->contacts[arr_name[0]].phone,addressBook->contacts[arr_name[0]].email);
                
                for (int i = arr_name[0]; i < addressBook->contactCount ; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i+1];  //Moving contacts for delete the name
                }

                printf("\033[1;32m\n==========> Deleted successfully.<==========\n\n\033[0m");
                listContacts(addressBook);       //After deleting listing contacts
            }
            else
            {

                //if similar name found showing the similar names
                printf("\033[1;34m\n==========> Below %d names are simillar.<==========\n\033[0m",count);

                printf("\n-----------------------------------------------------------------------\n");
                printf("\033[1;34m%-5s %-20s %-15s %-30s\n\033[0m", "SNO", "Name", "Phone", "Email");
                printf("-----------------------------------------------------------------------\n");
                for (int i = 0 ; i < count ; i++)
                {
                    printf("%d. %s      %s       %s\n",i+1,addressBook->contacts[arr_name[i]].name,addressBook->contacts[arr_name[i]].phone,addressBook->contacts[arr_name[i]].email);
                }

                printf("\nWhich one you prefered!\n");
                printf("Select the choise below and Delete the conduct!\n");

                do
                {

                    int ch;                       //Variable decleration for choise
                    printf("1.Index\n");
                    printf("2.Phone Number\n");
                    printf("3.Email id\n");
                    printf("4.Exit\n");
                    printf("Enter the choise:");
                    scanf("%d",&ch);             //Reading Choise

                    switch(ch)
                    {

                        case 1:

                            //Delete by index
                            int indx;
                            printf("Enter index number : ");
                            scanf("%d",&indx);              //reading index for deleting contact
                            addressBook->contactCount--;

                            for (int i = arr_name[indx-1] ; i < addressBook->contactCount ; i++)
                            {
                                //swaping contacts and deleting
                                addressBook->contacts[i] = addressBook->contacts[i+1];
                            }

                            printf("\033[1;32m\n==========> Deleted successfully.<==========\n\n\033[0m");
                            listContacts(addressBook);   //Listing contacts after deleting
                            break;

                        case 2:

                            //Delete by number
                            char s_num[20];
                            printf("Enter phone number : ");
                            scanf("%s",s_num);             //Reading number
                            addressBook->contactCount--;

                            for (int i = 0 ; i < count ; i++)    //Deleting and moving contacts
                            {
                                if(!(strcmp(s_num,addressBook->contacts[arr_name[i]].phone)))
                                {
                                    for (int j = arr_name[i] ; j < addressBook->contactCount ; j++)
                                    {
                                        addressBook->contacts[j] = addressBook->contacts[j+1];
                                    }
                                    printf("\033[1;32m\n==========> Deleted successfully.<==========\n\n\033[0m");
                                    listContacts(addressBook); //listing after deleting
                                }
                            }
                            break;

                        case 3:

                            //Delete by email
                            char s_email[50];
                            printf("Enter email id : ");
                            scanf("%s",s_email);           //Reading email
                            addressBook->contactCount--;

                            for (int i = 0 ; i < count ; i++)    //Deleting and moving contact
                            {
                                if(!(strcmp(s_email,addressBook->contacts[arr_name[i]].email)))
                                {
                                    for (int j = i ; j < addressBook->contactCount ; j++)
                                    {
                                        addressBook->contacts[j] = addressBook->contacts[j+1];
                                    }
                                    printf("\033[1;32m\n==========> Deleted successfully.<==========\n\n\033[0m");
                                    listContacts(addressBook);  //lisiting contacts after deleting
                                }
                            }
                            break;

                        default:
                            printf("\033[1;31mPlease enter valid choise!\n\033[0m");
                            break;

                    }

                }while(!4);

            }
            break;
        
        case 2:

            //Delete by number
            char snum[20];
            printf("Enter phone number : ");
            scanf("%s",snum);             //Reading number for deleting
            addressBook->contactCount--;

            for (int i = 0 ;i < addressBook->contactCount ; i++)   //Deleting and moving contacts
            {
                if(!(strcmp(snum,addressBook->contacts[i].phone)))
                {
                    for (int j = i ; j < addressBook->contactCount ; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                    }
                    printf("\033[1;32m\n==========> Deleted successfully.<==========\n\033[0m");
                    listContacts(addressBook);         //listing after deleting
                    break;

                }
            }
            break;
        
        case 3:

            char semail[50];
            printf("Enter phone number : ");
            scanf("%s",semail);               //Reading mail for deleting
            addressBook->contactCount--;

            for (int i = 0 ; i < addressBook->contactCount ; i++)     //Deleting and moving the contact
            {
                if(!(strcmp(semail,addressBook->contacts[i].phone)))
                {
                    for (int j = i ; j < addressBook->contactCount ; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                    }
                    printf("\033[1;32m\n==========> Deleted successfully.<==========\n\033[0m");
                    listContacts(addressBook);          //listing after deleting
                    break;
                }

            }
            break;

        default:
            printf("\033[1;31mInvaild option! Please enter valid option.\n\033[0m");
            break;
        }
        
    } while (!4);

}