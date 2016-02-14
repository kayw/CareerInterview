#include"hashTable.h"
/*
 * djb2
this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. another version of this algorithm (now favored by bernstein) uses xor: hash((unsigned char*)i) = hash((unsigned char*)i - 1) * 33 ^ str[i]; the magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained. 
*/
static unsigned long hash(unsigned char* str) {
    unsigned long h = 5381;
    int c;
    while(c = *str++)
        h = ((h << 5) + h) + c; /* h*33+c */
    return h;
}

/*
 * sdbm
 * this algorithm was created for sdbm (a public-domain reimplementation of ndbm) database library. it was found to do well in scrambling bits, causing better distribution of the keys and fewer splits. it also happens to be a good general hashing function with good distribution. the actual function is hash((unsigned char*)i) = hash((unsigned char*)i - 1) * 65599 + str[i]; what is included below is the faster version used in gawk. [there is even a faster, duff-device version] the magic constant 65599 was picked out of thin air while experimenting with different constants, and turns out to be a prime. this is one of the algorithms used in berkeley db (see sleepycat) and elsewhere. 
 */
static unsigned long hash_sdbm(unsigned char* str) {
    unsigned long h = 0;
    int c;
    while(c = *str++)
        h = c + (h << 6) + (h << 16) - h;
    return h;
}

/*
*static uint hash_qt(const uchar *p, int n) 
*{ 
*    uint h = 0; 
*    uint g; 
*
*    while (n--) { 
*        h = (h << 4) + *p++; 
*        g = h & 0xf0000000; 
*        h ^= g >> 23; 
*        h &= ~g; 
*    } 
*    return h; 
*} 
*/

hashTable::hashTable(int capacity, float fill_percent)
    :count_(0L), capacity_(capacity), fill_percent_(fill_percent) {
    table_ = new pEntry[capacity];
    for(int i = capacity; i-- > 0; )
        table_[i] = 0;
    threshold_ = int(capacity * fill_percent);
}

int hashTable::insert(const char* k, void* v) {
    int h = int(hash((unsigned char*)k) % capacity_);
    for(pEntry e = table_[h]; e != 0; e = e->next_) {
        if(!strcmp(k, e->key_)){
            e->value_ = v;
            return 1;
        }
    }
    if(count_ > threshold_) {
        rehash();
        h = int(hash((unsigned char*)k) % capacity_);
    }

    pEntry e = new hashTableEntry(k, v);
    /*
     * |h |-> |A|
     * |e->next_ | -> |A|
     * |h| -> |e e->next_| -> |A|
     */
    /*
     * e->next_ = table_[h]->next_;
     * table_[h]->next_ = e;
     */
    e->next_ = table_[h];
    table_[h] = e;
    count_++;
    return 0;
}

void* hashTable::find(const char* k) const {
    int h = int(hash((unsigned char*)k) % capacity_);
    for(pEntry e = table_[h]; e != 0; e = e->next_) {
        if(!strcmp(k, e->key_)){
            return e->value_;
        }
    }
    return NULL;
}

int hashTable::remove(char* k) {
    int h = int(hash((unsigned char*)k) % capacity_);
    for(pEntry e = table_[h], prev = NULL; e != 0; prev =e, e = e->next_) {
        if(!strcmp(e->key_, k)) {
            if(!prev){
                prev->next_ = e->next_;
            } else {
                table_[h] = e->next_;
            }
            delete e;
            e = NULL;
            return 1;
        }
    }
    return 0;
}

void hashTable::remove_all() {
    pEntry e;
    for(int i = capacity_; i-- > 0; ){
        for(e = table_[i]; e != NULL;) {
            pEntry tmp = e;
            e = e->next_;
            delete [] tmp->key_;
            delete tmp;
        }
        table_[i] = 0;
    }
    count_ = 0;
}

void hashTable::rehash(){
    pEntry* old_table = table_;
    int old_capacity = capacity_;
    /* table array of pointers can't be bigger than 64k, sizeof pointer 4*/
    if( capacity_ * 2 + 1 > 0xFFFF/4 ){
        threshold_ = 1000000L;
        return;
    }
    capacity_ = capacity_*2+1;
    table_ = new pEntry[capacity_];
    for(int i = 0; i < capacity_; i++)
        table_[i] = 0;
    threshold_ = int(capacity_*fill_percent_);
    pEntry e,enext;
    for(int i = old_capacity; i-- > 0;){
        for(e = old_table[i]; e != NULL; e = enext){
            enext = e->next_;
            int h = int(hash((unsigned char*)e->key_)%capacity_);
            e->next_ = table_[h];
            table_[h] = e;
        }
    }
    delete[] old_table;
}

/*   Sets the iterator to the beginning                                        
*/
void HashTableIterator::reset() {
    for( entry_ = 0, index_ = 0, next_entry_ = NULL ; index_ < hashtable_.getCapacity() ; index_++ )
        if( (hashtable_.get_table())[index_] != 0 ){
            next_entry_ = (hashtable_.get_table())[index_];
            return;
        }
}
//void HashTableIterator::reset(){
//    for( entry_ = 0, index_ = 0 ; index_ < hashtable_.getCapacity() ; index_++ )
//        if( (hashtable_.get_table())[index_] != 0 ){
//            entry_ = (hashtable_.get_table())[index_];
//            return;
//        }
//}

bool HashTableIterator::hasNext() {
    if(next_entry_== NULL) return false;
    else return true;
}

/*   Returns next element of the iteration                                    
*/
void HashTableIterator::next(){
    entry_ = next_entry_;
    if(entry_->next_ != 0)
        next_entry_ = entry_->next_;
    else {
        for( next_entry_=0, index_++ ; index_ < hashtable_.getCapacity() ; index_++ )
            if( hashtable_.get_table()[index_] != 0 ){
                next_entry_ = (hashtable_.get_table())[index_];
                break;
            }
    }
}

char* HashTableIterator::getKey(){
    return entry_->key_;
}

void* HashTableIterator::getValue() {
    return entry_->value_;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

int MultiHashTable::insert(char * key, void * value){
    // Find record in the hashtable.
    // long hash = HashCode(key);
    // int  index = (int) ((hash & 0x7FFFFFFFL) % capacity);
    int index = int(hash((unsigned char*)key) % capacity_);

    // Rehash the table if the threshold is exceeded.
    if(count_ >= threshold_){
        rehash();
        //index = (int)((hash & 0x7FFFFFFFL) % capacity);
        index = int(hash((unsigned char*)key) % capacity_);
    }

    // Create the new entry.
    hashTableEntry * e = new hashTableEntry(key, value);  

    e->next_  = table_[index];
    table_[index] = e;
    count_++;
    return 0;
}

void * MultiHashTable::pop(char * key)
{
    void * value = find(key);
    remove(key);
    return value;
}
