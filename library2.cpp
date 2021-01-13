#include "library2.h"
#include "CoursesManager.h"
void *Init(){
    CoursesManager* DS = new CoursesManager();
    return (void*)DS;
}

/* OLD CODE FROM WET1
 *
 *



#include "library.h"
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

StatusType AddCourse (void *DS, int courseID, int numOfClasses){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->AddCourse(courseID, numOfClasses));
}

StatusType RemoveCourse(void *DS, int courseID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->RemoveCourse(courseID));
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

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return getStatusTypeFromCMResult(((CoursesManager*)DS)->GetMostViewedClasses(numOfClasses, courses, classes));
}

void Quit(void** DS){
    delete((CoursesManager*)(*DS));
    *DS = nullptr;
}
