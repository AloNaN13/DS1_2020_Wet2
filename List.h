

// understand how to deal with void* for course or myclass



/****************************************************************************/
/* NOTE ABOUT THE LIST, NOT GENERIC                                    */
/****************************************************************************/

#ifndef DS1_WET2_LIST_H
#define DS1_WET2_LIST_H

//#include "AvlTree.h"

typedef enum ListResult_t{
    LIST_SUCCESS,
    LIST_ALLOCATION_ERROR,
    LIST_ALREADY_EXISTS,
    LIST_DOESNT_EXISTS
}ListResult;


// List implemented as if the node is created outside of the list
// List is not generic, no use of iterator in List

class ListNode{
private:
    const int _key; // the node's key (the hashed courseID or classID)
    void* _value; // a pointer to the node's struct
    ListNode* _prev_node; // a pointer to previous list's node
    ListNode* _next_node; // a pointer to next list's node
public:

    ListNode(int key, void* value): _key(key), _value(value), _prev_node(nullptr), _next_node(nullptr) {};
    //another ctor?
    ~ListNode() = default;
    ListNode(const ListNode& list_node) = default;
    ListNode& operator=(const ListNode& list_node) = default;

    // setters+getters
    int getNodeKey() {return this->_key;};
    void* getNodeValue() {return this->_value;};
    ListNode* getPrevNode() {return this->_prev_node;};
    ListNode* getNextNode() {return this->_next_node;};
    void setPrevNode(ListNode* new_prev_node) {this->_prev_node = new_prev_node;};
    void setNextNode(ListNode* new_next_node) {this->_next_node = new_next_node;};

};


// any need to keep list length?

class List{
private:
    ListNode* _first_node{};
    ListNode* _last_node;
public:

    List(): _first_node(nullptr), _last_node(nullptr) {};
    ~List();
    static void deleteListsNodes(ListNode* node);

    //cctor + assign
    List(const List& list) = default;
    List& operator=(const List& list) = default;

    // getters
    ListNode* getListsFirstNode() {return this->_first_node;};
    ListNode* getListsLastNode() {return this->_last_node;};
    // no need for setters?

    // other functions
    ListResult insertListNode(ListNode* node_to_insert);
    ListResult removeListNode(ListNode* node_to_remove);
};


#endif //DS1_WET2_LIST_H
