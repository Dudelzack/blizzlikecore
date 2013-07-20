UPDATE `version` SET `db_version` = 'BDB_20130718';

-- Boss Kil'Jaeden - 1st phase corrections
-- correct CREATURE_HAND_OF_THE_DECEIVER [25558]

-- this need correction --------------
REPLACE INTO `creature_equip_template`
            (`entry`,
			 `equipmodel1`,
--			 `equipmodel2`,
			 `equipmodel3`,
			 `equipinfo1`,
--			 `equipinfo2`,
			 `equipinfo3`,
			 `equipslot1`,
--			 `equipslot2`,
			 `equipslot3`)
VALUES ('25588',
		'47994',
--		'47994',
		'47994',
		'33490690',
--		'33490690',
		'33490436',
		'269',						
--		'17',						
		'1038');					
-- ------------------------------------	

UPDATE `creature_template`
SET `equipment_id` = '25588',
	`minhealth` = '180810',
	`maxhealth` = '180810',
	`minmana` = '165450',
	`maxmana` = '165450',
	`minlevel` = '72',
	`maxlevel` = '72'
where `entry` = '25588';


-- correct CREATURE_VOLATILE_FELFIRE_FIEND [25598]
UPDATE `creature_template`
SET `minhealth` = '1307',
	`maxhealth` = '1307',
	`minmana` = '16155',
	`maxmana` = '16200',
	`minlevel` = '71',
	`maxlevel` = '71'
where `entry` = '25598';


-- correct CREATURE_FELFIRE_PORTAL [25603]
UPDATE `creature_template`
SET `minlevel` = '71',
	`maxlevel` = '71'
where `entry` = '25603';