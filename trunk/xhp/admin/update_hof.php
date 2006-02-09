<?php
	require_once('common.php');

	function update_hof($date, $lid)
	{
		$rows = db_query(sprintf("select name, points, countries from xcl_prev_players where lid = %d order by points desc, pid limit 10", $lid));
		$rank = 1;
		while ($row = mysql_fetch_assoc($rows))
			db_query(sprintf("insert into xcl_hof (date, lid, rank, name, points, countries) values ('%s', %d, %d, '%s', %d, %d)",
				$date, $lid, $rank++, addslashes($row['name']), $row['points'], $row['countries']));
	}

	$year = gmdate('Y');
	$month = gmdate('m') - 1;
	if (!$month)
	{
		$month += 12;
		$year--;
	}
	$date = sprintf('%04d%02d00', $year, $month);
	$row = db_query_first(sprintf("select count(*) c from xcl_hof where date = '%s'", $date));
	if ($row['c'])
	{
		if ($_GET['force'] != 1)
			die('hof exists already');
		db_query(sprintf("delete from xcl_hof where date = '%s'", $date));
	}
	update_hof($date, 1);
	update_hof($date, 2);
	update_hof($date, 3);
	update_hof($date, 4);
	update_hof($date, 7);
	update_hof($date, 8);
	db_query("insert ignore into xcl_high_scores (name, points, rank) select name, points, rank from xcl_prev_players where lid = 3 and points");
	db_query("update xcl_high_scores h inner join xcl_prev_players p using (name) set h.points = greatest(h.points, p.points), h.rank = least(h.rank, p.rank) where lid = 3");
?>