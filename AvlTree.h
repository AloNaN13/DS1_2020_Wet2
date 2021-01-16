

/****************************************************************************/
/*                                                                          */
/* This file contains the generic Avl Tree we use in the assignment         */
/*                                                                          */
/*                                                                          */
/****************************************************************************/


#ifndef DS1_WET2_AVLTREE_H
#define DS1_WET2_AVLTREE_H

#include <cmath>
#include <iostream>

using namespace std;

typedef enum AvlTreeResult_t{
    AVL_TREE_SUCCESS,
    AVL_TREE_ALLOCATION_ERROR,
    AVL_TREE_KEY_ALREADY_EXISTS,
    AVL_TREE_KEY_DOESNT_EXISTS
}AvlTreeResult;

template<class Element,class Key>
class AvlTree {
private:
    class Node{ //the tree node, implemented to be general
    public:
        Element& data;
        const Key& key;
        Node* right_son;
        Node* left_son;
        Node* parent;
        int hl;
        int hr;
        int size_sub_tree;
        int size_left_sub_tree;
        int size_right_sub_tree;
        /**
         * constractor of the node
         * @param data
         * @param key
         */
        Node(const Element& data,const Key& key):data(*(new Element(data))),key(*(new Key(key))),right_son(nullptr)
                ,left_son(nullptr),parent(nullptr),hl(0),hr(0),size_sub_tree(1),
                 size_left_sub_tree(0),size_right_sub_tree(0) {};
        /**
         * destructor of the node
         */
        ~Node(){
            delete &data;
            delete &key;
        };
        /**
         * assignment operator
         * @return assigned node
         */
        Node& operator=(const Node&)= default;
        int getHeight(){
            if(hl>hr){
                return 1+hl;
            }
            return 1+hr;
        };
        /**
         * gets the balance factor of the tree
         * @return the relevant int
         */
        int getBalanceFactor();
        /**
         * get the size of the sub-tree
         * @return the relevant int
         */
        int getSubTreeSize(){ return size_sub_tree;};
        /**
         * get a nodes parent
         * @return the parent node
         */
        Node* getParent(){ return parent;};
        /**
         *get the node related to the key
         * @param key
         * @return node
         */
        Node& getNodeFromKey(const Key key);
        /**
         * finds the next node related to the iterator
         * @return
         */
        Node* FindNext();
    };

    Node* root;
    Node* iterator;
    Node* first;
    Node* last;
    int numOfNodes;
    /**
     * private functions related to the impelentation of the tree
     */
    Node* buildTreeFromArrays(Element* arrElement, Key* arrKey, int len );
    void InsertNode(Node &newNode);
    void swapNodes(Node *node_to_del,Node* next_by_value);
    Node* removeBinarySearch(Node* node_to_del);
    void deleteAllNodes(Node* node);
    void rotateLeft(Node& node);
    void rotateRight(Node& node);
    void BalanceInsert(Node& insertedNode);
    void BalanceRemove(Node* node);
    void fixHeightAfterInsert(Node& inserted_node);
    void fixHeightAfterRemove(Node* parent_of_removed);
    void fixHeightAfterRotation(Node* rotated_node);
    static Node* copyNodes(Node* current,const Node* Node_to_copy);

    /**
     * public function of the tree
     */
public:
    /**
     * ctor of the tree
     * creates an empty tree
     *@return an empty AVLtree
    */
    AvlTree():root(nullptr),iterator(nullptr),first(nullptr),last(nullptr),numOfNodes(0){};
    /**
     * ctor of the tree
     * @param arrElement: array of the elements
     * @param arrKey : key of the element for comparison
     *@return an empty AVLtree
     */
    AvlTree(Element* arrElement, Key* arrKey, int num);
    /**
    * dstractor of the tree
    */
    ~AvlTree();
    /**
     * copy ctor of the tree
     * @param other - AvlTree to be copied
     */
    AvlTree(const AvlTree& other);
    AvlTree& operator=(const AvlTree&)= default;

    /**
    * insert an elemnt to the three, balances the tree after the insert
    * @param ele, key : element and key to be insertes
    * @return result of success
    */

    AvlTreeResult insert (const Element& ele, const Key& key);
    /**
     * removes the element of the key provided from the tree, balances the tree in the process
     * @param key - the key to search in the tree
     */
    AvlTreeResult remove (const Key& key);
    /**
     * get the tree hight
     * @return int hight
     */

    int getHeight(){ return root->getHeight();};
    /**
     * get the element ptr in the tree of the key provided
     * @param key - the key to search for
     * @return ele ptr
     */
    Element* getElementptr(const Key& key);
    /**
     * get the first element
     * @return ele ptr first
     */
    Element* getFirst();
    /**
    * get the next element
    * @return ele ptr next
     */
    Element* getNext();
    /**
    * get the last element
    * @return ele ptr last
     */
    Element* getLast();
    /**
    * get the previous element
    * @return ele ptr prev
     */
    Element* getPrevious();
    /**
    * get the node in a specific rank
    * @return ele ptr in rank
     */
    Element* getNodeInRank(int rank);
    /**
     * @return key of the current node in the iterator
     */
    const Key& getKey(){return iterator->key;}
    /**
    * finds if the key is already in the tree
    * @param key - the key to search
    * @return true/false
     */
    bool findKeyAlreadyExists(const Key& key);
    /**
     * @return number of nodes in the tree
     */
    int getNumNodes() const { return numOfNodes;}
    /**
     * get the root tree
     * @return node of the root
     */
    const Node* getRoot() const { return  root;}

};

/**
 * implementations
 */

template <class Element,class Key>
AvlTree<Element,Key>::AvlTree(const AvlTree& other):root(nullptr),iterator(nullptr),first(nullptr),last(nullptr),numOfNodes(0){
    root=copyNodes(root,other.getRoot());
    first=root;
    while (first &&first->left_son){
        first=first->left_son;
    }
    last=root;
    while (last&&last->right_son){
        last=last->right_son;
    }
    this->numOfNodes=other.getNumNodes();
}

template <class Element,class Key>
AvlTree<Element,Key>::AvlTree(Element *arrElement, Key *arrKey, int num):root(nullptr)
        ,iterator(nullptr),first(nullptr),last(nullptr){
    root=buildTreeFromArrays(arrElement,arrKey,num);
    first=root;
    while(first && first->left_son){
        first=first->left_son;
    }
    last=root;
    while (last&&last->right_son){
        last=last->right_son;
    }
    numOfNodes = num;
}


template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::copyNodes(Node* current,const Node *Node_to_copy) {
    if(!Node_to_copy){
        return nullptr ;
    }
    current=new Node(Node_to_copy->data,Node_to_copy->key);
    current->right_son=copyNodes(current->right_son,Node_to_copy->right_son);
    if(current->right_son){
        current->right_son->parent=current;
    }
    current->left_son=copyNodes(current->left_son,Node_to_copy->left_son);
    if(current->left_son){
        current->left_son->parent=current;
    }
    current->size_sub_tree=Node_to_copy->size_sub_tree;
    if(Node_to_copy->size_right_sub_tree>0){
        current->size_right_sub_tree=Node_to_copy->size_right_sub_tree;
    }
    if(Node_to_copy->size_left_sub_tree>0){
        current->size_left_sub_tree=Node_to_copy->size_left_sub_tree;
    }
    current->hr=Node_to_copy->hr;
    current->hl=Node_to_copy->hl;
    return current;
}


template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::
buildTreeFromArrays (Element* arrElement, Key* arrKey, int len ){
    if(len==0){
        return nullptr;
    }
    int current_index=(int)(len/2);
    Node* currentNode=new Node(arrElement[current_index],arrKey[current_index]);
    currentNode->left_son=buildTreeFromArrays(arrElement,arrKey,current_index);
    currentNode->right_son=buildTreeFromArrays(arrElement+current_index+1,arrKey+current_index+1,len-current_index-1);
    if(currentNode->right_son!= nullptr){
        currentNode->right_son->parent=currentNode;
        currentNode->hr=currentNode->right_son->getHeight();
        currentNode->size_right_sub_tree=currentNode->right_son->size_sub_tree;
    }
    else{
        currentNode->hr=0;
        currentNode->size_right_sub_tree=0;
    }
    if(currentNode->left_son!= nullptr){
        currentNode->left_son->parent= currentNode;
        currentNode->hl=currentNode->left_son->getHeight();
        currentNode->size_left_sub_tree=currentNode->left_son->size_left_sub_tree;
    } else{
        currentNode->hl=0;
        currentNode->size_left_sub_tree=0;
    }
    currentNode->size_sub_tree=1+(currentNode->size_left_sub_tree) +(currentNode->size_right_sub_tree);
    return currentNode;
}


template <class Element,class Key>
AvlTree<Element,Key>::~AvlTree(){
    if(root){
        deleteAllNodes(root);
    }
    first= nullptr;
    root= nullptr;
    iterator= nullptr;
    last= nullptr;
}

template <class Element,class Key>
void AvlTree<Element,Key>::deleteAllNodes(Node *node) {
    if(node){
        deleteAllNodes((node->right_son));
        deleteAllNodes((node->left_son));
        delete(node);
    }
}


template <class Element,class Key>
Element* AvlTree<Element,Key>::getElementptr(const Key &key) {
    if(!findKeyAlreadyExists(key)){
        return nullptr;
    }
    Node& wanted=root->getNodeFromKey(key);
    return &wanted.data;
}

template <class Element,class Key>
Element* AvlTree<Element,Key>::getFirst() {
    if(root== nullptr){
        return nullptr;
    }
    iterator=first;
    return &iterator->data;
}

template <class Element,class Key>
Element* AvlTree<Element,Key>::getLast() {
    if(root== nullptr){
        return nullptr;
    }
    iterator=last;
    return &iterator->data;
}

template <class Element,class Key>
Element* AvlTree<Element,Key>::getPrevious() {
    if(iterator== nullptr){
        return nullptr;
    }
    if(iterator->left_son){
        iterator=iterator->left_son;
        while (iterator->right_son){
            iterator=iterator->right_son;
        }
        return &iterator->data;
    }
    if(!iterator->parent){
        iterator= nullptr;
        return nullptr;
    }
    if(iterator->parent->right_son==iterator){
        iterator=iterator->parent;
        return &iterator->data;
    }
    iterator = nullptr;
    return nullptr;
}

template <class Element,class Key>
Element* AvlTree<Element,Key>::getNext() {
    if(iterator== nullptr){
        return nullptr;
    }
    if(iterator->right_son){
        iterator=iterator->right_son;
        while (iterator->left_son){
            iterator=iterator->left_son;
        }
        return &iterator->data;
    }
    while (iterator->parent &&iterator->parent->right_son==iterator){
        iterator=iterator->parent;
    }
    if(iterator->parent== nullptr){
        iterator=iterator->parent;
        return nullptr;
    }
    iterator=iterator->parent;
    return &iterator->data;
}

template <class Element,class Key>
Element* AvlTree<Element,Key>::getNodeInRank(int rank) {
    if (rank <= 0 || rank > numOfNodes) {
        return nullptr;
    }
    int count = rank;
    Node *tmp = root;
    while (tmp != nullptr) {
        if (tmp->size_left_sub_tree == count - 1) {
            return &tmp->data;
        } else if (tmp->size_left_sub_tree > count - 1) {
            tmp = tmp->left_son;
        } else {
            count = count - 1 - tmp->size_left_sub_tree;
            tmp = tmp->right_son;
        }
    }
    return nullptr;
}

template <class Element,class Key>
void AvlTree<Element,Key>:: fixHeightAfterInsert(Node& inserted_node){
    inserted_node.hl=0;
    inserted_node.hr=0;
    Node* parent=inserted_node.parent;
    Node*  tmp=&inserted_node;
    while (parent!=nullptr){
        if(parent->left_son==tmp){
            parent->hl=tmp->getHeight();
        } else if(parent->right_son==tmp){
            parent->hr=tmp->getHeight();
        }
        parent->size_sub_tree++;
        if(parent->right_son){
            parent->size_right_sub_tree=parent->right_son->size_sub_tree;
        }
        if (parent->left_son){
            parent->size_left_sub_tree=parent->left_son->size_sub_tree;
        }
        tmp=parent;
        parent=tmp->parent;
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::fixHeightAfterRemove(Node* parent_of_removed) {
    if(!parent_of_removed){
        return;
    }
    Node* tmp=parent_of_removed;
    Node* parent=parent_of_removed->parent;
    if(parent_of_removed->right_son== nullptr){
        parent_of_removed->hr=0;
        parent_of_removed->size_right_sub_tree=0;
    } else{
        parent_of_removed->hr=parent_of_removed->right_son->getHeight();
        parent_of_removed->size_right_sub_tree=parent_of_removed->right_son->size_sub_tree;
    }
    if(parent_of_removed->left_son== nullptr){
        parent_of_removed->hl=0;
        parent_of_removed->size_left_sub_tree=0;
    } else{
        parent_of_removed->hl=parent_of_removed->left_son->getHeight();
        parent_of_removed->size_left_sub_tree=parent_of_removed->left_son->size_sub_tree;
    }
    parent_of_removed->size_sub_tree=1+(parent_of_removed->size_left_sub_tree)+(parent_of_removed->size_right_sub_tree);
    while (parent!=nullptr){
        if(parent->left_son==tmp){
            parent->hl=tmp->getHeight();
            parent->size_left_sub_tree=parent->left_son->size_sub_tree;
        } else if(parent->right_son==tmp){
            parent->hr=tmp->getHeight();
            parent->size_right_sub_tree=parent->right_son->size_sub_tree;
        }
        tmp=parent;
        parent=tmp->parent;
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::fixHeightAfterRotation(Node* rotated_Node) {
    Node* tmp=rotated_Node->parent;
    if(!rotated_Node->left_son){
        rotated_Node->hl=0;
        rotated_Node->size_left_sub_tree=0;
    }else{
        rotated_Node->hl=rotated_Node->left_son->getHeight();
        rotated_Node->size_left_sub_tree=rotated_Node->left_son->size_sub_tree;
    }
    if(!rotated_Node->right_son){
        rotated_Node->hr=0;
        rotated_Node->size_right_sub_tree=0;
    } else{
        rotated_Node->hr=rotated_Node->right_son->getHeight();
        rotated_Node->size_right_sub_tree=rotated_Node->right_son->size_sub_tree;
    }
    rotated_Node->size_sub_tree=1+(rotated_Node->size_right_sub_tree)+(rotated_Node->size_left_sub_tree);
    while (tmp!= nullptr){
        if(tmp->left_son==rotated_Node){
            tmp->hl=rotated_Node->getHeight();
            tmp->size_left_sub_tree=tmp->left_son->size_sub_tree;
        }
        else{
            tmp->hr=rotated_Node->getHeight();
            tmp->size_right_sub_tree=tmp->right_son->size_sub_tree;
        }
        tmp->size_sub_tree=1+(tmp->size_right_sub_tree)+(tmp->size_left_sub_tree);
        rotated_Node=tmp;
        tmp=rotated_Node->parent;
    }
}

template <class Element,class Key>
int AvlTree<Element,Key>::Node::getBalanceFactor() {
    if(!this){
        return 0;
    }
    if(this->right_son== nullptr){
        if(this->left_son== nullptr){
            return 0;
        }
        return left_son->getHeight();
    }
    if(this->left_son== nullptr){
        return -right_son->getHeight();
    }
    return left_son->getHeight()-right_son->getHeight();
}

template <class Element,class Key>
typename AvlTree<Element,Key>::Node&  AvlTree<Element,Key>::Node::getNodeFromKey(const Key key){
    Node* tmp=this;
    while (tmp!= nullptr){
        if(tmp->key==key){
            return *tmp;
        }
        if(tmp->key<key){
            tmp=(tmp->right_son);
        }
        else{
            tmp= (tmp->left_son);
        }
    }

    // would never reach this
    return *tmp;
}

template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::Node::FindNext() {
    Node *nextByOrder=this->right_son;
    if(nextByOrder== nullptr){
        return this;
    }
    while(nextByOrder->left_son){
        nextByOrder=nextByOrder->left_son;
    }
    return nextByOrder;
}


template <class Element,class Key>
void AvlTree<Element,Key>::rotateLeft(AvlTree<Element, Key>::Node &node) {
    if(node.right_son== nullptr){
        return;
    }
    Node* B=node.right_son;
    Node* parent=node.parent;
    if(B->left_son){
        node.size_right_sub_tree=node.right_son->size_left_sub_tree;
        node.size_sub_tree=1+(node.size_right_sub_tree)+(node.size_left_sub_tree);
    }  else{
        node.size_right_sub_tree=0;
        node.size_sub_tree=1+(node.size_right_sub_tree)+(node.size_left_sub_tree);
    }
    B->size_left_sub_tree=node.size_sub_tree;
    B->size_sub_tree=1+B->size_left_sub_tree+B->size_right_sub_tree;
    if(parent== nullptr){
        node.right_son=B->left_son;
        if(B->left_son){
            B->left_son->parent=&node;
        }
        B->left_son=&node;
        B->parent= nullptr;
        node.parent=B;
        node.hr=node.hl;
        B->hl++;
        root=B;
        return;
    }
    //else
    if(parent->right_son==&node){
        node.right_son=B->left_son;
        if(B->left_son){
            B->left_son->parent=&node;
        }
        B->left_son=&node;
        B->parent= parent;
        parent->right_son=B;
        node.parent=B;
        node.hr=node.hl;
        B->hl++;
        return;
    }
    node.right_son=B->left_son;
    if(B->left_son){
        B->left_son->parent=&node;
    }
    B->left_son=&node;
    B->parent= parent;
    parent->left_son=B;
    node.parent=B;
    node.hr=node.hl;
    B->hl++;
}

template <class Element,class Key>
void AvlTree<Element,Key>::rotateRight(AvlTree<Element, Key>::Node &node) {
    if(node.left_son== nullptr){
        return;
    }
    Node* A=node.left_son;
    Node*parent=node.getParent();
    if(A->right_son){
        node.size_left_sub_tree=A->size_right_sub_tree;
        node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
    }
    else{
        node.size_left_sub_tree=0;
        node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
    }
    A->size_right_sub_tree=node.size_sub_tree;
    A->size_sub_tree=1+(A->size_right_sub_tree)+(A->size_left_sub_tree);
    if(parent== nullptr){
        node.left_son=A->right_son;
        if(A->right_son){
            A->right_son->parent=&node;
        }
        A->right_son=&node;
        A->parent= nullptr;
        node.parent=A;
        node.hl=node.hr;
        A->hr++;
        root=A;
        return;
    }
    //else
    if(parent->right_son==&node){
        node.left_son=A->right_son;
        if(A->right_son){
            A->right_son->parent=&node;
        }
        A->right_son=&node;
        A->parent=parent;
        parent->right_son=A;
        node.parent=A;
        node.hl=node.hr;
        A->hr++;
        return;
    }
    node.left_son=A->right_son;
    if(A->right_son){
        A->right_son->parent=&node;
    }
    A->right_son=&node;
    A->parent=parent;
    parent->left_son=A;
    node.parent=A;
    node.hl=node.hr;
    A->hr++;
}

template <class Element,class Key>
void AvlTree<Element,Key>::InsertNode(Node &newNode){
    if(root== nullptr){
        root=&newNode;
        return;
    }
    Node*tmp=root;
    while(tmp!= nullptr){
        if(tmp->key<newNode.key){
            if(tmp->right_son== nullptr){
                tmp->right_son=&newNode;
                newNode.parent=tmp;
                fixHeightAfterInsert(newNode);
                BalanceInsert(newNode);
                return;
            }
            tmp=tmp->right_son;
        }
        else {
            if(tmp->left_son== nullptr){
                tmp->left_son=&newNode;
                newNode.parent=tmp;
                fixHeightAfterInsert(newNode);
                BalanceInsert(newNode);
                //tmp->hl=tmp->hl+1;

                return;
            }
            tmp=tmp->left_son;

        }
    }
}

template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::removeBinarySearch(Node* node_to_del) {

    if(node_to_del->right_son!= nullptr &&node_to_del->left_son!=nullptr){
        Node* next_by_value=node_to_del->FindNext();
        swapNodes(node_to_del,next_by_value);
    }
    Node* parent=node_to_del->parent;

    if(parent== nullptr){//the tree has maximum 2 nodes
        if(node_to_del->right_son!= nullptr){
            node_to_del->right_son->parent= nullptr;
            root=node_to_del->right_son;
            delete(node_to_del);
            return root;
        } else if(node_to_del->left_son!= nullptr){
            node_to_del->left_son->parent= nullptr;
            root=node_to_del->left_son;
            delete(node_to_del);
            return root;
        } else{
            delete (node_to_del);
            root= nullptr;
            return nullptr;
        }

    }

    if(node_to_del->left_son==nullptr&& node_to_del->right_son== nullptr){//its a leaf
        if(parent->right_son==node_to_del){
            parent->right_son= nullptr;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son= nullptr;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    if(node_to_del->left_son== nullptr){//has only a right child
        if(parent->right_son==node_to_del){
            parent->right_son=node_to_del->right_son;
            node_to_del->right_son->parent=parent;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son=node_to_del->right_son;
        node_to_del->right_son->parent=parent;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    if(node_to_del->right_son== nullptr){

        if(parent->right_son==node_to_del){
            parent->right_son=node_to_del->left_son;
            node_to_del->left_son->parent=parent;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son=node_to_del->left_son;
        node_to_del->left_son->parent=parent;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }
    return nullptr;
}

template <class Element,class Key>
void AvlTree<Element,Key>::swapNodes(Node* node_to_del,Node* next_by_value) {
    if(node_to_del==next_by_value){
        return;
    }
    if(node_to_del==root){
        root=next_by_value;
    }
    int tmp=next_by_value->size_sub_tree;
    next_by_value->size_sub_tree=node_to_del->size_sub_tree;
    node_to_del->size_sub_tree=tmp;
    tmp=next_by_value->size_left_sub_tree;
    next_by_value->size_left_sub_tree=node_to_del->size_left_sub_tree;
    node_to_del->size_left_sub_tree=tmp;
    tmp=next_by_value->size_right_sub_tree;
    next_by_value->size_right_sub_tree=node_to_del->size_right_sub_tree;
    node_to_del->size_right_sub_tree=tmp;
    if(node_to_del->right_son==next_by_value){
        next_by_value->left_son=node_to_del->left_son;
        if(next_by_value->left_son){
            next_by_value->left_son->parent=next_by_value;
        }
        next_by_value->hl=node_to_del->hl;
        node_to_del->left_son= nullptr;
        node_to_del->hl=0;
        node_to_del->hr=next_by_value->hr;
        next_by_value->hr++;

        Node* parent=node_to_del->parent;
        node_to_del->parent=next_by_value;
        node_to_del->right_son=next_by_value->right_son;
        next_by_value->right_son=node_to_del;
        if(parent!= nullptr){
            next_by_value->parent=parent;
            if(parent->right_son==node_to_del){
                parent->right_son=next_by_value;
            } else if(parent->left_son==node_to_del){
                parent->left_son=next_by_value;
            }
            return;
        }
        else{
            next_by_value->parent= nullptr;
            return;
        }
    }

    next_by_value->hr=node_to_del->hr;
    next_by_value->hl=node_to_del->hl;
    Node *parent=next_by_value->getParent();
    parent->left_son=next_by_value->right_son;
    next_by_value->right_son=node_to_del->right_son;
    next_by_value->left_son=node_to_del->left_son;
    if(next_by_value->left_son){
        next_by_value->left_son->parent=next_by_value;
    }
    if(next_by_value->right_son){
        next_by_value->right_son->parent=next_by_value;
    }
    next_by_value->parent=node_to_del->parent;
    node_to_del->left_son= nullptr;
    node_to_del->right_son=parent->left_son;
    parent->left_son=node_to_del;
    if(node_to_del->parent){
        if(node_to_del->parent->left_son==node_to_del){
            node_to_del->parent->left_son=next_by_value;
        }
        else{
            node_to_del->parent->right_son=next_by_value;
        }
    }
    node_to_del->parent=parent;
    if(next_by_value->parent== nullptr){
        root=next_by_value;
    }
    if(next_by_value->left_son==parent||next_by_value->right_son==parent){
        parent->parent=next_by_value;
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>:: BalanceInsert(Node& insertedNode){
    Node *p=insertedNode.parent;
    Node *tmp=&insertedNode;
    int balance_factor=0;
    while (tmp!=root){
        p=tmp->parent;

        balance_factor=p->getBalanceFactor();
        if(balance_factor==2){
            if(p->left_son->getBalanceFactor()<0){
                rotateLeft(*(p->left_son));
                fixHeightAfterRotation(p->left_son);
            }
            rotateRight(*p);
            fixHeightAfterRotation(p);
            return;
        }
        if(balance_factor==-2){
            if(p->right_son->getBalanceFactor()>0){
                rotateRight(*(p->right_son));
                fixHeightAfterRotation(p->right_son);
            }
            rotateLeft(*p);
            fixHeightAfterRotation(p);
            return;
        }
        tmp=tmp->parent;
    }
}

template <class Element,class Key>
bool AvlTree<Element,Key>::findKeyAlreadyExists(const Key& key){
    if(root== nullptr){
        return false;
    }
    Node *tmp2=root;

    while(tmp2!= nullptr){
        if(tmp2->key==key){
            return true;
        }
        if(tmp2->key<key){
            tmp2=tmp2->right_son;
        }
        else{
            tmp2=tmp2->left_son;
        }
    }
    return false;
}

template <class Element,class Key>
AvlTreeResult AvlTree<Element,Key>::insert(const Element &ele, const Key& key) {
    if(findKeyAlreadyExists(key)){
        return  AVL_TREE_KEY_ALREADY_EXISTS;
    }
    Node* ptr=new Node(ele,key);
    if(root== nullptr){
        root=ptr;
        root->left_son= nullptr;
        root->right_son= nullptr;
        root->parent= nullptr;
        root->hr=0;
        root->hl=0;
        root->size_sub_tree=1;
        root->size_right_sub_tree=0;
        root->size_left_sub_tree=0;
        first=root;
        last=root;
        numOfNodes++;
        return AVL_TREE_SUCCESS;
    }
    InsertNode(*ptr);
    if(key<first->key){
        first=ptr;
    }
    if(key>last->key){
        last=ptr;
    }
    numOfNodes++;
    return AVL_TREE_SUCCESS;
}

template <class Element,class Key>
AvlTreeResult AvlTree<Element,Key>:: remove (const Key& key){

    if(!findKeyAlreadyExists(key)){
        return  AVL_TREE_KEY_DOESNT_EXISTS;
    }
    Node& node_to_del=root->getNodeFromKey(key);
    bool setFirst=(&node_to_del==first);
    bool setLast=(&node_to_del==last);
    Node* parent=removeBinarySearch(&node_to_del);

    if(parent== nullptr){
        root= nullptr;
        first= nullptr;
        last= nullptr;
        iterator= nullptr;
        numOfNodes--;
        return AVL_TREE_SUCCESS;
    }

    while (parent!= nullptr){
        if(parent->left_son){
            parent->hl=parent->left_son->getHeight();
            parent->size_left_sub_tree=parent->left_son->size_sub_tree;
        }
        else{
            parent->hl=0;
            parent->size_left_sub_tree=0;
        }
        if(parent->right_son){
            parent->hr=parent->right_son->getHeight();
            parent->size_right_sub_tree=parent->right_son->size_sub_tree;
        }
        else{
            parent->hr=0;
            parent->size_right_sub_tree=0;
        }
        parent->size_sub_tree=1+(parent->size_left_sub_tree)+(parent->size_right_sub_tree);
        BalanceRemove(parent);

        parent=parent->parent;
    }

    if(setFirst){
        if(root== nullptr){
            return AVL_TREE_SUCCESS;
        }
        first=root;

        while (first &&first->left_son){
            first=first->left_son;
        }
    }
    if(setLast){
        if(root== nullptr){
            return AVL_TREE_SUCCESS;
        }
        last=root;
        while (last&&last->right_son){
            last=last->right_son;
        }
    }
    numOfNodes--;
    return AVL_TREE_SUCCESS;
}

template <class Element,class Key>
void AvlTree<Element,Key>::BalanceRemove(Node *node) {
    if(!node){
        return;
    }
    int balance_factor=0;
    Node* p=node->parent;
    balance_factor=p->getBalanceFactor();
    if(balance_factor==2){
        if(p->left_son->getBalanceFactor()<0){
            rotateLeft(*(p->left_son));
            fixHeightAfterRotation(p->left_son);
        }
        rotateRight(*p);
        fixHeightAfterRotation(p);
        return;
    }
    if(balance_factor==-2){
        if(p->right_son->getBalanceFactor()>0){
            rotateRight(*(p->right_son));
            fixHeightAfterRotation(p->right_son);
        }
        rotateLeft(*p);
        fixHeightAfterRotation(p);
        return;
    }
}


#endif //DS1_WET2_AVLTREE_H
