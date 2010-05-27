<?php
	require_once('config.php');
	require_once('../../b/common.php');

	function select_players($where)
	{
		return db_query(sprintf("select p.sid, p.pid, p.pass, p.name as pname, p.flags, c.name as cname, motd, p.mtime, p.ctime from xwi_serials s inner join xwi_players p using (sid) left join xwi_clans c using (cid)%s order by p.name", $where));
	}

	function echo_players($results)
	{
		while ($result = mysql_fetch_array($results))
		{
			$motd = trim($result['motd']);
			printf('<tr><td><a href=".?q=%s">%s</a>', $result[pname], $result[pname]);
			printf('<td>%s', $result[flags] & 2 ? '*' : '');
			printf('<td>%s', $result[cname]);
			printf('<td><a href="logins.php?pid=%d">L</a>', $result[pid]);
			printf('<td align=right><a href="?sid=%d">%d</a>', $result[sid], $result[sid]);
			printf('<td>%s<td>%s', gmdate("d-m-Y", $result[mtime]), gmdate("d-m-Y", $result[ctime]));
			printf('<td><a href="?a=motd&pid=%d">%s</a>', $result['pid'], $motd ? nl2br(htmlspecialchars(substr($motd, 0, 80))) : 'motd');
		}
	}

	function echo_warning($result)
	{
		printf('<tr><td align=right><a href="?a=show_warning;wid=%d">%d</a><td><a href=".?q=%s">%s</a><td>', $result['wid'], $result['wid'], $result['name'], $result['name']);
		if ($result[link])
			printf('<a href="%s">link</a>', htmlspecialchars($result[link]));
		printf("<td align=right>%d<td>%s<td>%s<td>%s", $result['duration'] / (24 * 60 * 60), htmlspecialchars($result[reason]), htmlspecialchars($result[admin]), gmdate("H:i d-m-Y", $result[mtime]));
	}

	function echo_warnings($results)
	{
		while ($result = mysql_fetch_array($results))
			echo_warning($result);
	}

	$remote_user = $_SERVER['REMOTE_USER'];
	if (empty($remote_user))
		die();
	db_connect();
	require('../../b/templates/top.php');
	require('../../b/templates/links.php');
	echo('<hr>');
	require('../../b/templates/search.php');
	echo('<hr>');
	$pname = trim($_REQUEST[pname]);
	switch ($_REQUEST['a'])
	{
	case 'chat':
		$offset = $_GET['offset'];
		$nids = array(0);
		$rows = db_query(sprintf("select nid from xwi_names where name like '%s'", addslashes($pname)));
		while ($row = mysql_fetch_assoc($rows))
		{
			// printf('%d<br>', $row['nid']);
			$nids[] = $row['nid'];
		}
		$chat_ids = array(0);
		$rows = db_query(sprintf("select chat_id from xwi_chat_to where nid in (%s) order by chat_id desc limit 10000", implode(',', $nids)));
		while ($row = mysql_fetch_assoc($rows))
		{
			// printf('%d<br>', $row['chat_id']);
			$chat_ids[] = $row['chat_id'];
		}
		$rows = db_query(sprintf("select c.*, name from xwi_chat1 c left join xwi_names on `from` = nid where chat_id in (%s) or `from` in (%s) order by chat_id desc", implode(',', $chat_ids), implode(',', $nids)));
		printf('<table>');
		while ($row = mysql_fetch_assoc($rows))
		{
			$to = '';
			$rows1 = db_query(sprintf("select name from xwi_chat_to inner join xwi_names using (nid) where chat_id = %d", $row['chat_id']));
			while ($row1 = mysql_fetch_assoc($rows1))
			{
				$to .= sprintf('%s<br>', htmlspecialchars($row1['name']));
			}
			printf('<tr>');
			// printf('<td align=right>%d', $row['chat_id']);
			printf('<td nowrap>%s', gmdate('H:i:s d-m-Y', $row['time']));
			printf('<td>%s', htmlspecialchars($row['name']));
			printf('<td>%s', $to);
			printf('<td>%s', htmlspecialchars($row['msg']));
		}
		printf('</table>');
		// printf('<a href="?a=chat;pname=%s;offset=%d">Next</a>', urlencode($pname), $offset + 1000);
		break;
	case 'bl_insert':
	case 'bl_insert_submit':
		$pid = $_REQUEST[pid];
		if ($result = mysql_fetch_array(db_query(sprintf("select * from xwi_players where pid = %d", $pid))))
		{
			$name = $result[name];
			$link = trim($_REQUEST['link']);
			$reason = trim($_REQUEST['reason']);
			$dura = $_REQUEST[dura] ? $_REQUEST[dura] : 32;
			if ($_REQUEST['a'] == "bl_insert_submit" && $name && $reason)
			{
				db_query(sprintf("insert into xbl (admin, name, link, reason, duration, mtime, ctime) values ('%s', '%s', '%s', '%s', %d, unix_timestamp(), unix_timestamp())",
					addslashes($remote_user), $name, addslashes($link), addslashes($reason), 24 * 60 * 60 * $dura));
			}
		}
		require('../../b/templates/bl_insert.php');
		break;
	case 'bad_passes':
		$results = db_query("select flags, name from xwi_players inner join bad_passes using (pass) where ~flags & 2 order by name");
		echo('<table>');
		while ($result = mysql_fetch_array($results))
			printf('<tr><td><a href="?pname=%s">%s</a><td>%s', $result['name'], $result['name'], $result[flags] & 2 ? '*' : '');
		echo('</table>');
		break;
	case 'games':
		$results = db_query(sprintf("select gid, ipa, sid, p.name, c.name cname from xcl_games_players gp inner join xcl_players p using (pid) left join xcl_players c on (gp.cid = c.pid) where p.name like '%s' order by gid desc", $pname));
		echo('<table>');
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr><td align=right><a href="http://xwis.net/ladders/games/%d/">%d</a><td><a href="logins.php?ipa=%d">%s</a><td align=right><a href="logins.php?sid=%d">%d</a><td>%s<td>%s',
				$result['gid'], $result['gid'], $result['ipa'], long2ip($result['ipa']), $result['sid'], $result['sid'], $result['name'], $result['cname']);
		}
		echo('</table>');
		break;
	case 'xbl':
		$results = db_query("select * from xbl order by wid desc limit 1000");
		echo('<table>');
		echo_warnings($results);
		echo('</table>');
		echo('<hr>');
		$results = db_query("select * from xbl_ipas order by wid desc");
		echo('<table>');
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr>');
			printf('<td align=right><a href="?a=show_warning;wid=%d">%d</a>', $result['wid'], $result['wid']);
			printf('<td>%s', long2ip($result['ipa']));
			printf('<td>%s', htmlspecialchars($result['creator']));
			printf('<td>%s', gmdate("H:i d-m-Y", $result['ctime']));
		}
		echo('</table>');
		break;
	case 'edit_warning_submit':
	case 'edit_warning_delete_ipa_submit':
	case 'edit_warning_insert_ipa_submit':
	case 'edit_warning_delete_serial_submit':
	case 'edit_warning_insert_serial_submit':
	case 'show_warning':
		$wid = $_REQUEST['wid'];
		if ($_REQUEST['a'] == 'edit_warning_submit')
		{
			$duration = $_REQUEST['duration'];
			$link = trim($_REQUEST['link']);
			$motd = trim($_REQUEST['motd']);
			$reason = trim($_REQUEST['reason']);
			db_query(sprintf("update xbl set duration = %d, motd = '%s', link = '%s', reason = '%s', mtime = unix_timestamp() where wid = %d",
				24 * 60 * 60 * $duration, addslashes($motd), addslashes($link), addslashes($reason), $wid));
		}
		$results = db_query(sprintf("select * from xbl where wid = %d", $wid));
		if ($row = mysql_fetch_array($results))
		{
			$ipa = $_REQUEST['ipa'];
			$sid = 0 + $_REQUEST['sid'];
			switch ($_REQUEST['a'])
			{
			case 'edit_warning_delete_ipa_submit':
				db_query(sprintf("delete from xbl_ipas where ipa = %d and wid = %d", $ipa, $wid));
				break;
			case 'edit_warning_insert_ipa_submit':
				if ($ipa)
					db_query(sprintf("insert ignore into xbl_ipas (wid, ipa, creator, ctime) values (%d, %d, '%s', unix_timestamp())", $wid, ip2long($ipa), addslashes($remote_user)));
				break;
				/*
			case 'edit_warning_delete_serial_submit':
				db_query(sprintf("delete from xbl_serials where sid = %d and wid = %d", $sid, $wid));
				break;
				*/
			case 'edit_warning_insert_serial_submit':
				if ($sid)
					db_query(sprintf("insert ignore into xbl_serials (wid, sid, creator, ctime) values (%d, %d, '%s', unix_timestamp())", $wid, $sid, addslashes($remote_user)));
				break;
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
				echo('<tr>');
				printf('<td><a href=".?q=%s">%s</a>', long2ip($row['ipa']), long2ip($row['ipa']));
				printf('<td>%s', $row['creator']);
				printf('<td>%s', gmdate("H:i d-m-Y", $row['ctime']));
				printf('<td><a href="?a=edit_warning_delete_ipa_submit;ipa=%d;wid=%d">delete</a>', $row['ipa'], $wid);
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
				// printf('<td><a href="?a=edit_warning_delete_serial_submit;sid=%d;wid=%d">delete</a>', $row['sid'], $wid);
			}
			echo('</table>');
			echo('<hr>');
			include('../../b/templates/edit_warning_insert_serial.php');
		}
		break;
	case 'washers':
		function compare0($a, $b)
		{
			return $a < $b ? -1 : $a != $b;
		}

		function compare($a, $b)
		{
			switch ($_REQUEST['o'])
			{
			case 1: return compare0($b['dc'], $a['dc']);
			case 2: return compare0($b['oos'], $a['oos']);
			case 3: return compare0($b['loss_count'] ? $b['c'] / $b['loss_count'] : 9999, $a['loss_count'] ? $a['c'] / $a['loss_count'] : 9999);
			case 4: return compare0($b['loss_count'] ? $b['dc'] / $b['loss_count'] : 9999, $a['loss_count'] ? $a['dc'] / $a['loss_count'] : 9999);
			case 5: return compare0($b['loss_count'] ? $b['oos'] / $b['loss_count'] : 9999, $a['loss_count'] ? $a['oos'] / $a['loss_count'] : 9999);
			}
			return compare0($b['c'], $a['c']);
		}

		$results = db_query_all("select pid, name, win_count, loss_count, points, count(*) c, sum(cmp = 2) dc, sum(oosy) oos from xcl_games inner join xcl_games_players using (gid) inner join xcl_players p using (pid) where p.lid < 17 and (cmp = 2 or oosy) and points group by pid having c >= 4 or oos >= 2");
		usort($results, compare);
		echo('<table id=players>');
		printf('<tr>');
		printf('<th>Name');
		printf('<th>L');
		printf('<th><a href="?a=washers;o=0#players">Washes</a>');
		printf('<th>Wins');
		printf('<th>Losses');
		printf('<th>Points');
		printf('<th><a href="?a=washers;o=1#players">DC</a>');
		printf('<th><a href="?a=washers;o=2#players">OoS</a>');
		printf('<th><a href="?a=washers;o=3#players">W</a>');
		printf('<th><a href="?a=washers;o=4#players">DC</a>');
		printf('<th><a href="?a=washers;o=5#players">OoS</a>');
		foreach ($results as $result)
		{
			printf('<tr>');
			printf('<td><a href=".?q=%s">%s</a>', htmlspecialchars($result['name']), htmlspecialchars($result['name']));
			printf('<td><a href="%s?q=%s">L</a>', $config['ladder_url'], $result['name']);
			printf('<td align=right>%d', $result['c']);
			printf('<td align=right>%d', $result['win_count']);
			printf('<td align=right>%d', $result['loss_count']);
			printf('<td align=right>%d', $result['points']);
			printf('<td align=right>%d', $result['dc']);
			printf('<td align=right>%d', $result['oos']);
			if ($result['loss_count'])
			{
				printf('<td align=right>%.2f', $result['c'] / $result['loss_count']);
				printf('<td align=right>%.2f', $result['dc'] / $result['loss_count']);
				printf('<td align=right>%.2f', $result['oos'] / $result['loss_count']);
			}
			else
				echo('<td><td><td>');
		}
		echo('</table>');
		echo('<hr>');
		$results = db_query_all("select p.pid, name, win_count, loss_count, points, count(*) c, sum(cmp = 2) dc, sum(oosy) oos from xcl_games inner join xcl_games_players gp using (gid) inner join xcl_players p on gp.cid = p.pid where lid < 17 and (cmp = 2 or oosy) and points group by pid having c >= 1");
		usort($results, compare);
		echo('<table id=clans>');
		printf('<tr>');
		printf('<th>Name');
		printf('<th>L');
		printf('<th><a href="?a=washers;o=0#clans">Washes</a>');
		printf('<th>Wins');
		printf('<th>Losses');
		printf('<th>Points');
		printf('<th><a href="?a=washers;o=1#clans">DC</a>');
		printf('<th><a href="?a=washers;o=2#clans">OoS</a>');
		printf('<th><a href="?a=washers;o=3#clans">W</a>');
		printf('<th><a href="?a=washers;o=4#clans">DC</a>');
		printf('<th><a href="?a=washers;o=5#clans">OoS</a>');
		foreach ($results as $result)
		{
			printf('<tr>');
			printf('<td><a href=".?q=%s">%s</a>', htmlspecialchars($result['name']), htmlspecialchars($result['name']));
			printf('<td><a href="%s?q=%s">L</a>', $config['ladder_url'], $result['name']);
			printf('<td align=right>%d', $result['c']);
			printf('<td align=right>%d', $result['win_count']);
			printf('<td align=right>%d', $result['loss_count']);
			printf('<td align=right>%d', $result['points']);
			printf('<td align=right>%d', $result['dc']);
			printf('<td align=right>%d', $result['oos']);
			if ($result['loss_count'])
			{
				printf('<td align=right>%.2f', $result['c'] / $result['loss_count']);
				printf('<td align=right>%.2f', $result['dc'] / $result['loss_count']);
				printf('<td align=right>%.2f', $result['oos'] / $result['loss_count']);
			}
			else
				echo('<td><td><td>');
		}
		echo('</table>');
		break;
	default:
		$cname = trim($_REQUEST[cname]);
		$pid = $_REQUEST[pid];
		$sid = $_REQUEST[sid];
		if (is_numeric($pname))
		{
			$sid = $pname;
			unset($pname);
		}
		if ($_REQUEST['a'] == "motds")
			$where = " where ~flags & 2 and motd != ''";
		else if ($cname)
			$where = sprintf(" where c.name like '%s'", addslashes($cname));
		else if ($pid)
			$where = sprintf(" where pid = %d", $pid);
		else if ($pname)
			$where = sprintf(" where p.name like '%s'", addslashes($pname));
		else if ($sid)
			$where = sprintf(" where p.sid = %d", $sid);
		else
			$where = " where 0";
		echo("<table><tr><th align=left>Player<th><th align=left>Clan<th><th align=right>SID<th align=left>Mtime<th align=left>Ctime");
		echo_players(select_players($where));
		echo('</table>');
	}
