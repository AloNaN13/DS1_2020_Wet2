
/****************************************************************************/
/*                                                                          */
/* COMMENT ABOUT COURSE                                                     */
/*                                                                          */
/****************************************************************************/

#ifndef DS1_WET2_COURSE_H
#define DS1_WET2_COURSE_H

#include "MyClass.h"
#include "HashTable.h"


class Course{
private:
    int _id; // the course id
    HashTable<MyClass> _classes_table; // table for the course's classes
    int _num_of_classes; // the total number of the course's classes
public:
    explicit Course(int id): _id(id), _classes_table(*(new HashTable<MyClass>(2))), _num_of_classes(0) {};
    // need another ctor?
    ~Course() = default;
    Course(const Course &course) = default;
    Course& operator=(const Course &course) = delete;

    HashTable<MyClass>& getClassesTable() {return _classes_table;};
    int getNumOfClasses() {return _num_of_classes;};

};

#endif //DS1_WET2_COURSE_H
