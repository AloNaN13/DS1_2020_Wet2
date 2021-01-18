
#ifndef DS1_WET2_COURSESMANAGER_H
#define DS1_WET2_COURSESMANAGER_H

#include "HashTable.h"
#include "List.h"
#include "AvlTree.h"
#include "MyClass.h"
#include "Course.h"
#include "TripleKey.h"


/*
 * enums and not exceptions
 */
typedef enum CMResult_t{
    CM_SUCCESS,
    CM_ALLOCATION_ERROR,
    CM_FAILURE,
    CM_INVALID_INPUT
}CMResult;


class CoursesManager{
private:
    HashTable<Course>* _general_courses_table; // a dynamic array that represents the courses in the system //coursrs? not int?
    AvlTree<TripleKey,TripleKey>* _general_views_tree; // an avl tree that represents the order of viewed classes
    int _num_of_courses; // number of total courses in the system
    int _num_of_classes; // number of total classes in the system
    int _num_of_viewed_classes; // number of total classes in the system with views
public:
    /**
     * constructor: initializing a new hash table for the courses to 2.
     * creates a tree to hold the views using TRIPLEKEY class that holds COURSE ID, CLASS ID, NUMBER OF VIEWS
     * and also initializing basic variable such as number of entities (shown above).
     */
    CoursesManager(): _general_courses_table(new HashTable<Course>(2)),
                      _general_views_tree(new AvlTree<TripleKey,TripleKey>),
                      _num_of_courses(0), _num_of_classes(0), _num_of_viewed_classes(0) {};
    /**
     * destructor: deletes the values of the courses and only then releases the tree and courses table .
     */
    ~CoursesManager()  {this->_general_courses_table->deleteHashValues();
                        delete _general_courses_table;
                        delete _general_views_tree;};
    /**
     * default copy constructor
     * @param courses_manager
     */
    CoursesManager(const CoursesManager& courses_manager) = default;
    /**
     * not using "=" operator in this context, cannot compare course managers.
     * @param courses_manager
     * @return
     */
    CoursesManager& operator=(const CoursesManager& courses_manager) = delete;

    //functions needed to be implemented in task
    CMResult AddCourse (int courseID);
    CMResult RemoveCourse(int courseID);
    CMResult AddClass(int courseID, int* classID);
    CMResult WatchClass(int courseID, int classID, int time);
    CMResult TimeViewed(int courseID, int classID, int *timeViewed);
    CMResult GetIthWatchedClass(int i, int *courseID, int *classID);

};


#endif //DS1_WET2_COURSESMANAGER_H
