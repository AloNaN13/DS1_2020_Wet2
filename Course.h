
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
    HashTable<MyClass>* _classes_table; // table for the course's classes
    int _num_of_classes; // the total number of the course's classes
    int _total_views;
    bool _is_classes;
public:
    explicit Course(int id): _id(id), _classes_table(new HashTable<MyClass>(2)), _num_of_classes(0),_is_classes(0),_total_views(0) {};
    // need another ctor?
    ~Course() = default;
    Course(const Course &course) = default;
    Course& operator=(const Course &course) = delete;
    int getTotalViews(){return _total_views;}
    bool getIsClasses(){return _is_classes;}
    void setTotalViews(int n);
    void incNumOfClasses(){_num_of_classes++;};
    void setIsClasses(bool is_class);
    HashTable<MyClass>* getClassesTable() {return _classes_table;};
    void setHashTable(HashTable<MyClass>* table){_classes_table = table;};
    int getNumOfClasses() {return _num_of_classes;};

};

#endif //DS1_WET2_COURSE_H
