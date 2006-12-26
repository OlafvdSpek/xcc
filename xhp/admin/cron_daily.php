<?php
	require('b/config.php');
	require('b/common.php');

	db_connect();
	db_query("delete from xwi_chat1 where time < unix_timestamp() - 35 * 24 * 60 * 60");
	db_query("delete xwi_chat1 from xwi_chat1 inner join xwi_names on `from` = nid where name = 'xwisadmin'");
	$row = db_query_first("select min(chat_id) id from xwi_chat1");
	db_query(sprintf("delete from xwi_chat_to where chat_id < %d", $row['id']));
	db_query("delete from xwi_login_failures where time < unix_timestamp() - 7 * 24 * 60 * 60");
	db_query("delete from xwsvs_log where time < unix_timestamp() - 7 * 24 * 60 * 60");
	db_query("update xwi_players set cid = 0 where flags & 2");
?>