<?php
	require_once('common.php');

	header("refresh: 60");
	require('templates/links.php');
	echo('<hr>');
	require('templates/search.php');
	echo('<hr>');
	$ipa = $_GET[ipa];
	$pid = $_GET[pid];
	$pname = trim($_GET[pname]);
	$sid = $_GET[sid];
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
		$where = sprintf(" where name like \"%s\"", AddSlashes($pname));
	else if ($sid)
		$where = sprintf(" where l.sid = %d", $sid);
	else
		$where = "";
	$results = db_query(sprintf("select name, l.ipa, valid, l.gsku, l.sid, time from xwi_players inner join xwi_logins l using (pid) inner join xwi_serials using (sid)%s order by time desc%s", $where, $where ? "" : " limit 250"));
	echo("<table>");
	while ($result = mysql_fetch_array($results))
	{
		printf("<tr><td><a href=\"?pname=%s\">%s<td><a href=\"players.php?pname=%s\">P<td><a href=\"?ipa=%d\">%s</a><td>%d<td align=right>%x<td align=right><a href=\"?sid=%d\">%d</a><td>%s",
			$result[name], $result[name], $result[name], $result[ipa], long2ip($result[ipa]), $result[valid], $result[gsku], $result[sid], $result[sid], gmdate("H:i:s d-m-Y", $result[time]));
	}
	echo("</table>");
	if ($where)
	{
		$results = db_query(sprintf("select ipa, count(*) c from xwi_logins l inner join xwi_players using (pid)%s group by ipa", $where));
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s<td>%s", $result[c], long2ip($result[ipa]), gethostbyaddr(long2ip($result[ipa])));
		echo("</table>");
		$results = db_query(sprintf("select gsku, count(*) c from xwi_logins l inner join xwi_players using (pid) %s group by gsku", $where));
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td align=right>%x", $result[c], $result[gsku]);
		echo("</table>");
		$results = db_query(sprintf("select xwi_serials.*, unix_timestamp(xwi_serials.mtime) as mtime, unix_timestamp(xwi_serials.wtime) as wtime, count(*) c from xwi_serials inner join xwi_logins l using (sid) inner join xwi_players using (pid) %s group by sid", $where));
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td align=right><a href=\"?sid=%d\">%d</a><td align=right>%x<td align=right>%d<td>%s<td>%s", $result[c], $result[sid], $result[sid], $result[gsku], $result[valid], gmdate("H:i d-m-Y", $result[mtime]), $result[wtime] ? gmdate("H:i d-m-Y", $result[wtime]) : "");
		echo("</table>");
	}
	echo('<hr>');
	require('templates/links.php');
?>