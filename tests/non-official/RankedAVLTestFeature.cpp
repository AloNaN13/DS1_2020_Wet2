/*
 * Made By Aviram Shubeili
 * 04.01.2021
 *
 */


#include <exception>

void detailedPrint(std::shared_ptr<RankedAVLNode<int>> root) {
    if(root == nullptr) {
        return;
    }
    detailedPrint(root->getLeftSon());
    std::cout << root->getKey() << " BF: " << getBF(root)
              << " Height: " << root->getHeight();

    // Check if Root's rank value is currect
    std::cout <<  "  || Rank: " << root->rank << "  Rank == subtreeSize : ";
    int realRank = recursiveCalcRank(root);
    if(realRank == root->rank) {
        std::cout << "TRUE";
    }
    else {
        std::cout << "FALSE  RealRank = " << realRank ;
        // throws something to stop run
        throw std::bad_alloc();
    }
    std::cout <<std::endl;
    detailedPrint(root->getRightSon());
}



int recursiveCalcRank(std::shared_ptr<RankedAVLNode<int>> node) {
    if(node == nullptr) {
        return 0;
    }
    return recursiveCalcRank(node->getLeftSon()) + recursiveCalcRank(node->getRightSon()) + 1;
}
