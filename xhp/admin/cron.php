<?php
	require_once('../xcc_common.php');

	db_connect();
	db_query("delete from bl");
	db_query("insert into bl select distinct name from xwi_players inner join xwi_serials using (sid) where wtime > now()");
	db_query("update bl inner join xcl_players using (name) set points = 0");
?>