
/* OLD CODE FROM WET1
 *
 *



/****************************************************************************/
/*                                                                          */
/* STRUCT FOR THE CLASS OBJECT                                              */
/* @var _views, _views_of_class : the class index,   */
/* number of views for the class, ptr to the node     */
/* in general views list of sum equal to views                              */
/*using getters and setters                                                 */
/****************************************************************************/
#ifndef DATA_SCTRUCTS_1_MyClass_H
#define DATA_SCTRUCTS_1_MyClass_H

#include "List.h"

class MyClass{
private:
    int _views; //number of total views
    ListNode* _views_of_class; //link to the sum node in the list (not specific node to head of sum connected to num of views
public:
    /**
     * constructor
     * @param index the class index
     * @param id_of_course the related course id
     */
    MyClass(int index, int id_of_course);
    /**
     * empty new class construtor
     */
    MyClass() = default;
    /**
     * copy constructor
     * @param myClass
     */
    MyClass(const MyClass& myClass);
    /**
     * defaukt destructor
     */
    ~MyClass() = default;
    /**
     * assignment operator
     * @param myClass
     * @return
     */
    MyClass& operator=(const MyClass& myClass) = default;

    //GETTERS AND SETTERS

    /**
     *
     * @return the node of the sum of views per class
     */
    ListNode* getListOfViews();
    /**
     *
     * @return the number of views
     */
    int getViews();
    /**
     * set the pointer to a new sum of views
     * @param new_sum_of_views
     */
    void setListOfViews(ListNode* new_sum_of_views);
    /**
     * change number of views per class
     * @param views
     */
    void setViews(int views);
};

#endif //DATA_SCTRUCTS_1_MyClass_H
