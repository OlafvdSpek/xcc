<?php
	chdir('/home/olaf/xwis.net/php/admin');
	require_once('../xcc_common.php');

	db_connect();
	db_query("delete xwi_clans from xwi_clans left join xwi_players p using (cid) where p.cid is null");
	db_query("delete from xwi_clan_reset_pass_requests where ctime < unix_timestamp() - 7 * 24 * 60 * 60");
	db_query("delete from bl");
	db_query("insert into bl select distinct name from xwi_players inner join xwi_serials using (sid) where wtime > now()");
	// db_query("insert ignore into bl select distinct p.name from xbl inner join xwi_logins l using (sid) inner join xwi_players p using (pid)");
	// select distinct p1.name from xbl inner join xwi_players p0 using (name) inner join xwi_logins using (pid) inner join xwi_players p1 using (sid);
	db_query("update xwi_serials s inner join xwi_serials_new sn on s.serial = md5(sn.serial) set valid = 0 where mtime < unix_timestamp() - 60 * 60 and valid = -1");
?>
