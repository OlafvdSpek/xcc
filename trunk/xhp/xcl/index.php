<?php
	require("../xcc_common.php");

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

	function lid2a($v)
	{
		$names = array("", "ra2", "ra2 c", "yr", "yr c", "ebfd", "ebfd c", "ts", "ts clan");
		return $names[$v];
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
	<link rel=stylesheet href="/egx.css">
	<title>XCC Community Ladder<?php if (gmdate("d") == 1) echo (" (frozen)") ?></title>
<table width="100%">
	<tr>
		<td valign=bottom>
			<p class=page_title>
				XCC Community Ladder
		<td align=right valign=bottom>
			<a href="/xwi/">Clans</a> |
			<a href="http://xccu.sourceforge.net/cgi-bin/forum.cgi">Forum</a> |
			<a href="http://xwis.net:4005/">Online</a> |
			<a href="http://strike-team.net/nuke/html/modules.php?op=modload&amp;name=News&amp;file=article&amp;sid=13">Rules</a> |
			<a href="http://xccu.sourceforge.net/utilities/XGS.zip" title="XCC Game Spy">XGS</a> |
			<a href="/downloads/XWISB.zip" title="XCC WOL IRC Server Beeper">XWISB</a> |
			<a href="/downloads/XWISC.exe" title="XCC WOL IRC Server Client">XWISC</a><br>
			<a href="?hof=" title="Hall of Fame">HoF</a> |
			<a href="?hos=" title="Hall of Shame">HoS</a> |
			<a href="?">Home</a> |
			<a href="?stats=">Stats</a>
</table>
<hr>
<?php
	function cmp2a($v)
	{
		switch ($v)
		{
		case 0x100:
			return "W";
		case 0x200:
		case 0x210:
		case 0x220:
			return "L";
		}
		return $v;
	}

	function get_country_name($i)
	{
		switch ($i & ~0xff)
		{
		case 0x100:
			$country_names = array
			(
				"Atreides",
				"Harkonnen",
				"Ordos",
			);
			break;
		case 0x200:
			$country_names = array
			(
				"GDI",
				"Nod",
			);
			break;
		default:
			$country_names = array
			(
				"America",
				"Korea",
				"France",
				"Germany",
				"Great Britain",
				"Libya",
				"Iraq",
				"Cuba",
				"Russia",
				"Yuri"
			);
		}
		return $country_names[$i & 0xff];
	}

	function get_country_flag_url($i)
	{
		switch ($i & ~0xff)
		{
		case 0x100:
			$country_flag_urls = array
			(
				"images/atreides.png",
				"images/harkonnen.png",
				"images/ordos.png",
			);
			break;
		case 0x200:
			$country_flag_urls = array
			(
				"images/gdi.png",
				"images/nod.png",
			);
			break;
		default:
			$country_flag_urls = array
			(
				"images/usai.png",
				"images/japi.png",
				"images/frai.png",
				"images/geri.png",
				"images/gbri.png",
				"images/djbi.png",
				"images/arbi.png",
				"images/lati.png",
				"images/rusi.png",
				"images/yrii.png",
			);
		}
		return $country_flag_urls[$i & 0xff];
	}

	function dura2a($v)
	{
		$r = sprintf("%02d", $v % 60);
		$v /= 60;
		$v = (int)$v;
		if ($v)
		{
			$r = sprintf("%02d", $v % 60) . ':' . $r;
			$v /= 60;
			$v = (int)$v;
			if ($v)
				$r = $v . ':' . $r;

		}
		return $r;
	}

	function gsku2a($v)
	{
		switch ($v)
		{
		case 0x1200:
			return "TS";
		case 0x1f00:
			return "EBFD";
		case 0x2100:
			return "RA2";
		case 0x2900:
			return "YR";
		}
		return sprintf("%x", $v);
	}

	function pc2a($v)
	{
		return $v ? $v > 0 ? '+' . $v : $v : "";
	}

	function update_ranks($lid)
	{
		$results = db_query(sprintf("select pid, rank from xcl_players where lid = %d order by points desc", $lid));
		$rank = 1;
		while ($result = mysql_fetch_assoc($results))
		{
			if ($result['rank'] != $rank)
				db_query(sprintf("update xcl_players set rank = %d, mtime = mtime where pid = %d", $rank, $result['pid']));
			$rank++;
		}
	}

	function echo_hof($lid, $title)
	{
		printf("<table><tr><th colspan=2>%s", $title);
		// echo("<tr><th>Rank<th>Name");
		$results = db_query(sprintf("select * from xcl_players where lid = %d order by points desc limit 10", $lid));
		$rank = 1;
		while ($result = mysql_fetch_assoc($results))
		{
			printf("<tr><td align=right>%d<td>%s", $rank++, $result['name']);
		}
		echo("</table>");
	}

	function echo_player($player)
	{
		echo($player[cid] ? "<td>" : "<td colspan=2>");
		printf("<a href=\"?pid=%d\" title=\"#%d %d / %d %dp\">%s</a>", $player['pid'], $player['rank'], $player['win_count'], $player['loss_count'], $player['points'], $player['name']);
		if ($player[cid])
			printf("<td><a href=\"?cid=%d\" title=\"#%d %d / %d %dp\">%s</a>", $player[cid], $player[crank], $player[cwin_count], $player[closs_count], $player[cpoints], $player[cname]);
		printf("<td align=center><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($player['cty']), get_country_name($player['cty']), cmp2a($player[cmp]), pc2a($player[pc]));
	}

	function echo_games($results, $pid, $cid, $unfair_games)
	{
		echo($cid
			? "<table><tr><th>GID<th colspan=5>Clan A<th colspan=4>Clan B<th colspan=2>Duration<th>Scenario<th>Date"
			: "<table><tr><th>GID<th colspan=5>Player A<th colspan=4>Player B<th colspan=2>Duration<th>Scenario<th>Date");
		if ($result = mysql_fetch_assoc($results))
		{
			do
			{
				printf("<tr><td align=right><a href=\"?gid=%d\" title=%d>%d</a>", $result[gid], $result[ws_gid], $result[gid]);
				$players_result = db_query(sprintf("select t1.*, t2.*, t3.rank crank, t3.name cname, t3.win_count cwin_count, t3.loss_count closs_count, t3.points cpoints from xcl_games_players t1 inner join xcl_players t2 using (pid) left join xcl_players t3 on (t1.cid = t3.pid) where gid = %d order by %s", $result[gid], $cid ? sprintf("cid != %d, t2.pid", $cid) : ($pid ? sprintf("t2.pid != %d", $pid) : "cid, t2.pid")));
				$plrs = mysql_num_rows($players_result) / 2;
				for ($player_i = 0; $players[$player_i] = mysql_fetch_assoc($players_result); $player_i++)
					;
				$player_a = 0;
				$player_b = $plrs;
				echo_player($players[$player_a++]);
				echo_player($players[$player_b++]);
				printf("<td align=right>%s<td>%s<td align=right>%s<td>%d<td>%d<td>%d",
					dura2a($result['dura']), $result['scen'], gmdate("H:i d-m", $result['mtime']), $result['afps'], $result[oosy], $result['trny']);
				if ($unfair_games)
					printf("<td><a href=\"/admin/xcl_return_points.php?gid=%d\">Return points</a>", $result[gid]);
				for (; $player_a < $plrs; $player_a++, $player_b++)
				{
					echo("<tr><td>");
					echo_player($players[$player_a]);
					echo_player($players[$player_b]);
					echo("<td colspan=4>");
				}
			}
			while ($result = mysql_fetch_assoc($results));
		}
		else
			echo("<tr><th colspan=15>-");
		echo("</table>");
	}

	if (isset($_GET['update_ranks']))
	{
		for ($i = 1; $i < 9; $i++)
			update_ranks($i);
	}
	if (isset($_GET['hof']))
	{
		echo("<center><table><tr><td>");
		echo_hof(1, "Red Alert 2");
		echo("<td><td>");
		echo_hof(2, "Clan");
		echo("<td><td>");
		echo_hof(3, "Yuri's Revenge");
		echo("<td><td>");
		echo_hof(4, "Clan");
		echo("<td><td>");
		echo_hof(7, "Tiberian Sun");
		echo("<td><td>");
		echo_hof(8, "Clan");
		echo("</table></center>");
		$results = db_query("select * from xcl_hof order by date desc, lid, rank");
		while ($result = mysql_fetch_assoc($results))
			$v[$result['date']][$result['lid']][$result['rank']] = $result['name'];
		foreach ($v as $date => $w)
		{
			printf("<hr><center><table><tr><th colspan=12>%s<tr>", gmdate("F Y", gmmktime(0, 0, 0, substr($date, 5, 2), 1, substr($date, 0, 4))));
			foreach ($w as $lid => $x)
			{
				echo("<td><table>");
				if ($lid)
					echo("<tr><th colspan=2>");
				switch ($lid)
				{
				case 1:
					echo("Red Alert 2");
					break;
				case 2:
				case 4:
				case 6:
				case 8:
					echo("Clan");
					break;
				case 3:
					echo("Yuri's Revenge");
					break;
				case 7:
					echo("Tiberian Sun");
					break;
				}
				// echo("<tr><th>Rank<th>Name");
				foreach ($x as $rank => $name)
					printf("<tr><td align=right>%d<td>%s", $rank, $name);
				printf("</table>");
			}
			printf("</table></center>");
		}
	}
	else if (isset($_GET['hos']))
	{
		echo("<center><table><tr><th>Name");
		$results = db_query("select xcl_players.pid from xcl_players inner join bl using (name) where points");
		while ($result = mysql_fetch_assoc($results))
			db_query(sprintf("update xcl_players set points = 0 where pid = %d", $result['pid']));
		$results = db_query("select distinct xcl_players.name from xcl_players inner join bl using (name) order by xcl_players.name");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td>%s", $result['name']);
		echo("</table></center>");
	}
	else if (isset($_GET['stats']))
	{
		$results = db_query("show table status like 'xcl_stats_gsku'");
		$result = mysql_fetch_assoc($results);
		if (time() - strtotime($result['Update_time']) > 15 * 60)
		{
			db_query("delete from xcl_stats_gsku");
			db_query("insert into xcl_stats_gsku select gsku, trny, count(*) as count from xcl_games group by gsku, trny");
			db_query("delete from xcl_stats_players");
			db_query("insert into xcl_stats_players select gsku, if(cid, 2, 1) as trny, if(cid, count(distinct cid), count(distinct pid)) as count from xcl_games inner join xcl_games_players using (gid) group by gsku, trny");
			db_query("delete from xcl_stats_countries");
			db_query("insert into xcl_stats_countries select cty, count(*) as count from xcl_games_players group by cty");
			db_query("delete from xcl_stats_maps");
			db_query("insert into xcl_stats_maps select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname group by scen");
			db_query("delete from xcl_stats_dura");
			db_query("insert into xcl_stats_dura select round(dura / 600) * 10 as dura, count(*) as count from xcl_games group by dura");
			db_query("delete from xcl_stats_afps");
			db_query("insert into xcl_stats_afps select afps, count(*) as count from xcl_games group by afps");
			db_query("delete from xcl_stats_time");
			db_query("insert into xcl_stats_time select hour(mtime) as h, dayofmonth(mtime) as d, count(*) as c from xcl_games group by d, h");
		}
		$games = array();
		$results = db_query("select * from xcl_stats_gsku order by count desc");
		while ($result = mysql_fetch_assoc($results))
		{
			$games[$result['gsku']][$result['trny']] = $result['count'];
			$games[$result['gsku']][-1] += $result['count'];
			$games[-1][$result['trny']] += $result['count'];
			$games[-1][-1] += $result['count'];
		}
		echo("<table><tr><th><th>Player<th>Clan");
		foreach ($games as $gsku => $game)
		{
			if ($gsku != -1)
				printf("<tr><td>%s<td align=right>%d<td align=right>%d<td align=right>%d", gsku2a($gsku), $game[1], $game[2], $game[-1]);
		}
		$game = $games[-1];
		printf("<tr><td><td align=right>%d<td align=right>%d<td align=right>%d", $game[1], $game[2], $game[-1]);
		echo("</table><hr>");
		$games = array();
		$results = db_query("select * from xcl_stats_players order by count desc");
		while ($result = mysql_fetch_assoc($results))
		{
			$games[$result['gsku']][$result['trny']] = $result['count'];
			$games[$result['gsku']][-1] += $result['count'];
			$games[-1][$result['trny']] += $result['count'];
			$games[-1][-1] += $result['count'];
		}
		echo("<table><tr><th><th>Player<th>Clan");
		foreach ($games as $gsku => $game)
		{
			if ($gsku != -1)
				printf("<tr><td>%s<td align=right>%d<td align=right>%d<td align=right>%d", gsku2a($gsku), $game[1], $game[2], $game[-1]);
		}
		$game = $games[-1];
		printf("<tr><td><td align=right>%d<td align=right>%d<td align=right>%d", $game[1], $game[2], $game[-1]);
		echo("</table><hr>");
		/*
		// $results = db_query("select gsku, count(*) count from xcl_games group by gsku order by count desc");
		$results = db_query("select * from xcl_stats_gsku order by count desc");
		echo("<table><tr><th>Games<th>Game");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td align=right>%d<td>%s", $result['count'], gsku2a($result['gsku']));
		echo("</table><hr>");
		*/
		/*
		// $results = db_query("select gsku, count(distinct pid) count from xcl_games inner join xcl_games_players using (gid) where not cid group by gsku order by count desc");
		$results = db_query("select * from xcl_stats_players order by count desc");
		echo("<table><tr><th>Players<th>Game");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td align=right>%d<td>%s", $result['count'], gsku2a($result['gsku']));
		echo("</table><hr>");
		// $results = db_query("select gsku, count(distinct cid) count from xcl_games inner join xcl_games_players using (gid) where cid group by gsku order by count desc");
		$results = db_query("select * from xcl_stats_clans order by count desc");
		echo("<table><tr><th>Clans<th>Game");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td align=right>%d<td>%s", $result['count'], gsku2a($result['gsku']));
		echo("</table><hr>");
		*/
		// $results = db_query("select cty, count(*) count from xcl_games_players group by cty order by count desc");
		$results = db_query("select * from xcl_stats_countries order by count desc");
		echo("<table><tr><th>Count<th>Country");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td align=right>%d<td align=center><img src=\"%s\" alt=\"%s\">", $result['count'], get_country_flag_url($result['cty']), get_country_name($result['cty']));
		echo("</table><hr>");
		// $results = db_query("select ifnull(xcl_maps.name, xcl_games.scen) scen, count(*) count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname group by scen order by count desc");
		// $results = db_query("select ifnull(xcl_maps.name, xcl_stats_maps.scen) scen, count from xcl_stats_maps left join xcl_maps on xcl_stats_maps.scen = xcl_maps.fname order by count desc");
		$results = db_query("select scen, count from xcl_stats_maps order by count desc");
		echo("<table><tr><th>Count<th>Scenario");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td align=right>%d<td>%s", $result['count'], $result['scen']);
		echo("</table><hr>");
		// $results = db_query("select round(dura / 600) * 10 dura, count(*) count from xcl_games group by dura order by dura");
		$results = db_query("select * from xcl_stats_dura order by dura");
		echo("<table><tr><th>Count<th>Duration");
		while ($result = mysql_fetch_assoc($results))
		{
			printf("<tr><td align=right>%d<td align=right>", $result['count']);
			if ($result['dura'])
				printf("%d - %d", $result['dura'] - 5, $result['dura'] + 5);
			else
				echo("< 5");
		}
		echo("</table><hr>");
		// $results = db_query("select afps, count(*) count from xcl_games group by afps order by afps");
		$results = db_query("select * from xcl_stats_afps order by afps");
		echo("<table><tr><th>Count<th>Average FPS");
		while ($result = mysql_fetch_assoc($results))
			printf("<tr><td align=right>%d<td>%d", $result['count'], $result['afps']);
		echo("</table><hr>");
		$games = array();
		// $results = db_query("select hour(mtime) h, dayofmonth(mtime) d, count(*) c from xcl_games group by dayofmonth(mtime), hour(mtime)");
		$results = db_query("select * from xcl_stats_time order by d, h");
		while ($result = mysql_fetch_assoc($results))
		{
			$games[$result['d']][$result['h']] = $result['c'];
			$games[$result['d']][24] += $result['c'];
			$games[32][$result['h']] += $result['c'];
			$games[32][24] += $result['c'];
		}
		echo("<table><tr><td>");
		for ($h = 0; $h < 24; $h++)
			printf("<th align=right>%d", $h);
		for ($d = 1; $d < 33; $d++)
		{
			if (!$games[$d][24])
				continue;
			if ($d == 32)
				echo("<tr><th>");
			else
				printf("<tr><th align=right>%d", $d);
			for ($h = 0; $h < 25; $h++)
			{
				if ($games[$d][$h])
					printf("<td align=right>%d", $games[$d][$h]);
				else
					echo("<td>");
			}
		}
		echo("</table>");
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
					select t1.*, ifnull(t3.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime
					from xcl_games t1 left join xcl_maps t3 on (t1.scen = t3.fname)
					where t1.gid = %d
					order by gid desc
					", $gid));
			else if ($recent_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime
					from xcl_games t1 left join xcl_maps t3 on (t1.scen = t3.fname)
					order by gid desc
					limit 25
					"));
			else if ($unfair_games)
			{
				$results = db_query("
					select distinct t1.*, ifnull(t4.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime
					from bl inner join xcl_players using (name) inner join xcl_games_players t2 using (pid) inner join xcl_games t1 using (gid) inner join xcl_games_players t3 using (gid) left join xcl_maps t4 on (t1.scen = t4.fname)
					where t2.pid != t3.pid and not t3.cid and t3.pc < 0
					order by gid desc
					");
				echo_games($results, 0, 0, true);
				echo("<hr>");
				$results = db_query("
					select distinct t1.*, ifnull(t4.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime
					from bl inner join xcl_players p using (name) inner join xcl_games_players t2 on p.pid = t2.cid inner join xcl_games t1 using (gid) inner join xcl_games_players t3 using (gid) left join xcl_maps t4 on (t1.scen = t4.fname)
					where t2.cid != t3.cid and t3.pc < 0
					order by gid desc
					");
			}
			else if ($wash_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime
					from xcl_games t1 left join xcl_maps t3 on (t1.scen = t3.fname)
					where oosy
					order by gid desc
					"));
			else
			{
				$results = db_query(sprintf("select xcl_players.*, unix_timestamp(xcl_players.mtime) mtime from xcl_players where pid = %d", $cid ? $cid : $pid));
				if ($result = mysql_fetch_assoc($results))
				{
					echo("<table><tr><th>Rank<th>Name<th colspan=2>Stats<th>Points<th>Date");
					do
					{
						printf("<tr><td align=right>%d<td>%s<td align=right>%d<td align=right>%d<td align=right>%d<td>%s", $result['rank'], $result['name'], $result['win_count'], $result['loss_count'], $result['points'], gmdate("H:i d-m-Y", $result['mtime']));
					}
					while ($result = mysql_fetch_assoc($results));
					echo("</table><hr>");
				}
				$results = db_query($cid
					? sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime from xcl_games t1 inner join xcl_games_players t2 using (gid) left join xcl_maps t3 on (t1.scen = t3.fname) where t2.cid = %d order by gid desc", $cid)
					: sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) scen, unix_timestamp(t1.mtime) mtime from xcl_games t1 inner join xcl_games_players t2 using (gid) left join xcl_maps t3 on (t1.scen = t3.fname) where not t2.cid and t2.pid = %d order by gid desc", $pid));
			}
			echo_games($results, $pid, $cid, $unfair_games);
			if ($cid || $pid)
			{
				if ($cid)
				{
					$results = db_query(sprintf("select p.name, sum(pc > 0) w,  sum(pc < 0) l, sum(greatest(pc, 0)) pw, sum(least(pc, 0)) pl, sum(pc) pc from xcl_games_players gp inner join xcl_players p using (pid) where cid = %d group by p.pid order by name", $cid));
					echo("<hr><table>");
					while ($result = mysql_fetch_assoc($results))
					{
						printf("<tr><td>%s<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d", $result['name'], $result[w], $result[l], $result[pw], $result[pl], $result[pc]);
					}
					echo("</table>");
				}
				$results = db_query($cid
					? sprintf("select cty, count(*) count from xcl_games_players where cid = %d group by cty order by count desc", $cid)
					: sprintf("select cty, count(*) count from xcl_games_players where not cid and pid = %d group by cty order by count desc", $pid));
				if ($result = mysql_fetch_assoc($results))
				{
					echo("<hr><table><tr><th>Count<th>Country");
					do
					{
						printf("<tr><td align=right>%d<td><img src=\"%s\" alt=\"%s\">", $result['count'], get_country_flag_url($result['cty']), get_country_name($result['cty']));
					}
					while ($result = mysql_fetch_assoc($results));
					echo("</table>");
				}
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) scen, count(*) count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where cid = %d group by scen order by count desc", $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) scen, count(*) count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where not cid and pid = %d group by scen order by count desc", $pid));
				if ($result = mysql_fetch_assoc($results))
				{
					echo("<hr><table><tr><th>Count<th>Scenario");
					do
					{
						printf("<tr><td align=right>%d<td>%s", $result['count'], $result['scen']);
					}
					while ($result = mysql_fetch_assoc($results));
					echo("</table>");
				}
			}
			else if ($gid)
			{
				$results = db_query(sprintf("select * from xcl_games_players inner join xcl_players using (pid) where gid = %d", $gid));
				echo("<hr><table>");
				while ($result = mysql_fetch_assoc($results))
				{
					printf("<tr><th>%s<th>killed<th>bought<th>left<th>captured", $result['name']);
					printf("<tr><td align=right>units<td align=right>%d<td align=right>%d<td align=right>%d", $result[unk], $result[unb], $result[unl]);
					printf("<tr><td align=right>buildings<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d", $result[blk], $result[blb], $result[bll], $result[blc]);
					printf("<tr><td align=right>infantry<td align=right>%d<td align=right>%d<td align=right>%d", $result[ink], $result[inb], $result[inl]);
					printf("<tr><td align=right>planes<td align=right>%d<td align=right>%d<td align=right>%d", $result[plk], $result[plb], $result[pll]);
				}
				echo("</table>");
			}
		}
		else
		{
?>
<center>
	<form action="<?php echo $_SERVER[SCRIPT_NAME]; ?>">
		<table>
			<tr>
				<td>Player:<input type=hidden name=lid value=<?php echo($lid) ?>>
				<td><input type=text name=pname size=9>
				<td><input type=submit value="Search">
			</tr>
		</table>
	</form>
</center>
<hr>
<?php
			if ($lid || $pname)
			{
				echo("<center><table><tr>");
				if (!$lid)
					echo("<th>Ladder");
				echo("<th>Rank<th><th>Name<th colspan=2>Stats<th>Points<th>Date<th colspan=10>Countries");
				$results = db_query($pname
					? $lid
					? sprintf("select xcl_players.*, unix_timestamp(xcl_players.mtime) mtime from xcl_players where xcl_players.lid = %d and xcl_players.name like \"%s\" order by points desc limit 250", $lid, AddSlashes($pname))
					: sprintf("select xcl_players.*, unix_timestamp(xcl_players.mtime) mtime from xcl_players where xcl_players.name like \"%s\" order by points desc limit 250", AddSlashes($pname))
					: sprintf("select xcl_players.*, unix_timestamp(xcl_players.mtime) mtime from xcl_players where xcl_players.lid = %d and points order by points desc limit 250", $lid));
				if ($result = mysql_fetch_assoc($results))
				{
					do
					{
						echo("<tr>");
						if (!$lid)
							printf("<td><a href=\"?lid=%d\">%s</a>", $result['lid'], lid2a($result['lid']));
						printf("<td align=right>%d<td>", $result['rank']);
						if ($lid & 1)
						{
							echo("<img src=\"images/cooperat.png\" alt=\"XCL Founder\">");
							if ($result['points_max'] > 1500)
								echo(" <img src=\"images/stargen.png\" alt=\"&gt; 1500p\">");
							else if ($result['points_max'] > 1000)
								echo(" <img src=\"images/general.png\"  alt=\"&gt; 1000p\">");
							else if ($result['points_max'] > 500)
								echo(" <img src=\"images/briggenr.png\" alt=\"&gt; 500p\">");
							if ($result['rank'] == 1)
								echo(" <img src=\"images/comchief.png\" alt=\"#1\">");
							else if ($result['rank'] && $result['rank'] < 26)
								echo(" <img src=\"images/colonel.png\" alt=\"< #26\">");
						}
						printf("<td><a href=\"?%s=%d\">%s</a><td align=right>%d<td align=right>%d<td align=right>%d<td>%s", $result['lid'] & 1 ? "pid" : "cid", $result['pid'], $result['name'], $result['win_count'], $result['loss_count'], $result['points'], gmdate("H:i d-m-Y", $result['mtime']));
						for ($i = 0; $i < 10; $i++)
						{
							if ($result['countries'] & 1 << $i)
							{
								switch ($result['lid'])
								{
								case 5:
								case 6:
									printf("<td><img src=\"%s\" alt=\"%s\"> ", get_country_flag_url(0x100 | $i), get_country_name(0x100 | $i));
									break;
								case 7:
								case 8:
									printf("<td><img src=\"%s\" alt=\"%s\"> ", get_country_flag_url(0x200 | $i), get_country_name(0x200 | $i));
									break;
								default:
									printf("<td><img src=\"%s\" alt=\"%s\"> ", get_country_flag_url($i), get_country_name($i));
								}
							}
							else
								echo("<td>");
						}
					}
					while ($result = mysql_fetch_assoc($results));
				}
				else
					echo("<tr><th colspan=10>-");
				echo("</table></center>");
			}
			else
			{
?>
<center>
	<table>
		<tr>
			<td align=right>Tiberian Sun
			<td><a href="?lid=ts">Player</a>
			<td><a href="?lid=ts_clan">Clan</a>
		<tr>
			<td align=right>Red Alert 2
			<td><a href="?lid=ra2">Player</a>
			<td><a href="?lid=ra2_clan">Clan</a>
		<tr>
			<td align=right>Yuri's Revenge
			<td><a href="?lid=ra2_yr">Player</a>
			<td><a href="?lid=ra2_yr_clan">Clan</a>
		<tr>
			<td align=center colspan=3><a href="ra2">Westwood Studios Style Ladder</a>
	</table>
</center>
<?php
			}
		}
	}
	@include("bottom.php");
?>