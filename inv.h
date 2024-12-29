/*
Name : N Venkata prasad
date : 26/10/24
description : inv.h
*/

#ifndef INVERTED_H
#define INVERTED_H

#define SUCCESS 1
#define FAILURE 0

typedef struct node
{
    char file_name[20];
    struct node *link;
} Slist;

typedef struct subnode
{
    int word_count;
    char file_name[20];
    struct subnode *link;
} sub_node;

typedef struct mainnode
{
    char word[10];
    int file_count;
    struct main_node *link;
    sub_node *sub_link;
} main_node;  // Correct type alias

int add_list(Slist **head, char name[20]);
int read_and_validate(int argc, char *argv[], Slist **head);
void display_list(Slist *head);
int initialize_main_array(main_node *arr[], int size);
int create_database(Slist **head, main_node *arr[], int size);
int save_database(main_node *arr[], int size, const char *output_filename);
int display_database(main_node *arr[], int size);
void search_in_database(const char *word_to_search, main_node *arr[], int size);
int update_database(const char *database_filename, main_node **arr, int size,Slist **head);
int file_exists(const char *filename);
void delete_node(Slist **head, const char *file_name);
#endif
