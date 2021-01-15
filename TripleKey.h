

/****************************************************************************/
/*                                                                          */
/* COMMENT ABOUT                                                     */
/*                                                                          */
/****************************************************************************/



#ifndef DS1_WET2_TRIPLEKEY_H
#define DS1_WET2_TRIPLEKEY_H


#include "List.h"
#include "AvlTree.h"


class TripleKey{
private:
    int _class_id;
    int _course_id;
    int _num_of_views;
public:

    TripleKey(int num_of_views, int course_id, int class_id): _num_of_views(num_of_views),
                                                              _course_id(course_id),
                                                              _class_id(class_id) {};
    ~TripleKey() = default;
    TripleKey(const TripleKey& tripleKey) = default;
    TripleKey& operator=(const TripleKey& tripleKey) = delete;

    // GETTERS AND SETTERS
    int getNumOfViews() {return _num_of_views;};
    int getCourseID() {return _course_id;};
    int getClassID() {return _class_id;};

    void setCourseID(int id) {_course_id = id;};
    void setClassID(int id) {_class_id = id;};
    void setNumOfViews(int num_of_views) {_num_of_views = num_of_views;};

    // comparison funcs
    bool operator==(const TripleKey other) const;
    bool operator>(const TripleKey other) const;
    bool operator<(const TripleKey other) const;

};

#endif //DS1_WET2_TRIPLEKEY_H

