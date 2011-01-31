<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<link rel=stylesheet href="/xcc1.css">
<title>XWI Admin</title>
<?php
	function page_search($search)
	{
		include(dirname(__FILE__) . '/templates/links.php');
	}

	function page_search_results($search)
	{
		global $config;
		if (0 + $search)
		{
			page_edit_serial(0 + $search);
		}
		else if (strstr($search, '@') !== FALSE)
		{
			$row = db_query_first(sprintf("select member_id from st_forum.invision_members where email = '%s'", addslashes($search)));
			if ($row)
				page_user($row['member_id']);
		}
		else
		{
			$rows = db_query(sprintf("select pid from xwi_players where server_id = %d and name like '%s' limit 100", $config['server_id'], addslashes($search)));
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
			table_login_failures(0, $search, 0);
		}
	}

	function table_login_failures($ipa, $player_name, $sid)
	{
		if ($ipa)
			$rows = db_query(sprintf("select * from xwi_login_failures where ipa = %d order by time desc limit 100", $ipa));
		else if ($sid)
			$rows = db_query(sprintf("select * from xwi_login_failures where sid = %d order by time desc limit 100", $sid));
		else
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
				$row['ipa'] &= 0xffffffff;
				printf('<tr>');
				printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
				printf('<td><a href="?q=%s">%s</a>', urlencode($row['name']), htmlspecialchars($row['name']));
				printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
				printf('<td>%s', gsku2a($row['gsku'] >> 8, $row['gsku'] & 0xff));
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
		printf('<th align=right>dc');
		printf('<th align=right>oos');
		printf('<th align=right>points');
		printf('<th>modified');
		while ($row = mysql_fetch_assoc($rows))
		{
			$sids[] = $row['sid'];
			printf('<tr>');
			printf('<td>%s', lid2a($row['lid']));
			printf('<td align=right>%d', $row['rank']);
			printf('<td align><a href="%s?q=%s">%s</a>', $config['ladder_url'] . ($prev ? 'prev/' : ''), urlencode($row['name']), htmlspecialchars($row['name']));
			printf('<td align=right>%d', $row['win_count']);
			printf('<td align=right>%d', $row['loss_count']);
			printf('<td align=right>%d', $row['dc_count']);
			printf('<td align=right>%d', $row['oos_count']);
			printf('<td align=right>%d', $row['points']);
			printf('<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
		}
		printf('</table>');
	}

	function table_logins($ipa, $pid, $sid)
	{
		if ($ipa & 0x80000000)
			$ipa -= 1 << 32;
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
		printf('<th>last');
		printf('<th>first');
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
		printf('<th>last');
		printf('<th>first');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $row['c']);
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
		printf('<th>last');
		printf('<th>first');
		while ($row = mysql_fetch_assoc($rows))
		{
			$row['ipa'] &= 0xffffffff;
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
		printf('<tr>');
		printf('<th>count');
		printf('<th align=right>sid');
		printf('<th>name');
		printf('<th>ipa');
		printf('<th>gsku');
		printf('<th>last');
		printf('<th>first');
		while ($row = mysql_fetch_assoc($rows))
		{
			$row['ipa'] &= 0xffffffff;
			printf('<tr>');
			printf('<td align=right>%dx', $row['count']);
			printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td><a href="?a=edit_player;pid=%d">%s</a>', $row['pid'], htmlspecialchars($row['name']));
			printf('<td><a href="?a=show_logins;ipa=%d">%s</a>', $row['ipa'], long2ip($row['ipa']));
			printf('<td>%s', gsku2a($row['gsku'] >> 8, $row['gsku'] & 0xff));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
		}
		printf('</table>');
	}

	function table_messages($pids)
	{
		$rows = db_query($pids == -1
			? "select m.*, p.name from xwi_messages m inner join xwi_players p using (pid) order by mid desc"
			: sprintf("select m.*, p.name from xwi_messages m inner join xwi_players p using (pid) where pid in (%s) order by mid desc", count($pids) ? implode(',', $pids) : '0'));
		if ($row = mysql_fetch_assoc($rows))
		{
			printf('<table>');
			printf('<tr>');
			printf('<th align=right>mid');
			printf('<th>name');
			printf('<th>body');
			printf('<th>created');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="?a=message;mid=%d">%d</a>', $row['mid'], $row['mid']);
				printf('<td><a href="?q=%s">%s</a>', $row['name'], $row['name']);
				printf('<td>%s', htmlspecialchars($row['body']));
				printf('<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
			}
			while ($row = mysql_fetch_assoc($rows));
			printf('</table>');
		}
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
		printf('<th>wtime');
		printf('<th>modified');
		printf('<th>created');
		printf('<th>names');
		while ($row = mysql_fetch_assoc($rows))
		{
			printf('<tr>');
			printf('<td align=right><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td>%s', gsku2a($row['gsku']));
			printf('<td>');
			if ($row['wtime'])
				printf('%s', gmdate('Y-m-d', $row['wtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['mtime']));
			printf('<td>%s', gmdate('Y-m-d', $row['ctime']));
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
		$rows = db_query(sprintf("select distinct wid from xbl_ipas where ipa in (%s)", count($ipas) ? implode(',', $ipas) : '0'));
		while ($row = mysql_fetch_assoc($rows))
			$wids[] = $row['wid'];
		$rows = db_query(sprintf("select distinct wid from xbl_serials where sid in (%s)", count($sids) ? implode(',', $sids) : '0'));
		while ($row = mysql_fetch_assoc($rows))
			$wids[] = $row['wid'];
		$rows = db_query(sprintf("select bl.*, p.name from xbl bl left join xwi_players p using (pid) where wid in (%s) order by wid desc", count($wids) ? implode(',', $wids) : '0'));
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
			printf('<th>created');
			printf('<th>ipas');
			printf('<th>sids');
			do
			{
				printf('<tr>');
				printf('<td align=right><a href="?a=warning;wid=%d">%d</a>', $row['wid'], $row['wid']);
				printf('<td><a href="?q=%s">%s</a>', $row['name'], $row['name']);
				printf('<td>');
				if ($row['link'])
					printf('<a href="%s">link</a>', htmlspecialchars($row['link']));
				printf('<td>%s', htmlspecialchars($row['reason']));
				printf('<td>%s', htmlspecialchars($row['admin']));
				printf('<td align=right>%sd', $row['duration'] / (24 * 60 * 60));
				printf('<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
				printf('<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
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
		$row = db_query_first(sprintf("select p.*, c.name cname, m.member_id, m.name fname, members_display_name, m.email from xwi_players p left join xwi_clans c using (cid) left join st_forum.invision_members m on p.uid = member_id where p.pid = %d", $pid));
		printf('<table>');
		printf('<tr><th>pid<td>%d', $row['pid']);
		printf('<tr><th>sid<td><a href="?a=edit_serial;sid=%d">%d</a>', $row['sid'], $row['sid']);
		printf('<tr><th>server<td>%d', $row['server_id']);
		printf('<tr><th>name<td>%s', htmlspecialchars($row['name']));
		printf('<tr><th>clan<td>');
		if ($row['cid'])
		{
			printf('<a href="?a=edit_clan;cid=%d">%s</a>', $row['cid'], htmlspecialchars($row['cname']));
		}
		printf('<tr><th>flags<td>%s', flags2a($row['flags']));
		if ($row['member_id'])
		{
			printf('<tr><th>forum name<td><a href="http://strike-team.net/forums/?showuser=%d">%s</a>', $row['member_id'], htmlspecialchars($row['fname']));
			if ($row['members_display_name'] != $row['fname'])
				echo(' - ' . htmlspecialchars($row['members_display_name']));
			// printf('<tr><th>forum email<td>%s</a>', htmlspecialchars($row['email']));
		}
		printf('<tr><th>last online<td>%s', gmdate('Y-m-d H:i:s', $row['last_online_time']));
		printf('<tr><th>modified<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
		printf('<tr><th>created<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
		printf('<tr><th><td><a href="?a=warning;pid=%d">-&gt; Black List</a>', $row['pid']);
		printf('<tr><th><td><a href="?a=message;pid=%d">Send Message</a>', $row['pid']);
		if ($row['flags'] & 8)
			printf('<tr><th><td><a href="?a=unrequest_screenshot;pid=%d">Unrequest Screenshot</a>', $row['pid']);
		else
			printf('<tr><th><td><a href="?a=request_screenshot;pid=%d">Request Screenshot</a>', $row['pid']);
		if ($row['flags'] & 2)
			printf('<tr><th><td><a href="?a=undelete_player;pid=%d">Undelete</a>', $row['pid']);
		else
			printf('<tr><th><td><a href="?a=delete_player;pid=%d">Delete</a>', $row['pid']);
		printf('</table>');
		$sids = array();
		$rows = db_query(sprintf("(select distinct sid from xwi_logins1 where pid = %d and mtime > unix_timestamp() - 365 * 24 * 60 * 60) union (select sid from xwi_players where pid = %d)", $pid, $pid));
		while ($row = mysql_fetch_assoc($rows))
			$sids[] = $row['sid'];
		table_messages(array($pid));
		table_warnings(array(), $sids);
		table_serials($sids);
		table_logins(0, $pid, 0);
	}

	function page_message($mid, $pid)
	{
		if (isset($_POST['body']))
		{
			$body = stripslashes($_POST['body']);
			if ($mid)
			{
				if (empty($body))
					return page_delete_message($mid);
				db_query(sprintf("update xwi_messages set body = '%s' where mid = %d", addslashes($body), $mid));
				$row = db_query_first(sprintf("select pid from xwi_messages where mid = %d", $mid));
				$pid = $row['pid'];
			}
			else
			{
				db_query(sprintf("insert into xwi_messages (pid, body, ctime) values (%d, '%s', unix_timestamp())", $pid, addslashes($body)));
				$mid = mysql_insert_id();
			}
			header(sprintf('location: ?a=edit_player;pid=%d', $pid));
			return;
		}
		$row = db_query_first($mid
			? sprintf("select m.*, name from xwi_messages m left join xwi_players using (pid) where mid = %d", $mid)
			: sprintf("select name from xwi_players where pid = %d", $pid));
		printf('<form method=post>');
		printf('<table>');
		if ($row['mid'])
			printf('<tr><th>mid<td>%d', $row['mid']);
		printf('<tr><th>to<td>%s', $row['name']);
		printf('<tr><th>body<td><textarea name=body cols=80 rows=10>%s</textarea>', htmlspecialchars($row['body']));
		if ($row['ctime'])
			printf('<tr><th>created<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
		printf('<tr><th><td><input type=submit value="Send">');
		// printf('<tr><th><td><a href="?a=delete_message;mid=%d">Delete</a>', $row['mid']);
		printf('</table>');
		printf('</form>');
	}

	function page_edit_serial($sid)
	{
		$row = db_query_first(sprintf("select s.*, m.member_id, m.name fname, members_display_name from xwi_serials s left join st_forum.invision_members m on s.uid = member_id where sid = %d", $sid));
		printf('<table>');
		printf('<tr><th>sid<td>%d', $row['sid']);
		printf('<tr><th>gsku<td>%s', gsku2a($row['gsku']));
		if ($row['member_id'])
		{
			printf('<tr><th>forum name<td><a href="http://strike-team.net/forums/?showuser=%d">%s</a>', $row['member_id'], htmlspecialchars($row['fname']));
			if ($row['members_display_name'] != $row['fname'])
				echo(' - ' . htmlspecialchars($row['members_display_name']));
		}
		printf('<tr><th>wtime<td>');
		if ($row['wtime'])
			printf('%s', gmdate('Y-m-d H:i:s', $row['wtime']));
		printf('<tr><th>modified<td>%s', gmdate('Y-m-d H:i:s', $row['mtime']));
		printf('<tr><th>created<td>%s', gmdate('Y-m-d H:i:s', $row['ctime']));
		printf('</table>');
		$pids = array();
		$rows = db_query(sprintf("(select distinct pid from xwi_logins1 where sid = %d and mtime > unix_timestamp() - 365 * 24 * 60 * 60) union (select distinct pid from xwi_players where sid = %d)", $sid, $sid));
		while ($row = mysql_fetch_assoc($rows))
			$pids[] = $row['pid'];
		table_messages($pids);
		table_warnings(array(), array($sid));
		table_players($pids);
		table_logins(0, 0, $sid);
		table_login_failures(0, '', $sid);
	}

	function page_user($uid)
	{
		$row = db_query_first(sprintf("select member_id, member_group_id, name, members_display_name from st_forum.invision_members where member_id = %d", $uid));
		printf('<table>');
		printf('<tr><th>uid<td>%d', $row['member_id']);
		printf('<tr><th>gid<td>%d', $row['member_group_id']);
		printf('<tr><th>forum name<td><a href="http://strike-team.net/forums/?showuser=%d">%s</a>', $row['member_id'], htmlspecialchars($row['members_display_name']));
		if ($row['members_display_name'] != $row['name'])
			echo(' - ' . htmlspecialchars($row['name']));
		$rows = db_query(sprintf("select distinct sid from xwi_serials where uid = %d", $uid));
		while ($row = mysql_fetch_assoc($rows))
			$sids[] = $row['sid'];
		printf('</table>');
		table_serials($sids);
	}

	function insert_admin_log($pid, $sid, $message)
	{
		global $remote_user;
		db_query(sprintf("insert into xwi_admin_log (administrator, pid, sid, message, time) values ('%s', %d, %d, '%s', unix_timestamp())",
			addslashes($remote_user), $pid, $sid, addslashes($message)));
	}

	function page_delete_message($mid)
	{
		$row = db_query_first(sprintf("select * from xwi_messages where mid = %d", $mid));
		if ($row)
		{
			insert_admin_log($row['pid'], 0, 'deleted message ' . $mid);
			db_query(sprintf("delete from xwi_messages where mid = %d", $mid));
		}
		header(sprintf('location: ?a=edit_player;pid=%d', $row['pid']));
	}

	function page_delete_player($pid)
	{
		$row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid));
		if ($row && !($row['flags'] & 2))
		{
			insert_admin_log($pid, 0, 'deleted player ' . $row['name']);
			db_query(sprintf("update xwi_players set flags = flags | 2 where pid = %d", $pid));
		}
		header(sprintf('location: ?a=edit_player;pid=%d', $pid));
	}

	function page_undelete_player($pid)
	{
		$row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid));
		if ($row && $row['flags'] & 2)
		{
			insert_admin_log($pid, 0, 'undeleted player ' . $row['name']);
			db_query(sprintf("update xwi_players set flags = flags & ~2 where pid = %d", $pid));
		}
		header(sprintf('location: ?a=edit_player;pid=%d', $pid));
	}

	function page_request_screenshot($pid)
	{
		$row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid));
		if ($row && !($row['flags'] & 8))
		{
			insert_admin_log($pid, 0, 'request screenshot from ' . $row['name']);
			db_query(sprintf("update xwi_players set flags = flags | 8 where pid = %d", $pid));
		}
		header(sprintf('location: ?a=edit_player;pid=%d', $pid));
	}

	function page_unrequest_screenshot($pid)
	{
		$row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid));
		if ($row && $row['flags'] & 8)
		{
			insert_admin_log($pid, 0, 'unrequest screenshot from ' . $row['name']);
			db_query(sprintf("update xwi_players set flags = flags & ~8 where pid = %d", $pid));
		}
		header(sprintf('location: ?a=edit_player;pid=%d', $pid));
	}

	function page_black_list()
	{
		$results = db_query("select b.*, p.name from xbl b left join xwi_players p using (pid) order by wid desc limit 1000");
		echo('<table>');
		while ($row = mysql_fetch_array($results))
		{
			printf('<tr><td align=right><a href="?a=warning;wid=%d">%d</a><td><a href=".?q=%s">%s</a><td>', $row['wid'], $row['wid'], $row['name'], $row['name']);
			if ($row['link'])
				printf('<a href="%s">link</a>', htmlspecialchars($row['link']));
			printf("<td align=right>%d<td>%s<td>%s<td>%s", $row['duration'] / (24 * 60 * 60), htmlspecialchars($row[reason]), htmlspecialchars($row[admin]), gmdate("H:i d-m-Y", $row[mtime]));
		}
		echo('</table>');
		echo('<hr>');
		$results = db_query("select * from xbl_ipas order by wid desc");
		echo('<table>');
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr>');
			printf('<td align=right><a href="?a=warning;wid=%d">%d</a>', $result['wid'], $result['wid']);
			printf('<td>%s', long2ip($result['ipa']));
			printf('<td>%s', htmlspecialchars($result['creator']));
			printf('<td>%s', gmdate("H:i d-m-Y", $result['ctime']));
		}
		echo('</table>');
	}

	function page_warning($wid, $pid)
	{
		global $remote_user;
		if (!$wid)
		{
			if ($row = db_query_first(sprintf("select * from xwi_players where pid = %d", $pid)))
			{
				$name = $row['name'];
				$link = trim($_REQUEST['link']);
				$reason = trim($_REQUEST['reason']);
				$dura = isset($_REQUEST['dura']) ? $_REQUEST['dura'] : 32;
				if ($reason)
				{
					db_query(sprintf("insert into xbl (pid, admin, link, reason, duration, mtime, ctime) values (%d, '%s', '%s', '%s', %d, unix_timestamp(), unix_timestamp())", $pid, addslashes($remote_user), addslashes($link), addslashes($reason), 24 * 60 * 60 * $dura));
					header(sprintf('location: ?a=warning;wid=%d', mysql_insert_id()));
					return;
				}
				require('../../b/templates/bl_insert.php');
				return;
			}
		}
		$row = db_query_first(sprintf("select b.*, p.name from xbl b left join xwi_players p using (pid) where wid = %d", $wid));
		if (!$row)
			return;
		if ($_REQUEST['a2'] == "update")
		{
			$duration = $_REQUEST['duration'];
			$link = trim($_REQUEST['link']);
			$motd = trim($_REQUEST['motd']);
			$reason = trim($_REQUEST['reason']);
			db_query(sprintf("update xbl set duration = %d, link = '%s', reason = '%s', mtime = unix_timestamp() where wid = %d", 24 * 60 * 60 * $duration, addslashes($link), addslashes($reason), $wid));
			header(sprintf('location: ?a=warning;wid=%d', $wid));
		}
		$ipa = $_REQUEST['ipa'];
		$sid = 0 + $_REQUEST['sid'];
		switch ($_REQUEST['a2'])
		{
		case 'delete_ipa':
			db_query(sprintf("delete from xbl_ipas where ipa = %d and wid = %d", $ipa, $wid));
			header(sprintf('location: ?a=warning;wid=%d', $wid));
			return;
		case 'insert_ipa':
			if ($ipa)
				db_query(sprintf("insert ignore into xbl_ipas (wid, ipa, creator, ctime) values (%d, %d, '%s', unix_timestamp())", $wid, ip2long($ipa), addslashes($remote_user)));
			header(sprintf('location: ?a=warning;wid=%d', $wid));
			return;
		case 'insert_serial':
			if ($sid)
				db_query(sprintf("insert ignore into xbl_serials (wid, sid, creator, ctime) values (%d, %d, '%s', unix_timestamp())", $wid, $sid, addslashes($remote_user)));
			header(sprintf('location: ?a=warning;wid=%d', $wid));
			return;
		}
		$creator = $row['admin'];
		$ctime = gmdate("H:i d-m-Y", $row['ctime']);
		$duration = htmlspecialchars(ceil($row['duration'] / (24 * 60 * 60)));
		$link = htmlspecialchars($row['link']);
		$mtime = gmdate("H:i d-m-Y", $row['mtime']);
		$motd = htmlspecialchars($row['motd']);
		$name = htmlspecialchars($row['name']);
		$reason = htmlspecialchars($row['reason']);
		$sid = $row['sid'];
		include('../../b/templates/show_warning.php');
		echo('<hr>');
		echo('<table>');
		$results = db_query(sprintf("select * from xbl_ipas where wid = %d", $wid));
		while ($row = mysql_fetch_array($results))
		{
			$row['ipa'] &= 0xffffffff;
			echo('<tr>');
			printf('<td><a href=".?q=%s">%s</a>', long2ip($row['ipa']), long2ip($row['ipa']));
			printf('<td>%s', $row['creator']);
			printf('<td>%s', gmdate("H:i d-m-Y", $row['ctime']));
			printf('<td><a href="?a=warning;a2=delete_ipa;ipa=%d;wid=%d">delete</a>', $row['ipa'], $wid);
		}
		echo('</table>');
		echo('<hr>');
		include('../../b/templates/edit_warning_insert_ipa.php');
		echo('<hr>');
		echo('<table>');
		$results = db_query(sprintf("select * from xbl_serials where wid = %d", $wid));
		while ($row = mysql_fetch_array($results))
		{
			echo('<tr>');
			printf('<td align=right><a href=".?q=%d">%d</a>', $row['sid'], $row['sid']);
			printf('<td>%s', $row['creator']);
			printf('<td>%s', gmdate("H:i d-m-Y", $row['ctime']));
		}
		echo('</table>');
		echo('<hr>');
		include('../../b/templates/edit_warning_insert_serial.php');
	}

	require_once(dirname(__FILE__) . '/common.php');
	$remote_user = $_SERVER['REMOTE_USER'];
	if (empty($remote_user))
		die();
	db_connect();
	$a = $_REQUEST['a'];
	$ipa = $_REQUEST['ipa'];
	$pid = 0 + $_REQUEST['pid'];
	$search = trim($_REQUEST[isset($_REQUEST['q']) ? 'q' : 'search']);
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
	case 'black_list':
		page_black_list();
		break;
	case 'delete_message':
		page_delete_message($_REQUEST['mid']);
		break;
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
	case 'message':
		page_message($_REQUEST['mid'], $pid);
		break;
	case 'messages':
		table_messages(-1);
		break;
	case 'request_screenshot':
		page_request_screenshot($pid);
		break;
	case 'unrequest_screenshot':
		page_unrequest_screenshot($pid);
		break;
	case 'search':
		page_search_results($search);
		break;
	case 'show_logins':
		table_logins($ipa, 0, 0);
		table_login_failures($ipa, '', 0);
		break;
	case 'user':
		page_user($_REQUEST['uid']);
		break;
	case 'warning':
		page_warning($_REQUEST['wid'], $pid);
		break;
	}
