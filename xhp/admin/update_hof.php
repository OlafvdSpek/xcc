<?php
	require_once('config.php');
	require_once('../../b/common.php');

	function update_hof($date, $lid)
	{
		$rows = db_query(sprintf("select name, points, countries from xcl_prev_players where lid = %d order by points desc, pid limit 10", $lid));
		if (!mysql_num_rows($rows))
			return;
		$first = true;
		$rank = 1;
		echo("insert into xcl_hof (date, lid, rank, name) values<br>");
		while ($row = mysql_fetch_assoc($rows))
		{
			if (!$first)
				echo(",<br>");
			$first = false;
			printf("('%s', %d, %d, '%s')", $date, $lid, $rank++, addslashes($row['name']));
		}
		echo(";<br>");
	}

	db_connect();
	$row = db_query_first("select mtime from xcl_games order by gid limit 1");
	$year = gmdate('Y', $row['mtime']);
	$month = gmdate('m', $row['mtime']) - 1;
	if (!$month)
	{
		$month += 12;
		$year--;
	}
	$date = sprintf('%04d%02d00', $year, $month);
	// printf("delete from xcl_hof where date = '%s';<br>", $date);
	// echo("update xcl_prev_players inner join bl using (name) set points = 0 where lid & 1 and points;<br>");
	update_hof($date, 1);
	update_hof($date, 2);
	update_hof($date, 3);
	update_hof($date, 4);
	update_hof($date, 7);
	update_hof($date, 8);
	$rows = db_query("select name, points from xcl_prev_players where lid = 3 and points order by points desc, pid");
	echo("insert into xcl_high_scores (name, points, rank) values<br>");
	$first = true;
	$rank = 1;
	while ($row = mysql_fetch_assoc($rows))
	{
		if (!$first)
			echo(",<br>");
		$first = false;
		printf("('%s', %d, %d)", addslashes($row['name']), $row['points'], $rank++);
	}
	echo("<br>on duplicate key update points = greatest(points, values(points)), rank = least(rank, values(rank));<br>");
