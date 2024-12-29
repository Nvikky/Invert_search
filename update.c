/*
Name : N Venkata prasad
date : 26 / 10 / 24
description : update.c 
*/
#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

// Function to update the database based on the input file
int update_database(const char *database_filename, main_node **ptr, int size,Slist **head) 
{
    FILE *file = fopen(database_filename, "r");

    // Initialize all nodes in the array to NULL
    for (int i = 0; i < size; i++) {
        ptr[i] = NULL; // Start with NULL for all indexes
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the line (if present)
        line[strcspn(line, "\n")] = 0;

        // Strip the '#' characters
        line[strlen(line) - 1] = '\0'; // Remove last '#'
        char *line_without_hash = line + 1; // Skip the first '#'

        // Parse the line (format: index:word:file_count:filename1:file_count1:filename2:file_count2)
        int index = 0;
        char word[10];
        int file_count = 0;
        // Extract index, word, and file_count
        char *token = strtok(line_without_hash, ";");
        if (token) index = atoi(token);
        token = strtok(NULL, ";");
        if (token) strncpy(word, token, sizeof(word));
        token = strtok(NULL, ";");
        if (token) file_count = atoi(token);


        // Create a new main node if it doesn't exist for the index
            // If no main node exists, create one
            main_node *new_main = (main_node *)malloc(sizeof(main_node));
            if (new_main == NULL) {
                fclose(file);
                return FAILURE; // Memory allocation failed
            }
            //new_main = ptr[index];
            strncpy(new_main->word, word, sizeof(new_main->word));
            new_main->file_count = file_count;
            new_main->link = NULL;
            new_main->sub_link = NULL;
            if (ptr[index] == NULL) {
            // Assign the new main node to the array
            ptr[index] = new_main;
        } 
        else 
        {
            main_node *current_main = ptr[index];
            while (current_main->link != NULL) 
            {
                current_main = current_main->link; // Move to the last main node
            }
            current_main->link = new_main; 
           
        }

        // Create subnodes based on file_count
        for (int i = 0; i < file_count; i++) {
            // Read the next filename and word_count
            token = strtok(NULL, ";"); // Get the filename
            char file_name[20];
            if (token) {
                strncpy(file_name, token, sizeof(file_name));
                 /*Delete the file names from Single link list while  updating   of data  """if you want to create data 
                base after updation""" .if same file found duplicate data will be update So, we need to delete that 
                file name from Single linked list
                */
              delete_node(head,file_name);
            } else {
                printf("ERROR: Missing filename for subnode at index %d\n", index);
                break; // Break if there's an error
            }

            token = strtok(NULL, ";"); // Get the word_count
            int word_count = 0;
            if (token) {
                word_count = atoi(token);
            } else {
                printf("ERROR: Missing word count for subnode at index %d\n", index);
                break; // Break if there's an error
            }

            // Create a new subnode
            sub_node *new_subnode = malloc(sizeof(sub_node));
            if (new_subnode == NULL) {
                fclose(file);
                return FAILURE; // Memory allocation failed
            }
            new_subnode->word_count = word_count;
            strncpy(new_subnode->file_name, file_name, sizeof(new_subnode->file_name));
            new_subnode->link = NULL;

            // Append the new subnode to the linked list of subnodes for this main node
            if (new_main->sub_link == NULL) {
                new_main->sub_link = new_subnode; // First subnode
            } else {
                // Find the last subnode and append the new one
                sub_node *current = new_main->sub_link;
                while (current->link != NULL) {
                    current = current->link; // Move to the last subnode
                }
                current->link = new_subnode; // Append the new subnode
            }
        }
    }

    fclose(file);
    return SUCCESS; // Database updated successfully
}


// Function to check if a file exists and if all lines start and end with '#'
int file_exists(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        return FAILURE; // File does not exist
    }

    char line[256]; // Buffer to hold each line
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);

        // Check if the line has at least 2 characters for '#' at start and end
        if (len < 2 || line[0] != '#' || line[len - 2] != '#') {
            fclose(file);
            return FAILURE; // Invalid line found
        }
    }

    fclose(file);
    return SUCCESS; // All lines are valid
}



void delete_node(Slist **head, const char *file_name) 
{
    if (head == NULL || *head == NULL) {
        return; // List is empty or head pointer is NULL
    }

    Slist *temp = *head; // Start from the head
    Slist *prev = NULL;   // Previous pointer

    // Traverse the list
    while (temp != NULL) 
    {
        // Check if the current node matches the file_name
        if (strcmp(temp->file_name, file_name) == 0) 
        {
            // If the node to delete is the head
            if (prev == NULL) 
            {
                *head = temp->link; // Move head pointer to next node
            } 
            else 
            {
                prev->link = temp->link; // Bypass the node to delete
            }

            // Free the memory allocated for the node
            free(temp);       // Free the node itself
            return;          // Node deleted, exit function
        }
        // Move to the next node
        prev = temp;       // Update previous pointer
        temp = temp->link; // Move to the next node
    }
    return;
}