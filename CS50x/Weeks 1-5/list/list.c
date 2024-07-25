#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

#define LIST_SIZE 2

bool unload(node *list);
void visualizer(node *list);

int main(void)
{
    node *list = NULL;

    // Add items to list
    for (int i = 0; i < LIST_SIZE; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // TODO: add phrase to new node in list
        // Create note
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return 1;
        }

        // Populate node with our phrase
        n->phrase = phrase;
        n->next = NULL;

        // Link the list
        n->next = list;
        list = n;
        // Visualize list after adding a node.
        visualizer(list);
    }

    // Free all memory used
    if (!unload(list))
    {
        printf("Error freeing the list.\n");
        return 1;
    }

    printf("Freed the list.\n");
    return 0;
}

bool unload(node *list)
{
    // TODO: Free all allocated nodes
    // Create helper variable to keep track of nodes
    node *ptr = list;

    while( ptr != NULL)
    {
        //set the helper variable to the next item in the list
        ptr = list->next;
        //free list
        free(list);
        //set list equal to that next item
        list = ptr;
    }
    return false;
}

void visualizer(node *list)
{
    printf("\n+-- List Visualizer --+\n\n");
    while (list != NULL)
    {
        printf("Location %p\nPhrase: \"%s\"\nNext: %p\n\n", list, list->phrase, list->next);
        list = list->next;
    }
    printf("+---------------------+\n\n");
}
