<?php
	ob_start('ob_gzhandler');
?>
<link rel=stylesheet href="/xcc.css">
<a href="?">Home</a> | <a href="logins.php">Logins</a> | <a href="?a=bad_passes">Bad passes</a> | <a href="?a=invalid_serials">Invalid serials</a> | <a href="?a=update_bl">Update BL</a> | <a href="?a=xbl">Show BL</a> | <a href="?a=motds">Show MOTDs</a> | <a href="?a=xwsvs">XWSVS</a>
<hr>
<table><form><tr><td><input type=text name=pname> <input type=submit value="Search"></tr></form></table>
<?php
	require("../xcc_common.php");

	db_connect();

	function select_players($where)
	{
		return db_query(sprintf("select p.sid, p.pid, p.pass, p.name as pname, p.flags, c.name as cname, motd, unix_timestamp(p.mtime) as mtime, unix_timestamp(p.ctime) as ctime from xwi_serials s inner join xwi_players p using (sid) left join xwi_clans c using (cid)%s order by p.name", $where));
	}

	function echo_players($results)
	{
		while ($result = mysql_fetch_array($results))
		{
			printf('<tr><td><a href="?pid=%d">%s</a><td>%s<td>%s<td><a href="logins.php?pid=%d">L</a><td><a href="/xcl/?pname=%s">P</a><td><a href="/xcl/?pname=%s">C</a><td align=right><a href="?sid=%d">%d</a><td>', $result[pid], $result[pname], $result[pass] && !($result[flags] & 2) ? "" : "*", $result[cname], $result[pid], $result[pname], $result[cname], $result[sid], $result[sid]);
			printf('<a href="?a=bl_insert&pid=%d">-&gt;BL</a>', $result[pid]);
			printf('<td><a href="?a=rb_insert&pid=%d">-&gt;RB</a>', $result[pid]);
			printf('<td>%s<td>%s', gmdate("d-m-Y", $result[mtime]), gmdate("d-m-Y", $result[ctime]));
			printf('<td><a href="?a=motd&pid=%d">%s</a>', $result[pid], $result[motd] ? nl2br(htmlspecialchars(substr($result[motd], 0, 80))) : "motd");
		}
	}

	function echo_warning($result)
	{
		printf('<tr><td align=right>%d<td><a href="?pname=%s">%s</a><td>', $result[wid], $result[name], $result[name]);
		if ($result[link])
			printf('<a href="%s">link</a>', htmlspecialchars($result[link]));
		printf("<td>%s<td>%s<td>%s", htmlspecialchars($result[reason]), htmlspecialchars($result[admin]), gmdate("H:i d-m-Y", $result[mtime]));
	}

	function echo_warnings($results)
	{
		while ($result = mysql_fetch_array($results))
			echo_warning($result);
	}

	function update_bl()
	{
		db_query("delete from bl");
		db_query("insert into bl select distinct p.name from xwi_players p inner join xwi_serials using (sid) where wtime > now()");
		// db_query("insert ignore into bl select distinct p.name from xbl inner join xwi_logins l using (sid) inner join xwi_players p using (pid)");
		// select distinct p1.name from xbl inner join xwi_players p0 using (name) inner join xwi_logins using (pid) inner join xwi_players p1 using (sid);
	}

	echo("<hr>");
	if ($_GET[a] == "motd" || $_GET[a] == "motd_submit")
	{
		$pid = $_GET[pid];
		$results = db_query(sprintf("select p.*, s.motd from xwi_players p inner join xwi_serials s using (sid) where pid = %d", $pid));
		$result = mysql_fetch_array($results);
		$name = $result[name];
		$sid = $result['sid'];

		if ($_GET[a] == "motd_submit" && name)
		{
			$motd = $_GET[motd];
			db_query(sprintf("update xwi_logins l inner join xwi_serials s using (sid) set s.motd = '%s' where l.pid = %d", addslashes($motd), $pid));
			db_query(sprintf("update xwi_serials set motd = '%s' where sid = %d", addslashes($motd), $sid));
			echo("<b>Updated!</b><hr>");
		}
		else
			$motd = $result[motd];
?>
<table>
	<form method=get>
		<input type=hidden name=a value="motd_submit">
		<input type=hidden name=pid value="<?php printf("%d", $pid) ?>">
		<tr><td align=right>Name:<td><a href="?pid=<?php echo $pid ?>"><?php echo $name ?></a>
		<tr><td align=right>Message:<td><textarea name=motd cols=80 rows=10><?php echo htmlspecialchars($motd) ?></textarea>
		<tr><td><td><input type=submit></tr>
	</form>
</table>
<?php
	}
	else if ($_GET[a] == "bl_insert" || $_GET[a] == "bl_insert_submit")
	{
		$pid = $_GET[pid];
		$results = db_query(sprintf("select * from xwi_players where pid = %d", $pid));
		$result = mysql_fetch_array($results);
		$sid = $result[sid];
		$name = $result[name];
		$link = $_GET[link];
		$reason = $_GET[reason];
		$dura = $_GET[dura] ? $_GET[dura] : 4;
		if ($_GET[a] == "bl_insert_submit" && $name && $reason)
		{
			db_query(sprintf("insert into xbl (admin, sid, name, link, reason) values ('%s', %d, '%s', '%s', '%s')", AddSlashes($_SERVER[REMOTE_USER]), $sid, $name, AddSlashes($link), AddSlashes($reason)));
			// db_query(sprintf("update xwi_serials set wtime = from_days(to_days(now()) + %d) where sid = %d", $dura, $sid));

			$results = db_query(sprintf("select distinct l.sid from xwi_logins l inner join xwi_players using (pid) where name = '%s'", addslashes($name)));
			$sids = array();
			$sids[] = $sid;
			while ($result = mysql_fetch_array($results))
				$sids[] = $result[sid];
			db_query(sprintf("update xwi_serials set wtime = from_days(to_days(now()) + %d) where sid in (%s)", $dura, addslashes(implode(",", $sids))));
			update_bl();
		}
		?>
<table>
	<form method=get>
		<input type=hidden name=a value="bl_insert_submit">
		<input type=hidden name=pid value="<?php printf("%d", $pid) ?>">
		<tr><td align=right>Name:<td><?php echo $name ?>
		<tr><td align=right>Reason:<td><input type=text name=reason size=60 value="<?php echo htmlspecialchars($reason) ?>">
		<tr><td align=right>Link:<td><input type=text name=link size=60 value="<?php echo htmlspecialchars($link) ?>">
		<tr><td align=right>Duration:<td><input type=text name=dura size=60 value="<?php printf("%d", $dura) ?>"> days
		<tr><td><td><input type=submit>
	</form>
</table>
<hr>
		<?php
			echo("<table>");
			echo_players(select_players(sprintf(" where p.sid = %d", $sid)));
			echo("</table>");
	}
	else if ($_GET[a] == "rb_insert")
	{
		$pid = $_GET[pid];
		db_query(sprintf("update xwi_players set flags = flags ^ 2 where pid = %d", $pid));
		echo("<table>");
		echo_players(select_players(sprintf(" where pid = %d", $pid)));
		echo("</table>");
	}
	else if ($_GET[a] == "bad_passes")
	{
		$results = db_query("select name from xwi_players inner join bad_passes using (pass) order by name");
		echo("<table>");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td>%s", $result[name]);
		echo("</table>");
	}
	else if ($_GET[a] == "invalid_serials")
	{
		$results = db_query("select name from xwi_players inner join xwi_serials using (sid) where ~flags & 2 and valid < 0 order by name");
		echo("<table>");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td>%s", $result[name]);
		echo("</table>");
		$results = db_query("select valid, count(*) c from xwi_serials group by valid");
		echo("<hr><table>");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td align=right>%d", $result[c], $result[valid]);
		echo("</table>");
	}
	else if ($_GET[a] == "xbl")
	{
		$results = db_query("select *, unix_timestamp(xbl.mtime) as mtime from xbl order by wid desc");
		echo("<table>");
		echo_warnings($results);
		echo("</table>");
	}
	else if ($_GET[a] == "xwsvs")
	{
		$results = db_query("select * from xwsvs_log order by time desc");
		echo("<table>");
		while ($result = mysql_fetch_array($results))
			printf('<tr><td align=right>%d<td align=right><a href="?sid=%d">%d</a><td>%s<td>%s', $result['gsku'], $result['sid'], $result['sid'], nl2br(htmlspecialchars($result['msg'])), gmdate("H:i d-m-Y", $result['time']));
		echo("</table>");
	}
	else
	{
		if ($_GET[a] == "update_bl")
			update_bl();
		$cname = trim($_GET[cname]);
		$pid = $_GET[pid];
		$pname = trim($_GET[pname]);
		$sid = $_GET[sid];
		if (is_numeric($pname))
		{
			$sid = $pname;
			unset($pname);
		}
		if ($_GET[a] == "motds")
			$where = " where motd != ''";
		else if ($cname)
			$where = sprintf(" where c.name like '%s'", AddSlashes($cname));
		else if ($pid)
			$where = sprintf(" where pid = %d", $pid);
		else if ($pname)
			$where = sprintf(" where p.name like '%s'", AddSlashes($pname));
		else if ($sid)
			$where = sprintf(" where p.sid = %d", $sid);
		else
			$where = " where wtime > now()";
		echo("<table><tr><th align=left>Player<th><th align=left>Clan<th><th><th><th align=right>SID<th><th><th align=left>Mtime<th align=left>Ctime");
		echo_players(select_players($where));
		echo("</table>");
		if ($sid)
		{
			$results = db_query(sprintf("select *, unix_timestamp(ctime) ctime, unix_timestamp(mtime) mtime, unix_timestamp(wtime) wtime from xwi_serials where sid = %d", $sid));
			if ($result = mysql_fetch_array($results))
			{
				echo("<br><table><tr><th align=right>SID<th align=right>GSKU<th align=right>Valid<th align=left>Wtime<th align=left>Mtime<th align=left>Ctime");
				do
				{
					printf("<tr><td align=right>%d<td align=right>%x<td align=right>%d<td>%s<td>%s<td>%s", $result[sid], $result[gsku], $result[valid], $result[wtime] ? gmdate("H:i d-m-Y", $result[wtime]) : "", gmdate("H:i d-m-Y", $result[mtime]), gmdate("H:i d-m-Y", $result[ctime]));
				}
				while ($result = mysql_fetch_array($results));
				echo("</table>");
			}
			$results = db_query(sprintf("select *, unix_timestamp(xbl.mtime) mtime from xbl where sid = %d", $sid));
			if ($result = mysql_fetch_array($results))
			{
				echo("<br><table>");
				do
				{
					echo_warning($result);
				}
				while ($result = mysql_fetch_array($results));
				echo("</table>");
			}
		}
	}
?>
<hr>
<a href="?">Home</a>
