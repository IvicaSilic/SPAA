#ifndef HASH_H
#define HASH_H

typedef struct Bin {
    char* word;
    struct Bin* next;
} Bin;

typedef struct {
    Bin** table;
    int size;
    int load;
} HashTable;

HashTable* NewTable(int size);
unsigned int hash(const char* word);
void Insert(HashTable* ht, char* word);
int Get(HashTable* ht, const char* word);
void DeleteTable(HashTable* ht);

#endif
