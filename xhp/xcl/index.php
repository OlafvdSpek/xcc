<?php
	require("../xcc_common.php");

	header('refresh: 300');
	ob_start("ob_gzhandler");
	db_connect();

	function a2lid($v)
	{
		switch ($v)
		{
		case "1":
		case "ra2":
			return 1;
		case "2":
		case "ra2_clan":
			return 2;
		case "3":
		case "ra2_yr":
			return 3;
		case "4":
		case "ra2_yr_clan":
			return 4;
		case "5":
		case "ebfd":
			return 5;
		case "6":
		case "ebfd_clan":
			return 6;
		case "7":
		case "ts":
			return 7;
		case "8":
		case "ts_clan":
			return 8;
		}
		return 0;
	}

	function js_encode($v)
	{
		return addcslashes($v, '\'');
	}

	$cid = isset($_GET['cid']) ? $_GET['cid'] : 0;
	$lid = isset($_GET['lid']) ? a2lid($_GET['lid']) : 0;
	$pid = isset($_GET['pid']) ? $_GET['pid'] : 0;
	$pname = isset($_GET['pname']) ? $_GET['pname'] : "";
	if (isset($_GET['js']))
	{
		$pnames = explode(",", $pname);
		foreach ($pnames as $key => $pname)
			$pnames[$key] = sprintf("\"%s\"", AddSlashes(trim($pname)));
		$results = db_query(sprintf("select * from xcl_players where name in (%s)", implode(",", $pnames)));
		while ($result = mysql_fetch_assoc($results))
			printf("document.write(\"<a href=\\\"http://xwis.net/xcl/?%s=%d\\\">%s</a>: #%d %d / %d %dp<br>\");", $result['lid'] & 1 ? "pid" : "cid", $result['pid'], $result['name'], $result['rank'], $result['win_count'], $result['loss_count'], $result['points']);
		return;
	}
	else if (isset($_GET['pure']))
	{
		if ($cid)
		{
			$results = db_query(sprintf("select p.name, sum(pc > 0) w,  sum(pc < 0) l, sum(greatest(pc, 0)) pw, sum(least(pc, 0)) pl, sum(pc) pc from xcl_games_players gp inner join xcl_players p using (pid) where cid = %d group by p.pid order by name", $cid));
			while ($result = mysql_fetch_assoc($results))
				printf("%s %d %d %d %d %d\n", $result['name'], $result[w], $result[l], $result[pw], $result[pl], $result[pc]);
		}
		else if ($lid || $pid)
		{
			if ($pid)
				$results = db_query(sprintf("select * from xcl_players where pid = %d", $pid));
			else if ($pname)
				$results = db_query(sprintf("select * from xcl_players where lid = %d and name = \"%s\"", $lid, AddSlashes($_GET['pname'])));
			else
				$results = db_query(sprintf("select * from xcl_players where lid = %d and points", $lid));
			while ($result = mysql_fetch_assoc($results))
				printf("%d %d %d %d %s\n", $result['rank'], $result['win_count'], $result['loss_count'], $result['points'], $result['name']);
		}
		return;
	}
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<script type="text/javascript" src="xcl.js"></script>
<script type="text/javascript">page_top(0);
<?php
	function echo_hof($lid)
	{
		printf("t13(%d,new Array(", $lid);
		$results = db_query(sprintf("select * from xcl_players where lid = %d order by points desc limit 10", $lid));
		while ($result = mysql_fetch_assoc($results))
			printf("'%s',", $result['name']);
		printf("0));");
	}

	function echo_player($v)
	{
		return sprintf("%d,%d,'%s',%d,%d,%d,%d,%d,'%s',%d,%d,%d,%d,%d,%d",
			$v['rank'], $v['pid'], $v['name'], $v['win_count'], $v['loss_count'], $v['points'],
			$v['crank'], $v['cid'], $v['cname'], $v['cwin_count'], $v['closs_count'], $v['cpoints'], $v['cty'], $v['cmp'], $v['pc']);
	}

	function echo_games($results, $pid, $cid, $unfair_games)
	{
		printf("tr1f(%d);", $cid);
		if ($result = mysql_fetch_assoc($results))
		{
			do
			{
				$players_result = db_query(sprintf("select t1.*, t2.*, t3.rank crank, t3.name cname, t3.win_count cwin_count, t3.loss_count closs_count, t3.points cpoints from xcl_games_players t1 inner join xcl_players t2 using (pid) left join xcl_players t3 on (t1.cid = t3.pid) where gid = %d order by %s", $result[gid], $cid ? sprintf("cid != %d, t2.pid", $cid) : ($pid ? sprintf("t2.pid != %d", $pid) : "cid, t2.pid")));
				$plrs = mysql_num_rows($players_result) / 2;
				for ($player_i = 0; $players[$player_i] = mysql_fetch_assoc($players_result); $player_i++)
					;
				$player_a = 0;
				$player_b = $plrs;
				printf("tr1a(%d,%d,new Array(%s,%s),%d,'%s',%d,%d,%d,%d,%d);", $result[gid], $result[ws_gid], echo_player($players[$player_a++]), echo_player($players[$player_b++]),
					$result['dura'], js_encode($result['scen']), $result['mtime'], $result['afps'], $result[oosy], $result['trny'], $unfair_games);
				while ($player_a < $plrs)
					printf("tr1d(new Array(%s,%s));", echo_player($players[$player_a++]), echo_player($players[$player_b++]));
			}
			while ($result = mysql_fetch_assoc($results));
		}
		else
			echo("tr1g();");
		echo("tr1h();");
	}

	if (isset($_GET['hof']))
	{
		echo("t13a();");
		echo_hof(1);
		echo_hof(2);
		echo_hof(3);
		echo_hof(4);
		echo_hof(7);
		echo_hof(8);
		echo("t13c();");
		$results = db_query("select * from xcl_hof order by date desc, lid, rank");
		while ($result = mysql_fetch_assoc($results))
			$v[$result['date']][$result['lid']][] = $result['name'];
		foreach ($v as $date => $w)
		{
			printf("t13d('%s',new Array(", gmdate("F Y", gmmktime(0, 0, 0, substr($date, 5, 2), 1, substr($date, 0, 4))));
			foreach ($w as $lid => $x)
			{
				printf("%d,new Array(", $lid);
				foreach ($x as $name)
					printf("'%s',", $name);
				printf("0),");
			}
			printf("0));");
		}
	}
	else if (isset($_GET['hos']))
	{
		echo("t14(new Array(");
		$results = db_query("select distinct xcl_players.name from xcl_players inner join bl using (name) order by xcl_players.name");
		while ($result = mysql_fetch_assoc($results))
			printf("'%s',", $result['name']);
		echo("0));");
	}
	else if (isset($_GET['stats']))
	{
		$games = array();
		$players = array();
		$clans = array();
		$results = db_query("select * from xcl_stats_gsku");
		while ($result = mysql_fetch_assoc($results))
		{
			$games[$result['gsku']][$result['trny']] = $result['games'];
			$games[-1][$result['trny']] += $result['games'];
			$players[$result['gsku']][$result['trny']] = $result['players'];
			$players[-1][$result['trny']] += $result['players'];
			$clans[$result['gsku']][$result['trny']] = $result['clans'];
			$clans[-1][$result['trny']] += $result['clans'];
		}
		echo("p6(new Array(");
		foreach ($games as $gsku => $game)
		{
			if ($gsku != -1)
				printf("%d,%d,%d,", $gsku, $game[1], $game[2]);
		}
		$game = $games[-1];
		printf("0,%d,%d),new Array(", $game[1], $game[2]);
		foreach ($players as $gsku => $player)
		{
			if ($gsku != -1)
				printf("%d,%d,%d,", $gsku, $player[1], $player[2]);
		}
		$player = $players[-1];
		printf("0,%d,%d),new Array(", $player[1], $player[2]);
		foreach ($clans as $gsku => $clan)
		{
			if ($gsku != -1)
				printf("%d,%d,%d,", $gsku, $clan[1], $clan[2]);
		}
		$clan = $clans[-1];
		printf("0,%d,%d),new Array(", $clan[1], $clan[2]);
		$d = array();
		$results = db_query("select * from xcl_stats_countries order by count desc");
		while ($result = mysql_fetch_assoc($results))
			$d[$result['cty']][$result['gsku']][$result['trny']] = $result['count'];
		foreach($d as $cty => $d0)
			printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", $cty, $d0[18][0], $d0[18][1], $d0[18][2], $d0[33][0], $d0[33][1], $d0[33][2], $d0[41][0], $d0[41][1], $d0[41][2]);
		echo("0),new Array(");
		$results = db_query("select lid, name, count from xcl_stats_games order by count desc");
		while ($result = mysql_fetch_assoc($results))
			printf("%d,%d,'%s',", $result['count'], $result['lid'], $result['name']);
		echo("0),new Array(");
		$d = array();
		$results = db_query("select * from xcl_stats_maps order by count desc");
		while ($result = mysql_fetch_assoc($results))
			$d[$result['scen']][$result['gsku']][$result['trny']] = $result['count'];
		foreach($d as $scen => $d0)
			printf("'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,", js_encode($scen), $d0[18][0], $d0[18][1], $d0[18][2], $d0[33][0], $d0[33][1], $d0[33][2], $d0[41][0], $d0[41][1], $d0[41][2]);
		echo("0),new Array(");
		$d = array();
		$results = db_query("select * from xcl_stats_dura order by dura");
		while ($result = mysql_fetch_assoc($results))
			$d[$result['dura']][$result['gsku']][$result['trny']] = $result['count'];
		foreach($d as $dura => $d0)
			printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", $dura, $d0[18][0], $d0[18][1], $d0[18][2], $d0[33][0], $d0[33][1], $d0[33][2], $d0[41][0], $d0[41][1], $d0[41][2]);
		echo("0),new Array(");
		$d = array();
		$results = db_query("select * from xcl_stats_afps order by afps");
		while ($result = mysql_fetch_assoc($results))
			$d[$result['afps']][$result['gsku']][$result['trny']] = $result['count'];
		foreach($d as $afps => $d0)
			printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", $afps, $d0[18][0], $d0[18][1], $d0[18][2], $d0[33][0], $d0[33][1], $d0[33][2], $d0[41][0], $d0[41][1], $d0[41][2]);
		echo("0),new Array(");
		$games = array();
		$results = db_query("select d, h, sum(c) c from xcl_stats_time group by d, h");
		while ($result = mysql_fetch_assoc($results))
			$games[$result['d']][$result['h']] = $result['c'];
		foreach ($games as $d => $hours)
		{
			printf("%d,", $d);
			for ($h = 0; $h < 24; $h++)
				printf("%d,", $hours[$h]);
		}
		echo("0));");
	}
	else
	{
		$cid = isset($_GET['cid']) ? $_GET['cid'] : 0;
		$gid = isset($_GET['gid']) ? $_GET['gid'] : 0;
		$pid = isset($_GET['pid']) ? $_GET['pid'] : 0;
		$pname = isset($_GET['pname']) ? trim($_GET['pname']) : "";
		$recent_games = isset($_GET['recent_games']) ? $_GET['recent_games'] : 0;
		$unfair_games = isset($_GET['unfair_games']) ? $_GET['unfair_games'] : 0;
		$wash_games = isset($_GET['wash_games']) ? $_GET['wash_games'] : 0;
		if ($cid || $gid || $pid || $recent_games || $unfair_games || $wash_games)
		{
			if ($gid)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) scen
					from xcl_games t1 left join xcl_maps t3 on (t1.scen = t3.fname)
					where t1.gid = %d
					order by gid desc
					", $gid));
			else if ($recent_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) scen
					from xcl_games t1 left join xcl_maps t3 on (t1.scen = t3.fname)
					order by gid desc
					limit 25
					"));
			else if ($unfair_games)
			{
				$results = db_query("
					select distinct t1.*, ifnull(t4.name, t1.scen) scen
					from bl inner join xcl_players using (name) inner join xcl_games_players t2 using (pid) inner join xcl_games t1 using (gid) inner join xcl_games_players t3 using (gid) left join xcl_maps t4 on (t1.scen = t4.fname)
					where t2.pid != t3.pid and not t3.cid and t3.pc < 0
					order by gid desc
					");
				echo_games($results, 0, 0, true);
				echo("document.write('<hr>');");
				$results = db_query("
					select distinct t1.*, ifnull(t4.name, t1.scen) scen
					from bl inner join xcl_players p using (name) inner join xcl_games_players t2 on p.pid = t2.pid inner join xcl_games t1 using (gid) inner join xcl_games_players t3 using (gid) left join xcl_maps t4 on (t1.scen = t4.fname)
					where t2.cid != t3.cid and t3.pc < 0
					order by gid desc
					");
			}
			else if ($wash_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) scen
					from xcl_games t1 left join xcl_maps t3 on (t1.scen = t3.fname)
					where oosy
					order by gid desc
					"));
			else
			{
				$results = db_query(sprintf("select xcl_players.* from xcl_players where pid = %d", $cid ? $cid : $pid));
				if ($result = mysql_fetch_assoc($results))
				{
					echo("t15(new Array(");
					do
					{
						printf("%d,%d,%d,'%s',%d,%d,%d,%d,%d,%d,", $result['rank'], $result['lid'], $result['pid'], $result['name'], $result['win_count'], $result['loss_count'], $result['points'], $result['points_max'], $result['mtime'], $result['countries']);
					}
					while ($result = mysql_fetch_assoc($results));
					echo("0));");
				}
				$results = db_query($cid
					? sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) scen from xcl_games t1 inner join xcl_games_players t2 using (gid) left join xcl_maps t3 on (t1.scen = t3.fname) where t2.cid = %d order by gid desc", $cid)
					: sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) scen from xcl_games t1 inner join xcl_games_players t2 using (gid) left join xcl_maps t3 on (t1.scen = t3.fname) where not t2.cid and t2.pid = %d order by gid desc", $pid));
			}
			echo_games($results, $pid, $cid, $unfair_games);
			if ($cid || $pid)
			{
				if ($cid)
				{
					$results = db_query(sprintf("select p.name, sum(pc > 0) w,  sum(pc < 0) l, sum(greatest(pc, 0)) pw, sum(least(pc, 0)) pl, sum(pc) pc from xcl_games_players gp inner join xcl_players p using (pid) where cid = %d group by p.pid order by name", $cid));
					echo('t2(new Array(');
					while ($result = mysql_fetch_assoc($results))
					{
						printf("'%s',%d,%d,%d,%d,%d,", $result['name'], $result[w], $result[l], $result[pw], $result[pl], $result[pc]);
					}
					echo("0));");
				}
				$results = db_query($cid
					? sprintf("select cty, count(*) count from xcl_games_players where cid = %d group by cty order by count desc", $cid)
					: sprintf("select cty, count(*) count from xcl_games_players where not cid and pid = %d group by cty order by count desc", $pid));
				if ($result = mysql_fetch_assoc($results))
				{
					echo('t3(new Array(');
					do
					{
						printf('%d,%d,', $result['count'], $result['cty']);
					}
					while ($result = mysql_fetch_assoc($results));
					echo('0));');
				}
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) scen, count(*) count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where cid = %d group by scen order by count desc", $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) scen, count(*) count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where not cid and pid = %d group by scen order by count desc", $pid));
				if ($result = mysql_fetch_assoc($results))
				{
					echo('t4(new Array(');
					do
					{
						printf("%d,'%s',", $result['count'], js_encode($result['scen']));
					}
					while ($result = mysql_fetch_assoc($results));
					echo('0));');
				}
			}
			else if ($gid)
			{
				$results = db_query(sprintf("select * from xcl_games_players inner join xcl_players using (pid) where gid = %d", $gid));
				echo("t5(new Array(");
				while ($result = mysql_fetch_assoc($results))
				{
					printf("'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", $result['name'],
						$result['unk'], $result['unb'], $result['unl'],
						$result['blk'], $result['blb'], $result['bll'], $result['blc'],
						$result['ink'], $result['inb'], $result['inl'],
						$result['plk'], $result['plb'], $result['pll']);
				}
				echo("0));");
			}
		}
		else
		{
			printf("page_search(%d);", $lid);
			if ($lid || $pname)
			{
				$cty = $_REQUEST['cty'] ? sprintf("and !(xcl_players.countries & %d)", $_REQUEST['cty']) : '';
				$results = db_query($pname
					? $lid
					? sprintf("select * from xcl_players where lid = %d and name like '%s' order by points desc, rank limit 250", $lid, AddSlashes($pname))
					: sprintf("select * from xcl_players where name like '%s' order by points desc, rank limit 250", AddSlashes($pname))
					: sprintf("select * from xcl_players where lid = %d and points %s order by points desc, rank limit 250", $lid, $cty));
				echo('t0(new Array(');
				while ($result = mysql_fetch_assoc($results))
					printf("%d,%d,%d,'%s',%d,%d,%d,%d,%d,%d,", $result['rank'], $result['lid'], $result['pid'], $result['name'], $result['win_count'], $result['loss_count'], $result['points'], $result['points_max'], $result['mtime'], $result['countries']);
				printf('0), %d);', !$lid);
			}
			else
				echo('page_ladders();');
		}
	}
	printf("page_bottom(%d);", time());
	echo('</script>');
?>