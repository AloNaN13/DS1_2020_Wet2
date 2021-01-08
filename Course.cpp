
/* OLD CODE FROM WET1
 *
 *



#include "MyClass.h"
#include "Course.h"
#include "List.h"


Course::Course(const int id,int num_of_classes): _id(id), _num_of_classes(num_of_classes) {
    _classes_array = new MyClass[num_of_classes];
    for(int i = 0; i < num_of_classes; i++){
        MyClass *my_class = (new MyClass(i,id));
        _classes_array[i] = *my_class;
        delete my_class;
    }
};

Course::Course(const Course& course): _id(course._id), _num_of_classes(course._num_of_classes) {
    _classes_array = new MyClass[course._num_of_classes];
    for(int i = 0; i < course._num_of_classes; i++){
        this->_classes_array[i] = course._classes_array[i];
    }
}

MyClass* Course::getClasses(){
    return _classes_array;
}

int Course::getNumOfClasses(){
    return _num_of_classes;
}
