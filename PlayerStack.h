//
// Created by gilad on 26/12/2022.
//

#ifndef HW2_PLAYERSTACK_H
#define HW2_PLAYERSTACK_H

#include "Player.h"
#include "Exception.h"

class PlayerStack {
public:
    struct node{
        explicit node(const Player& p, node* next = nullptr): m_data(p), m_next(next){}
        Player m_data;
        node* m_next;
    };
    PlayerStack():m_start(nullptr){}
    ~PlayerStack(){
        while(m_start!=nullptr){
            if(--top().m_team->m_numOfPlayers == 0)
                delete top().m_team;
            pop();
        }
    }
    void push(const Player& p){
        node* tmp;
        try{
            tmp = new node(p,m_start);
        }
        catch(...){
            throw AllocationError();
        }
        m_start = tmp;
    }
    void pop(){
        if (m_start == nullptr) throw Failure();
        node* tmp = m_start;
        m_start = m_start->m_next;
        delete tmp;
    }
    Player& top() const{
        return m_start->m_data;
    }
    class iterator{
    public:
        explicit iterator(node* node):m_node(node){}
        iterator& operator++(){
            if (m_node == nullptr) throw InvalidInput();
            m_node = m_node->m_next;
            return *this;
        }
        bool operator!=(const iterator& other) const{
            return m_node != other.m_node;
        }
        Player& operator*() const{
            return m_node->m_data;
        }
    //fields:
        node* m_node;
    };
    iterator begin(){
        return iterator(m_start);
    }
    iterator end(){
        return iterator(nullptr);
    }



//fields
    node* m_start;
};


#endif //HW2_PLAYERSTACK_H
