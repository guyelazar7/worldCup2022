//
// Created by gilad on 29/12/2022.
//

#ifndef MAIN23A1_CPP_NEWTREE_H
#define MAIN23A1_CPP_NEWTREE_H



#include "Exception.h"
#include "Conditionals.h"
#include <iostream>
#include <memory>

using std::shared_ptr;


template<class T>
class Tree{
public:
    //general tree functions:
    struct node{
        explicit node(const T& data): m_data(data), m_left(nullptr), m_right(nullptr), m_height(1), m_rank(1){}
        virtual ~node()=default;

        T m_data;
        node* m_left;
        node* m_right;
        int m_height;
        int m_rank;
    };
    explicit Tree(condition* c):m_conditional(c), m_root(nullptr), m_size(0){}
    virtual ~Tree(){
        destroy(m_root);
    }
    T& find(int id) const{
        return find(m_root, id);
    }
    T& find(node* root, int id) const{
        if (root == nullptr) throw Failure();
        if(m_conditional->isEqual(id , root->m_data))
            return root->m_data;
        if(m_conditional->isLower(id, root->m_data))
            return find(root->m_left, id);
        return find(root->m_right, id);//id is bigger
    }
    void add(const T& toAdd) {
        m_root = addNode(m_root, toAdd);
        m_size++;
    }
    node* addNode(node* root, const T& toAdd){
        if(root == nullptr)
            return new node(toAdd);
        if(m_conditional->isLower(toAdd, root->m_data)){
            root->m_left = addNode(root->m_left, toAdd);
        }
        else if(m_conditional->isLower(root->m_data, toAdd)){
            root->m_right = addNode(root->m_right, toAdd);
        }
        else{
            throw Failure();
        }
        updateHeight(root);
        updateRank(root);
        return roll(root);
    }
    void remove(const T& toRemove){
        m_root = removeNode(m_root, toRemove);
        m_size--;
    }
    node* removeNode(node* root, const T& toRemove){
        if(root == nullptr) return nullptr;
        if(m_conditional->isLower(toRemove, root->m_data)){
            if(root->m_left != nullptr)
                root->m_left = removeNode(root->m_left, toRemove);
            else
                throw Failure();
        }
        else if(m_conditional->isLower(root->m_data, toRemove)){
            if(root->m_right != nullptr)
                root->m_right = removeNode(root->m_right, toRemove);
            else
                throw Failure();
        }
        else{
            if(root->m_left == nullptr && root->m_right == nullptr){
                delete root;
                return nullptr;
            }
            else if(root->m_left == nullptr || root->m_right == nullptr){
                node* tmp = (root->m_left == nullptr) ? root->m_right : root->m_left;
                delete root;
                return tmp;
            }
            else{
                node* follower = root->m_right;
                while(follower->m_left != nullptr)
                    follower = follower->m_left;
                root->m_data = follower->m_data;
                root->m_right = removeNode(root->m_right, follower->m_data);
            }
        }
        updateHeight(root);
        updateRank(root);
        return roll(root);
    }

    node* roll(node* n){
        if (getBalFactor(n)==2 && getBalFactor(n->m_left)>=0) return LLroll(n);
        else if (getBalFactor(n)==2 && getBalFactor(n->m_left)==-1) return LRroll(n);
        else if (getBalFactor(n)==-2 && getBalFactor(n->m_right)<=0) return RRroll(n);
        else if (getBalFactor(n)==-2 && getBalFactor(n->m_right)==1) return RLroll(n);
        return n;
    }
    node* LLroll(node* n){
        node* nodeA= n->m_left;
        n->m_left= nodeA->m_right;
        nodeA->m_right = n;
        updateHeight(n);
        updateRank(n);
        updateHeight(nodeA);
        updateRank(nodeA);
        return nodeA;
    }
    node* LRroll(node* n){
        node* nodeA = n->m_left;
        node* nodeB = nodeA->m_right;
        n->m_left= nodeB->m_right;
        nodeA->m_right= nodeB->m_left;
        nodeB->m_right=n;
        nodeB->m_left= nodeA;
        updateHeight(nodeA);
        updateRank(nodeA);
        updateHeight(n);
        updateRank(n);
        updateHeight(nodeB);
        updateRank(nodeB);
        return nodeB;
    }
    node* RRroll(node* n){
        node* nodeA= n->m_right;
        n->m_right= nodeA->m_left;
        nodeA->m_left = n;
        updateHeight(n);
        updateRank(n);
        updateHeight(nodeA);
        updateRank(nodeA);
        return nodeA;
    }
    node* RLroll(node* n){
        node* nodeA = n->m_right;
        node* nodeB = nodeA->m_left;
        n->m_right= nodeB->m_left;
        nodeA->m_left= nodeB->m_right;
        nodeB->m_left=n;
        nodeB->m_right= nodeA;
        updateHeight(nodeA);
        updateRank(nodeA);
        updateHeight(n);
        updateRank(n);
        updateHeight(nodeB);
        updateRank(nodeB);
        return nodeB;
    }

    int height(node* n) const{
        if(n == nullptr) return 0;
        return n->m_height;
    }
    int max(int a, int b) const{
        if (a > b) return a;
        return b;
    }
    void updateHeight(node* n) const{
        if(n == nullptr) return;
        n->m_height = 1 + max(height(n->m_left), height(n->m_right));
    }

    int rank(node* n) const{
        if(n == nullptr) return 0;
        return n->m_rank;
    }
    void updateRank(node* n) const{
        if(n == nullptr) return;
        n->m_rank = 1 + rank(n->m_left) + rank(n->m_right);
    }
    int getBalFactor(node* n) const{
        if(n == nullptr) return 0;
        return height(n->m_left) - height(n->m_right);
    }

    void destroy(node* ptr){
        if(ptr!= nullptr){
            destroy(ptr->m_left);
            destroy(ptr->m_right);
            delete ptr;
        }
    }

    int getElementByIndex(node* n, int index) const{
        if(n->m_left== nullptr && n->m_right== nullptr){
            return n->m_data->m_teamId;
        }
        if(n->m_left== nullptr){
            if(index==0)
                return n->m_data->m_teamId;
            return getElementByIndex(n->m_right, index-1);
        }
        if(n->m_right == nullptr)
        {
            if(index == n->m_rank-1)
                return n->m_data->m_teamId;
            return getElementByIndex(n->m_left, index);
        }
        if(n->m_left->m_rank==index)
            return n->m_data->m_teamId;
        if(n->m_left->m_rank>index-1)
            return getElementByIndex(n->m_left, index);
        return getElementByIndex(n->m_right,  index-n->m_left->m_rank-1);
    }
    int getTeamByIndex(int index){
        if(m_size <= index || index < 0) throw Failure();
        return getElementByIndex(m_root, index);
    }

    void destructorHelper(node* ptr){
        if(ptr!= nullptr){
            destructorHelper(ptr->m_left);
            destructorHelper(ptr->m_right);
            if(ptr->m_data->m_numOfPlayers == 0)
                delete ptr->m_data;
        }
    }
    void destructorHelper(){
        destructorHelper(m_root);
    }

//fields:
    condition* m_conditional;
    node* m_root;
    int m_size;
};




#endif //MAIN23A1_CPP_NEWTREE_H
