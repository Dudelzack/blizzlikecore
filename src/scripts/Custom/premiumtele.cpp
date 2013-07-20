/*
 * Copyright (C) 2008 - 2013 nR7GaminG <http://nR7GaminG.eu>
 */

#include "GossipDef.h"
#include "Player.h"
#include "ScriptPCH.h"
#include "ScriptedGossip.h"
#include "Database/DatabaseEnv.h"
#include "SpellMgr.h"
#include "Common.h"

bool GossipHello_vip_teleporter(Player* player, Creature* creature)
{
	player->SetTaxiCheater(true);
	// player->ADD_GOSSIP_ITEM(5, "VIP Teleport",	             GOSSIP_SENDER_MAIN, 0);
	player->ADD_GOSSIP_ITEM(5, "VIP Account",	                 GOSSIP_SENDER_MAIN, 0);
	player->ADD_GOSSIP_ITEM(5, "Normale Account",	             GOSSIP_SENDER_MAIN, 1);
	// player->ADD_GOSSIP_ITEM(5, "Normaler Teleporter",	     GOSSIP_SENDER_MAIN, 2);
	player->ADD_GOSSIP_ITEM(5, "Build",                         GOSSIP_SENDER_MAIN, 100);

	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,            creature->GetGUID());

	return true;	   
}

void SendDefaultMenu_vip_teleporter(Player* player, Creature* creature, uint32 action)
{
	switch(action)
    {
	   case 0: // VIP Nutzer! Menü 2
		   if (player->GetSession()->IsPremium() && (player->getAttackers().empty()))// Premium status abfragen?
		   {
                player->ADD_GOSSIP_ITEM(5, "Teleport",                GOSSIP_SENDER_MAIN, 2);
                // player->ADD_GOSSIP_ITEM(3, "more",                 GOSSIP_SENDER_MAIN, xxxx);
                player->ADD_GOSSIP_ITEM(3, "Waffen F\303\244higkeit auf Max",                 GOSSIP_SENDER_MAIN, 6);
 			    player->ADD_GOSSIP_ITEM(0, "Sch\303\266nen Tag noch", GOSSIP_SENDER_MAIN, 101);

			    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,       creature->GetGUID());
		   }	   
		   else
		   {
			   player->GetSession()->SendNotification("Tut uns Leid, du bist kein V.I.P");

			   player->CLOSE_GOSSIP_MENU();
		   }
		   break;

	   case 1: // Normale Nutzer Menü 2
		   if (player->getAttackers().empty())                        // im Kampf?
		    {
                player->ADD_GOSSIP_ITEM(5, "Teleport",                GOSSIP_SENDER_MAIN, 4);
 			    player->ADD_GOSSIP_ITEM(0, "Sch\303\266nen Tag noch", GOSSIP_SENDER_MAIN, 101);
			    
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,       creature->GetGUID());
            }	   
		   else
		   {
			   player->CLOSE_GOSSIP_MENU();
		   }
		   break;

	   case 2: // VIP Nutzer! Menü 3
		   if (player->GetSession()->IsPremium() && (player->getAttackers().empty()))// Premium status abfragen?
		   {
                player->ADD_GOSSIP_ITEM(5, "Hauptst\303\244dte",        GOSSIP_SENDER_MAIN, 3);
                player->ADD_GOSSIP_ITEM(5, "Instanzen",                 GOSSIP_SENDER_MAIN, 5);
                player->ADD_GOSSIP_ITEM(5, "Welt",                 GOSSIP_SENDER_MAIN, 102);
 			    player->ADD_GOSSIP_ITEM(0, "Zur\303\274ck",   GOSSIP_SENDER_MAIN, 0);

			    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,         creature->GetGUID());
		   }	   
		   else
		   {
			   player->GetSession()->SendNotification("Tut uns Leid, du bist kein V.I.P");
			   player->CLOSE_GOSSIP_MENU();
		   }
		   break;

	   case 3:
		   if (player->GetTeam() == ALLIANCE)
		   {
			    // player->ADD_GOSSIP_ITEM(5, "Gurubashi Arena",          GOSSIP_SENDER_MAIN, 10);
			    player->ADD_GOSSIP_ITEM(5, "Sturmwind",		           GOSSIP_SENDER_MAIN, 11);
			    player->ADD_GOSSIP_ITEM(5, "Darnassus",                   GOSSIP_SENDER_MAIN, 12);
		        player->ADD_GOSSIP_ITEM(5, "Eisenschmiede",               GOSSIP_SENDER_MAIN, 13);
		   	    player->ADD_GOSSIP_ITEM(5, "Exodar",                      GOSSIP_SENDER_MAIN, 14);
	    	    player->ADD_GOSSIP_ITEM(5, "Shattrath",                   GOSSIP_SENDER_MAIN, 15);
	    	    player->ADD_GOSSIP_ITEM(5, "Quel'Danas",                  GOSSIP_SENDER_MAIN, 20);
			    player->ADD_GOSSIP_ITEM(0, "Teleport Men\303\274",        GOSSIP_SENDER_MAIN,  2);

			   player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,          creature->GetGUID());
		   }
		   else
		   if (player->GetTeam() == HORDE)
		   {
			   // player->ADD_GOSSIP_ITEM(5, "Gurubashi Arena",           GOSSIP_SENDER_MAIN, 10);
			    player->ADD_GOSSIP_ITEM(5, "Orgrimmar",                   GOSSIP_SENDER_MAIN, 16);
		        player->ADD_GOSSIP_ITEM(5, "Donnerfels",                  GOSSIP_SENDER_MAIN, 17);
			    player->ADD_GOSSIP_ITEM(5, "Unterstadt",                  GOSSIP_SENDER_MAIN, 18);
			    player->ADD_GOSSIP_ITEM(5, "Silbermond",                  GOSSIP_SENDER_MAIN, 19);
			    player->ADD_GOSSIP_ITEM(5, "Shattrath",                   GOSSIP_SENDER_MAIN, 15);
	    	    player->ADD_GOSSIP_ITEM(5, "Quel'Danas",                  GOSSIP_SENDER_MAIN, 20);
			    player->ADD_GOSSIP_ITEM(0, "Teleport Men\303\274",        GOSSIP_SENDER_MAIN,  2);

			   player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,            creature->GetGUID());
		   }
			  break;

          // Normal Teleporter!
	   case 4:
		   if (player->GetTeam() == ALLIANCE)
		   {
			   player->ADD_GOSSIP_ITEM(5, "Sturmwind",		               GOSSIP_SENDER_MAIN, 11);
 			   player->ADD_GOSSIP_ITEM(0, "Sch\303\266nen Tag noch",      GOSSIP_SENDER_MAIN, 101);

			   player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,           creature->GetGUID());

		   }
		   else
		   if (player->GetTeam() == HORDE)
		   {
			   player->ADD_GOSSIP_ITEM(5, "Orgrimmar",                   GOSSIP_SENDER_MAIN, 16);
 			   player->ADD_GOSSIP_ITEM(0, "Sch\303\266nen Tag noch",     GOSSIP_SENDER_MAIN, 101);

			   player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,          creature->GetGUID());
		   }
			  break;
	   
           case 5:                                                         // INSTANZEN
		   {

			    player->ADD_GOSSIP_ITEM(5, "Der Schwarzer Tempel",             GOSSIP_SENDER_MAIN, 21);
		        player->ADD_GOSSIP_ITEM(5, "Festung der St\303\274rme",               GOSSIP_SENDER_MAIN, 22);
		   	    // player->ADD_GOSSIP_ITEM(5, "Gruuls Unterschlupf",              GOSSIP_SENDER_MAIN, 23);
	    	    // player->ADD_GOSSIP_ITEM(5, "H\303\266hle des Schlangenschreins",      GOSSIP_SENDER_MAIN, 24);
	    	    player->ADD_GOSSIP_ITEM(5, "Hyjal",                            GOSSIP_SENDER_MAIN, 25);
	    	    // player->ADD_GOSSIP_ITEM(5, "Karazahn",                         GOSSIP_SENDER_MAIN, 26);
	    	    // player->ADD_GOSSIP_ITEM(5, "Magtheridons Kammer",              GOSSIP_SENDER_MAIN, 27);
	    	    // player->ADD_GOSSIP_ITEM(5, "Sonnenbrunnenplateau",             OSSIP_SENDER_MAIN, 28);
	    	    player->ADD_GOSSIP_ITEM(5, "Zul'Aman",                         GOSSIP_SENDER_MAIN, 29);
			    // player->ADD_GOSSIP_ITEM(0, "Teleport Men\303\274",             GOSSIP_SENDER_MAIN, 0);
                player->ADD_GOSSIP_ITEM(0, "Teleport Men\303\274",        GOSSIP_SENDER_MAIN,  2);

			    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,          creature->GetGUID());
		   }
			    break;

			case 6: // Max Skills
				player->CLOSE_GOSSIP_MENU();
				player->UpdateSkillsToMaxSkillsForLevel();

				break;
/*
#############################################
#############################################
################ HAUPTSTÄDTE ################
#############################################
#############################################
*/
        //Gurubashi Arena!
        case  10: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(0,   -13240.937500f,    204.797928f,     30.869392f, 1.102942f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
         //Sturmwind
        case  11: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(0,    -8881.000000f,    575.000000f,     93.000000f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Darnassus
        case  12: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(1,     9951.890000f,   2280.550000f,   1341.390000f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Eisenschmiede
        case  13: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(0,    -4981.000000f,   -881.000000f,    501.660000f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Exodar
        case  14: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,  -4014.000000f, -11895.790000f,     -2.000000f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Shattrath
        case  15: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,  -1887.510010f,   5359.379883f,    -12.427300f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Orgrimmar
        case  16: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(1,     1629.777344f,  -4373.210449f,     31.246769f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Donnerfels
        case  17: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(1,    -1196.858398f,     30.147331f,    176.949188f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;

        // Unterstadt
        case  18: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(0,     1844.765625f,    237.655991f,     62.275150f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;

		// Silbermod
        case  19: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,   9400.486328f,  -7278.376953f,     14.206780f, 0.000000f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;

		//Quel'Danas
        case  20: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,   12942.400391f,  -6930.770020f,     4.213060f, 2.437920f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;


/*
#############################################
#############################################
################# INSTANZEN #################
#############################################
#############################################
*/
        // Der Schwarzer Tempel
		case  21: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,   -3640.432861f,  314.126221f,     35.256004f, 2.897555f);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //FDS: Das Auge
		case  22: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,   3088.391357f,  1386.200073f,     184.957825f, 4.546514f);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Gruuls Unterschlupf
		// case  23: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Höhle des Schlangenschreins
		// case  24: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Hyjal
		case  25: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(1,   -8168.119629f,  -4177.029785f,     -165.076645f, 4.125618f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Karazahn
		// case  26: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Magtheridons Kammer
		// case  27: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Sonnenbrunnenplateau
		// case  28: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        //Zul'Aman
		case  29: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(530,   6851.297852f,  -7954.612793f,     170.040161f, 4.668588f); break; // creature->MonsterSay(4444405, player->GetGuid()); break;

/*
#############################################
#############################################
#################### WELT ###################
#############################################
#############################################
*/
        //XXXXXX
		// case  30: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;

        //XXXXXX
		// case  31: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;

        //XXXXXX
		// case  32: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;

        //XXXXXX
		// case  33: player->CLOSE_GOSSIP_MENU(); player->TeleportTo(MAP,   XXXXXf,  YYYYf,     ZZZZZf, OOOOOf);  break; // creature->MonsterSay(4444405, player->GetGuid()); break;
		
        case 100:
	        player->ADD_GOSSIP_ITEM(6, "Version",                   GOSSIP_SENDER_MAIN, 110);
	        player->ADD_GOSSIP_ITEM(6, "Entwickler",                GOSSIP_SENDER_MAIN, 111);
	        player->ADD_GOSSIP_ITEM(0, "Sch\303\266nen Tag noch",   GOSSIP_SENDER_MAIN, 101);

	        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,        creature->GetGUID());
		break;

		case 101:
			player->GetSession()->SendNotification("Viel Spa\303\237 noch auf Sturmschlag");
			player->CLOSE_GOSSIP_MENU();
		break;

		case 102:
			player->GetSession()->SendNotification("Dies befindet sich noch in Entwicklung");
			player->CLOSE_GOSSIP_MENU();
		break;

		case 110:
			player->CLOSE_GOSSIP_MENU();
		    player->GetSession()->SendNotification("Version 2.0.2");
		  //creature->MonsterSay(4444406, player->GetGuid());
	    break;

		case 111:
			player->CLOSE_GOSSIP_MENU();
		    player->GetSession()->SendNotification("by KillaVulkan");
	    break;
    }
}

bool GossipSelect_vip_teleporter(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (sender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_vip_teleporter(player, creature, action);

    return true;
}

void AddSC_vip_teleporter()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="vip_teleporter";
    newscript->pGossipHello =  &GossipHello_vip_teleporter;
    newscript->pGossipSelect = &GossipSelect_vip_teleporter;
    newscript->RegisterSelf();
}