<?php
    require("../xcc_common.php");

	ob_start(ob_gzhandler);
	if (isset($HTTP_GET_VARS[pure]))
	{
		$fname = "/home/groups/x/xc/xccu/data/xla/black_list.txt";
		if (time() - @filemtime($fname) < 900)
		{
			$f = fopen($fname, "rb");
			fpassthru($f);
			return;
		}
		$d = "";
		db_connect();
		db_query("create table if not exists bl (name char(9) primary key)");
		db_query("delete from bl");
		db_query("insert ignore into bl select name from xla_black_list");
		db_query("insert ignore into bl select name from xla_black_list_names");
		db_query("insert ignore into bl select name from xwl_accounts inner join xwl_players using (aid) where now() < wtime");
		db_query("insert ignore into bl select distinct name from xtr_index where count > 8");
		$results = db_query("select * from bl");
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
	<title>XCC Black List</title>
<p class=page_title>
	Black list
<hr>
<?php
	function create_tables()
	{
		db_query("
			create table if not exists xla_black_list
			(
				name varchar(255) not null primary key,
				comments text not null,
				last_modified timestamp
			);");
		db_query("
			create table if not exists xla_black_list_addresses
			(
				bid int not null,
				address int not null primary key,
				last_modified timestamp
			);");
	}

	function show_aliases($address)
	{
		$query = sprintf("select t1.name, t2.count from hal_index as t1 left join xtr_index as t2 using (name) left join xla_black_list as t3 on (t1.name = t3.name) left join xla_black_list_names as t4 on (t1.name = t4.name) where address = %d and t3.name is null and t4.name is null order by name", $address);
		$results = db_query($query);
		while ($result = mysql_fetch_array($results))
		{
			$xtr_count = $result[count] && trust_remote_host() ? sprintf(" (%d)", $result[count]) : "";
			printf("<a href=\"?name=%s\">%s</a>%s<br>", urlencode($result[name]), htmlspecialchars($result[name]), $xtr_count);
		}
	};

	if (isset($HTTP_GET_VARS[name]) && trust_remote_host())
	{
		echo("<table border=1>");
		$name = UCFirst(strtolower($HTTP_GET_VARS[name]));
		$results = db_query(sprintf("select *, unix_timestamp(last_modified) as last_modified from xla_black_list where name = \"%s\"", $name));
		if ($result = mysql_fetch_array($results))
		{
			echo("<tr><th colspan=4>BL");
			echo("<tr><th align=left>Name<th align=left colspan=2>Comments<th align=left>Last modified");
			do
			{
				echo "<tr>";
				printf("<td>%s", htmlspecialchars($result[name]));
				printf("<td colspan=2>%s", htmlspecialchars($result[comments]));
				printf("<td>%s", date("H:i d-m-Y", $result[last_modified]));
			}
			while ($result = mysql_fetch_array($results));
		}
		$results = db_query(sprintf("select t2.name, t2.comments, unix_timestamp(t2.last_modified) as last_modified from xla_black_list_names as t1, xla_black_list as t2 where t1.name = \"%s\" and t1.bid = t2.bid", $name));
		if ($result = mysql_fetch_array($results))
		{
			echo("<tr><th colspan=4>BLN");
			echo("<tr><th align=left>Name<th align=left colspan=2>Comments<th align=left>Last modified");
			do
			{
				echo "<tr>";
				printf("<td>%s", htmlspecialchars($result[name]));
				printf("<td colspan=2>%s", htmlspecialchars($result[comments]));
				printf("<td>%s", date("H:i d-m-Y", $result[last_modified]));
			}
			while ($result = mysql_fetch_array($results));
		}
		$results = db_query(sprintf("select *, unix_timestamp(last_modified) as last_modified from xtr_index where name = \"%s\"", $name));
		if ($result = mysql_fetch_array($results))
		{
			echo("<tr><th colspan=4>XTR");
			echo("<tr><th align=left>Name<th align=left>SID<th align=right>Count<th align=left>Last modified");
			do
			{
				echo "<tr>";
				printf("<td><a href=\"xtr_index.php?sid=%d\">%s</a>", $result[sid], htmlspecialchars($result[name]));
				printf("<td>%x", $result[sid]);
				printf("<td align=right>%d", $result[count]);
				printf("<td>%s", date("H:i d-m-Y", $result[last_modified]));
			}
			while ($result = mysql_fetch_array($results));
		}
		echo("</table></html>");
		return;
	}

	$trusted = trust_remote_host();
	create_tables();
	$results = db_query("select name, comments from xla_black_list order by name");
?>
<table border=1>
	<tr>
		<th align=left>Name
<?php
	while ($result = mysql_fetch_array($results))
	{
		printf("<tr><td><a target=_top href=\"/xla/gamelist.php?lid=ra2&amp;pid=%s\">%s</a>", urlencode(htmlspecialchars($result[name])), htmlspecialchars($result[name]));
		if ($trusted)
			printf("<td>%s<td><a href=\"/xla/hal_index.php?name=%s\">AL</a> <a href=\"/xla/admin/xla_black_list_add_names.php?name=%s\">BL</a> %s", $result[comments], urlencode($name), urlencode($name), get_stats_links($name));
	}
?>
</table>
</html>