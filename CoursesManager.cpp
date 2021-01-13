

#include "CoursesManager.h"




CMResult CoursesManager::AddCourse(int courseID){
    try{
        if(courseID <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table.getTableNode(courseID) != nullptr){
            return CM_FAILURE;
        }
        Course* course = new Course(courseID);
        ListNode<Course> *course_node = new ListNode<Course>(courseID,course);
        _general_courses_table.insertTableNode(course_node); //where link to course from table?
    //    free(course_node);




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
        Course *course_element = _general_courses_table.getTableNode(courseID)->getNodeValue();
        HashTable<MyClass> *relevant_classes = course_element->getClassesTable();
        int relevant_num_of_views;
        //NEED TO SOMEWARE COMPARISON MATHOD ROTATING BETWEEN KEYS
        for(int i=0;i<course_element->getNumOfClasses();i++){
            relevant_num_of_views = relevant_classes->getTableNode(i)->getNodeValue()->getNumOfViews();
            TripleKey* to_delete = new TripleKey(i,courseID,relevant_num_of_views);
            _general_views_tree.remove(*to_delete);
            free(to_delete);
        }
        relevant_classes->deleteHashLists();
        _general_courses_table.removeTableNode(courseID);

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
        MyClass* clas = new MyClass(*classID,courseID);
        ListNode<MyClass> *clas_node = new ListNode<MyClass>(*classID,clas);
        Course* relevant_course = _general_courses_table.getTableNode(courseID)->getNodeValue();
        HashTable<MyClass> clas_table = relevant_course->getClassesTable();
        clas_table.insertTableNode(clas_node);
        if(relevant_course->getIsClasses()==0) {
            relevant_course->setIsClasses(1);
            relevant_course->incNumOfClasses();
        }
        else{
            relevant_course->incNumOfClasses();
        }
   //     free(clas_node);
     //   free(clas);
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

void CoursesManager::Quit() {
   int num_of_courses = _general_courses_table.getTableSize();
   int course_id = _general_courses_table//need to have iteration over list
   for(int i=0;i<num_of_courses;i++){
       CoursesManager::RemoveCourse(course_id);
       course_id
       ///NOT FINISHED ///
   }
}
