
/****************************************************************************/
/* NOTE ABOUT THE HASHTABLE                                                 */
/****************************************************************************/

#ifndef DS1_WET2_HASHTABLE_H
#define DS1_WET2_HASHTABLE_H

#include "List.h"

typedef enum HashTable_t{
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


class HashTable{
private:
    List* _hash_table;
    int _hash_table_size;
public:
    //ctor
    explicit HashTable(int size): _hash_table(new List[size]), _hash_table_size(size) {};
    //dtor
    ~HashTable() {delete[] _hash_table;};
    //delete cctor + assignctor
    HashTable(const HashTable& hash_table) = delete;
    HashTable& operator=(const HashTable& hash_table) = delete;

    //getters+setters
    ListNode* getTableNode(int key);
    int getTableSize() {return _hash_table_size;};
    //other funcs
    int getHashedKey(int key, int purpose);
    HTResult insertTableNode(ListNode* node_to_insert);
    HTResult removeTableNode(int key);
    HTResult shrinkTable();
    HTResult expandTable();
    HTResult adjustTable(int purpose);
    HTResult deleteHashLists();

};


#endif //DS1_WET2_HASHTABLE_H
