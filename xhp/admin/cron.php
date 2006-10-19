<?php
	require('b/config.php');
	require('b/common.php');

	db_connect();
	db_query("delete b from xbl a inner join xbl_ipas b using (wid) where a.ctime + a.duration < unix_timestamp()");
	db_query("delete xwi_clans from xwi_clans left join xwi_players p using (cid) where p.cid is null");
	db_query("delete from xwi_clan_reset_pass_requests where ctime < unix_timestamp() - 7 * 24 * 60 * 60");
?>