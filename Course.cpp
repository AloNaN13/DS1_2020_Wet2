
#include "MyClass.h"
#include "Course.h"
#include "List.h"
#include "HashTable.h"


Course::Course(const int id): _id(id), _num_of_classes(0), _total_views(0), _is_classes(0),_classes_table(new HashTable<MyClass>(2)) {
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
void Course::setTotalViews(int n){
    _total_views = _total_views+n;
}
void Course::setIsClasses(bool is_class){
    _is_classes = is_class;
}