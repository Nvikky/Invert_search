/*
Name : N Venkata prasad
date : 26/10/24
description : validation.c 
*/
#include "inv.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int read_and_validate(int argc, char *argv[], Slist **head)
{
    if (argc == 1)
    {
        printf("ERROR : Usage: <./a.exe> <file1.txt> <file2.txt> ...\n");
        return FAILURE;
    }
    else
    {
        // Iterate over the provided files
        for (int i = 1; i < argc; i++)
        {
                // Check if the file has a .txt extension
                char *txt_position = strstr(argv[i], ".txt");
                // Check if ".txt" is at the end
                if (txt_position != NULL && strcmp(txt_position, ".txt") == 0)
                {
                int is_duplicate = 0;

                // Check for duplicate filenames
                for (int j = 1; j < i; j++)
                {
                    if (strcmp(argv[i], argv[j]) == 0)
                    {
                        printf("ERROR : Duplicate file name exists: %s\n", argv[i]);
                        is_duplicate = 1;
                        break;
                    }
                }

                // If not a duplicate, proceed to open the file
                if (!is_duplicate)
                {
                    FILE *file = fopen(argv[i], "r");
                    if (file != NULL)
                    {
                        fseek(file, 0, SEEK_END);
                        long fileSize = ftell(file); // Get the file size

                        // Check if the file is empty
                        if (fileSize > 0)
                        {
                            // Add the file to the linked list
                            if (add_list(head, argv[i]) == FAILURE)
                            {
                                printf("ERROR : Could not add file to the list: %s\n", argv[i]);
                                fclose(file);
                                return FAILURE;
                            }
                        }
                        else
                        {
                            printf("ERROR : The file is empty: %s\n", argv[i]);
                        }
                        fclose(file); // Close the file
                    }
                    else
                    {
                        printf("ERROR : The file does not exist: %s\n", argv[i]);
                    }
                }
            }
            else
            {
                // If the file extension is not .txt
                printf("ERROR : Invalid file extension, expected .txt: %s\n", argv[i]);
            }
        }
    }

    // Display the list only once after processing all files
    display_list(*head);

    return SUCCESS;
}

// Function to add a file to the linked list
int add_list(Slist **head, char argv[20])
{
    // Create a new node
    Slist *new = malloc(sizeof(Slist));
    if (new == NULL)
    {
        return FAILURE;
    }

    // Copy the file name to the new node
    strcpy(new->file_name, argv);
    new->link = NULL;

    // If the list is empty, add the new node as the head
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        // Otherwise, append the new node at the end
        Slist *temp = *head;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
    }

    return SUCCESS;
}

// Function to display the linked list
void display_list(Slist *head)
{
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        while (head)
        {
            printf("%s -> ", head->file_name);
            head = head->link;
        }
        printf("NULL\n");
    }
}

