

/****************************************************************************/
/*                                                                          */
/* COMMENT ABOUT MYCLASS                                                    */
/*                                                                          */
/****************************************************************************/


#ifndef DS1_WET2_MYCLASS_H
#define DS1_WET2_MYCLASS_H

#include "List.h"
#include "AvlTree.h"
#include "TripleKey.h"
#include "HashTable.h"
#include "Course.h"
#include "CoursesManager.h"


class MyClass{
private:
    int _id; // the class id
    int _num_of_views; // number of total class's views
    int _course_id;//related course id
    AvlTree<int,TripleKey>& _views;
    HashTable<MyClass>& _classes_table; // table for the course's classes
    // a pointer to a tree_node - really necessary? if so, how to do it? tree_node is internal...
public:
    explicit MyClass(int class_id, int course_id) : _id(class_id), _course_id(course_id), _num_of_views(0), _views(
            nullptr),_classes_table(*_general_courses_table.getTableNode(course_id)->getNodeValue()->getClassesTable()){};
    ~MyClass() = default;
    MyClass(const MyClass& myClass) = default;
    MyClass& operator=(const MyClass& myClass) = delete;

    // GETTERS AND SETTERS
    int getClassID() {return _id;};
    int getCourseID() {return _course_id;};
    int getNumOfViews() {return _num_of_views;};
    HashTable<MyClass>& getClassTable() {return _classes_table;};
    AvlTree<int,TripleKey>& getTreeOfViews(){return _views;}
    void setClassID(int id) {_id = id;};
    void setCourseID(int course_id) {_course_id = course_id;};
    void setViewsTree(AvlTree<int,TripleKey>& tree) {_views = tree;};
    void setHashClassesTable(HashTable<MyClass>& table) {_classes_table = table;};
    void setNumOfViews(int num_of_views) {_num_of_views = num_of_views;};
    // get and set for a pointer to a tree_node?
};


#endif //DS1_WET2_MYCLASS_H
