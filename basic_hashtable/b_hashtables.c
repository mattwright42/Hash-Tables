#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair
{
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable
{
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL)
  {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char *u_str = (unsigned char *)str;

  while ((c = *u_str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  // Allocate memory
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));
  ht->storage = calloc(capacity, sizeof(Pair *));
  ht->capacity = capacity;

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // Create a new pair with key and value arguments
  Pair *new_pair = create_pair(key, value);
  // Make the index by using the hashing function on the key
  unsigned int index = hash(key, ht->capacity);
  //check to see if the index already exists
  if (ht->storage[index])
  {
    // If the key values don't match, print a warning
    if (strcmp(ht->storage[index]->key, key) != 0)
    {
      fprintf(stderr, "%s\n", "Warning: key value will be overwritten.");
    }
    // Destroy the old pair
    destroy_pair(ht->storage[index]);
  }
  //store the new pair
  ht->storage[index] = new_pair;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // find the storage index of the key
  unsigned int index = hash(key, ht->capacity);

  if (strcmp(ht->storage[index]->key, key) == 0)
  {
    ht->storage[index] = NULL;
    destroy_pair(ht->storage[index]);
    }
  else
  {
    fprintf(stderr, "%s\n", "Could not find key.");
  }
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  //find the storage index of the key
  unsigned int index = hash(key, ht->capacity);
  // return the value of the index
  if (ht->storage[index])
  {
    return ht->storage[index]->value;
  }
  else
  // Return NULL
  {
    fprintf(stderr, "%s\n", "NULL");
    return NULL;
  }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  for (int i = 0; i < ht->capacity; i++)
  {
    free(ht->storage[i]);
  }
  free(ht->storage);
  free(ht);
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL)
  {
    printf("...gone tomorrow. (success)\n");
  }
  else
  {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
