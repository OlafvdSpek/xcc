<?php
	chdir('/home/olaf/xwis.net/php/admin');
	require_once('../xcc_common.php');

	function update_xbl_serials()
	{
		$b = '';
		$pids = '';
		$rows = db_query("select distinct b.wid, p.pid, p.sid from xbl b inner join xwi_players p using (name)");
		while ($row = mysql_fetch_assoc($rows))
		{
			$b .= sprintf("(%d, %d, 'xwis', unix_timestamp()),", $row['wid'], $row['sid']);
			$pids[$row['pid']][] = $row['wid'];
		}
		if ($pids)
		{
			$rows = db_query(sprintf("select distinct pid, sid from xwi_logins where pid in (%s)", implode(',', array_keys($pids))));
			while ($row = mysql_fetch_assoc($rows))
			{
				foreach ($pids[$row['pid']] as $wid)
				{
					$b .= sprintf("(%d, %d, 'xwis', unix_timestamp()),", $wid, $row['sid']);
				}
			}
		}
		db_query(sprintf("insert ignore into xbl_serials (wid, sid, creator, ctime) values %s", substr($b, 0, -1)));
	}

	db_connect();
	db_query("delete a from xbl a inner join xbl_ipas b using (wid) where a.ctime + a.duration < unix_timestamp()");
	db_query("delete xwi_clans from xwi_clans left join xwi_players p using (cid) where p.cid is null");
	db_query("delete from xwi_clan_reset_pass_requests where ctime < unix_timestamp() - 7 * 24 * 60 * 60");
	update_xbl_serials();
	$rows = db_query("select bs.sid, max(b.ctime + b.duration) wtime from xbl b inner join xbl_serials bs using (wid) group by bs.sid");
	while ($row = mysql_fetch_assoc($rows))
		db_query(sprintf("update xwi_serials set wtime = %d where sid = %d", $row['wtime'], $row['sid']));
	db_query("delete from bl");
	db_query("insert into bl select distinct name from xwi_players inner join xwi_serials using (sid) where ~flags & 2 and wtime > unix_timestamp()");
?>