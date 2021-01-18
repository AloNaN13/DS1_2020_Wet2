

/****************************************************************************/
/*                                                                          */
/*CLASS FOR TRIPLEKEY = COURSE ID, CLASS ID, NUMBER OF VIEWS                */
/*THE KEY IS USED FOR SEARCHING IN AVLTREE USING THE 3 PARAMETERS AS KEY    */
/* FOR COMPARING AND SORTING                                                */
/*                                                                          */
/****************************************************************************/



#ifndef DS1_WET2_TRIPLEKEY_H
#define DS1_WET2_TRIPLEKEY_H


#include "List.h"
#include "AvlTree.h"


class TripleKey{
private:
    int _num_of_views;//KEY 1
    int _course_id;//KEY 2
    int _class_id; //KEY 3
public:
    /**
     * constructor
     * @param num_of_views
     * @param course_id
     * @param class_id
     */
    TripleKey(int num_of_views, int course_id, int class_id): _num_of_views(num_of_views),
                                                              _course_id(course_id),
                                                              _class_id(class_id) {};
    /**
     * default destructor and default copy constructor
     */
    ~TripleKey() = default;
    TripleKey(const TripleKey& tripleKey) = default;
    /**
     * we dont use this operator as default, made operator overloading as shown below
     */
    TripleKey& operator=(const TripleKey& tripleKey) = delete;

    /*
     * BASIC GETTERS AND SETTERS
     */
    int getNumOfViews() {return _num_of_views;};
    int getCourseID() {return _course_id;};
    int getClassID() {return _class_id;};
    void setCourseID(int id) {_course_id = id;};
    void setClassID(int id) {_class_id = id;};
    void setNumOfViews(int num_of_views) {_num_of_views = num_of_views;};

    /*
     * OPERATOR OVERLOADING FOR COMPARING TRIPLE KEY, IMPLEMENTED IN CPP FILE
     */
    bool operator==(const TripleKey other) const;
    bool operator>(const TripleKey other) const;
    bool operator<(const TripleKey other) const;

};

#endif //DS1_WET2_TRIPLEKEY_H

