
/* OLD CODE FROM WET1
 *
 *



/****************************************************************************/
/*                                                                          */
/* STRUCT FOR THE COURSE OBJECT                                             */
/* @var _id, _classes_array, _num_of_classes :                  */
/* the course ID, classes array, number of classes      */
/* using getters and setters                                                */
/*                                                                          */
/****************************************************************************/

#ifndef DATA_STRUCTS_1_COURSE_H
#define DATA_STRUCTS_1_COURSE_H

#include "MyClass.h"



class Course{
private:
    int _id; //class id
    MyClass* _classes_array; //pointer to classes array
    int _num_of_classes; //number of total classes
public:
    /**
     * constructor of new course
     * @param id id of course
     * @param num_of_classes total number of classes per course
     */
    Course(const int id, int num_of_classes);
    /**
     * destructor, not default to avoid mem leaks
     */
    ~Course() {delete [] _classes_array;};
    /**
     * copy constructor
     * @param course
     */
    Course(const Course &course);
    /**
     * assignment operator
     * @param course
     * @return node with new value
     */
    Course& operator=(const Course &course) = default;
    /**
     *
     * @return pointer to the classes array
     */
    MyClass* getClasses();
    /**
     *
     * @return number of classes
     */
    int getNumOfClasses();
};

#endif //DATA_STRUCTS_1_COURSE_H
