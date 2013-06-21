/*
 * BlizzLikeCore Copyright (C) 2012-2013  BlizzLikeGroup
 * Integrated Files: CREDITS.md and LICENSE.md
 */

#ifndef _GROUPREFMANAGER
#define _GROUPREFMANAGER

#include "Utilities/LinkedReference/RefManager.h"

class Group;
class Player;
class GroupReference;

class GroupRefManager : public RefManager<Group, Player>
{
    public:
        GroupReference* getFirst() { return ((GroupReference*) RefManager<Group, Player>::getFirst()); }
};
#endif

