

// template instead of void* for course or myclass



/****************************************************************************/
/* NOTE ABOUT THE LIST, NOT GENERIC                                    */
/****************************************************************************/

#ifndef DS1_WET2_LIST_H
#define DS1_WET2_LIST_H

typedef enum ListResult_t{
    LIST_SUCCESS,
    LIST_ALLOCATION_ERROR,
    LIST_ALREADY_EXISTS,
    LIST_DOESNT_EXISTS
}ListResult;


// List implemented as if the node is created outside of the list
// List is not generic, no use of iterator in List

template<class Element>
class ListNode{
private:
    const int _key; // the node's key (the hashed courseID or classID)
    Element* _value; // a pointer to the node's struct
    ListNode* _prev_node; // a pointer to previous list's node
    ListNode* _next_node; // a pointer to next list's node
public:

    ListNode(int key, Element* value): _key(key), _value(value), _prev_node(nullptr), _next_node(nullptr) {};
    //another ctor?
    ~ListNode() = default;
    ListNode(const ListNode& list_node) = default;
    ListNode& operator=(const ListNode& list_node) = default;

    // setters+getters
    int getNodeKey() {return this->_key;};
    Element* getNodeValue() {return this->_value;};
    ListNode* getPrevNode() {return this->_prev_node;};
    ListNode* getNextNode() {return this->_next_node;};
    void setPrevNode(ListNode* new_prev_node) {this->_prev_node = new_prev_node;};
    void setNextNode(ListNode* new_next_node) {this->_next_node = new_next_node;};

};


// any need to keep list length?

template<class Element>
class List{
private:
    ListNode<Element>* _first_node{};
    ListNode<Element>* _last_node;
public:

    List(): _first_node(nullptr), _last_node(nullptr) {};
    ~List();
    static void deleteListsNodes(ListNode<Element>* node);

    //cctor + assign
    List(const List& list) = default;
    List& operator=(const List& list) = default;

    // getters
    ListNode<Element>* getListsFirstNode() {return this->_first_node;};
    ListNode<Element>* getListsLastNode() {return this->_last_node;};
    // no need for setters?

    // other functions
    ListResult insertListNode(ListNode<Element>* node_to_insert);
    ListResult removeListNode(ListNode<Element>* node_to_remove);
};




template <class Element>
void List<Element>::deleteListsNodes(ListNode<Element>* node){
    if(node){
        deleteListsNodes(node->getNextNode());
        delete(node);
    }
}

template <class Element>
List<Element>::~List(){
    if(_first_node){
        deleteListsNodes(_first_node);
    }
}

// insert the given node as the first node
// no need to check if the node exists - happens outside of func?
template <class Element>
ListResult List<Element>::insertListNode(ListNode<Element>* node_to_insert) {

    if(_first_node == nullptr){
        _first_node = node_to_insert;
        _first_node->setPrevNode(nullptr);
        _first_node->setNextNode(nullptr);
        _last_node = node_to_insert;
    }
    else{
        node_to_insert->setNextNode(_first_node);
        node_to_insert->setPrevNode(nullptr);
        _first_node->setPrevNode(node_to_insert);
        _first_node = node_to_insert;
    }
    return LIST_SUCCESS;
}


// no need to check if the node exists - happens outside of func?
template <class Element>
ListResult List<Element>::removeListNode(ListNode<Element>* node_to_remove) {
    if(node_to_remove != _first_node){
        node_to_remove->getPrevNode()->setNextNode(node_to_remove->getNextNode());
    }
    else{ // it is the first node
        _first_node = node_to_remove->getNextNode();
    }
    if(node_to_remove != _last_node){
        node_to_remove->getNextNode()->setPrevNode(node_to_remove->getPrevNode());
    }
    else{ // it is the last node
        _last_node = node_to_remove->getPrevNode();
    }
    delete(node_to_remove);
    return LIST_SUCCESS;
}



#endif //DS1_WET2_LIST_H
