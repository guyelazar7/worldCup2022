//
// Created by gilad on 14/12/2022.
//

#include "Player.h"

Player::Player(): m_playerId(-1), m_team(nullptr), m_spirit(permutation_t::neutral()),
        m_partialSpirit(permutation_t::neutral()), m_gamesPlayed(0), m_ability(0), m_cards(0), m_isGoalkeeper(false){}

Player::Player(int playerId, Team* teamPtr, const permutation_t& spirit, int gamesPlayed, int ability, int cards,
               bool isGoalKeeper): m_playerId(playerId), m_team(teamPtr), m_spirit(spirit),
        m_partialSpirit(teamPtr->m_buyerSpirit.inv() * teamPtr->m_spirit * spirit),
        m_gamesPlayed(gamesPlayed), m_ability(ability), m_cards(cards), m_isGoalkeeper(isGoalKeeper){}

