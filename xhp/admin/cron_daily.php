<?php
	require('config.php');
	require(dirname(__FILE__) . '/../../b/common.php');

	db_connect();
	db_query("delete from xbl_ipas where ctime < unix_timestamp() - 365 * 24 * 60 * 60");
	db_query("delete from xwi_chat1 where time < unix_timestamp() - 77 * 24 * 60 * 60");
	db_query("delete xwi_chat1 from xwi_chat1 inner join xwi_names on `from` = nid where name = 'xwisadmin'");
	$row = db_query_first("select min(chat_id) id from xwi_chat1");
	db_query(sprintf("delete from xwi_chat_to where chat_id < %d", $row['id']));
	db_query("delete from xwi_login_failures where time < unix_timestamp() - 7 * 24 * 60 * 60");
	db_query("delete from xwi_messages where ctime < unix_timestamp() - 35 * 24 * 60 * 60");
	db_query("delete from xwi_messages where ctime < unix_timestamp() - 3 * 24 * 60 * 60 and body like '%Your game against%'");
	db_query("delete from xwi_players where flags = 2 and mtime < unix_timestamp() - 3 * 365 * 24 * 60 * 60");
	db_query("update xwi_players p inner join xbl using (pid) set p.flags = p.flags | 0x100");
	db_query("update xwi_players set flags = flags | 2, mtime = unix_timestamp() where last_online_time < unix_timestamp() - 3 * 365 * 24 * 60 * 60 and ctime < unix_timestamp() - 31 * 24 * 60 * 60");
	db_query("update xwi_players set cid = 0 where flags & 2");
	db_query("update xwi_clans a inner join (select cid, count(*) c from xwi_players group by cid) b using (cid) set player_count = b.c");

	db_query("update st_forum.invision_members set member_group_id = 11 where member_group_id = 3 and warn_level >= 3");
	db_query("update st_forum.invision_members set member_group_id = 3 where member_group_id = 11 and warn_level < 3");