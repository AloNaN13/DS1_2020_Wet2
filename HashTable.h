
/****************************************************************************/
/* NOTE ABOUT THE HASHTABLE                                                 */
/****************************************************************************/

#ifndef DS1_WET2_HASHTABLE_H
#define DS1_WET2_HASHTABLE_H

#include "List.h"

typedef enum HashTableResult_t{
    HT_SUCCESS,
    HT_ALLOCATION_ERROR,
    HT_ALREADY_EXISTS,
    HT_DOESNT_EXISTS
}HTResult;

enum{
    EXPAND,
    SHRINK,
    FUNCS
};


// Add comments


template<class Element>
class HashTable{
private:
    List<Element>* _hash_table;
    int _hash_table_size;
public:
    //ctor
    explicit HashTable(int size): _hash_table(new List<Element>[size]), _hash_table_size(size) {

    };
    //dtor
    ~HashTable() {
        delete[] _hash_table;};
    //delete cctor + assignctor
    HashTable(const HashTable& hash_table) = default;
    HashTable& operator=(const HashTable& hash_table) = delete;

    //getters+setters
    ListNode<Element>* getTableNode(int key);
    int getTableSize() {return _hash_table_size;};
    //other funcs
    int getHashedKey(int key, int purpose);
    HTResult insertTableNode(ListNode<Element>* node_to_insert);
    HTResult removeTableNode(int key);
    //HTResult shrinkTable();
    //HTResult expandTable();
    HTResult adjustTable(int purpose);
    HTResult deleteHashValues();

};


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

/*
template<class Element>
HTResult HashTable<Element>::shrinkTable(){
    return adjustTable(SHRINK);
}

template<class Element>
HTResult HashTable<Element>::expandTable(){
    return adjustTable(EXPAND);
}
*/

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
        while(curr_node != nullptr  ){
            delete (curr_node->getNodeValue());
            curr_node = curr_node->getNextNode();
        }
    }
    return HT_SUCCESS;
}


#endif //DS1_WET2_HASHTABLE_H
