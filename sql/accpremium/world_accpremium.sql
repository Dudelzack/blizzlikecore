DELETE FROM `command` WHERE `name`='accpadd' OR `name`='accpdel';
INSERT INTO `command` VALUES ('accpadd', 3, 'Syntax: .accpadd $account_id $5d2h10m15s\r\n\r\nAdd a premium account with time to expire.'),('accpdel', 3, 'Syntax: .accpdel $account_id\r\n\r\nDelete a premium account.');
