
#include "CoursesManager.h"

CMResult CoursesManager::AddCourse(int courseID){
    try{
        if(courseID <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table->getTableNode(courseID) != nullptr){
            return CM_FAILURE;
        }

        Course* course = new Course(courseID);
        ListNode<Course> *course_node = new ListNode<Course>(courseID,course);
        _general_courses_table->insertTableNode(course_node); //where link to course from table?
        _num_of_courses++;
        // free(course_node);

        // when needed - expand general_courses_table
        if(_num_of_courses == _general_courses_table->getTableSize()){
            _general_courses_table->adjustTable(EXPAND);
        }

        // delete course_node;


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
        if(_general_courses_table->getTableNode(courseID) == nullptr){
            return CM_FAILURE;
        }

        Course* course_to_remove = _general_courses_table->getTableNode(courseID)->getNodeValue();
        HashTable<MyClass>* classes_to_remove_table = course_to_remove->getClassesTable();
        int num_of_classes = course_to_remove->getNumOfClasses();
        for(int i = 0; i < num_of_classes; i++){
            int curr_class_num_of_views = classes_to_remove_table->getTableNode(i)->getNodeValue()->getNumOfViews();
            if(curr_class_num_of_views != 0){
                _num_of_viewed_classes--;
            }
            TripleKey class_to_remove_from_tree(curr_class_num_of_views, courseID, i);
            _general_views_tree->remove(class_to_remove_from_tree);
        }

//        classes_to_remove_table->deleteHashValues();
        _general_courses_table->removeTableNode(courseID);
        _num_of_courses--;
        delete course_to_remove;

        // when needed - shrink general_courses_table
        if(_num_of_courses == _general_courses_table->getTableSize() / 4){
            _general_courses_table->adjustTable(SHRINK);
        }

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::AddClass(int courseID, int* classID) {
    try{
        if (courseID <= 0 || classID == nullptr){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table->getTableNode(courseID) == nullptr){
            return CM_FAILURE;
        }

        Course* course_to_add_to = _general_courses_table->getTableNode(courseID)->getNodeValue();
        *classID = course_to_add_to->getNumOfClasses();

        MyClass* class_to_add = new MyClass(*classID);
        ListNode<MyClass>* class_node_to_add = new ListNode<MyClass>(*classID, class_to_add);
        HashTable<MyClass>* classes_table_to_add_to = course_to_add_to->getClassesTable();
        classes_table_to_add_to->insertTableNode(class_node_to_add);
        course_to_add_to->setNumOfClasses(course_to_add_to->getNumOfClasses()+1);
        _num_of_classes++;

        // when needed - expand _classes_table
        if(course_to_add_to->getNumOfClasses() == course_to_add_to->getClassesTable()->getTableSize()){
            _general_courses_table->adjustTable(EXPAND);
        }
        // delete class_node_to_add;

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
        if(_general_courses_table->getTableNode(courseID) == nullptr){ // what about if class doesnt exist???
            return CM_FAILURE;
        }
        if(classID + 1 > _general_courses_table->getTableNode(courseID)->getNodeValue()->getNumOfClasses()){
            return CM_INVALID_INPUT;
        }

        // go to course in hashtable
        // go its to class table
        // go to class in classes hash table
            // if num_of_views is not 0 - delete the old node for the class
            // insert new node to the general views tree
            // update the num_of_views of the class

        Course* course_to_update = _general_courses_table->getTableNode(courseID)->getNodeValue();
        MyClass* class_to_update = course_to_update->getClassesTable()->getTableNode(classID)->getNodeValue();
        int old_num_of_views = class_to_update->getNumOfViews();
        int new_num_of_views = old_num_of_views + time;
        if(old_num_of_views == 0){
            _num_of_viewed_classes++;
        }
        else{
            TripleKey triplekey_to_remove(old_num_of_views, courseID, classID);
            _general_views_tree->remove(triplekey_to_remove);
        }
        TripleKey triplekey_to_insert(new_num_of_views, courseID, classID);
        _general_views_tree->insert(triplekey_to_insert, triplekey_to_insert);
        class_to_update->setNumOfViews(new_num_of_views);

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed){
    try{
        if(courseID <= 0 || classID < 0  || timeViewed == nullptr){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_table->getTableNode(courseID) == nullptr){
            return CM_FAILURE;
        }
        if(classID + 1 > _general_courses_table->getTableNode(courseID)->getNodeValue()->getNumOfClasses()){
            return CM_INVALID_INPUT;
        }
        *timeViewed = _general_courses_table->getTableNode(courseID)->getNodeValue()->
                getClassesTable()->getTableNode(classID)->getNodeValue()->getNumOfViews();
        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::GetIthWatchedClass(int i, int *courseID, int *classID){
    try{
        if(i <= 0 || courseID == nullptr || classID == nullptr){
            return CM_INVALID_INPUT;
        }
        if(_num_of_viewed_classes < i){
            return CM_FAILURE;
        }

        TripleKey* ith_watched_class = _general_views_tree->getNodeInRank(i);
        *courseID = ith_watched_class->getCourseID();
        *classID = ith_watched_class->getClassID();

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}



/*
void CoursesManager::Quit() {
   int num_of_courses = _general_courses_table.getTableSize();
   int course_id = _general_courses_table//need to have iteration over list
   for(int i=0;i<num_of_courses;i++){
       CoursesManager::RemoveCourse(course_id);
       course_id
       ///NOT FINISHED ///
   }
}
*/
