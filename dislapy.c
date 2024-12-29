/*
Name : N Venkata prasad
date : 26 / 10 / 24
description : display.c 
*/
#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int display_database(main_node *ptr[], int size)
{
    // Loop through each index of the array
    for (int i = 0; i < size; i++)
    {
        if (!ptr[i]) continue;  // Skip if no main_node at this index

        printf("Index %d:\n", i);

        // Traverse the main_node linked list at the current index
        for (main_node *main = ptr[i]; main; main = main->link)
        {
            printf("  Word: %s, File Count: %d\n", main->word, main->file_count);

            // Traverse the subnode linked list for each word
            for (sub_node *sub = main->sub_link; sub; sub = sub->link)
            {
                printf("    File Name: %s, Word Count: %d\n", sub->file_name, sub->word_count);
            }
        }
    }

    return SUCCESS;  // Return success status
}
