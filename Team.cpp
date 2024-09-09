//
// Created by gilad on 14/12/2022.
//

#include "Team.h"
Team::Team(int teamId): m_teamId(teamId), m_sumAbilityPlayers(0), m_teamPoints(0), m_spirit(permutation_t::neutral()),
    m_buyerSpirit(permutation_t::neutral()), m_isRemoved(false), m_size(1), m_father(nullptr),
    m_teamGames(0), m_goalkeepers(0), m_numOfPlayers(0){}

int Team::getId() const {
    return m_teamId;
}


int Team::getGames() const{
    if(m_father == nullptr)
        return m_teamGames;
    return m_teamGames + m_father->getGames();
}
void Team::buySmallerTeam(Team* smallerTeamPtr){
    smallerTeamPtr->m_father = this;
    m_teamPoints += smallerTeamPtr->m_teamPoints;
    smallerTeamPtr->m_buyerSpirit = m_buyerSpirit.inv() * m_spirit * smallerTeamPtr->m_buyerSpirit;
    m_spirit = m_spirit * smallerTeamPtr->m_spirit;
    smallerTeamPtr->m_teamGames -= m_teamGames;
    m_size += smallerTeamPtr->m_size;
    m_goalkeepers += smallerTeamPtr->m_goalkeepers;
    m_sumAbilityPlayers += smallerTeamPtr->m_sumAbilityPlayers;
}
void Team::buyBiggerTeam(Team* biggerTeamPtr){
    m_father = biggerTeamPtr;
    biggerTeamPtr->m_teamPoints += m_teamPoints;

    biggerTeamPtr->m_buyerSpirit = m_spirit * biggerTeamPtr->m_buyerSpirit;
    m_buyerSpirit= biggerTeamPtr->m_buyerSpirit.inv() * m_buyerSpirit;
    biggerTeamPtr->m_spirit = m_spirit * biggerTeamPtr->m_spirit;

    m_teamGames -= biggerTeamPtr->m_teamGames;
    biggerTeamPtr->m_size += m_size;
    biggerTeamPtr->m_goalkeepers += m_goalkeepers;
    biggerTeamPtr->m_sumAbilityPlayers += m_sumAbilityPlayers;
    biggerTeamPtr->m_teamId = m_teamId;
}
Team* Team::findTeam(){
    if (m_father == nullptr) return this;
    int sumGames = m_teamGames;
    permutation_t totalBuyer = m_buyerSpirit;
    Team* father = m_father;
    while(father->m_father!=nullptr){
        sumGames += father->m_teamGames;
        totalBuyer = father->m_buyerSpirit * totalBuyer;
        father=father->m_father;
    }
    Team* tmp = this;
    while(tmp->m_father != father){
        sumGames -= tmp->m_teamGames;
        tmp->m_teamGames += sumGames;

        totalBuyer = totalBuyer * tmp->m_buyerSpirit.inv();
        tmp->m_buyerSpirit = totalBuyer * tmp->m_buyerSpirit;

        Team* tmpFather = tmp->m_father;
        tmp->m_father = father;
        if(tmp->m_numOfPlayers == 0) delete tmp;
        tmp=tmpFather;
    }
    return father;
}

permutation_t Team::getTotalBuyerSpirit() const{
    if(m_father == nullptr) return m_buyerSpirit;
    return m_father->getTotalBuyerSpirit() * m_buyerSpirit;
}