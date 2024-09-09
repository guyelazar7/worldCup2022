//
// Created by gilad on 26/12/2022.
//

#ifndef HW2_HASHTABLE_H
#define HW2_HASHTABLE_H

#include "Player.h"
#include "PlayerStack.h"
#include "Exception.h"
static const int INITIAL_MAX_SIZE = 1000;
static const int EXPANSION_FACTOR = 2;

class HashTable {
public:
    explicit HashTable(int size = INITIAL_MAX_SIZE);
    ~HashTable();

    void expand();
    void changeSize();
    int hash(int id) const;
    void add(const Player& p);
    Player& operator[](int id);

//fields:
    PlayerStack* m_players;
    int m_maxSize;
    int m_currentSize;
};


#endif //HW2_HASHTABLE_H
