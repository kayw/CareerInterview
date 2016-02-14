#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct hashTableEntry {
    char* key_;
    void* value_;
    hashTableEntry* next_;
    hashTableEntry(const char* k, void* v) : value_(v) {
        key_ = new char[strlen(k) + 1];
        strcpy(key_,k);
    }
}* pEntry;
    
class hashTable {
public:
    // Capacity the initial number of buckets.
    // FillPercent is usually a number between 0.0 and 1.0
    // (but you can use it in range 0..10.0 or
    //  use 0.75 and set table limit 16000 in function Rehash)
    hashTable(int capacity = 101, float fill_percent = 0.75);
    ~hashTable(){ remove_all(); delete[]table_; }

    int insert(const char* k, void* v);
    void* find(const char* k) const;
    int remove(char* k);
    void remove_all();
    inline int getCapacity() const { return capacity_;}
    inline pEntry* get_table() { return table_;}

protected:
    void rehash();
    pEntry* table_;
    int count_; // number of table * pEntry
    int capacity_;  // length of allocated memory 
    long threshold_; //rehash the table when exceed threshold
    float fill_percent_;
};

//-----------------------------------------------------------------------
//                    Hash table iterator
//-----------------------------------------------------------------------
class HashTableIterator {
    int index_;
    hashTableEntry *entry_;
    hashTableEntry* next_entry_;
    hashTable   &hashtable_;
    void reset();

    public:
    HashTableIterator(hashTable &ht) : hashtable_(ht) { reset(); }
    char* getKey();
    void* getValue();
    void next();
    bool hasNext();
};

class MultiHashTable : public hashTable {
    public:
        int insert(char * k, void * v);
        void * pop(char * k);
};
#endif
