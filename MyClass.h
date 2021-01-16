

/****************************************************************************/
/*                                                                          */
/* COMMENT ABOUT MYCLASS                                                    */
/*                                                                          */
/****************************************************************************/


#ifndef DS1_WET2_MYCLASS_H
#define DS1_WET2_MYCLASS_H

#include "List.h"
//#include "AvlTree.h"
//#include "TripleKey.h"


class MyClass{
private:
    int _id; // the class id
    int _num_of_views; // number of total class's views
    //int _course_id;//related course id
    //AvlTree<int,TripleKey>& _views;
    // a pointer to a tree_node - really necessary? if so, how to do it? tree_node is internal...
public:
    explicit MyClass(int id): _id(id), _num_of_views(0) {};
    ~MyClass() = default;
    MyClass(const MyClass& myClass) = default;
    MyClass& operator=(const MyClass& myClass) = delete;

    // GETTERS AND SETTERS
    int getID() {return _id;};
    int getNumOfViews() {return _num_of_views;};
    //AvlTree<int,TripleKey>& getTreeOfViews(){return _views;}
    void setID(int id) {_id = id;};
    //void setViewsTree(AvlTree<int,TripleKey>& tree) {_views = tree;};
    void setNumOfViews(int num_of_views) {_num_of_views = num_of_views;};
    // get and set for a pointer to a tree_node?
};


#endif //DS1_WET2_MYCLASS_H
