

#include "CoursesManager.h"

bool TripleKey::operator==(const TripleKey other){
    return (_num_of_views == other._num_of_views &&
            _course_id == other._course_id &&
            _class_id == other._class_id);
}

bool TripleKey::operator<(const TripleKey other){
    //TODO
}

bool TripleKey::operator>(const TripleKey other){
    //TODO
}


CMResult CoursesManager::AddCourse(int courseID){
    try{
        if(courseID <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table.getTableNode(courseID) != nullptr){
            return CM_FAILURE;
        }

        //TODO

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::RemoveCourse(int courseID) {
    try{
        if (courseID <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table.getTableNode(courseID) != nullptr){
            return CM_FAILURE;
        }

        //TODO

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

























CMResult CoursesManager::AddClass(int courseID, int* classID) {
    try{
        if (courseID <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table.getTableNode(courseID) != nullptr){
            return CM_FAILURE;
        }

        //TODO

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::WatchClass(int courseID, int classID, int time){
    try{
        if(courseID <= 0 || classID < 0 || time <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_tree.getElementptr(courseID) == nullptr){
            return CM_FAILURE;
        }
        if(classID + 1 > _general_courses_tree.getElementptr(courseID)->getNumOfClasses()){
            return CM_INVALID_INPUT;
        }

        //TODO

        // go to course
        // go its to class arr
        // go the curr views node in list
        // change the time_of_views in the class_arr
        // find the new views node in deltaT
        // create it if it doesnt exist
        // add the class to the new views_node's avltree
        // remove the class from the old views_node's avltree
        // if the only one in the second - remove node from first tree
        // if the only node in first tree - remove node from list
        // not if its the node 0
        // point the class in the class_arr to the new_node

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed){
    try{
        if(courseID <= 0 || classID < 0 ){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table.getTableNode(courseID) != nullptr){
            return CM_FAILURE;
        }
        if(classID + 1 > _general_courses_table.getTableNode(courseID)->getNodeValue()->getNumOfClasses()){
            return CM_INVALID_INPUT;
        }
        *timeViewed = _general_courses_table.getTableNode(courseID)->getNodeValue()->getClasses()
        *timeViewed = _general_courses_table.getTableNode(courseID)->getNodeValue()->getClasses().getTableNode(classID)->getNodeValue()->getViews();
        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::GetIthWatchedClasses(int i, int *coursID, int *classID){
    try{
        if(i <= 0){
            return CM_INVALID_INPUT;
        }
        if(_num_of_viewed_classes < i){
            return CM_FAILURE;
        }

        //TODO

        // get the last node of list
        // run with a loop until reaches numOfClasses
            // get first course
                // get first song
                // up the counter by 1 and get the next song
                // if last song, go to next course
            // if last course, go to prev node in list

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}
