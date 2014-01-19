#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "types.h"

//List all the integer number no less than 57 total number is 28
//And each number is about half of its next number
static int prime[] =
{
    57,        97,         193,        389,        769,
    1543,      3079,       6151,       12289,      24593,
    49157,     98317,      196613,     393241,     786433,
    1572869,   3145739,    6291469,    12582917,   25165843,
    50331653,  100663319,  201326611,  402653189,  805306457,
    1610612741
};

class HashMapUtil
{
public:
    static int find_next_prime(int current)
    {
        //Find the next prime number by searching in the prime number list
        size_t i = 0;
        for( ; i < ARRAYSIZEOF(prime); i++ )
            if(current < prime[i])
                break;
        return prime[i];     //return the next larger prime.
    }
};

template <class Key, class Value, class HashFunc, class EqualKey>
class HashMap
{
private:
    template <class _Key, class _Value>
    class KeyNode
    {
        public:
        _Value  value;      //Store the value
        _Key    key;        //Store the keyword
        int    used;
        //if the type of Value/Key is your own class, make sure they can handle copy constructor and operator =
        KeyNode():used(0){}
        KeyNode(const KeyNode &other)
        {
            value = other.value;
            key = other.key;
            used = other.used;
        }
        KeyNode & operator=(const KeyNode &other)
        {
            if(this == &other) {
             return *this;
            }
            value = other.value;
            key = other.key;
            used = other.used;
            return *this;
        }
    };

public:
       HashMap();
       ~HashMap();
       bool insert(const Key& hashKey, const Value& value);
       bool remove(const Key& hashKey);
       void rehash();  //use it when rehashing
       Value& find(const Key& hashKey);
       const Value& operator [](const Key& hashKey) const;
       Value& operator [](const Key& hashKey);
private:
        int findKey(const Key& hashKey);  //find the index of a key
private:
        static const double loadingFactor = 0.9;
        HashFunc hash;
        EqualKey equal;
        KeyNode<Key ,Value> *table;
        int size;    //current number of itmes
        int capacity;   //capacity of the array
       
  
};


template<class Key , class Value , class HashFunc , class EqualKey>
HashMap<Key, Value, HashFunc, EqualKey>::HashMap()
{
    hash = HashFunc();
    equal = EqualKey();
    capacity = HashMapUtil::find_next_prime(0); //initialize the capacity with first primer 57
    //resize the table with capacity because an extra one is used
    //to return the NULL type of Value in the function find
    table = new KeyNode<Key,Value>[capacity+1];
    for(int i = 0 ; i < capacity ; i++)    //initialize the table
        table[i].used = 0;
    size = 0;
}

template<class Key, class Value, class HashFunc, class EqualKey>
HashMap<Key, Value, HashFunc, EqualKey>::~HashMap()
{
    delete []table;
    table = NULL;
}

template<class Key, class Value, class HashFunc, class EqualKey>
bool HashMap<Key, Value, HashFunc, EqualKey>::insert(const Key& hashKey, const Value& value)
{
    int index = hash(hashKey)%capacity;
   
    if(table[index].used == 1)  //the key-value's hash is unique
    {
        return false;
    }
    table[index].used = 1;         //modify the KeyNode
    table[index].key = hashKey;
    table[index].value = value;

    size++;
    //if the table's size is too large ,then rehash it
    if (size >= capacity * loadingFactor)
        rehash();
    return true;
}

template<class Key, class Value, class HashFunc, class EqualKey>
void HashMap<Key, Value, HashFunc, EqualKey>::rehash()
{
    int pastsize = capacity;
    //create a new array to copy the information in the old table
    capacity = HashMapUtil::find_next_prime(capacity);
    KeyNode<Key,Value>* tmp = new KeyNode<Key,Value>[capacity];
    for(int i = 0 ; i < pastsize ; i++)
    {
        if(table[i].used == 1)       //copy the KeyNode into the tmp array
        {
            tmp[i] = table[i];
        }
    }
    delete []table; //release the memory of the old table

    table = new KeyNode<Key,Value>[capacity+1];   //resize the table
    for(int i = 0 ; i < capacity ; i++) //initialize the table
    {
        table[i].used = 0;
    }
    for(int i = 0 ; i < pastsize ; i++) //insert the item into the table one by one
    {
        if(tmp[i].used == 1)
            insert(tmp[i].key, tmp[i].value);
    }
    delete []tmp;               //delete the tmp array
}

template<class Key, class Value, class HashFunc, class EqualKey>
bool HashMap<Key, Value, HashFunc, EqualKey>::remove(const Key& hashKey)
{
    int index = findKey(hashKey); //find the index of the key
    if(index < 0) //if find modify the flag with 0,else print out "no such key!"
    {
        printf("No such key!\n");
        return false;
    }
    else
    {
        table[index].used = 0;
        size--;
        return true;
    }
}

template<class Key, class Value, class HashFunc, class EqualKey>
Value& HashMap<Key, Value, HashFunc, EqualKey>::find(const Key& hashKey)
{
    int index = findKey(hashKey);
    if(index < 0) //if index <0 ,not found,else return the index
    {
        printf("No such key!\n");
        return table[capacity].value; //return NULL
    }
    else
    {
        return table[index].value;
    }
}

template<class Key, class Value, class HashFunc, class EqualKey>
const Value& HashMap<Key, Value, HashFunc, EqualKey>::operator[](const Key& hashKey) const
{
    return find(hashKey); //overload the operation to return the value of the element
}

template<class Key, class Value, class HashFunc, class EqualKey>
Value& HashMap<Key, Value, HashFunc, EqualKey>::operator[](const Key& hashKey)
{
    return find(hashKey); //overload the operation to return the value of the element
}

template<class Key, class Value, class HashFunc, class EqualKey>
int HashMap<Key, Value, HashFunc, EqualKey>::findKey(const Key& hashKey)
{
    int index = hash(hashKey)%capacity;
    if ((table[index].used != 1) || !equal(table[index].key,hashKey))
        return -1;
    else
        return index;
}

#endif /* HASHMAP_H_ */
