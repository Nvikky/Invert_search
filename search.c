/*
Name : N Venkata prasad
date : 26 / 10 / 24
description : search.c
*/
#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void search_in_database(const char *word_to_search, main_node *ptr[], int size) 
{    
        int index;
        char letter = tolower(word_to_search[0]);  // Convert to lowercase

        if (letter >= 'a' && letter <= 'z') {
            index = letter - 'a';  // Letters get index 0 to 25
        }
        else if (isdigit(letter)) {
            index = 26;  // Digits get index 26
        }
        else {
            index = 27;  // Special characters get index 27
        }
        if (ptr[index] != NULL) 
        {
        main_node *main_temp = ptr[index];
        while (main_temp != NULL) 
        {
            if (strcmp(main_temp->word, word_to_search) == 0) 
            {
                printf("The word '%s' is present in %d file(s).\n", main_temp->word, main_temp->file_count);
                sub_node *sub_temp = main_temp->sub_link;
                while (sub_temp != NULL) 
                {
                    printf("%s - %d occurrences\n", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->link;
                }
                return;
            }
            main_temp = main_temp->link;
        }
    }
    printf("The word '%s' is not present in the database.\n", word_to_search);
}