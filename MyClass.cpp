
#include "MyClass.h"

MyClass::MyClass(int index, int id_of_course): _views(0),_views_of_class(nullptr){
}

MyClass::MyClass(const MyClass& myClass):   _views(myClass._views),
                                            _views_of_class(myClass._views_of_class) {};

ListNode* MyClass::getListOfViews() {
    return _views_of_class;
}

int MyClass::getViews() {
    return _views;
}

void MyClass::setListOfViews (ListNode* new_sum_of_views) {
    _views_of_class = new_sum_of_views;
}

void MyClass::setViews(int views) {
    _views = views;
}
