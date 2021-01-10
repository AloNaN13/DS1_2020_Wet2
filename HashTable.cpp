
#include "HashTable.h"


ListNode* HashTable::getTableNode(int key){
    int hashed_key = getHashedKey(key, FUNCS);
    ListNode* curr_node = _hash_table[hashed_key].getListsFirstNode();
    while(curr_node != nullptr){
        if(curr_node->getNodeKey() == key){ // TO IMPLEMENT getNodeKey in List
            return curr_node;
        }
        curr_node = curr_node->getNextNode()
    }
    return nullptr;
}

int HashTable::getHashedKey(int key, int purpose){
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

HTResult HashTable::insertTableNode(ListNode* node_to_insert){
    // creates node outside of function, in CoursesManager
    int hashed_key = getHashedKey(node_to_insert->getNodeValue()->getID(), FUNCS) // IMPLEMENT getPtrFromNode
    _hash_table[hashed_key].insertListNode(node_to_insert);
    return HT_SUCCESS;
}

HTResult HashTable::removeTableNode(int key){
    int hashed_key = getHashedKey(key, FUNCS);
    ListNode* curr_node = _hash_table[hashed_key].getListsFirstNode();
    while(curr_node != nullptr){
        if(curr_node->getNodeKey() == key){
            _hash_table[hashed_key].removeListNode(curr_node);
            break;
        }
        curr_node = curr_node->getNextNode();
    }
    return HT_SUCCESS;
}

HTResult HashTable::shrinkTable(){
    return adjustTable(SHRINK);
}

HTResult HashTable::expandTable(){
    return adjustTable(EXPAND);
}

HTResult HashTable::adjustTable(int purpose){
    int new_table_size = 0;
    if(purpose == SHRINK){
        new_table_size = (this->_hash_table_size / 2);
    }
    else if(purpose == EXPAND){
        new_table_size = (this->_hash_table_size * 2);
    }
    List* new_hash_table = new List[new_table_size];
    for(int i = 0; i < this->_hash_table_size; i++){
        ListNode* curr_node = this->_hash_table[i].getListsFirstNode();
        while(curr_node != nullptr){
            ListNode* node_to_insert = new ListNode(*curr_node);
            int hashed_key = getHashedKey(node_to_insert->getNodeValue()->getID(), purpose); // MAKE SURE THAT getID is in COURSE and CLASS
            new_hash_table[hashed_key].insertListNode(node_to_insert);
            curr_node = curr_node->getNextNode()
        }
    }
    List* old_hash_table = this->_hash_table;
    this->_hash_table = new_hash_table;
    this->_hash_table_size = new_table_size;
    delete[] old_hash_table;
    return HT_SUCCESS;
}

HTResult HashTable::deleteHashLists(){
    //TODO
}
