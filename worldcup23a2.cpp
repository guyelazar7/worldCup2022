#include "worldcup23a2.h"
#include <iostream>

world_cup_t::world_cup_t() : m_teamTree(&m_cond1), m_rankTree(&m_cond2){}

world_cup_t::~world_cup_t(){
    m_teamTree.destructorHelper();
}

StatusType world_cup_t::add_team(int teamId)
{
	if(teamId<=0) return StatusType::INVALID_INPUT;
   Team* teamPtr = new Team(teamId);
    try{
        m_teamTree.add(teamPtr);
    }
    catch(Failure&){
        delete teamPtr;
        return StatusType::FAILURE;
    }
	catch(...){
        delete teamPtr;
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        m_rankTree.add(teamPtr);
    }
    catch(...){
        m_teamTree.remove(teamPtr);
        delete teamPtr;
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if(teamId<=0) return StatusType::INVALID_INPUT;
	Team* teamPtr;
    try{
        teamPtr = m_teamTree.find(teamId);
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
    m_rankTree.remove(teamPtr);
	m_teamTree.remove(teamPtr);
    teamPtr->m_isRemoved = true;
    if(teamPtr->m_numOfPlayers == 0)
        delete teamPtr;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	if(playerId<=0 || teamId<=0 || !spirit.isvalid() || gamesPlayed<0 || cards<0)
		return StatusType::INVALID_INPUT;
	Team* teamPtr;
    try{
        teamPtr = m_teamTree.find(teamId);
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
    try{
        m_hash.add(Player(playerId, teamPtr, spirit, gamesPlayed - teamPtr->m_teamGames, ability, cards, goalKeeper));
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
	catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    try{
        m_hash.changeSize();
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    m_rankTree.remove(teamPtr);
	teamPtr->m_spirit = teamPtr->m_spirit * spirit;
	teamPtr->m_sumAbilityPlayers+= ability;
    teamPtr->m_numOfPlayers++;
	if(goalKeeper) teamPtr->m_goalkeepers++;
    try{
        m_rankTree.add(teamPtr);
    }
    catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1<=0||teamId2<=0||teamId1==teamId2)
		return StatusType::INVALID_INPUT;
	Team* team1ptr, *team2ptr;
    try{
        team1ptr=m_teamTree.find(teamId1)->findTeam();
        team2ptr=m_teamTree.find(teamId2)->findTeam();
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
	if(team1ptr->m_goalkeepers==0 || team2ptr->m_goalkeepers==0)
		return StatusType::FAILURE;
    team1ptr->m_teamGames++;
	team2ptr->m_teamGames++;
	if(team1ptr->m_teamPoints + team1ptr->m_sumAbilityPlayers > team2ptr->m_teamPoints + team2ptr->m_sumAbilityPlayers)
    {
		team1ptr->m_teamPoints += 3;
		return 1;
	}
	if(team1ptr->m_teamPoints + team1ptr->m_sumAbilityPlayers < team2ptr->m_teamPoints + team2ptr->m_sumAbilityPlayers)
	{
		team2ptr->m_teamPoints+=3;
		return 3;
	}
	if(team1ptr->m_spirit.strength()>team2ptr->m_spirit.strength()){
		team1ptr->m_teamPoints+=3;
		return 2;
		
	}
	if(team1ptr->m_spirit.strength() < team2ptr->m_spirit.strength()){
		team2ptr->m_teamPoints+=3;
		return 4;
	}
	team1ptr->m_teamPoints++;
	team2ptr->m_teamPoints++;
	return 0;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <= 0) return StatusType::INVALID_INPUT;
    Player* playerPtr;
    try{
        playerPtr=&m_hash[playerId];
    }
    catch(...){
        return StatusType::FAILURE;
    }
	return playerPtr->m_gamesPlayed + playerPtr->m_team->getGames();
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	if(playerId<=0||cards<0) return StatusType::INVALID_INPUT;
    Player* playerPtr;
    try{
        playerPtr=&m_hash[playerId];
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
    if(playerPtr->m_team->findTeam()->m_isRemoved) return StatusType::FAILURE;
    playerPtr->m_cards+=cards;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId<=0) return StatusType::INVALID_INPUT;
    Player* playerPtr;
    try{
        playerPtr=&m_hash[playerId];
    }
    catch(...){
        return StatusType::FAILURE;
    }
	return playerPtr->m_cards;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId<=0)
		return StatusType::INVALID_INPUT;
    Team* teamPtr;
    try{
        teamPtr = m_teamTree.find(teamId);
    }
	catch(Failure&){
        return StatusType::FAILURE;
    }
	return teamPtr->m_teamPoints;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    try{
        return m_rankTree.getTeamByIndex(i);
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId<=0) return StatusType::INVALID_INPUT;
    Player* playerPtr;
    try{
        playerPtr=&m_hash[playerId];
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
    if(playerPtr->m_team->findTeam()->m_isRemoved) return StatusType::FAILURE;
    return playerPtr->m_team->getTotalBuyerSpirit() * playerPtr->m_partialSpirit;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    Team* teamPtr1, *teamPtr2;
    try{
        teamPtr1 = m_teamTree.find(teamId1)->findTeam();
        teamPtr2 = m_teamTree.find(teamId2)->findTeam();
    }
    catch(Failure&){
        return StatusType::FAILURE;
    }
    if(teamPtr2->m_numOfPlayers == 0){
        m_rankTree.remove(teamPtr2);
        m_teamTree.remove(teamPtr2);
        delete teamPtr2;
        return StatusType::SUCCESS;
    }
    if(teamPtr1->m_numOfPlayers == 0){
        m_rankTree.remove(teamPtr2);
        m_teamTree.remove(teamPtr2);
        m_rankTree.remove(teamPtr1);
        m_teamTree.remove(teamPtr1);
        teamPtr2->m_teamId = teamPtr1->m_teamId;
        try{
            m_rankTree.add(teamPtr2);
        }catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
        try{
            m_teamTree.add(teamPtr2);
        }catch(...){
            m_rankTree.remove(teamPtr2);
            return StatusType::ALLOCATION_ERROR;
        }
        delete teamPtr1;
        return StatusType::SUCCESS;
    }
    if(teamPtr1->m_size >= teamPtr2->m_size) {
        m_rankTree.remove(teamPtr2);
        m_rankTree.remove(teamPtr1);
        teamPtr1->buySmallerTeam(teamPtr2);
        try{
            m_rankTree.add(teamPtr1);
        }catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
        m_teamTree.remove(teamPtr2);
        if(teamPtr2->m_numOfPlayers == 0){
            delete teamPtr2;
        }
    }
    else
    {
        int id1=teamPtr1->m_teamId, id2=teamPtr2->m_teamId;
        m_rankTree.remove(teamPtr1);
        m_rankTree.remove(teamPtr2);
        m_teamTree.remove(teamPtr1);
        m_teamTree.remove(teamPtr2);
        teamPtr1->buyBiggerTeam(teamPtr2);
        teamPtr2->m_teamId=id1;
        teamPtr1->m_teamId=id2;
        try{
            m_teamTree.add(teamPtr2);
            m_rankTree.add(teamPtr2);
        }
        catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
        if(teamPtr1->m_numOfPlayers == 0){
            delete teamPtr1;
        }
    }
    return StatusType::SUCCESS;
}