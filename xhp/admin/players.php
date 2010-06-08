<?php
	require_once('config.php');
	require_once('../../b/common.php');

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
	}
