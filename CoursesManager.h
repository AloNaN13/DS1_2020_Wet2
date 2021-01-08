
/* OLD CODE FROM WET1
 *
 *



#ifndef DATA_STRUCTS_1_COURSESMANAGER_H
#define DATA_STRUCTS_1_COURSESMANAGER_H

#include "AvlTree.h"
#include "List.h"
#include "Course.h"
#include "MyClass.h"


// enums and not exceptions
typedef enum CMResult_t{
    CM_SUCCESS,
    CM_ALLOCATION_ERROR,
    CM_FAILURE,
    CM_INVALID_INPUT
}CMResult;


class CoursesManager {
private:
    AvlTree<Course,int> _general_courses_tree; //the general tree of all courses in the system
    List general_views_list; //the list that represents the views of different classes
    int num_of_classes; //number of total classes
public:
    /**
     * ctor+dtor+ccot+assignop
     */
    CoursesManager(): num_of_classes(0) {}; // need to implement it more explicitly?
    ~CoursesManager() = default;
    CoursesManager(const CoursesManager& courses_manager) = default;
    CoursesManager& operator=(const CoursesManager& courses_manager) = default;

    //functions needed to be implemented in task
    /***
    * Adds a course to the system- adds to the general tree of courses
     * connects to the sum "0" tree connected to the node in list of views and classes to the tree under the course
     * @param courseID,numOfClasses - the course ID and number of classes to add
    * @return result
    */
    CMResult AddCourse (int courseID, int numOfClasses);
    /***
    * Removes the course provided in the ID from the system
     * deletes from tree of views, general courses tree, deletes sum if needed and updates total views
     * @param courseID - the course ID to remove
    * @return result
    */
    CMResult RemoveCourse(int courseID);
    /***
    * Adds time watched
    * Adds the time to the provided class and course - updates the views list, deletes sum in needed
     * updates the tree under thr=e privious sum and inserts the node under the new sum
     * (number of iterations on the list is is new time - previous)
    * @param courseID,classID,time
    * @return result
    */
    CMResult WatchClass(int courseID, int classID, int time);
    /***
    * number of total views per class in course provided
    * return the parameter that is stored in class object that holds the time
    * @param courseID,classID - the relevant IDs
    * @param timeViewed - ptr of the return variable that time will be inserted there
    * @return result
    */
    CMResult TimeViewed(int courseID, int classID, int *timeViewed);
    /***
    * return the most viewed classes, if the sum is the same, we return it by the course index
    * iterates over the watch list from the last node numOfClasses times and returns by order
    * @param  numOfClasses - number of classes to be printed
    * @param classes,courses - the arrays to store the relevant classes and courses
    * @return result
    */
    CMResult GetMostViewedClasses(int numOfClasses, int *courses, int *classes);

};


#endif //DATA_STRUCTS_1_COURSESMANAGER_H
