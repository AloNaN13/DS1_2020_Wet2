
/* OLD CODE FROM WET1
 *
 *



#include "List.h"

void List::deleteListsNodes(ListNode* node){
    if(node){
        deleteListsNodes(node->getNextNode());
        delete(node);
    }
}

List::~List(){
    if(first_node){
        deleteListsNodes(first_node);
    }
}

// insert a node after the curr_node given as a parameter
// no need to check if the node exists - happens outside of func
ListResult List::insertListNode(ListNode *curr_node,
                                AvlTree<AvlTree<int, int>, int> &views_courses,
                                int time_of_views) {
    ListNode* new_node = new ListNode(time_of_views,views_courses);
    if(curr_node != last_node){
        curr_node->getNextNode()->setPrevNode(new_node);
        new_node->setNextNode(curr_node->getNextNode());
    }
    if(curr_node == last_node){
        last_node = new_node;
    }
    new_node->setPrevNode(curr_node);
    curr_node->setNextNode(new_node);
    return LIST_SUCCESS;
}

// no need to check if the node exists - happens outside of func
ListResult List::removeListNode(ListNode *node) {
    // we never try to erase the first_node if it's not quit? - deal with it?
    if(node != first_node){
        node->getPrevNode()->setNextNode(node->getNextNode());
    }
    else{ // it is the first node
        //ERROR? should happen only in quit
    }
    if(node != last_node){
        node->getNextNode()->setPrevNode(node->getPrevNode());
    }
    else{ // it is the last node
        last_node = node->getPrevNode();
    }
    delete(node);
    return LIST_SUCCESS;
}

