
/****************************************************************************/
/* IMPLEMENTATION OF HASHTABLE USING DYNAMIC ARRAYS OF LISTS                */
/****************************************************************************/

#ifndef DS1_WET2_HASHTABLE_H
#define DS1_WET2_HASHTABLE_H

#include "List.h"
/*
 * ENUM FOR RESULT OPTIONS IN FUNCTIONS
 */
typedef enum HashTableResult_t{
    HT_SUCCESS,
    HT_ALLOCATION_ERROR,
    HT_ALREADY_EXISTS,
    HT_DOESNT_EXISTS
}HTResult;

/*
 * ENUM FOR OPERATION ON THE TABLE
 */
enum{
    EXPAND,
    SHRINK,
    FUNCS
};


template<class Element>
class HashTable{
private:
    List<Element>* _hash_table; // pointer to the array of lists
    int _hash_table_size; //table size
public:
    /**
     * constructor initializing a new array of lists given the size
     * @param size
     */
    explicit HashTable(int size): _hash_table(new List<Element>[size]), _hash_table_size(size) {};
    /**
     * destructor frees the allocations of the hash array
     */
    ~HashTable() {

        delete[] _hash_table;};
    /**
     * DONT USR COPY CONSTRUCTOR AND "=" OPERATOR IN THIS CONTEXT
     * @param hash_table
     */
    HashTable(const HashTable& hash_table) = default;
    HashTable& operator=(const HashTable& hash_table) = delete;

    /*
     * BASIC GETTERS AND SETTERS
     */
    ListNode<Element>* getTableNode(int key);
    int getTableSize() {return _hash_table_size;};
    /**
     * hashes the given key while considering table size changes (in purpose)
     * @param key
     * @param purpose if we need to shink, expand or func,
     * @return hashed key
     */
    int getHashedKey(int key, int purpose);
    /**
     * insert a new node to the table lists
     * @param node_to_insert
     * @return result
     */
    HTResult insertTableNode(ListNode<Element>* node_to_insert);
    /**
     * removes the given key from the table
     * @param key
     * @return result
     */
    HTResult removeTableNode(int key);
    /**
     * adjust the new table considering number of elements that need to be fitted.
     * @param purpose : table options: EXPAND or SHRINK
     * @return result
     */
    HTResult adjustTable(int purpose);
    /**
     * deletes all the hashed data in the table, not the nodes but the data that was hashed
     * @return result
     */
    HTResult deleteHashValues();

};


/*
 * IMPLEMENTATION OF FUNCTIONS
 */

template<class Element>
ListNode<Element>* HashTable<Element>::getTableNode(int key){
    int hashed_key = getHashedKey(key, FUNCS);
    ListNode<Element>* curr_node = _hash_table[hashed_key].getListsFirstNode();
    while(curr_node != nullptr){
        if(curr_node->getNodeKey() == key){
            return curr_node;
        }
        curr_node = curr_node->getNextNode();
    }
    return nullptr;
}

template<class Element>
int HashTable<Element>::getHashedKey(int key, int purpose){
    switch(purpose){
        case EXPAND:
            return (key % (this->_hash_table_size * 2));
        case SHRINK:
            return (key % (this->_hash_table_size / 2));
        case FUNCS:
            return (key % (this->_hash_table_size));
    }
    // would not reach this line
    return  (key % (this->_hash_table_size * 2));
}

template<class Element>
HTResult HashTable<Element>::insertTableNode(ListNode<Element>* node_to_insert){
    // creates node outside of function, in CoursesManager
    int hashed_key = getHashedKey(node_to_insert->getNodeValue()->getID(), FUNCS);
    _hash_table[hashed_key].insertListNode(node_to_insert);
    return HT_SUCCESS;
}

template<class Element>
HTResult HashTable<Element>::removeTableNode(int key){
    int hashed_key = getHashedKey(key, FUNCS);
    ListNode<Element>* curr_node = _hash_table[hashed_key].getListsFirstNode();
    while(curr_node != nullptr){
        if(curr_node->getNodeKey() == key){
            _hash_table[hashed_key].removeListNode(curr_node);
            break;
        }
        curr_node = curr_node->getNextNode();
    }
    return HT_SUCCESS;
}

template<class Element>
HTResult HashTable<Element>::adjustTable(int purpose){
    int new_table_size = 0;
    if(purpose == SHRINK){
        new_table_size = (this->_hash_table_size / 2);
    }
    else if(purpose == EXPAND){
        new_table_size = (this->_hash_table_size * 2);
    }
    List<Element>* new_hash_table = new List<Element>[new_table_size];
    for(int i = 0; i < this->_hash_table_size; i++){
        ListNode<Element>* curr_node = this->_hash_table[i].getListsFirstNode();
        while(curr_node != nullptr){
            ListNode<Element>* node_to_insert = new ListNode<Element>(*curr_node);
            int hashed_key = getHashedKey(node_to_insert->getNodeValue()->getID(), purpose); // MAKE SURE THAT getID is in COURSE and CLASS
            new_hash_table[hashed_key].insertListNode(node_to_insert);
            curr_node = curr_node->getNextNode();
        }
    }
    List<Element>* old_hash_table = this->_hash_table;
    this->_hash_table = new_hash_table;
    this->_hash_table_size = new_table_size;
    delete[] old_hash_table;

    return HT_SUCCESS;
}

template<class Element>
HTResult HashTable<Element>::deleteHashValues(){
    for(int i = 0; i < _hash_table_size; i++){
        ListNode<Element>* curr_node = this->_hash_table[i].getListsFirstNode();
        while(curr_node != nullptr && curr_node->getNodeValue() != nullptr){
            delete (curr_node->getNodeValue());
            curr_node = curr_node->getNextNode();
        }
    }
    return HT_SUCCESS;
}


#endif //DS1_WET2_HASHTABLE_H
