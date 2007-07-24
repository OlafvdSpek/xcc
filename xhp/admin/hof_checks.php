<link rel=stylesheet href="/xcc1.css">
<title>XWI Admin</title>
<?php
	require_once(dirname(__FILE__) . '/b/config.php');
	require_once(dirname(__FILE__) . '/b/common.php');
	$remote_user = $_SERVER['REMOTE_USER'];
	if (0 && empty($remote_user))
		die();
	db_connect();
	set_time_limit(0);
	if (1)
	{
		$rows0 = db_query("select pid, name from xcl_prev_players where lid in (2, 4) order by points desc limit 25");
		while ($row0 = mysql_fetch_assoc($rows0))
		{
			$cid = $row0['pid'];
			$rows = db_query(sprintf("
				select distinct gp0.gid, gp0.pid, gp0.cid, p0.name, gp1.gid, gp1.pid, gp1.cid, p3.name, l.sid
				from xcl_prev_games_players gp0
					inner join xcl_prev_players p0 on gp0.pid = p0.pid
					inner join xwi_players p1 on p0.name = p1.name
					inner join xwi_logins1 l on p1.pid = l.pid
					inner join xwi_players p2 on l.sid = p2.sid
					inner join xcl_prev_players p3 on p2.name = p3.name
					inner join xcl_prev_games_players gp1 on p3.pid = gp1.pid
				where gp0.cid = %d and gp0.cid != gp1.cid and gp0.gid = gp1.gid
				", $cid));
			if ($row = mysql_fetch_row($rows))
			{
				printf('<h1>%s</h1>', htmlspecialchars($row0['name']));
				printf('<table>');
				printf('<tr>');
				printf('<th align=right>gid');
				printf('<th align=right>pid');
				printf('<th align=right>cid');
				printf('<th align>name');
				printf('<th align=right>gid');
				printf('<th align=right>pid');
				printf('<th align=right>cid');
				printf('<th align>name');
				printf('<th align=right>sid');
				do
				{
					printf('<tr>');
					printf('<td align=right><a href="http://xwis.net/xcl/prev?gid=%d">%d</a>', $row[0], $row[0]);
					printf('<td align=right><a href="http://xwis.net/xcl/prev?pid=%d">%d</a>', $row[1], $row[1]);
					printf('<td align=right><a href="http://xwis.net/xcl/prev?cid=%d">%d</a>', $row[2], $row[2]);
					printf('<td><a href="http://xwis.net/xcl/prev?pid=%d">%s</a>', $row[1], htmlspecialchars($row[3]));
					printf('<td align=right><a href="http://xwis.net/xcl/prev?gid=%d">%d</a>', $row[4], $row[4]);
					printf('<td align=right><a href="http://xwis.net/xcl/prev?pid=%d">%d</a>', $row[5], $row[5]);
					printf('<td align=right><a href="http://xwis.net/xcl/prev?cid=%d">%d</a>', $row[6], $row[6]);
					printf('<td><a href="http://xwis.net/xcl/prev?pid=%d">%s</a>', $row[5], htmlspecialchars($row[7]));
					printf('<td align=right><a href=".?a=edit_serial;sid=%d">%d</a>', $row[8], $row[8]);
				}
				while ($row = mysql_fetch_row($rows));
				printf('</table>');
			}
		}
	}
	// echo('<hr>');
	$rows0 = db_query("select pid, name from xcl_prev_players where lid in (1, 3) order by points desc limit 250");
	while ($row0 = mysql_fetch_assoc($rows0))
	{
		$pid = $row0['pid'];
		$rows = db_query(sprintf("
			select distinct gp0.gid, gp0.pid, gp0.cid, p0.name, gp1.gid, gp1.pid, gp1.cid, p3.name, l.sid
			from xcl_prev_games_players gp0
				inner join xcl_prev_players p0 on gp0.pid = p0.pid
				inner join xwi_players p1 on p0.name = p1.name
				inner join xwi_logins1 l on p1.pid = l.pid
				inner join xwi_players p2 on l.sid = p2.sid
				inner join xcl_prev_players p3 on p2.name = p3.name
				inner join xcl_prev_games_players gp1 on p3.pid = gp1.pid
				inner join xcl_prev_games g on gp0.gid = g.gid
			where gp0.pid = %d and gp0.pid != gp1.pid and (not gp0.cid or gp0.cid != gp1.cid) and gp0.gid = gp1.gid and g.trny in (1, 2)
			", $pid));
		if ($row = mysql_fetch_row($rows))
		{
			printf('<h1>%s</h1>', htmlspecialchars($row0['name']));
			printf('<table>');
			printf('<tr>');
			printf('<th align=right>gid');
			printf('<th align=right>pid');
			printf('<th align=right>cid');
			printf('<th align>name');
			printf('<th align=right>gid');
			printf('<th align=right>pid');
			printf('<th align=right>cid');
			printf('<th align>name');
			printf('<th align=right>sid');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="http://xwis.net/xcl/prev?gid=%d">%d</a>', $row[0], $row[0]);
				printf('<td align=right><a href="http://xwis.net/xcl/prev?pid=%d">%d</a>', $row[1], $row[1]);
				printf('<td align=right><a href="http://xwis.net/xcl/prev?cid=%d">%d</a>', $row[2], $row[2]);
				printf('<td><a href="http://xwis.net/xcl/prev?pid=%d">%s</a>', $row[1], htmlspecialchars($row[3]));
				printf('<td align=right><a href="http://xwis.net/xcl/prev?gid=%d">%d</a>', $row[4], $row[4]);
				printf('<td align=right><a href="http://xwis.net/xcl/prev?pid=%d">%d</a>', $row[5], $row[5]);
				printf('<td align=right><a href="http://xwis.net/xcl/prev?cid=%d">%d</a>', $row[6], $row[6]);
				printf('<td><a href="http://xwis.net/xcl/prev?pid=%d">%s</a>', $row[5], htmlspecialchars($row[7]));
				printf('<td align=right><a href=".?a=edit_serial;sid=%d">%d</a>', $row[8], $row[8]);
			}
			while ($row = mysql_fetch_row($rows));
			printf('</table>');
			flush();
		}
	}
?>
