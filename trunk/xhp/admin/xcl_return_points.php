<?php
	require("../xcc_common.php");

	db_connect();

	$gid = $_GET[gid];
	if (!$gid)
	{
		return;
	}
	$results = db_query(sprintf("
		select distinct t1.*
		from bl inner join xcl_players using (name) inner join xcl_games_players using (pid) inner join xcl_games_players as t1 using (gid)
		where not t1.cid and t1.gid = %d and t1.pc < 0
		", $gid));
	if ($result = mysql_fetch_array($results))
	{
		db_query(sprintf("update xcl_games_players set pc = 0 where gid = %d and pid = %d", $gid, $result[pid]));
		db_query(sprintf("update xcl_players set points = points - %d where pid = %d", $result[pc], $result[pid]));
	}
	else
	{
		$results = db_query(sprintf("
			select distinct t1.*
			from bl inner join xcl_players p using (name) inner join xcl_games_players gp using (pid) inner join xcl_games_players as t1 using (gid)
			where t1.gid = %d and t1.pc < 0
			", $gid));
		if ($result = mysql_fetch_array($results))
		{
			db_query(sprintf("update xcl_games_players set pc = 0 where gid = %d and pid = %d", $gid, $result[pid]));
			db_query(sprintf("update xcl_players set points = points - %d where pid = %d", $result[pc], $result[cid]));
		}
	}
	Header(sprintf("Location: /xcl?gid=%d", $gid));
?>