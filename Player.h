//
// Created by gilad on 14/12/2022.
//

#ifndef HW2_PLAYER_H
#define HW2_PLAYER_H

#include "wet2util.h"
#include "Team.h"

class Player {
public:
    Player();
    Player(int playerId, Team* teamPtr, const permutation_t& spirit, int gamesPlayed, int ability, int cards, bool isGoalKeeper);
    virtual ~Player()= default;


//fields:
    int m_playerId;
    Team* m_team;
    permutation_t m_spirit;
    permutation_t m_partialSpirit;
    int m_gamesPlayed;
    int m_ability;
    int m_cards;
    bool m_isGoalkeeper;
};


#endif //HW2_PLAYER_H
