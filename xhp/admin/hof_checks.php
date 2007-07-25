<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN">
<link rel=stylesheet href="/xcc1.css">
<title>HoF Checks</title>
<?php
	require_once(dirname(__FILE__) . '/b/config.php');
	require_once(dirname(__FILE__) . '/b/common.php');

	function check_player($pid, $name)
	{
		global $config;
		$ladder_url = $config['ladder_url'];
		$rows = db_query(sprintf("
			select distinct gp0.gid, gp0.pid, gp0.cid, p0.name, gp1.gid, gp1.pid, gp1.cid, p3.name, l1.sid
			from xcl_prev_games_players gp0
				inner join xcl_prev_players p0 on gp0.pid = p0.pid
				inner join xwi_players p1 on p0.name = p1.name
				inner join xwi_logins1 l1 on p1.pid = l1.pid
				inner join xwi_logins1 l2 on l1.ipa = l2.ipa or l1.sid = l2.sid
				inner join xwi_players p2 on l2.pid = p2.pid
				inner join xcl_prev_players p3 on p2.name = p3.name
				inner join xcl_prev_games_players gp1 on p3.pid = gp1.pid
				inner join xcl_prev_games g on gp0.gid = g.gid
			where gp0.pid = %d and gp0.pid != gp1.pid and (not gp0.cid or gp0.cid != gp1.cid) and gp0.gid = gp1.gid and g.trny in (1, 2)
				and unix_timestamp() - l1.mtime < 365 * 24 * 60 * 60 and unix_timestamp() - l2.mtime < 365 * 24 * 60 * 60
			", $pid));
		if ($row = mysql_fetch_row($rows))
		{
			printf('<table>');
			printf('<caption><a href="%s?pid=%d">%s</a></caption>', $ladder_url, $pid, htmlspecialchars($name));
			printf('<tr>');
			printf('<th align=right>gid');
			printf('<th align=right>cid');
			printf('<th align>name');
			printf('<th align=right>gid');
			printf('<th align=right>cid');
			printf('<th align>name');
			printf('<th align=right>sid');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="%s?gid=%d">%d</a>', $ladder_url, $row[0], $row[0]);
				printf('<td align=right><a href="%s?cid=%d">%d</a>', $ladder_url, $row[2], $row[2]);
				printf('<td><a href="%s?pid=%d">%s</a>', $ladder_url, $row[1], htmlspecialchars($row[3]));
				printf('<td align=right><a href="%s?gid=%d">%d</a>', $ladder_url, $row[4], $row[4]);
				printf('<td align=right><a href="%s?cid=%d">%d</a>', $ladder_url, $row[6], $row[6]);
				printf('<td><a href="%s?pid=%d">%s</a>', $ladder_url, $row[5], htmlspecialchars($row[7]));
				printf('<td align=right><a href=".?a=edit_serial;sid=%d">%d</a>', $row[8], $row[8]);
			}
			while ($row = mysql_fetch_row($rows));
			printf('</table>');
		}
		$rows = db_query(sprintf("select gid from xcl_prev_games_players where pid = %d and not cid", $pid));
		if ($row = mysql_fetch_assoc($rows))
		{
			do
			{
				$gids[] = $row['gid'];
			}
			while ($row = mysql_fetch_assoc($rows));
			$row0 = db_query_first(sprintf("select count(*) c, scen from xcl_prev_games where gid in (%s) group by scen order by c desc limit 1", implode(',', $gids)));
			$row1 = db_query_first(sprintf("select count(*) c from xcl_prev_games where gid in (%s)", implode(',', $gids)));
			if (4 * $row0['c'] > $row1['c'])
			{
				printf('<table>');
				printf('<caption><a href="%s?pid=%d">%s</a></caption>', $ladder_url, $pid, htmlspecialchars($name));
				printf('<tr>');
				printf('<th align=right>count');
				printf('<th>scenario');
				printf('<tr>');
				printf('<td align=right>%d / %d', $row0['c'], $row1['c']);
				printf('<td>%s', htmlspecialchars($row0['scen']));
				printf('</table>');
			}
		}
	}

	function check_clan($cid, $name)
	{
		global $config;
		$ladder_url = $config['ladder_url'];
		if (0)
		{
			$rows = db_query(sprintf("
				select distinct gp0.gid, gp0.pid, p0.name, gp1.pid, gp1.cid, p3.name, l1.sid
				from xcl_prev_games_players gp0
					inner join xcl_prev_players p0 on gp0.pid = p0.pid
					inner join xwi_players p1 on p0.name = p1.name
					inner join xwi_logins1 l1 on p1.pid = l1.pid
					inner join xwi_logins1 l2 on l1.ipa = l2.ipa or l1.sid = l2.sid
					inner join xwi_players p2 on l2.pid = p2.pid
					inner join xcl_prev_players p3 on p2.name = p3.name
					inner join xcl_prev_games_players gp1 on p3.pid = gp1.pid
					inner join xcl_prev_games_players gp2 on gp1.gid = gp2.gid
				where gp0.cid = %d and gp0.cid != gp1.cid and gp0.cid = gp2.cid
					and unix_timestamp() - l1.mtime < 365 * 24 * 60 * 60 and unix_timestamp() - l2.mtime < 365 * 24 * 60 * 60
				", $cid));
			if ($row = mysql_fetch_row($rows))
			{
				printf('<table>');
				printf('<caption><a href="%s?cid=%d">%s</a></caption>', $ladder_url, $cid, htmlspecialchars($name));
				printf('<tr>');
				printf('<th align=right>gid');
				printf('<th align>name');
				printf('<th align>name');
				printf('<th align=right>cid');
				printf('<th align=right>sid');
				do
				{
					printf('<tr>');
					printf('<td align=right><a href="%s?gid=%d">%d</a>', $ladder_url, $row[0], $row[0]);
					printf('<td><a href="%s?pid=%d">%s</a>', $ladder_url, $row[1], htmlspecialchars($row[2]));
					printf('<td><a href="%s?pid=%d">%s</a>', $ladder_url, $row[3], htmlspecialchars($row[5]));
					printf('<td align=right><a href="%s?cid=%d">%d</a>', $ladder_url, $row[4], $row[4]);
					printf('<td align=right><a href=".?a=edit_serial;sid=%d">%d</a>', $row[6], $row[6]);
				}
				while ($row = mysql_fetch_row($rows));
				printf('</table>');
			}
		}
		$rows = db_query(sprintf("
			select distinct gid
			from xcl_prev_games_players
			where cid = %d and cmp = 2 and not pc
			", $cid));
		if ($row = mysql_fetch_row($rows))
		{
			printf('<table>');
			printf('<caption><a href="%s?cid=%d">%s</a></caption>', $ladder_url, $cid, htmlspecialchars($name));
			printf('<tr>');
			printf('<th align=right>gid');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="%s?gid=%d">%d</a>', $ladder_url, $row[0], $row[0]);
			}
			while ($row = mysql_fetch_row($rows));
			printf('</table>');
		}
		$rows = db_query(sprintf("
			select distinct bl.*
			from xcl_prev_games_players gp0
				inner join xcl_prev_players p0 on gp0.pid = p0.pid
				inner join xwi_players p1 on p0.name = p1.name
				inner join xwi_logins1 l1 on p1.pid = l1.pid
				inner join xbl_serials bls on l1.sid = bls.sid
				inner join xbl bl on bls.wid = bl.wid
			where gp0.cid = %d
				and unix_timestamp() - l1.mtime < 365 * 24 * 60 * 60
			order by wid desc
			", $cid));
		if ($row = mysql_fetch_assoc($rows))
		{
			printf('<table>');
			printf('<caption><a href="%s?cid=%d">%s</a></caption>', $ladder_url, $cid, htmlspecialchars($name));
			printf('<tr>');
			printf('<th align=right>wid');
			printf('<th>name');
			printf('<th>link');
			printf('<th>reason');
			printf('<th>admin');
			printf('<th>duration');
			printf('<th>modified');
			printf('<th>ipas');
			printf('<th>sids');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="players.php?a=show_warning&amp;wid=%d">%d</a>', $row['wid'], $row['wid']);
				printf('<td><a href="?search=%s">%s</a>', $row['name'], $row['name']);
				printf('<td>');
				if ($row['link'])
					printf('<a href="%s">link</a>', htmlspecialchars($row['link']));
				printf('<td>%s', htmlspecialchars($row['reason']));
				printf('<td>%s', htmlspecialchars($row['admin']));
				printf('<td align=right>%sd', $row['duration'] / (24 * 60 * 60));
				printf('<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
				printf('<td>');
				$rows1 = db_query(sprintf("select * from xbl_ipas where wid = %d", $row['wid']));
				while ($row1 = mysql_fetch_assoc($rows1))
				{
					printf('<a href=".?a=show_logins;ipa=%d">%s</a> ', $row1['ipa'], long2ip($row1['ipa']));
				}
				printf('<td>');
				$rows1 = db_query(sprintf("select * from xbl_serials where wid = %d", $row['wid']));
				while ($row1 = mysql_fetch_assoc($rows1))
				{
					printf('<a href=".?a=edit_serial;sid=%d">%d</a> ', $row1['sid'], $row1['sid']);
				}
			}
			while ($row = mysql_fetch_assoc($rows));
			printf('</table>');
		}
	}

	function check_ladder($lid)
	{
		$rows = db_query(sprintf("select pid, name from xcl_prev_players where lid = %d order by points desc limit 25", $lid));
		while ($row = mysql_fetch_assoc($rows))
		{
			if ($lid & 1)
				check_player($row['pid'], $row['name']);
			else
				check_clan($row['pid'], $row['name']);
		}
	}

	$remote_user = $_SERVER['REMOTE_USER'];
	if (0 && empty($remote_user))
		die();
	db_connect();
	set_time_limit(0);
	for ($i = 1; $i < 9; $i++)
		check_ladder($i);
?>
