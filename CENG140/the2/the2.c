#include <stdio.h>
#include <stdlib.h>

int transform_name(const char *name)
{
    int sum = 0;
    int i;
    int n = 0;
    while (name[n] != '\0')
    {
        n++;
    }
    for (i = 0;i < n;i++)
    {
        sum += (i+1)*(i+1)*(name[i]);
    }
    
    return sum;
}

int** initialize_storage(int IA_size, int DA_size, int** DA_sizes)
{
    int **storage;
    int i, j;
   
    *DA_sizes = malloc(sizeof(int)*IA_size);
    if (DA_sizes == NULL)
    {
        return NULL;
    }
        
    storage = malloc(sizeof(int*)*IA_size);
    if (storage == NULL)
    {
        return NULL;
    }
    
    for (i = 0;i < IA_size;i++)
    {
        storage[i] = malloc(sizeof(int)*DA_size);
        (*DA_sizes)[i] = DA_size;
    }
    
    for (i = 0;i < IA_size;i++)
    {
        for (j = 0;j < (*DA_sizes)[i];j++)
        {
            storage[i][j] = 0;
        }
    }
    
    return storage;
}

void print_storage(int** storage, int IA_size, int* DA_sizes)
{
    int i, j;
    for (i = 0;i < IA_size;i++)
    {
        printf("%d ->", i);
        for (j = 0;j < DA_sizes[i];j++)
        {
            printf(" %d", storage[i][j]);
        }
        printf("\n");
    }
}

void insert(int** storage, int IA_size, const char* name, int* DA_sizes)
{
    int name_code = transform_name(name);
    int index = name_code % IA_size;
    int i, j;
    int flag = 0;
    int new_size;
    for (i = 0;i < DA_sizes[index]; i++)
    {
        if (storage[index][i] == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        storage[index][i] = name_code;
    }
    else
    {
        new_size = DA_sizes[index] * 2;
        storage[index] = realloc(storage[index], sizeof(int)*new_size);
        if (storage[index] == NULL)
        {
            return;
        }
        
        for (j = DA_sizes[index];j < new_size;j++)
        {
            storage[index][j] = 0;
        }
        DA_sizes[index] = new_size;
        for (;i < new_size;i++)
        {
            if (storage[index][i] == 0)
            {
                storage[index][i] = name_code;
                break;
            }
        }
    }
    
}

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes)
{
    int index = name_code % IA_size;
    int i, j;
    int flag = 0;
    int new_size;
    for (i = 0;i < DA_sizes[index]; i++)
    {
        if (storage[index][i] == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        storage[index][i] = name_code;
    }
    else
    {
        new_size = DA_sizes[index] * 2;
        storage[index] = realloc(storage[index], sizeof(int)*new_size);
        if (storage[index] == NULL)
        {
            return;
        }
        
        for (j = DA_sizes[index];j < new_size;j++)
        {
            storage[index][j] = 0;
        }
        DA_sizes[index] = new_size;
        for (;i < new_size;i++)
        {
            if (storage[index][i] == 0)
            {
                storage[index][i] = name_code;
                break;
            }
        }
    }
}

void fill_new_storage(int** storage, int IA_size, int** new_storage, int *DA_sizes, int** new_DA_sizes)
{
    int i,j;
 
    for (i = 0;i < IA_size;i++)
    {
        for (j = 0;j < DA_sizes[i];j++)
        {
            if (storage[i][j] != 0)
            {
                insert2(new_storage, IA_size*2, storage[i][j], *new_DA_sizes);
            }
        }
    }
}

void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes)
{
    int total = 0;
    int i;
    int** new_storage;
    int* new_DA_sizes;
    float factor = (*IA_size)*(DA_size)*1.5;
    int new_IA_size;
    
    for (i = 0;i < *IA_size;i++)
    {
        total += (*DA_sizes)[i];
    }
    
    if (factor<=total)
    {
        new_IA_size = (*IA_size)*2;
        new_storage = initialize_storage(new_IA_size, DA_size, &new_DA_sizes);

        fill_new_storage(*storage, *IA_size, new_storage, *DA_sizes, &new_DA_sizes);
        
        free(*DA_sizes);
        for (i = 0;i < *IA_size;i++)
        {
            free((*storage)[i]);
        }
        free(*storage);
        
        *storage = new_storage;
        *DA_sizes = new_DA_sizes;
        *IA_size = new_IA_size;
        
    }
}

