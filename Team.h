//
// Created by gilad on 14/12/2022.
//

#ifndef HW2_TEAM_H
#define HW2_TEAM_H

#include "wet2util.h"
#include <memory>

class Team {
public:
    explicit  Team(int teamId=0);
    virtual ~Team() = default;

    int getId() const;

    //unionFind:
    permutation_t getTotalBuyerSpirit() const;
    int getGames() const;
    void buySmallerTeam(Team* smallerTeamPtr);
    void buyBiggerTeam(Team* biggerTeamPtr);
    Team* findTeam();

//fields:
    int m_teamId;
    int m_sumAbilityPlayers;
    int m_teamPoints;

    permutation_t m_spirit;
    permutation_t m_buyerSpirit;

    bool m_isRemoved;
    int m_size;
    Team* m_father;
    int m_teamGames;
    int m_goalkeepers;

    int m_numOfPlayers;
};


#endif //HW2_TEAM_H
