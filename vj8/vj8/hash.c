#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define HCONST 3567892

HashTable* NewTable(int size)
{
    HashTable* dict = malloc(sizeof(HashTable));
    if (!dict) return NULL;

    dict->table = malloc(sizeof(Bin*) * size);
    if (!dict->table)
    {
        free(dict);
        return NULL;
    }

    dict->size = size;
    dict->load = 0;

    for (int i = 0; i < size; i++)
        dict->table[i] = NULL;

    return dict;
}

unsigned int hash(const char* word)
{
    unsigned int key = 0;
    while (*word)
        key = key * HCONST + (unsigned char)*word++;
    return key;
}

void Insert(HashTable* ht, char* word)
{
    unsigned int key = hash(word) % ht->size;

    Bin* tmp = malloc(sizeof(Bin));
    if (!tmp) return;

    tmp->word = word;
    tmp->next = ht->table[key];
    ht->table[key] = tmp;

    ht->load++;
}


int Get(HashTable* ht, const char* word)
{
    unsigned int key = hash(word) % ht->size;
    Bin* item = ht->table[key];

    while (item)
    {
        if (strcmp(item->word, word) == 0)
            return 1;
        item = item->next;
    }
    return 0;
}

void DeleteTable(HashTable* ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        Bin* cur = ht->table[i];
        while (cur)
        {
            Bin* next = cur->next;
            free(cur->word);
            free(cur);
            cur = next;
        }
    }
    free(ht->table);
    free(ht);
}
