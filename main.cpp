
/* OLD CODE FROM WET1
 *
 *


//
// Created by svet on 12/18/2020.
//


// MAIN FOR TESTING!!!!




#include "AvlTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>


#define addNode insert
#define removeNode remove

#include "AvlTree.h"
//#include "AVL_tests_OLD.h"
#include "CoursesManager.h"
//#include "MusicManger_sari_tests.h"

int main(){
    //MusicMangerTest();

/*

    AvlTree<int,int> check;
    check.insert(1,1);
    check.remove(1);
    check.insert(2,2);

*/












    CoursesManager manager=*new CoursesManager();
    manager.AddCourse(17,26);
    manager.AddCourse(14,26);
    manager.RemoveCourse(14);
    manager.AddCourse(14,26);
    manager.WatchClass(14,0,16);
    manager.WatchClass(17,0,31);
    manager.WatchClass(14,0,14);
    manager.WatchClass(14,0,4);
    manager.WatchClass(14,0,9);






















/*
    CoursesManager manager=*new CoursesManager();
    manager.AddCourse(1,5);
    manager.AddCourse(1,6);
    manager.AddCourse(2,5);

    manager.AddCourse(3,5);
    manager.WatchClass(2,0,10);
    manager.WatchClass(3,0,10);
    manager.WatchClass(1,1,10);

    manager.WatchClass(1,2,10);
    int timeViewed = 0;
    manager.TimeViewed(1,0,&timeViewed);

    manager.RemoveCourse(1);

    int courses[15] = {-20};
    int classes[15] = {-20};
    manager.GetMostViewedClasses(9,courses,classes);
    for(int i = 0; i < 9; i++){
        printf("number %d: course %d, class %d.\n", i+1, courses[i], classes[i]);
    }


    printf("Here\n");

    //manager.MMAddToSongCount(2,1);
    //manager.MMAddArtist(1,5);





    printf("hello\n");

*/
    return 0;
}



