<link rel=stylesheet href="/xcc1.css">
<title>XWI Admin</title>
<?php
	function page_search($search)
	{
		$search = htmlspecialchars($search);
		include(dirname(__FILE__) . '/templates/search.php');
	}

	function page_search_results($search)
	{
		if (0 + $search)
		{
			page_edit_serial(0 + $search);
		}
		else
		{
			$rows = db_query(sprintf("select pid from xwi_players where name like '%s' limit 100", addslashes($search)));
			if (mysql_num_rows($rows) == 1)
			{
				$row = mysql_fetch_assoc($rows);
				page_edit_player($row['pid']);
			}
			else
			{
				$pids = array();
				while ($row = mysql_fetch_assoc($rows))
					$pids[] = $row['pid'];
				table_players($pids);
			}
			table_login_failures($search);
		}
	}

	function table_login_failures($player_name)
	{
		$rows = db_query(sprintf("select * from xwi_login_failures where name like '%s' order by time desc limit 100", addslashes($player_name)));
		if ($row = mysql_fetch_assoc($rows))
		{
			printf('<table>');
			printf('<tr>');
			// printf('<th align=right>pid');
			printf('<th align=right>sid');
			printf('<th>name');
			printf('<th>ipa');
			printf('<th>gsku');
			printf('<th>time');
			printf('<th>message');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
				printf('<td>%s', htmlspecialchars($row['name']));
				printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
				printf('<td>%s', gsku2a($row['gsku'] >> 8));
				printf('<td>%s', gmdate('Y-m-d H:i:s', $row['time']));
				printf('<td>%s', htmlspecialchars($row['msg']));
			}
			while ($row = mysql_fetch_assoc($rows));
			printf('</table>');
		}
	}

	function table_ladder($names, $prev)
	{
		global $config;
		if (!count($names))
			return;
		$rows = db_query(sprintf("select * from xcl_%splayers left join xcl_%splayers_rank using (pid) where lid < 17 and points and name in ('%s') order by points desc", $prev ? 'prev_' : '', $prev ? 'prev_' : '', implode("','", $names)));
		if (!mysql_num_rows($rows))
			return;
		printf('<table>');
		printf('<tr>');
		printf('<th>ladder');
		printf('<th align=right>rank');
		printf('<th align>name');
		printf('<th align=right>wins');
		printf('<th align=right>losses');
		printf('<th align=right>points');
		printf('<th>modified');
		while ($row = mysql_fetch_assoc($rows))
		{
			$sids[] = $row['sid'];
			printf('<tr>');
			printf('<td>%s', lid2a($row['lid']));
			printf('<td align=right>%d', $row['rank']);
			printf('<td align><a href="%s?pid=%d">%s</a>', $config['ladder_url'] . ($prev ? 'prev.php' : ''), $row['pid'], htmlspecialchars($row['name']));
			printf('<td align=right>%d', $row['win_count']);
			printf('<td align=right>%d', $row['loss_count']);
			printf('<td align=right>%d', $row['points']);
			printf('<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
		}
		printf('</table>');
	}

	function table_logins($ipa, $pid, $sid)
	{
		if ($ipa)
		{
			$ipa2 = $ipa;
			if (!($ipa & 0xffffff))
				$ipa2 |= 0xffffff;
			else if (!($ipa & 0xffff))
				$ipa2 |= 0xffff;
			else if (!($ipa & 0xff))
				$ipa2 |= 0xff;
			$where = $ipa == $ipa2
				? sprintf(" where l.ipa = %d", $ipa)
				: sprintf(" where l.ipa >= %d and l.ipa <= %d", $ipa, $ipa2);
		}
		else if ($pid)
			$where = sprintf(" where l.pid = %d", $pid);
		else if ($sid)
			$where = sprintf(" where l.sid = %d", $sid);
		else
			return;
		$rows = db_query(sprintf("select sid, sum(count) c, max(mtime) mtime, min(ctime) ctime from xwi_logins1 l%s group by sid order by mtime desc", $where));
		printf('<table>');
		printf('<tr>');
		printf('<th>count');
		printf('<th>sid');
		printf('<th>modified');
		printf('<th>created');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $row['c']);
			printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
		}
		printf('</table>');
		$rows = db_query(sprintf("select pid, p.name, sum(count) c, max(l.mtime) mtime, min(l.ctime) ctime from xwi_logins1 l left join xwi_players p using (pid)%s group by pid order by mtime desc", $where));
		printf('<table>');
		printf('<tr>');
		printf('<th>count');
		printf('<th>name');
		printf('<th>modified');
		printf('<th>created');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $row['c']);
			// printf('<td align=right><a href="?a=edit_player;pid=%d">%d</a>', $row['pid'], $row['pid']);
			printf('<td><a href="?a=edit_player;pid=%d">%s</a>', $row['pid'], htmlspecialchars($row['name']));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
		}
		printf('</table>');
		$rows = db_query(sprintf("select ipa, sum(count) c, max(mtime) mtime, min(ctime) ctime from xwi_logins1 l%s group by ipa order by mtime desc", $where));
		printf('<table>');
		printf('<tr>');
		printf('<th>count');
		printf('<th>ipa');
		printf('<th>modified');
		printf('<th>created');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $row['c']);
			printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
			if (isset($_REQUEST['resolve']))
				printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], gethostbyaddr(long2ip($row['ipa'])));
		}
		printf('</table>');
		$rows = db_query(sprintf("select l.*, p.name from xwi_logins1 l left join xwi_players p using (pid)%s order by mtime desc", $where));
		printf('<table>');
		// printf('<tr><th colspan=7>logins');
		printf('<tr>');
		printf('<th>count');
		// printf('<th align=right>pid');
		printf('<th align=right>sid');
		printf('<th>name');
		printf('<th>ipa');
		printf('<th>gsku');
		printf('<th>modified');
		printf('<th>created');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $row['count']);
			// printf('<td align=right><a href="?a=edit_player;pid=%d">%d</a>', $row['pid'], $row['pid']);
			printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td><a href="?a=edit_player;pid=%d">%s</a>', $row['pid'], htmlspecialchars($row['name']));
			printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
			printf('<td>%s', gsku2a($row['gsku'] >> 8));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
		}
		printf('</table>');
	}

	function table_players($pids)
	{
		$sids = array();
		$rows = db_query(sprintf("select p.*, c.name cname from xwi_players p left join xwi_clans c using (cid) where p.pid in (%s) order by p.name", count($pids) ? implode(',', $pids) : '0'));
		$names = array();
		printf('<table>');
		printf('<tr>');
		// printf('<th align=right>pid');
		printf('<th align=right>sid');
		printf('<th>name');
		printf('<th>clan');
		printf('<th>flags');
		printf('<th>modified');
		printf('<th>created');
		printf('<th>sids');
		while ($row = mysql_fetch_assoc($rows))
		{
			$sids[] = $row['sid'];
			$names[] = $row['name'];
			$names[] = $row['cname'];
			printf('<tr>');
			// printf('<td align=right><a href="?a=edit_player;pid=%d">%d</a>', $row['pid'], $row['pid']);
			printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td><a href="?a=edit_player;pid=%d">%s</a>', $row['pid'], htmlspecialchars($row['name']));
			printf('<td>');
			if ($row['cid'])
				printf('<a href="?a=edit_clan;cid=%d">%s</a>', $row['cid'], htmlspecialchars($row['cname']));
			printf('<td>');
			if ($row['flags'])
				printf('%s', flags2a($row['flags']));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
			printf('<td>');
			$rows1 = db_query(sprintf("select distinct sid from xwi_logins1 where pid = %d order by sid", $row['pid']));
			while ($row1 = mysql_fetch_assoc($rows1))
				printf('<a href="?a=edit_serial;sid=%d">%d</a> ', $row1['sid'], $row1['sid']);
		}
		printf('</table>');
		table_ladder($names, false);
		table_ladder($names, true);
	}

	function table_serials($sids)
	{
		$rows = db_query(sprintf("select * from xwi_serials where sid in (%s) order by sid", count($sids) ? implode(',', $sids) : '0'));
		$names = array();
		printf('<table>');
		printf('<tr>');
		printf('<th align=right>sid');
		printf('<th>gsku');
		printf('<th align=right>valid');
		printf('<th>ipa');
		printf('<th>wtime');
		printf('<th>modified');
		printf('<th>created');
		printf('<th>motd');
		printf('<th>names');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td>%s', gsku2a($row['gsku']));
			printf('<td align=right>%d', $row['valid']);
			printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
			printf('<td>');
			if ($row['wtime'])
				printf('%s', gmdate('Y-m-d', $row['wtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
			printf('<td>');
			if ($row['motd'])
				printf('motd');
			printf('<td>');
			$pids = array();
			$rows1 = db_query(sprintf("select distinct pid from xwi_logins1 where sid = %d", $row['sid']));
			while ($row1 = mysql_fetch_assoc($rows1))
				$pids[] = $row1['pid'];
			if (!empty($pids))
			{
				$rows1 = db_query(sprintf("select distinct p3.name from xwi_players p0 inner join xcl_players p1 using (name) inner join xcl_games_players p2 on p1.pid = p2.pid inner join xcl_players p3 on p2.cid = p3.pid where p0.pid in (%s)", implode(',', $pids)));
				while ($row1 = mysql_fetch_assoc($rows1))
					$names[] = $row1['name'];
			}
			// $rows1 = db_query(sprintf("select pid, name from xwi_players where pid in (select pid from xwi_logins1 where sid = %d) or sid = %d order by name", $row['sid'], $row['sid']));
			$rows1 = db_query(sprintf("select p.pid, p.name, p.cid, c.name cname from xwi_players p left join xwi_clans c using (cid) where pid in (%s) or sid = %d order by name", count($pids) ? implode(',', $pids) : '0', $row['sid']));
			while ($row1 = mysql_fetch_assoc($rows1))
			{
				$names[] = $row1['name'];
				printf('<a href="?a=edit_player;pid=%d">%s</a> ', $row1['pid'], htmlspecialchars($row1['name']));
				if ($row1['cid'])
					printf('(<a href="?a=edit_clan;cid=%d">%s</a>) ', $row1['cid'], htmlspecialchars($row1['cname']));
			}
		}
		printf('</table>');
		table_ladder($names, false);
		table_ladder($names, true);
	}

	function table_warnings($ipas, $sids)
	{
		$wids = array();
		$rows = db_query(sprintf("select wid from xbl_ipas where ipa in (%s)", count($ipas) ? implode(',', $ipas) : '0'));
		while ($row = mysql_fetch_assoc($rows))
			$wids[] = $row['wid'];
		$rows = db_query(sprintf("select wid from xbl_serials where sid in (%s)", count($sids) ? implode(',', $sids) : '0'));
		while ($row = mysql_fetch_assoc($rows))
			$wids[] = $row['wid'];
		$rows = db_query(sprintf("select * from xbl where wid in (%s) order by wid desc", count($wids) ? implode(',', $wids) : '0'));
		if (($row = mysql_fetch_assoc($rows)))
		{
			printf('<table>');
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
					printf('<a href="?a=show_logins;ipa=%d">%s</a> ', $row1['ipa'], long2ip($row1['ipa']));
				}
				printf('<td>');
				$rows1 = db_query(sprintf("select * from xbl_serials where wid = %d", $row['wid']));
				while ($row1 = mysql_fetch_assoc($rows1))
				{
					printf('<a href="?a=edit_serial;sid=%d">%d</a> ', $row1['sid'], $row1['sid']);
				}
			}
			while ($row = mysql_fetch_assoc($rows));
			printf('</table>');
		}
	}

	function page_edit_clan($cid)
	{
		$row = db_query_first(sprintf("select * from xwi_clans where cid = %d", $cid));
		printf('<table>');
		printf('<tr><th>cid<td>%d', $row['cid']);
		printf('<tr><th>name<td>%s', htmlspecialchars($row['name']));
		printf('<tr><th>full name<td>%s', htmlspecialchars($row['full_name']));
		printf('<tr><th>mail<td><a href="mailto:%s">%s</a>', htmlspecialchars($row['mail']), htmlspecialchars($row['mail']));
		printf('<tr><th>pass<td>');
		printf('<tr><th>modified<td>%s', gmdate('Y-m-d', $row['mtime']));
		printf('<tr><th>created<td>%s', gmdate('Y-m-d', $row['ctime']));
		printf('</table>');
		$pids = array();
		$rows = db_query(sprintf("select pid from xwi_players where cid = %d", $cid, $cid));
		while ($row = mysql_fetch_assoc($rows))
			$pids[] = $row['pid'];
		table_players($pids);
	}

	function page_edit_player($pid)
	{
		$row = db_query_first(sprintf("select p.*, c.name cname from xwi_players p left join xwi_clans c using (cid) where p.pid = %d", $pid));
		printf('<table>');
		printf('<tr><th>pid<td>%d', $row['pid']);
		printf('<tr><th>cid<td>');
		printf('<a href="?a=edit_clan;cid=%d">%d</a>', $row['cid'], $row['cid']);
		printf('<tr><th>sid<td><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
		printf('<tr><th>name<td>%s', htmlspecialchars($row['name']));
		if ($row['cid'])
		{
			printf('<tr><th>clan<td><a href="?a=edit_clan;cid=%d">%s</a>', $row['cid'], htmlspecialchars($row['cname']));
		}
		printf('<tr><th>pass<td>');
		printf('<tr><th>flags<td>%s', flags2a($row['flags']));
		printf('<tr><th>modified<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
		printf('<tr><th>created<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
		printf('<tr><th><td><a href="players.php?a=bl_insert&amp;pid=%d">-&gt; Black List</a>', $row['pid']);
		if ($row['flags'] & 2)
			printf('<tr><th><td><a href="?a=undelete_player&amp;pid=%d">Undelete</a>', $row['pid']);
		else
			printf('<tr><th><td><a href="?a=delete_player&amp;pid=%d">Delete</a>', $row['pid']);
		printf('</table>');
		$sids = array();
		$rows = db_query(sprintf("(select distinct sid from xwi_logins1 where pid = %d) union (select sid from xwi_players where pid = %d)", $pid, $pid));
		while ($row = mysql_fetch_assoc($rows))
			$sids[] = $row['sid'];
		table_warnings(array(), $sids);
		table_serials($sids);
		table_logins(0, $pid, 0);
	}

	function page_edit_serial($sid)
	{
		$row = db_query_first(sprintf("select * from xwi_serials where sid = %d", $sid));
		printf('<table>');
		printf('<tr><th>sid<td>%d', $row['sid']);
		printf('<tr><th>serial<td>');
		printf('<tr><th>gsku<td>%s', gsku2a($row['gsku']));
		printf('<tr><th>valid<td>%d', $row['valid']);
		printf('<tr><th>ipa<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
		printf('<tr><th>wtime<td>');
		if ($row['wtime'])
			printf('%s', gmdate('Y-m-d H:i:s', $row['wtime']));
		printf('<tr><th>modified<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
		printf('<tr><th>created<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
		printf('<tr><th>motd<td>%s', nl2br(htmlspecialchars($row['motd'])));
		printf('</table>');
		$pids = array();
		$rows = db_query(sprintf("(select distinct pid from xwi_logins1 where sid = %d) union (select distinct pid from xwi_players where sid = %d)", $sid, $sid));
		while ($row = mysql_fetch_assoc($rows))
			$pids[] = $row['pid'];
		table_warnings(array(), array($sid));
		table_players($pids);
		table_logins(0, 0, $sid);
	}

	function insert_admin_log($pid, $sid, $message)
	{
		global $remote_user;
		db_query(sprintf("insert into xwi_admin_log (administrator, pid, sid, message, time) values ('%s', %d, %d, '%s', unix_timestamp())",
			addslashes($remote_user), $pid, $sid, addslashes($message)));
	}

	function page_delete_player($pid)
	{
		$row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid));
		if ($row && !($row['flags'] & 2))
		{
			insert_admin_log($pid, 0, 'deleted player ' . $row['name']);
			db_query(sprintf("update xwi_players set flags = flags | 2 where pid = %d", $pid));
		}
		header(sprintf('location: ?a=edit_player&pid=%d', $pid));
	}

	function page_undelete_player($pid)
	{
		$row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid));
		if ($row && $row['flags'] & 2)
		{
			insert_admin_log($pid, 0, 'undeleted player ' . $row['name']);
			db_query(sprintf("update xwi_players set flags = flags & ~2 where pid = %d", $pid));
		}
		header(sprintf('location: ?a=edit_player&pid=%d', $pid));
	}

	require_once(dirname(__FILE__) . '/common.php');
	$remote_user = $_SERVER['REMOTE_USER'];
	if (empty($remote_user))
		die();
	db_connect();
	$a = $_REQUEST['a'];
	$ipa = $_REQUEST['ipa'];
	$pid = 0 + $_REQUEST['pid'];
	$search = trim($_REQUEST['search']);
	page_search($search);
	if (strlen($search))
	{
		if (ip2long($search) === false || ip2long($search) == $search)
			$a = 'search';
		else
		{
			$ipa = ip2long($search);
			$a = 'show_logins';
		}
	}
	switch ($a)
	{
	case 'delete_player':
		page_delete_player($pid);
		break;
	case 'undelete_player':
		page_undelete_player($pid);
		break;
	case 'edit_clan':
		page_edit_clan($_REQUEST['cid']);
		break;
	case 'edit_player':
		page_edit_player($pid);
		break;
	case 'edit_serial':
		page_edit_serial($_REQUEST['sid']);
		break;
	case 'search':
		page_search_results($search);
		break;
	case 'show_logins':
		table_logins($ipa, 0, 0);
		break;
	}
?>