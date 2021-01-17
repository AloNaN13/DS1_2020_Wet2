

/****************************************************************************/
/*                                                                          */
/* MYCLASS - A CLASS CLASS, CONTAINS CLASS ENTITY INFO.                     */
/*                                                                          */
/****************************************************************************/


#ifndef DS1_WET2_MYCLASS_H
#define DS1_WET2_MYCLASS_H

#include "List.h"


class MyClass{
private:
    int _id; // the class id
    int _num_of_views; // number of total class's views

public:
    /**
     * CONSTRATCTOR
     * @param id of class
     */
    explicit MyClass(int id): _id(id), _num_of_views(0) {};
    /**
     * default destractor
     */
    ~MyClass() = default;
    /**
     * copy constractor
     * @param myClass
     */
    MyClass(const MyClass& myClass) = default;
    /**
     * operator "=" is not used in this class context
     * @param myClass
     * @return
     */
    MyClass& operator=(const MyClass& myClass) = delete;

    /*
     * BASIC GETTERS AND SETTERS
     */
    int getID() {return _id;};
    int getNumOfViews() {return _num_of_views;};
    void setID(int id) {_id = id;};
    void setNumOfViews(int num_of_views) {_num_of_views = num_of_views;};
};


#endif //DS1_WET2_MYCLASS_H
