

/****************************************************************************/
/*                                                                          */
/* COMMENT ABOUT                                                     */
/*                                                                          */
/****************************************************************************/




#include "List.h"
#include "AvlTree.h"


class TripleKey{
private:
    int _class_id;
    int _course_id;
    int _num_of_views;
    int _rank;
public:

    explicit TripleKey(int class_id,int course_id,int num_of_views,int rank ): _class_id(class_id), _course_id(course_id), _num_of_views(num_of_views),_rank(rank) {};
    explicit TripleKey(int class_id,int course_id,int num_of_views): _class_id(class_id), _course_id(course_id), _num_of_views(num_of_views),_rank(0) {};
    explicit TripleKey(int class_id, int course_id ): _class_id(class_id), _course_id(course_id), _num_of_views(0), _rank(0){};
    ~TripleKey() = default;
    TripleKey(const TripleKey& tripleKey) = default;
    TripleKey& operator=(const TripleKey& tripleKey) = delete;

    // GETTERS AND SETTERS
    int getCourseID() {return _course_id;};
    int getClassID() {return _class_id;};
    int getRank() {return _rank;};
    int getNumOfViews() {return _num_of_views;};

    void setCourseID(int id) {_course_id = id;};
    void setClassID(int id) {_class_id = id;};
    void setRank(int rank) {_rank = rank;};
    void setNumOfViews(int num_of_views) {_num_of_views = num_of_views;};

    // comparison funcs
    bool operator==(const TripleKey other);
    bool operator<(const TripleKey other);
    bool operator>(const TripleKey other);

};



