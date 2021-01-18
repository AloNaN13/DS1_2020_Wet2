
/****************************************************************************/
/* GENERIC LIST (FOR COURSES OR MYCLASSES)                                  */
/****************************************************************************/

#ifndef DS1_WET2_LIST_H
#define DS1_WET2_LIST_H

typedef enum ListResult_t{
    LIST_SUCCESS,
    LIST_ALLOCATION_ERROR,
    LIST_ALREADY_EXISTS,
    LIST_DOESNT_EXISTS
}ListResult;

/*
 * List implemented as if the node is created outside of the list
 * no use of iterator in List
 */

/**
 * CLASS NODE ELEMENT FOR ENTITY IN THE LIST
 * @tparam Element
 */
template<class Element>
class ListNode{
private:
    const int _key; // the node's key (the hashed courseID or classID)
    Element* _value; // a pointer to the node's struct
    ListNode* _prev_node; // a pointer to previous list's node
    ListNode* _next_node; // a pointer to next list's node
public:
    /**
     * constructor
     * @param key
     * @param value
     */
    ListNode(int key, Element* value): _key(key), _value(value), _prev_node(nullptr), _next_node(nullptr) {};
    /**
     * default destructor, copy constructor and operator "="
     */
    ~ListNode() = default;
    ListNode(const ListNode& list_node) = default;
    ListNode& operator=(const ListNode& list_node) = default;

    /*
     * BASIC GETTERS AND SETTERS
     */
    int getNodeKey() {return this->_key;};
    Element* getNodeValue() {return this->_value;};
    ListNode* getPrevNode() {return this->_prev_node;};
    ListNode* getNextNode() {return this->_next_node;};
    void setPrevNode(ListNode* new_prev_node) {this->_prev_node = new_prev_node;};
    void setNextNode(ListNode* new_next_node) {this->_next_node = new_next_node;};

};


/**
 * LIST CLASS
 * @tparam Element
 */

template<class Element>
class List{
private:
    ListNode<Element>* _first_node{}; //lists first element
    ListNode<Element>* _last_node; //lists last element
public:
    /**
     * constructor,initialize to nullptr all the pointers, and default destructor
     */
    List(): _first_node(nullptr), _last_node(nullptr) {};
    ~List();
    /**
     * deletes all the nodes in the list
     * @param node
     */
    static void deleteListsNodes(ListNode<Element>* node);

    /**
     * default copy constructor and "=" operator
     * @param list
     */
    List(const List& list) = default;
    List& operator=(const List& list) = default;

    /*
     * BASIC GETTERS
     */
    ListNode<Element>* getListsFirstNode() {return this->_first_node;};
    ListNode<Element>* getListsLastNode() {return this->_last_node;};

    /**
     * insert new node of element to the list
     * @param node_to_insert
     * @return result
     */
    ListResult insertListNode(ListNode<Element>* node_to_insert);
    /**
     * remove a given node from the list
     * @param node_to_remove
     * @return result
     */
    ListResult removeListNode(ListNode<Element>* node_to_remove);
};


/*
 * IMPLEMENTATIONS
 */

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

// no need to check if the node exists - happens outside of func
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
