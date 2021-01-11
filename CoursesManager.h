
#ifndef DS1_WET2_COURSESMANAGER_H
#define DS1_WET2_COURSESMANAGER_H

#include "HashTable.h"
#include "AvlTree.h"
#include "Course.h"
#include "MyClass.h"


// enums and not exceptions
typedef enum CMResult_t{
    CM_SUCCESS,
    CM_ALLOCATION_ERROR,
    CM_FAILURE,
    CM_INVALID_INPUT
}CMResult;


class TripleKey{
private:
    int _num_of_views;
    int _course_id;
    int _class_id;
public:
    TripleKey(int num_of_views, int course_id, int class_id):
                                                _num_of_views(num_of_views),
                                                _course_id(course_id),
                                                _class_id(class_id) {};
    ~TripleKey() = default;
    TripleKey(const TripleKey& tri_key) = default;
    TripleKey& operator=(const TripleKey& tri_key) = delete;

    // getters
    int getNumOfViews() { return _num_of_views;};
    int getCourseID() { return _course_id;};
    int getClassID() {return _class_id;};

    // comparison funcs
    bool operator==(const TripleKey other);
    bool operator<(const TripleKey other);
    bool operator>(const TripleKey other);

};


class CoursesManager{
private:
    HashTable<Course> _general_courses_table; // a dynamic array that represents the courses in the system
    AvlTree<TripleKey,int> _general_views_tree; // an avl tree that represents the order of viewed classes
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

};


#endif //DS1_WET2_COURSESMANAGER_H
