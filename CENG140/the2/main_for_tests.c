#include <stdio.h>
#include "the2.h"

int main()
{
    char names[][10] = {"John", "Sophia", "Evelyn", "Aaron", "Emily",
    "Russell", "April", "Patrick", "Eva", "Jesse"}; /* names to be added into storage */
    int i; /* iterators */
    int IA_size = 3; /* initial IndexArray size */
    int DA_size = 3; /* default data array size */
    int** storage; /* storage variable */
    int* DA_sizes; /* data array sizes */
    
    storage = initialize_storage(IA_size, DA_size, &DA_sizes); /* initialize the storage */
    for (i = 0; i < 10; i++) /* for each person name in the list */
    {
        insert(storage, IA_size, names[i], DA_sizes); /* insert a person name into storage */
        print_storage(storage, IA_size, DA_sizes); /* print storage */
        /* Check if there is a need for the IndexArray extension. */
        /* Sent references of storage, current IndexArray size and data array sizes */
        /* to not lose their references while updating them in the implemented functions */
        resize_IA(&storage, &IA_size, DA_size, &DA_sizes);
    }
    /* Free up allocated memory for storage and DA_sizes */
    for (i = 0; i < IA_size; i++)
    {
        free(storage[i]);
    }
    free(storage);
    free(DA_sizes);
    return 0;
}
