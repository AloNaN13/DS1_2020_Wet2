
/* OLD CODE FROM WET1
 *
 *



#include "CoursesManager.h"


/***
* Adds a course to the system- adds to the general tree of courses
 * connects to the sum "0" tree connected to the node in list of views and classes to the tree under the course
 * @param courseID,numOfClasses - the course ID and number of classes to add
* @return result
*/
CMResult CoursesManager::AddCourse(int courseID, int numOfClasses){
    try{
        if(courseID <= 0 || numOfClasses <= 0){
            return CM_INVALID_INPUT;
        }
        if(_general_courses_tree.getElementptr(courseID) != nullptr){
            return CM_FAILURE;
        }

        // create course and insert it to the general courses tree
        Course* course_to_add = new Course(courseID, numOfClasses);
        _general_courses_tree.insert(*course_to_add, courseID);
        delete course_to_add;
        // all classes will now point to 0 views in views_list
        Course* new_course = _general_courses_tree.getElementptr(courseID);
        for(int i = 0; i < numOfClasses; i++){
            new_course->getClasses()[i].setListOfViews(general_views_list.getListsFirstNode());
        }

        // create the classes tree (inside courses node in the views courses tree)
        int classes_arr_by_index[numOfClasses];
        for(int i = 0; i < numOfClasses; i++){
            classes_arr_by_index[i] = i;
        }
        AvlTree<int,int> classes_tree_from_arr(classes_arr_by_index, classes_arr_by_index, numOfClasses);
        general_views_list.getListsFirstNode()->getViewsCoursesTree().insert(classes_tree_from_arr, courseID);

        // update the num of courses for the Courses Manager
        num_of_classes = num_of_classes + numOfClasses;

        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

// removes from tree of views, if only view then deletes the sum in general views list
// removes from general tree
CMResult CoursesManager::RemoveCourse(int courseID) {
    try{
        if (courseID <= 0){
            return CM_INVALID_INPUT;
        }
        if (_general_courses_tree.getElementptr(courseID) == nullptr){
            return CM_FAILURE;
        }

        // get the course to remove
        Course* course_to_remove = _general_courses_tree.getElementptr(courseID);

        for(int i = 0; i < course_to_remove->getNumOfClasses(); i++) {
            //get the relevant node in the views list
            ListNode* list_node_to_remove_from = course_to_remove->getClasses()[i].getListOfViews();
            //get the tree that represents the course's classes with this num of views
            if(list_node_to_remove_from == nullptr ||
            !list_node_to_remove_from->getViewsCoursesTree().findKeyAlreadyExists(courseID)){
                continue;
            }
            AvlTree<int,int>* views_course_tree_to_remove = list_node_to_remove_from->getViewsCoursesTree().getElementptr(courseID);
            //remove all of the nodes in that tree - all of the courses classes with the num of views
            if(views_course_tree_to_remove == nullptr){
                continue;
            }
            int* class_to_remove = views_course_tree_to_remove->getFirst();
            while(class_to_remove != nullptr){
                int* next_node_to_remove = views_course_tree_to_remove->getNext();
                course_to_remove->getClasses()[*class_to_remove].setListOfViews(nullptr);
                class_to_remove = next_node_to_remove;
            }
            //remove the courses node in the from the tree
            list_node_to_remove_from->getViewsCoursesTree().remove(courseID);
            //check if there are no more courses under the views list node - if so, remove the node as long as it's not 0
            if(list_node_to_remove_from->getViewsCoursesTree().getNumNodes() == 0 &&
               (list_node_to_remove_from != general_views_list.getListsFirstNode())) {
                general_views_list.removeListNode(list_node_to_remove_from);
            }
        }
        // update the num of courses for the Courses Manager
        num_of_classes = num_of_classes - _general_courses_tree.getElementptr(courseID)->getNumOfClasses();

        //remove the course from the general tree
        _general_courses_tree.remove(courseID);

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

        int old_time_of_views = _general_courses_tree.getElementptr(courseID)->getClasses()[classID].getViews();
        int new_time_of_views = old_time_of_views + time;
        _general_courses_tree.getElementptr(courseID)->getClasses()[classID].setViews(new_time_of_views);
        ListNode* curr_views_node = _general_courses_tree.getElementptr(courseID)->getClasses()[classID].getListOfViews();

        //remove the old time for class from the relevant course node in views_courses tree
        AvlTree<AvlTree<int,int>,int>* curr_node_tree = &(curr_views_node->getViewsCoursesTree());
        curr_node_tree->getElementptr(courseID)->remove(classID);
        if(curr_node_tree->getElementptr(courseID)->getFirst() == nullptr){
            curr_node_tree->remove(courseID);
        }
        if(curr_node_tree->getFirst() == nullptr && (curr_views_node != general_views_list.getListsFirstNode())){
            ListNode* old_views_node = curr_views_node;
            curr_views_node = curr_views_node->getPrevNode();
            general_views_list.removeListNode(old_views_node);
        }

        // add the new time for class in the relevant course node in views_courses tree
        while((curr_views_node != general_views_list.getListsLastNode()) &&
        (curr_views_node->getNextNode()->getTimeOfViews() <= new_time_of_views)){
            curr_views_node = curr_views_node->getNextNode();
        }

        if(curr_views_node->getTimeOfViews() < new_time_of_views){
            AvlTree<AvlTree<int, int>, int>* new_node_tree = new AvlTree<AvlTree<int, int>, int>();
            general_views_list.insertListNode(curr_views_node,*new_node_tree,new_time_of_views);
            curr_views_node = curr_views_node->getNextNode();

        }
        curr_node_tree = &(curr_views_node->getViewsCoursesTree());

        if(curr_node_tree->getElementptr(courseID) == nullptr){ // create a new node for the course if doesnt exist
            AvlTree<int,int> *new_classes_tree_for_course = (new AvlTree<int,int>);
            curr_node_tree->insert(*new_classes_tree_for_course,courseID);
            delete new_classes_tree_for_course;
        }
        // there should be no chance of an exact classes node (int), so we dont check it
        curr_node_tree->getElementptr(courseID)->insert(classID,classID);

        // adjust the class object - set views + pointer
        _general_courses_tree.getElementptr(courseID)->getClasses()[classID].setViews(new_time_of_views);
        _general_courses_tree.getElementptr(courseID)->getClasses()[classID].setListOfViews(curr_views_node);

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
        if(_general_courses_tree.getElementptr(courseID) == nullptr){
            return CM_FAILURE;
        }
        if(classID + 1 > _general_courses_tree.getElementptr(courseID)->getNumOfClasses()){
            return CM_INVALID_INPUT;
        }

        *timeViewed = _general_courses_tree.getElementptr(courseID)->getClasses()[classID].getViews();
        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}

CMResult CoursesManager::GetMostViewedClasses(int numOfClasses, int *courses, int *classes){
    try{
        if(numOfClasses <= 0){
            return CM_INVALID_INPUT;
        }
        if(num_of_classes < numOfClasses){
            return CM_FAILURE;
        }

        // get the last node of list
        // run with a loop until reaches numOfClasses
            // get first course
                // get first song
                // up the counter by 1 and get the next song
                // if last song, go to next course
            // if last course, go to prev node in list

        int counter = 0;
        ListNode* curr_views_node = general_views_list.getListsLastNode();
        AvlTree<int,int>* curr_course;
        int* curr_class;
        int curr_course_id = 0;

        while(counter < numOfClasses){
            curr_course = curr_views_node->getViewsCoursesTree().getFirst();
            while((counter < numOfClasses)  & (curr_course != nullptr)){
                curr_course_id = curr_views_node->getViewsCoursesTree().getKey();
                curr_class = curr_views_node->getViewsCoursesTree().getElementptr(curr_course_id)->getFirst();
                while((counter < numOfClasses) && (curr_class != nullptr)){
                    courses[counter] = curr_course_id;
                    classes[counter] = *curr_class;
                    counter++;
                    curr_class = curr_course->getNext();
                }
                curr_course = curr_views_node->getViewsCoursesTree().getNext();
            }
            curr_views_node = curr_views_node->getPrevNode();
        }
        return CM_SUCCESS;
    } catch(...){
        return CM_ALLOCATION_ERROR;
    }
}
