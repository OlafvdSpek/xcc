<?php
	require_once('b/config.php');
	require_once('b/common.php');

	db_connect();
	require('templates/top.php');
	require('templates/links.php');
	echo('<hr>');
	require('templates/search.php');
	echo('<hr>');
	$ipa = $_REQUEST['ipa'];
	$pid = $_REQUEST['pid'];
	$pname = trim($_REQUEST['pname']);
	$sid = $_REQUEST['sid'];
	if (strlen($pname) && ip2long($pname) != -1)
		$ipa = ip2long($pname);
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
	else if ($pname)
		$where = sprintf(" where name like '%s'", AddSlashes($pname));
	else if ($sid)
		$where = sprintf(" where l.sid = %d", $sid);
	else
		$where = " where 0 = 1";
	$results = db_query(sprintf("select name, l.ipa, valid, l.gsku, l.sid, l.count, l.mtime, l.ctime from xwi_players inner join xwi_logins1 l using (pid) inner join xwi_serials s on l.sid = s.sid%s order by mtime desc%s", $where, $where ? "" : " limit 250"));
	echo('<table>');
	while ($result = mysql_fetch_array($results))
	{
		printf('<tr>');
		printf('<td align=right>%dx', $result['count']);
		printf('<td><a href="?pname=%s">%s', $result['name'], $result['name']);
		printf('<td><a href="players.php?pname=%s">P', $result['name']);
		printf('<td><a href="?ipa=%d">%s</a>', $result['ipa'], long2ip($result['ipa']));
		printf('<td align=right>%x', $result['gsku']);
		printf('<td align=right><a href="?sid=%d">%d</a>', $result['sid'], $result['sid']);
		printf('<td>%s', gmdate("H:i:s d-m-Y", $result['mtime']));
		printf('<td>%s', gmdate("H:i:s d-m-Y", $result['ctime']));
	}
	echo("</table>");
	if ($where)
	{
		$results = db_query(sprintf("select name, sum(count) c from xwi_logins1 l inner join xwi_players using (pid)%s group by name order by c desc", $where));
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $result['c']);
			printf('<td><a href="?pname=%s">%s', $result['name'], $result['name']);
			printf('<td><a href="players.php?pname=%s">P', $result['name']);
		}
		echo("</table>");
		$results = db_query(sprintf("select ipa, sum(count) c from xwi_logins1 l inner join xwi_players using (pid)%s group by ipa order by c desc", $where));
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $result['c']);
			printf('<td><a href="?ipa=%d">%s</a>', $result['ipa'], long2ip($result['ipa']));
			printf('<td>%s', gethostbyaddr(long2ip($result['ipa'])));
		}
		echo("</table>");
		$results = db_query(sprintf("select gsku, sum(count) c from xwi_logins1 l inner join xwi_players using (pid) %s group by gsku order by c desc", $where));
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $result['c']);
			printf('<td align=right>%x', $result['gsku']);
		}
		echo('</table>');
		$results = db_query(sprintf("select xwi_serials.*, sum(count) c from xwi_serials inner join xwi_logins1 l using (sid) inner join xwi_players using (pid) %s group by sid order by c desc", $where));
		echo('<hr><table>');
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr>');
			printf('<td align=right>%dx', $result['c']);
			printf('<td align=right><a href="?sid=%d">%d</a>', $result['sid'], $result['sid']);
			printf('<td align=right>%x', $result['gsku']);
			printf('<td align=right>%d', $result['valid']);
			printf('<td>%s', gmdate('H:i d-m-Y', $result['mtime']));
			if ($result['wtime'])
				printf('<td>%s', gmdate('H:i d-m-Y', $result['wtime']));
		}
		echo('</table>');
	}
?>