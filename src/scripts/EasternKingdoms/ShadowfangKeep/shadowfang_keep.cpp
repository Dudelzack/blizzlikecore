/*
 * BlizzLikeCore Copyright (C) 2012-2013  BlizzLikeGroup
 * Integrated Files: CREDITS.md and LICENSE.md
 */

/* ScriptData
Name: Shadowfang_Keep
Complete(%): 75
Comment: npc_shadowfang_prisoner using escortAI for movement to door. Might need additional code in case being attacked. Add proper texts/say().
Category: Shadowfang Keep
EndScriptData */

/* ContentData
npc_shadowfang_prisoner
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "shadowfang_keep.h"

/*######
## npc_shadowfang_prisoner
######*/

enum eEnums
{
    SAY_FREE_AS             = -1033000,
    SAY_OPEN_DOOR_AS        = -1033001,
    SAY_POST_DOOR_AS        = -1033002,
    SAY_FREE_AD             = -1033003,
    SAY_OPEN_DOOR_AD        = -1033004,
    SAY_POST1_DOOR_AD       = -1033005,
    SAY_POST2_DOOR_AD       = -1033006,

    SPELL_UNLOCK            = 6421,
    NPC_ASH                 = 3850,

    SPELL_DARK_OFFERING     = 7154
};

#define GOSSIP_ITEM_DOOR        "Thanks, I'll follow you to the door."

struct npc_shadowfang_prisonerAI : public npc_escortAI
{
    npc_shadowfang_prisonerAI(Creature* c) : npc_escortAI(c)
    {
        pInstance = c->GetInstanceData();
        uiNpcEntry = c->GetEntry();
    }

    ScriptedInstance *pInstance;
    uint32 uiNpcEntry;

    void WaypointReached(uint32 uiPoint)
    {
        switch (uiPoint)
        {
            case 0:
                if (uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_FREE_AS, me);
                else
                    DoScriptText(SAY_FREE_AD, me);
                break;
            case 10:
                if (uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_OPEN_DOOR_AS, me);
                else
                    DoScriptText(SAY_OPEN_DOOR_AD, me);
                break;
            case 11:
                if (uiNpcEntry == NPC_ASH)
                    DoCast(me, SPELL_UNLOCK);
                break;
            case 12:
                if (uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_POST_DOOR_AS, me);
                else
                    DoScriptText(SAY_POST1_DOOR_AD, me);

                if (pInstance)
                    pInstance->SetData(TYPE_FREE_NPC, DONE);
                break;
            case 13:
                if (uiNpcEntry != NPC_ASH)
                    DoScriptText(SAY_POST2_DOOR_AD, me);
                break;
        }
    }

    void Reset() {}
    void EnterCombat(Unit* /*who*/) {}
};

CreatureAI* GetAI_npc_shadowfang_prisoner(Creature* pCreature)
{
    return new npc_shadowfang_prisonerAI(pCreature);
}

bool GossipHello_npc_shadowfang_prisoner(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = pCreature->GetInstanceData();

    if (pInstance && pInstance->GetData(TYPE_FREE_NPC) != DONE && pInstance->GetData(TYPE_RETHILGORE) == DONE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DOOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_shadowfang_prisoner(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_escortAI* pEscortAI = CAST_AI(npc_shadowfang_prisonerAI, pCreature->AI()))
            pEscortAI->Start(false, false);
    }
    return true;
}

struct npc_arugal_voidwalkerAI : public ScriptedAI
{
    npc_arugal_voidwalkerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* pInstance;

    uint32 uiDarkOffering;

    void Reset()
    {
        uiDarkOffering = urand(290,10);
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (uiDarkOffering <= uiDiff)
        {
            if (Creature* pFriend = me->FindNearestCreature(me->GetEntry(),25.0f,true))
            {
                if (pFriend)
                    DoCast(pFriend,SPELL_DARK_OFFERING);
            }
            else
                DoCast(me,SPELL_DARK_OFFERING);
            uiDarkOffering = urand(4400,12500);
        } else uiDarkOffering -= uiDiff;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*pKiller*/)
    {
        if (pInstance)
            pInstance->SetData(TYPE_FENRUS, pInstance->GetData(TYPE_FENRUS) + 1);
    }
};

CreatureAI* GetAI_npc_arugal_voidwalker(Creature* pCreature)
{
    return new npc_arugal_voidwalkerAI(pCreature);
}

void AddSC_shadowfang_keep()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_shadowfang_prisoner";
    newscript->pGossipHello =  &GossipHello_npc_shadowfang_prisoner;
    newscript->pGossipSelect = &GossipSelect_npc_shadowfang_prisoner;
    newscript->GetAI = &GetAI_npc_shadowfang_prisoner;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_arugal_voidwalker";
    newscript->GetAI = &GetAI_npc_arugal_voidwalker;
    newscript->RegisterSelf();
}

