/*
Name : N Venkata prasad
date : 26 / 10 / 24
description : save.c 
*/
#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int save_database(main_node *ptr[], int size, const char *output_filename)
{
    FILE *output_file = fopen(output_filename, "w"); // Open the output file in write mode
    if (output_file == NULL)
    {
        printf("ERROR: Could not open file %s for writing\n", output_filename);
        return FAILURE;
    }

    for (int i = 0; i < size; i++)
    {
        main_node *current_main = ptr[i];
        while (current_main != NULL) // Traverse the linked list for each index
        {
            // Start line with '#' and write index, word, and file_count
            fprintf(output_file, "#%d;%s;%d", i, current_main->word, current_main->file_count); 

            sub_node *current_sub = current_main->sub_link;
            while (current_sub != NULL) // Traverse the subnode list
            {
                // Write filename and word_count
                fprintf(output_file, ";%s;%d", current_sub->file_name, current_sub->word_count); 
                current_sub = current_sub->link;
            }

            // End line with '#' and add newline for the next main_node
            fprintf(output_file, "#\n"); 
            current_main = current_main->link;
        }
    }

    fclose(output_file); // Close the output file
    return SUCCESS;
}
