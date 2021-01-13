
#ifndef DS1_WET2_COURSESMANAGER_H
#define DS1_WET2_COURSESMANAGER_H

#include "HashTable.h"
#include "List.h"
#include "AvlTree.h"
#include "MyClass.h"
#include "Course.h"
#include "TripleKey.h"

//made global because i need in my class and i dont have a pointer to course manager, if you have better idea

HashTable<Course> _general_courses_table; // a dynamic array that represents the courses in the system //coursrs? not int?
AvlTree<TripleKey,TripleKey> _general_views_tree; // an avl tree that represents the order of viewed classes

// enums and not exceptions
typedef enum CMResult_t{
    CM_SUCCESS,
    CM_ALLOCATION_ERROR,
    CM_FAILURE,
    CM_INVALID_INPUT
}CMResult;




class CoursesManager{
private:
//  HashTable<Course> _general_courses_table; // a dynamic array that represents the courses in the system //coursrs? not int?
//    AvlTree<TripleKey,int> _general_views_tree; // an avl tree that represents the order of viewed classes
    int _num_of_classes; // number of total classes in the system
    int _num_of_viewed_classes; // number of total classes in the system with views
public:
    CoursesManager(): _general_courses_table(*(new HashTable<Course>(2))),
                      _general_views_tree(*(new AvlTree<TripleKey,int>)),
                      _num_of_classes(0), _num_of_viewed_classes(0) {}; // need to implement it more explicitly?
    ~CoursesManager() = default;
    CoursesManager(const CoursesManager& courses_manager) = default;
    CoursesManager& operator=(const CoursesManager& courses_manager) = delete;

    //functions needed to be implemented in task
    CMResult AddCourse (int courseID);
    CMResult RemoveCourse(int courseID);
    CMResult AddClass(int courseID, int* classID);
    CMResult WatchClass(int courseID, int classID, int time);
    CMResult TimeViewed(int courseID, int classID, int *timeViewed);
    CMResult GetIthWatchedClasses(int i, int *coursID, int *classID);
    void Quit();

};


#endif //DS1_WET2_COURSESMANAGER_H
