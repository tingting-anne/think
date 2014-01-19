/* 
 *  HashMap.h 
 *  Declaration of the members and functions. 
 *  The type of key,value and the hash function,compare function is defined by users. 
 *  KeyNode represent the node in the hash table,putting them into the container. 
 *  Author: luxiaoxun 
 *  Modified by YJH. 
 */ 
#ifndef HASHMAP_H_ 
#define HASHMAP_H_ 
 
#include "types.h" 

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
    static int findNextPrimeNumber(int current)
    {
        //Find the next prime number by searching in the prime number list
        size_t i = 0;
        for( ; i < ARRAYSIZEOF(prime) ; i++)
            if(current < prime[i])
                break;
        return prime[i];     //return the next larger prime.
    }
};

 
/* 
 *  Inner class of HashMap. 
 *  Define the node of HashMap. 
 */ 
template<class Key, class Value> 
class KeyNode { 
public: 
	//Store the value 
	Value  value; 
	//Store the keyword 
    Key    key; 
    int removed; 
}; 
 
template<class Key, class Value, class HashFunc, class EqualKey> 
class HashMap { 
public: 
	HashMap(); 
	void insert(const Key& hashKey, const Value& value); 
	bool remove(const Key& hashKey); 
	void clear(); 
	Value& find(const Key& hashKey); 
	Value& operator[](const Key& hashKey); 
	~HashMap(); 
private: 
	//Used as a bucket 
	KeyNode<Key, Value>* table; 
	int size; 
	
	//Store the number of elements inserted 
	int num_element; 
	const static double _loadingFactor = 0.5; 
	static Value valueNull;
	int findKey(const Key& hashKey); 
	KeyNode<Key,Value>* rehash(int size, KeyNode<Key, Value>*&); 
}; 

template<class Key , class Value , class HashFunc , class EqualKey>
Value HashMap<Key, Value, HashFunc, EqualKey>::valueNull = Value();

/** 
 * Initialize hash table
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
HashMap<Key, Value, HashFunc, EqualKey>::HashMap() { 
	size=HashMapUtil::findNextPrimeNumber(0); 
	num_element = 0; 
	//New an array for the KeyNode 
	table = new KeyNode<Key,Value>[size]; 
	for ( int i = 0; i < size; i++ ) 
		// "removed = 1" means this space is empty 
		table[i].removed = 1; 
} 
 
/** 
 * destruction for Hash_Map 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
HashMap<Key, Value, HashFunc, EqualKey>::~HashMap() { 
	//Empty here. 
	delete []table; 
} 
 
/** 
 * Find the node with assigned key 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
Value& HashMap<Key, Value, HashFunc, EqualKey>::find(const Key& hashKey) { 
	//Find the index of the key by calling findKey. 
	int index = findKey(hashKey); 
	if ( index >= 0 && index < size ) 
		//Return the copy of the value. 
		return table[index].value; 
	else {
		printf("NOT FOUND!\n");
		return valueNull;
    }
		
    
	
} 
 
/** 
 * Insert a node in correct position 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
void HashMap<Key, Value, HashFunc, EqualKey>::insert(const Key& hashKey, const Value& value) { 
	if ( ( num_element + 1 ) > size * _loadingFactor ) 
		table = rehash(size,table); 
	// Calculate the hash value by calling HashFunc 
	int index=HashFunc::hashCode(hashKey) % size; 
	//if conflict, keep searching the key until find empty position. 
	while ( table[index].removed == 0 ) { 
		//If reach the end of the array, go to the first and continue 
		if ( index == ( size - 1 ) ) 
			index = 0; 
		else 
			index++; 
	} 
	//do the assignment 
	table[index].value = value; 
	table[index].key = hashKey; 
	table[index].removed = 0; 
	num_element++; 
} 
 
/** 
 * Rehash 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
KeyNode<Key,Value>* HashMap<Key, Value, HashFunc, EqualKey>::rehash(int old_size,KeyNode<Key,Value>*&) { 
	int tmpkey; 
	// find the updated size 
	size = HashMapUtil::findNextPrimeNumber(old_size); 
	//relocate a table for the map 
	KeyNode<Key,Value> *tmp = new KeyNode<Key,Value>[size]; 
	for ( int i = 0 ; i < old_size; i++ ) { 
		if ( table[i].removed == 0 ) {             //this space is occupied 
			//each node need to be inserted again 
			tmpkey = HashFunc::hashCode(table[i].key) % size; 
			while ( tmp[tmpkey].removed == 0 ) {	// conflict 
				if ( tmpkey == ( size - 1 ) ) 
					tmpkey = 0; 
				else 
					tmpkey++; 
			} 
		//find the right place and do the assignment 
		tmp[tmpkey].value = table[i].value; 
		tmp[tmpkey].key = table[i].key; 
		tmp[tmpkey].removed = 0; 
		} 
	} 
	//delete the old table 
	delete []table; 
	//return the new table 
	return tmp; 
} 
 
/** 
 * Clear the whole HashMap 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
void HashMap<Key, Value, HashFunc, EqualKey>::clear() { 
	int tmpsize = size; 
	//Reset the size of array. 
	size = HashMapUtil::findNextPrimeNumber(0); 
	int i; 
	for ( i = 0; i < size; i++ ) { 
		// the first nodes clear by lazy delete -- removed = 1 
		table[i].removed = 1; 
	} 
	for ( ; i < tmpsize; i++ ) 
		// delete the next nodes 
		delete table[i]; 
	num_element = 0; 
} 
 
/** 
 * Remove the node with assigned key 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
bool HashMap<Key, Value, HashFunc, EqualKey>::remove(const Key& hashKey) { 
	//Find the index of the key by calling findKey. 
	int i = findKey(hashKey); 
	if ( i != -1 ) 
		//Remove the key by setting its remove flag. 
		table[i].removed = 1; 
	return  (i != -1);
} 
 
template<class Key, class Value, class HashFunc, class EqualKey> 
int HashMap<Key, Value, HashFunc, EqualKey>::findKey(const Key& hashKey) { 
	//Calculate the hash value by calling HashFunc 
	int i = HashFunc::hashCode(hashKey) % size; 
	while ( table[i].removed == 0 ) { 
		//Find the pointer. 
		if ( EqualKey::equals(table[i].key, hashKey) ) 
			return i; 
		//If reach the end of the array, go to the first and continue. 
		if ( i == ( size-1 ) ) 
			i = 0; 
		else 
			i++; 
	} 
	//if not found, return -1 
	return -1; 
} 
 
 
/** 
 * Overload operator[] and return the value of the hashKey 
 */ 
template<class Key, class Value, class HashFunc, class EqualKey> 
Value& HashMap<Key, Value, HashFunc, EqualKey>::operator[](const Key& hashKey) { 
	//Call the find function. 
	return find(hashKey); 
} 
 
 
#endif /* HASHMAP_H_ */ 
