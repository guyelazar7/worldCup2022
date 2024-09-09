//
// Created by gilad on 26/12/2022.
//

#include "HashTable.h"
#include <exception>
#include <cmath>

static const double HASHER = (sqrt(5) - 1)/2;

HashTable::HashTable(int initialSize) :m_players(new PlayerStack[initialSize]),
    m_maxSize(initialSize), m_currentSize(0){}
HashTable::~HashTable(){
    delete[] m_players;
}
void HashTable::expand(){
    HashTable tmp(m_maxSize * EXPANSION_FACTOR);
    for(int i = 0; i < m_maxSize; i++){
        for(Player& p : m_players[i]){
            tmp.add(p);
            p.m_team->m_numOfPlayers++;
        }
    }
    m_maxSize = tmp.m_maxSize;
    PlayerStack* tmp2 = tmp.m_players;
    tmp.m_players = m_players;
    m_players = tmp2;
}
void HashTable::changeSize(){
    if(m_currentSize >= m_maxSize) expand();
}

int HashTable::hash(int id) const{
    double tmp = HASHER * id;
    tmp-= floor(tmp);
    return (int)(m_maxSize * tmp);
}

void HashTable::add(const Player& p){
    for(Player& element : m_players[hash(p.m_playerId)])
        if ( element.m_playerId == p.m_playerId)
            throw Failure();
    m_players[hash(p.m_playerId)].push(p);
}

Player& HashTable::operator[](int id){
    for(Player& element : m_players[hash(id)])
        if ( element.m_playerId == id )
            return element;
    throw Failure();
}
