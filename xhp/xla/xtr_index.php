<?php
    require("../xcc_common.php");

	ob_start(ob_gzhandler);
	db_connect();
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<link rel=stylesheet href="/xcc.css">
	<title>XTR Report</title>
<p class=page_title>
	XTR report
<hr>
<table border=1>
	<tr>
		<th align=left>Name (<a href="?sort_column=0">A</a>)
		<th align=left>Links
		<th align=left>SID (<a href="?sort_column=1">A</a>)
		<th align=right>Count (<a href="?sort_column=2">D</a>)
		<th align=left>Mtime (<a href="?sort_column=3">D</a>)
<?php
	$column_names = array("name", "sid", "count desc", "last_modified desc");
	if (!isset($sort_column) || $sort_column < 0 || $sort_column > 3)
		$sort_column = 3;
	$results = db_query(isset($HTTP_GET_VARS[sid])
		? sprintf("select *, unix_timestamp(last_modified) as mtime from xtr_index where sid = %d order by " . $column_names[$sort_column], $HTTP_GET_VARS[sid])
		: "select *, unix_timestamp(last_modified) as mtime from xtr_index order by " . $column_names[$sort_column]);
	while ($result = mysql_fetch_array($results))
		printf("<tr><td><a href=\"?sid=%d\">%s</a><td><a href=\"/xla/hal_index.php?name=%s\">AL</a> <a target=_top href=\"/xla/gamelist.php?lid=ra2&amp;pid=%s\">GL</a><td>%x<td align=right>%d<td>%s",
			$result[sid], htmlspecialchars($result[name]), urlencode($result[name]), urlencode($result[name]), $result[sid], $result[count], date("H:i d-m-Y", $result[mtime]));
?>
</table>
<hr>
<a href="?">Home</a>
</html>