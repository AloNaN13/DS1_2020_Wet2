//
// Created by svet on 1/13/2021.
//
#include "TripleKey.h"
bool TripleKey::operator==(const TripleKey other){
    return (_num_of_views == other._num_of_views &&
            _course_id == other._course_id &&
            _class_id == other._class_id);
}

bool TripleKey::operator>(const TripleKey other){
    if(this->_num_of_views>other._num_of_views){return (true);}
    else if(this->_num_of_views<other._num_of_views){return (false);}
    else{
        if(this->_course_id>other._course_id){return (true);}
        else if(this->_course_id<other._course_id){return (false);}
        else{
            if(this->_class_id>other._class_id){return (true);}
            else{
                return false;
            }
        }
    }

}

bool TripleKey::operator<(const TripleKey other){
    if(this->_num_of_views<other._num_of_views){return (true);}
    else if(this->_num_of_views>other._num_of_views){return (false);}
    else{
        if(this->_course_id<other._course_id){return (true);}
        else if(this->_course_id>other._course_id){return (false);}
        else{
            if(this->_class_id<other._class_id){return (true);}
            else{
                return false;
            }
        }
    }

}