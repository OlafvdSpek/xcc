<?php
    require("../xcc_common.php");

	ob_start(ob_gzhandler);
	if (isset($HTTP_GET_VARS[pure]))
	{
		$fname = "/home/groups/x/xc/xccu/data/xla/white_list.txt";
		if (time() - @filemtime($fname) < 900)
		{
			$f = fopen($fname, "rb");
			fpassthru($f);
			return;
		}
		$d = "";
		db_connect();
		db_query("create table if not exists wl (name char(9) primary key)");
		db_query("delete from wl");
		db_query("insert ignore into wl select name from xwl_accounts inner join xwl_players using (aid) where now() > wtime");
		$results = db_query("select * from wl");
		while ($result = mysql_fetch_array($results))
			$d .= sprintf("%s\n", $result[name]);
		echo $d;
		$f = fopen($fname, "wb");
		fwrite($f, $d);
		fclose($f);
		return;
	}
	db_connect();
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<link rel=stylesheet href="/xcc.css">
	<title>XCC White List</title>
<p class=page_title>
	White list
<hr>
<table border=1>
	<tr>
		<th align=left>Name (<a href="?sort_column=0">A</a>)
		<th align=left>Links</th>
		<th align=left>SID (<a href="?sort_column=1">A</a>)
		<th align=left>Ctime (<a href="?sort_column=2">D</a>)
		<th align=left>Mtime (<a href="?sort_column=3">D</a>)
		<th align=left>Wtime (<a href="?sort_column=4">D</a>)
<?php
	$column_names = array("name", "sid", "ctime desc", "mtime desc", "wtime desc");
	if (!isset($sort_column) || $sort_column < 0 || $sort_column > 4)
		$sort_column = 2;
	$results = db_query($sid
		? sprintf("select t2.name, t2.pid, t1.sid, unix_timestamp(t2.ctime) as ctime, unix_timestamp(t2.mtime) as mtime, unix_timestamp(t1.wtime) as wtime from xwl_accounts as t1 inner join xwl_players as t2 using (aid) where sid = %d order by %s", $sid, $column_names[$sort_column])
		: sprintf("select t2.name, t1.sid, unix_timestamp(t2.ctime) as ctime, unix_timestamp(t2.mtime) as mtime, unix_timestamp(t1.wtime) as wtime from xwl_accounts as t1 inner join xwl_players as t2 using (aid) order by %s", $column_names[$sort_column]));
	while ($result = mysql_fetch_array($results))
	{
		printf("<tr><td>%s<td><a href=\"/xla/hal_index.php?name=%s\">AL</a> <a href=\"/xla/xtr_index.php?sid=%s\">TR</a> <a target=_top href=\"/xla/gamelist.php?lid=ra2&amp;pid=%s\">RA2</a> <a target=_top href=\"/xla/gamelist.php?lid=ra2_yr&amp;pid=%s\">YR</a>", htmlspecialchars($result[name]), urlencode($result[name]), $result[sid], urlencode($result[name]), urlencode($result[name]));
		if (isset($sid))
			printf(" <a href=\"/xla/admin/xla_white_list_warning.php?pid=%d\">Warn</a>", $result[pid]);
		printf("<td><a href=\"?sid=%d\">%x</a><td>%s<td>%s<td>%s", $result[sid], $result[sid], date("d-m-Y", $result[ctime]), date("d-m-Y", $result[mtime]), $result[wtime] ? date("d-m-Y", $result[wtime]) : "&nbsp");
	}
	if ($sid)
	{
		$results = db_query(sprintf("select t3.wid, t2.name, t3.link, t3.reason, unix_timestamp(t3.mtime) as mtime from xwl_accounts as t1, xwl_players as t2, xwl_warnings as t3 where t1.aid = t2.aid and t2.pid = t3.pid and t1.sid = %d order by wid", $sid));
		if (($result = mysql_fetch_array($results)))
		{
			echo "</table><br><table border=1>";
			do
				printf("<tr><td align=right>%d<td>%s<td><a target=_top href=\"%s\">%s</a><td>%s<td>%s", $result[wid], htmlspecialchars($result[name]), htmlspecialchars($result[link]), htmlspecialchars($result[link]), htmlspecialchars($result[reason]), date("H:i d-m-Y", $result[mtime]));
			while ($result = mysql_fetch_array($results));
		}
	}
?>
</table>
<hr>
<a href="?">Home</a>
</html>