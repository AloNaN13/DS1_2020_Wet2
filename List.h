
/* OLD CODE FROM WET1
 *
 *



/****************************************************************************/
/*  !!NOT A GENERIC LIST!!                                                  */
/* each node represents sum of views                                        */
/* he list holds an AVL tree of courses IDs and AvlTrees of classes,        */
/*   the classes must have the nodes "sum" of views per course              */
/*  a two sided list!                                                       */
/****************************************************************************/
#ifndef DS1_WET1_LIST_H
#define DS1_WET1_LIST_H

#include "AvlTree.h"
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
    const int time_of_views; //the relevant number of views that the node represents
    AvlTree<AvlTree<int,int>,int>& views_courses; // tree of courses containing classes of the _time_of_views sum
    ListNode* prev_node; //pointer to previous node
    ListNode* next_node; //pointer to next node
public:
    /***
    * List node usual functions of ctor , dtor , cctor, managing nodes
    */

    /**
     * constructor for node without a tree
     * @param time_of_views
     */
    explicit ListNode(int time_of_views): time_of_views(time_of_views),
                                views_courses(*(new AvlTree<AvlTree<int,int>,int>())),
                                prev_node(nullptr),
                                next_node(nullptr) {};
    /**
     * constructor of node with tree to be assigned under
     * @param time_of_views
     * @param views_courses
     */
    ListNode(int time_of_views, AvlTree<AvlTree<int,int>,int>& views_courses): time_of_views(time_of_views),
                                views_courses(views_courses),
                                prev_node(nullptr),
                                next_node(nullptr) {};
    /**
     * destructor
     */
    ~ListNode() {delete(&views_courses);};

    // setters+getters

    /**
     *
     * @return previous node to the current one
     */
    ListNode* getPrevNode() {return this->prev_node;};
    /**
     *
     * @return next node to current one
     */
    ListNode* getNextNode() {return this->next_node;};
    /**
     * set new pointer to previous node
     * @param new_prev_node
     */
    void setPrevNode(ListNode* new_prev_node) {this->prev_node = new_prev_node;};
    /**
     * srt new pointer to next node
     * @param new_next_node
     */
    void setNextNode(ListNode* new_next_node) {this->next_node = new_next_node;};

    // other functions
     /***
    * getViewsCoursesTree() - special function for getting the courses tree under each node
    * getTimeOfViews() - returns the "sum" of views of the node
    */
    AvlTree<AvlTree<int,int>,int>& getViewsCoursesTree() {return this->views_courses;};
    int getTimeOfViews() {return this->time_of_views;};
};


class List{
private:
    ListNode* first_node;
    ListNode* last_node;
public:
    /***
    * List usual functions of ctor , dtor , cctor, managing nodes
    */
    List(): first_node(new ListNode(0)),
            last_node(nullptr) {
            last_node = first_node;
    }
    ~List();
    static void deleteListsNodes(ListNode* node);

    //cctor + assign
    List(const List& list) = default;
    List& operator=(const List& list) = default;

    // getters
    ListNode* getListsFirstNode() {return this->first_node;};
    ListNode* getListsLastNode() {return this->last_node;};
    // no need for setters

    // other functions
    ListResult insertListNode(ListNode* curr_node, AvlTree<AvlTree<int,int>,int>& views_courses, int time_of_views);
    ListResult removeListNode(ListNode* node);
};


#endif //DS1_WET1_LIST_H
