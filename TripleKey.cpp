
#include "TripleKey.h"

bool TripleKey::operator==(const TripleKey other) const{
    return (_num_of_views == other._num_of_views &&
            _course_id == other._course_id &&
            _class_id == other._class_id);
}

bool TripleKey::operator>(const TripleKey other) const{
    if(_num_of_views<other._num_of_views){return (true);}
    else if(_num_of_views>other._num_of_views){return (false);}
    else{
        if(_course_id>other._course_id){return (true);}
        else if(_course_id<other._course_id){return (false);}
        else{
            if(_class_id>other._class_id){return (true);}
            else{
                return false;
            }
        }
    }
    // need return statement for warnings
}

bool TripleKey::operator<(const TripleKey other) const{
    if(_num_of_views>other._num_of_views){return (true);}
    else if(_num_of_views<other._num_of_views){return (false);}
    else{
        if(_course_id<other._course_id){return (true);}
        else if(_course_id>other._course_id){return (false);}
        else{
            if(_class_id<other._class_id){return (true);}
            else{
                return false;
            }
        }
    }
    // need return statement for warnings?
}