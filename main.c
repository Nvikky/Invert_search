/*
Name : N Venkata prasad
date : 26 / 10 / 24
description : display.c 
*/
#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    Slist *head = NULL;
    char output_filename[30];
    char database_filename[256];
    if (read_and_validate(argc, argv, &head) == SUCCESS)
    {
        printf("INFO: VALIDATED SUCCESSFULLY\n");

        int n;
        int is_database_created = 0; // Flag to track if database is created
        int is_database_updated = 0; // Flag to track if database is updated
        main_node *ptr[28];

        do
        {
            printf("\nChoose the option: \n1.Create Database\n2.Display Database\n3.Search Database\n4.Save Database\n5.Update Database\n6.Exit\n");
            scanf("%d", &n);
            switch (n)
            {
            case 1:
            {
                    if(is_database_updated == 0)
                    {
                        if (initialize_main_array(ptr, 28) == SUCCESS)
                        {
                            printf("INFO: Initialized Database Array\n");
                        }
                        else
                        {
                            printf("ERROR: Failed to Initialize Database Array\n");
                        }
                    }
                    if (create_database(&head, ptr, 28) == SUCCESS)
                    {
                        is_database_created = 1; // Mark database as created
                        printf("INFO: Database Created Successfully\n");
                    }
                        else
                        {
                            printf("ERROR: Failure in Creating Database\n");
                        }
               
                break;
            }
            case 2:
            {
                if (is_database_created || is_database_updated)
                {
                    display_database(ptr, 28);
                    printf("INFO: Database displayed successfully.\n");
                }
                else
                {
                    printf("ERROR: No existing database.\n");
                }
                break;
            }

            case 3:
            {
                if (is_database_created || is_database_updated)
                {
                char word_to_search[20]; // Buffer to hold the word to search
                printf("Enter the word to search in the database: ");
                scanf("%s", word_to_search); // Read the word from the user
                search_in_database(word_to_search, ptr, 28); // Call the search function
                }
                else
                {
                    printf("ERROR: No Database found, cannot search\n");
                }
                break;
            }
            case 4:
            {
                if (is_database_created) // Ensure the database was created before saving
                {
                    char save_filename[30]; // Specify the output file name
                    printf("Enter the filename you want to save : ");
                    scanf("%s",save_filename);
                    if (save_database(ptr, 28, save_filename) == SUCCESS)
                    {
                        printf("INFO: Database successfully saved to %s\n", save_filename);
                    }
                    else
                    {
                        printf("ERROR: Failed to save database\n");
                    }
                }
                else if (is_database_updated)
                {
                    printf("ERROR: Database has already been updated. Cannot save again.\n");
                }
                else
                {
                    printf("ERROR: Database not created yet, cannot save\n");
                }
                break;
            }

            case 5:
            {
				// Check for existing database
                if (is_database_created)
                {
                    printf("ERROR: Database already created. Update (reloading) is not allowed.\n");
                }
                else if (is_database_updated)
                {
                    printf("ERROR: Database has already been updated. Cannot update again.\n");
                }
                else
                {
                    //char database_filename[256];
                    printf("Enter the existing database file : ");
                    scanf("%s",database_filename);
                    if (!file_exists(database_filename))
                    {
                    printf("ERROR: No saved database to update. Please create a database first.\n");
                    }
                    else
                    {
                        if (initialize_main_array(ptr, 28) == SUCCESS)
                        {
                            if (update_database(database_filename, ptr, 28,&head) == SUCCESS)
                            {
                                is_database_updated = 1; // Mark database as updated
                                printf("INFO: Database updated successfully.\n");
                            }
                        }
                    else
                    {
                        printf("ERROR: Failed to update database.\n");
                    }
                    }
                }
                break;
            }
            case 6:
            {
                printf("Exiting...\n");
                exit(0);
                break;
            }
            default:
            {
                printf("Please Enter valid choice\n");
            }
            }

        } while (n >= 1 && n < 6);
    }

    return 0; // Return 0 on successful execution
}
