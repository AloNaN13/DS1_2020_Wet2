
#include "List.h"

void List::deleteListsNodes(ListNode* node){
    if(node){
        deleteListsNodes(node->getNextNode());
        delete(node);
    }
}

List::~List(){
    if(_first_node){
        deleteListsNodes(_first_node);
    }
}

// insert the given node as the first node
// no need to check if the node exists - happens outside of func?
ListResult List::insertListNode(ListNode* node_to_insert) {

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
ListResult List::removeListNode(ListNode* node_to_remove) {
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

