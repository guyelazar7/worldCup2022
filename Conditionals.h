#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include <iostream>
#include "Team.h"
#include "Exception.h"

class condition{
public:
    virtual bool isLower(Team* const& t1, Team* const& t2) const = 0;
    virtual bool isLower(Team* const& t, int id) const = 0;
    virtual bool isLower(int id, Team* const& t) const = 0;

    virtual bool isEqual(Team* const& t1, Team* const& t2) const = 0;
    virtual bool isEqual(Team* const& t, int id) const = 0;
    virtual bool isEqual(int id, Team* const& t) const = 0;
};

class ByIdForPointers: public condition{
public:
    bool isLower(Team* const& t1, Team* const& t2) const override{
        return t1->getId() < t2->getId();
    }
    bool isLower(Team* const& t, int id) const override{
        return t->getId() < id;
    }
    bool isLower(int id, Team* const& t) const override{
        return id < t->getId();
    }

    bool isEqual(Team* const& t1, Team* const& t2) const override{
        return t1->getId() == t2->getId();
    }
    bool isEqual(Team* const& t, int id) const override{
        return t->getId() == id;
    }
    bool isEqual(int id, Team* const& t) const override{
        return t->getId() == id;
    }
};

class ByAbility: public condition{
public:
    bool isLower(Team* const& t1, Team* const& t2) const override{
        if(t1->m_sumAbilityPlayers < t2->m_sumAbilityPlayers) return true;
        if(t1->m_sumAbilityPlayers > t2->m_sumAbilityPlayers) return false;
        return t1->getId() < t2->getId();
    }
    bool isLower(Team* const& t, int id) const override{
        throw Failure();
    }
    bool isLower(int id, Team* const& t) const override{
        throw Failure();
    }

    bool isEqual(Team* const& t1, Team* const& t2) const override{
        return t1->getId() == t2->getId();
    }
    bool isEqual(Team* const& t, int id) const override{
        return t->getId() == id;
    }
    bool isEqual(int id, Team* const& t) const override{
        return t->getId() == id;
    }
};

#endif //CONDITIONALS_H