// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "worldcup23a2.h"
#include <string>
#include <iostream>



using namespace std;

istream& operator>>(istream &in, permutation_t &obj)
{
	string str;
	in >> str;
	obj = permutation_t::read(str.c_str());
	return in;
}

void print(string cmd, StatusType res);

template<typename T>
void print(string cmd, output_t<T> res);


//int main(){
//    world_cup_t* fifa = new world_cup_t();
//    StatusType res = StatusType::SUCCESS;
//    for(int i = 1; i<100 ;++i){
//        res = fifa->add_team(i);
//        if(res != StatusType::SUCCESS) return -1;
//    }
//    for(int i = 1; i<90 ;++i){
//        res = fifa->remove_team(i);
//        if(res != StatusType::SUCCESS) return -2;
//    }
//    for(int i=0;i<10;i++)
//        std::cout <<fifa->get_ith_pointless_ability(i).ans();
//    for(int i =1; i<10; ++i){
//        for(int j = 1; j<10; ++j){
//            int a[5] = {( j%5),((j+1)%5),((j+2)%5),((j+3)%5),((j+4)%5)};
//            res = fifa->add_player(i*1000 +j, i, a, i, 2000-i, j, true);
//            if(res != StatusType::SUCCESS) return -2;
//        }
//        std::cout<<"Team " <<i<<" ability:" <<fifa->m_teamTree.find(i)->m_sumAbilityPlayers<<std::endl ;
//    }
//    for(int i = 0; i<9; ++i) std::cout<<fifa->get_ith_pointless_ability(i).ans()<<std::endl;
//    int res2 = fifa->play_match(3,5).ans();
//    std::cout<<res2<<",     first team pts:"<<fifa->m_teamTree.find(3)->m_teamPoints
//                        <<",     2nd team pts:"<<fifa->m_teamTree.find(5)->m_teamPoints<<std::endl;
//    res2 = fifa->play_match(1,2).ans();
//    std::cout<<res2<<",     first team pts:"<<fifa->m_teamTree.find(1)->m_teamPoints
//             <<",     2nd team pts:"<<fifa->m_teamTree.find(2)->m_teamPoints<<std::endl;
//    res2 = fifa->play_match(6,4).ans();
//    std::cout<<res2<<",     first team pts:"<<fifa->m_teamTree.find(6)->m_teamPoints
//             <<",     2nd team pts:"<<fifa->m_teamTree.find(4)->m_teamPoints<<std::endl;
//    std::cout<< fifa->get_partial_spirit(3001).ans() <<std::endl;
//    fifa->buy_team(3,8);
//    std::cout<< fifa->get_partial_spirit(8001).ans() <<std::endl;
//    res2 = fifa->play_match(3,6).ans();
//    std::cout<< fifa->get_partial_spirit(3001).ans() <<std::endl;
//    std::cout<< fifa->get_partial_spirit(8001).ans() <<std::endl;
//    res2 = fifa->play_match(3,1).ans();
//    std::cout<< fifa->get_partial_spirit(3001).ans() <<std::endl;
//    std::cout<< fifa->get_partial_spirit(8001).ans() <<std::endl;
//    fifa->buy_team(7,3);
//    std::cout<< fifa->get_partial_spirit(3001).ans() <<std::endl;
//    std::cout<< fifa->get_partial_spirit(7001).ans() <<std::endl;
//    fifa->play_match(7,2).ans();
//    std::cout<< fifa->get_partial_spirit(3001).ans() <<std::endl;
//    std::cout<< fifa->get_partial_spirit(7001).ans() <<std::endl;*/
//    return 0;
//}

int main()
{
	cin >> std::boolalpha;

	int pid, tid, tid2;
	int d1, d2, d3;
	permutation_t p1;
	bool b1;

	// Init
	world_cup_t *obj = new world_cup_t();
	// Execute all commands in file
	string op;
	while (cin >> op)
	{
		if (!op.compare("add_team"))
		{
			cin >> tid;
			print(op, obj->add_team(tid));
		}
		else if (!op.compare("remove_team"))
        {
			cin >> tid;
			print(op, obj->remove_team(tid));
		}
		else if (!op.compare("add_player")) {
            cin >> pid >> tid >> p1 >> d1 >> d2 >> d3 >> b1;
            print(op, obj->add_player(pid, tid, p1, d1, d2, d3, b1));
        }
		else if (!op.compare("play_match"))
        {
			cin >> tid >> tid2;
			print(op, obj->play_match(tid, tid2));
		}
		else if(!op.compare("num_played_games_for_player"))
		{
			cin >> pid;
			print(op, obj->num_played_games_for_player(pid));
		}
		else if(!op.compare("add_player_cards"))
		{
			cin >> pid >> d1;
			print(op, obj->add_player_cards(pid, d1));
		}
		else if(!op.compare("get_player_cards"))
		{
			cin >> pid;
			print(op, obj->get_player_cards(pid));
		}
		else if(!op.compare("get_team_points"))
		{
			cin >> tid;
			print(op, obj->get_team_points(tid));
		}
		else if(!op.compare("get_ith_pointless_ability"))
		{
			cin >> d1;
			print(op, obj->get_ith_pointless_ability(d1));
		}
		else if(!op.compare("get_partial_spirit"))
		{
			cin >> pid;
			print(op, obj->get_partial_spirit(pid));
		}
		else if(!op.compare("buy_team"))
		{
			cin >> tid >> tid2;
			print(op, obj->buy_team(tid, tid2));
		}
		else
		{
			cout << "Unknown command: " << op << endl;
			return -1;
		}

		// Verify no faults
		if (cin.fail())
		{
			cout << "Invalid input format" << endl;
			return -1;
		}
	}

	// Quit
	delete obj;
	return 0;
}

// Helpers
static const char *StatusTypeStr[] =
{
   	"SUCCESS",
	"ALLOCATION_ERROR",
	"INVALID_INPUT",
	"FAILURE"
};

void print(string cmd, StatusType res) 
{
	cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

template<typename T>
void print(string cmd, output_t<T> res)
{
    if (res.status() == StatusType::SUCCESS)
    {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    }
    else
    {
	    cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}
