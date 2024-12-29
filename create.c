/*
Name : N Venkata prasad
date : 26/10/ 24
description : create.c 
*/
#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int initialize_main_array(main_node *arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = NULL;
    }
    return SUCCESS;
}

int create_database(Slist **head, main_node *arr[], int size)
{
    Slist *temp = *head;
    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->file_name, "r");
        if (fptr == NULL)
        {
            printf("ERROR: Could not open file %s\n", temp->file_name);
            return FAILURE;
        }
        
        char word1[20];
        while (fscanf(fptr, "%s", word1) != EOF)
        {
            int index;
        char letter = tolower(word1[0]);  // Convert to lowercase

        if (letter >= 'a' && letter <= 'z') {
            index = letter - 'a';  // Letters get index 0 to 25
        }
        else if (isdigit(letter)) {
            index = 26;  // Digits get index 26
        }
        else {
            index = 27;  // Special characters get index 27
        }


            if (arr[index] == NULL)
            {
                // Create new main_node and subnode for the word
                main_node *new = (main_node *)malloc(sizeof(main_node));
                if (new == NULL)
                    return FAILURE;

                sub_node *new2 = malloc(sizeof(sub_node));
                if (new2 == NULL)
                    return FAILURE;

                strcpy(new->word, word1);
                new->file_count = 1;
                new->sub_link = new2;
                new->link = NULL;

                strcpy(new2->file_name, temp->file_name);
                new2->word_count = 1;
                new2->link = NULL;

                arr[index] = (main_node *)new;
            }
            else
            {
                int flag = 0;
                main_node *find = arr[index];
                
                // Traverse the main_node list to check for the word
                while (find != NULL)
                {
                    if (strcmp(find->word, word1) == 0)
                    {
                        // Word is found, check subnodes for file name
                        sub_node *subfind = find->sub_link;
                        while (subfind != NULL)
                        {
                            if (strcmp(subfind->file_name, temp->file_name) == 0)
                            {
                                // Word found in the same file, increment word count
                                //printf("%s, %s\n", temp->file_name, word1);
                                subfind->word_count++;
                                flag = 1;
                                break;
                            }
                            subfind = subfind->link;
                        }

                        if (flag == 0)
                        {
                            // Word is found, but not in the current file, create new subnode
                            sub_node *new2 = malloc(sizeof(sub_node));
                            if (new2 == NULL)
                                return FAILURE;

                            strcpy(new2->file_name, temp->file_name);
                            new2->word_count = 1;
                            new2->link = NULL;

                            // Attach the new subnode at the end of the subnode list
                            sub_node *subfind2 = find->sub_link;
                            while (subfind2->link != NULL)
                            {
                                subfind2 = subfind2->link;
                            }
                            subfind2->link = new2;
                            find->file_count++;
                        }
                        break;
                    }
                    find = find->link;
                }

                if (flag == 0 && find == NULL)
                {
                    // Word not found in the main_node list, create a new main_node
                    main_node *new5 = malloc(sizeof(main_node));
                    if (new5 == NULL)
                        return FAILURE;

                    sub_node *new6 = malloc(sizeof(sub_node));
                    if (new6 == NULL)
                        return FAILURE;

                    strcpy(new5->word, word1);
                    new5->file_count = 1;
                    new5->sub_link = new6;
                    new5->link = NULL;

                    strcpy(new6->file_name, temp->file_name);
                    new6->word_count = 1;
                    new6->link = NULL;

                    main_node *find2 = arr[index];
                    while (find2->link != NULL)
                    {
                        find2 = find2->link;
                    }
                    find2->link = new5;
                }
            }
        }

        fclose(fptr);
        temp = temp->link; // Move to the next file in the list
    }

    return SUCCESS;
}
