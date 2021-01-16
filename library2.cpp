
#include "library2.h"
#include "CoursesManager.h"

// helper function
StatusType getStatusTypeFromCMResult(CMResult res){
    switch(res){
        case CM_INVALID_INPUT:
            return INVALID_INPUT;
        case CM_FAILURE:
            return FAILURE;
        case CM_SUCCESS:
            return SUCCESS;
        case CM_ALLOCATION_ERROR:
            return ALLOCATION_ERROR;
    }
    return SUCCESS; // only for compilation - would not reach this line
}


void *Init(){
    CoursesManager* DS = new CoursesManager();
    return (void*)DS;
}

StatusType AddCourse (void *DS, int courseID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->AddCourse(courseID));
}

StatusType RemoveCourse(void *DS, int courseID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->RemoveCourse(courseID));
}

StatusType AddClass(void *DS, int courseID, int* classID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->AddClass(courseID, classID));
}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->WatchClass(courseID, classID, time));
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->TimeViewed(courseID, classID, timeViewed));
}

StatusType GetIthWatchedClass(void *DS, int i, int *courseID, int *classID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->GetIthWatchedClass(i, courseID, classID));
}

void Quit(void** DS){
    delete((CoursesManager*)(*DS));
    *DS = nullptr;
}
