/*
 * File: hashing_doublehashing.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: November 1, 2023
 * Description: This program implements hashing using using double hashing for collision resolution
 */


// IMPORTANT: Use hash2(x) = 11 - (x % 11) as the 2nd hash function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 23

typedef struct KeyValue {
    char *key;
    char *value;
    bool isDeleted;
} KeyValue;

typedef struct {
    KeyValue **array;
    int size;
    float load_factor;
    // num of keys present
    int num_keys;
    // num of array indices of the table that are occupied
    int num_occupied_indices;
    // num of ops done so far
    int num_ops;
} HashTable;


KeyValue *createKeyValue(char *key, char *value) {
    KeyValue* newKeyValue = (KeyValue*)malloc(sizeof(KeyValue));
    if (newKeyValue != NULL) {
        newKeyValue->key = key;
        newKeyValue->value = value;
    }
    newKeyValue->isDeleted = false;
    return newKeyValue;
}

HashTable* createHashTable() {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->array = (KeyValue **)malloc(TABLE_SIZE * sizeof(KeyValue *));
    for (int i=0; i<TABLE_SIZE; i++)
        newTable->array[i] = NULL;

    newTable->size = TABLE_SIZE;
    newTable->load_factor = 0;
    newTable->num_keys = 0;
    newTable->num_occupied_indices = 0;
    newTable->num_ops = 0;
    return newTable;
}


// use sum of ascii values to convert string to int
int key_to_int(char* key) {
    int sum = 0;
    for(int i = 0; key[i]!='\0'; i++) {
        sum += key[i];
    }
    return sum;
}

int hash1(HashTable* ht, char* key) {
    return (key_to_int(key) % ht->size);
}

int hash2(HashTable* ht, char* key) {
    return (11 - (key_to_int(key)%11));
}

// return the index position in the table where the insertion happens
// return -1 if insertion fails
int insert_key_value(HashTable *ht, char* key, char* value) {
    if(ht->num_keys==ht->size) {
        printf("Hash Table is full");
        return -1;
    }
    else {
        KeyValue* kv = createKeyValue(key, value);
        int i = 0;
        int index;
        index = (hash1(ht,kv->key) + i*hash2(ht,kv->key))%ht->size;
        ht->num_ops++;
        while(ht->array[index]!=NULL && !ht->array[index]->isDeleted && i<ht->size) {
            if(strcmp(ht->array[index]->key, kv->key)==0) {
                ht->array[index]->value = strdup(kv->value);
                return index;
            }
            i++;
            index = (hash1(ht,kv->key) + i*hash2(ht,kv->key))%ht->size;
            ht->num_ops++;
        }
        ht->array[index] = kv;
        ht->num_keys++;
        ht->num_occupied_indices++;
        ht->load_factor = (ht->num_keys*1.0) / (ht->size);
        return index;
    }
}

// return the value of the key in the table
// return NULL if key not found
char *search_key(HashTable *ht, char* key) {
        int i = 0;
        int index;
        index = (hash1(ht,key) + i*hash2(ht,key))%ht->size;
        while(ht->array[index]!=NULL && i<ht->size) {
            ht->num_ops++;
            if(!ht->array[index]->isDeleted && strcmp(ht->array[index]->key, key)==0) {
                
                return ht->array[index]->value;
            }
            i++;
            index = (hash1(ht,key) + i*hash2(ht,key))%ht->size;
        }
        return NULL;
}

// return the index position in the table where the deletion happens
// return -1 if deletion fails
int delete_key(HashTable *ht, char* key) {
        int i = 0;
        int index;
        index = (hash1(ht,key) + i*hash2(ht,key))%ht->size;
        while(ht->array[index]!=NULL && i<ht->size) {
            ht->num_ops++;
            if(!ht->array[index]->isDeleted && strcmp(ht->array[index]->key, key)==0) {
                ht->array[index]->isDeleted = true;
                ht->num_keys--;
                return index;
            }
            i++;
            index = (hash1(ht,key) + i*hash2(ht,key))%ht->size;
        }
        return -1; 
}

// this equals the number of keys in table/size of table
float get_load_factor(HashTable *ht) {
    return ht->load_factor;
}

// this equals the number of operations done so far/num of elems in table
float get_avg_probes(HashTable *ht) {
    if (ht->num_keys == 0) return 0;
    return (ht->num_ops*1.0) / (ht->num_occupied_indices);
}

// display hash table visually
void display(HashTable *ht) {
    printf("\nHash Table : \n\n");
    printf("\t\tKey\t\t\tValue\n");
    for(int i = 0; i<ht->size; i++) {
        if(ht->array[i]!=NULL && !ht->array[i]->isDeleted) {
            printf("%d\t|%-23s|%-23s|\n", i, ht->array[i]->key, ht->array[i]->value);
        }
        else {
            printf("%d\t|\t\t\t|\t\t\t|\n", i);
        }  
    }
    printf("\n\n");
}

int main() {
    HashTable* ht = createHashTable();
    insert_key_value(ht, "first name", "Manan");
    insert_key_value(ht, "last name", "Kher");
    insert_key_value(ht, "uid", "2022300049");
    insert_key_value(ht, "sport", "Football");
    insert_key_value(ht, "food", "Chicken Noodles");
    insert_key_value(ht, "holiday", "Backwaters");
    insert_key_value(ht, "role_model", "PewDiePie");
    insert_key_value(ht, "subject", "Maths");
    insert_key_value(ht, "song", "Never Gonna Give You Up");
    insert_key_value(ht, "movie", "Avengers: EndGame");
    insert_key_value(ht, "colour", "Purple");
    insert_key_value(ht, "book", "Goosebumps");
    display(ht);
    printf("Load factor is %f and average probes are %f\n", get_load_factor(ht), get_avg_probes(ht));
    printf("%s\n", search_key(ht, "sport"));
    printf("%s\n", search_key(ht, "uid"));
    printf("%s\n", search_key(ht, "last name"));
    printf("%s\n", search_key(ht, "book"));
    printf("%s\n", search_key(ht, "food"));
    delete_key(ht, "uid");
    delete_key(ht, "book");
    display(ht);
    printf("%s\n", search_key(ht, "book"));
    return 0;
}


// -> Insert the following key, values in the table:
// 1. 'first name' -> <your first name>
// 2. 'last name' -> <your last name>
// 3. 'uid' -> <your uid>
// 4. 'sport' -> <your favorite sport>
// 5. 'food' -> <your favorite food>
// 6. 'holiday' -> <your favorite holiday destination>
// 7. 'role_model' -> <your role model>
// 8. 'subject' -> <your favourite subject>
// 9. 'song' -> <your favourite song>
// 10. 'movie' -> <your favorite movie>
// 11. 'colour' -> <your favorite colour>
// 12. 'book' -> <your favorite book>

// -> Test the table with search and delete operations