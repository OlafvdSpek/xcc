<?php
	chdir('/home/olaf/xwis.net/php/admin');
	require_once('../xcc_common.php');

	db_connect();
	db_query("delete a from xbl a inner join xbl_ipas b using (wid) where a.ctime + a.duration < unix_timestamp()");
	db_query("delete xwi_clans from xwi_clans left join xwi_players p using (cid) where p.cid is null");
	db_query("delete from xwi_clan_reset_pass_requests where ctime < unix_timestamp() - 7 * 24 * 60 * 60");
	db_query("insert ignore into xbl_serials (wid, sid, creator, ctime) select distinct b.wid, p.sid, 'xwis', unix_timestamp() from xbl b inner join xwi_players p using (name)");
	// db_query("insert ignore into xbl_serials (wid, sid, creator, ctime) select distinct b.wid, l.sid, 'xwis', unix_timestamp() from xbl b inner join xwi_players using (name) inner join xwi_logins l using (pid)");
	db_query("update xbl b inner join xbl_serials bs using (wid) inner join xwi_serials s on bs.sid = s.sid set s.wtime = greatest(s.wtime, b.ctime + b.duration)");
	$rows = db_query("select bs.sid, max(b.ctime + b.duration) wtime from xbl b inner join xbl_serials bs using (wid) group by bs.sid");
	while ($row = mysql_fetch_assoc($rows))
		db_query(sprintf("update xwi_serials set wtime = %d where sid = %d", $row['wtime'], $row['sid']));
	db_query("delete from bl");
	db_query("insert into bl select distinct name from xwi_players inner join xwi_serials using (sid) where ~flags & 2 and wtime > unix_timestamp()");
?>
