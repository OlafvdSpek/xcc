<?php
	require("../xcc_common.php");

	ob_start(ob_gzhandler);
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
		}
		return 0;
	}

	function lid2a($v)
	{
		$names = array("", "ra2", "ra2 c", "yr", "yr c");
		return $names[$v];
	}

	$lid = a2lid($_GET[lid]);
	if (isset($_GET[js]))
	{
		$results = db_query(sprintf("select * from xcl_players where name = \"%s\"", AddSlashes($_GET[pname])));
		while ($result = mysql_fetch_array($results))
			printf("document.write(\"<a href=\\\"http://xccu.sourceforge.net/xcl/\\\">XCL</a>: <a href=\\\"http://xccu.sourceforge.net/xcl/?pid=%d\\\">%s</a>: #%d %d / %d %dp<br>\");", $result[pid], $result[name], $result[rank], $result[win_count], $result[loss_count], $result[points]);
		return;
	}
	else if (isset($_GET[pure]))
	{
		$results = db_query(sprintf("select * from xcl_players where lid = %d and name = \"%s\"", $lid, AddSlashes($_GET[pname])));
		if ($result = mysql_fetch_array($results))
			printf("%d %d %d %d", $result[rank], $result[win_count], $result[loss_count], $result[points]);
		return;
	}
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<link rel=stylesheet href="/xcl.css">
	<meta http-equiv=content-type content="text/html; charset=us-ascii">
	<title>XCC Community Ladder</title>
<table width="100%">
	<tr>
		<td valign=bottom>
			<p class=page_title>
				XCC Community Ladder
		<td align=right valign=bottom>
			<a href="/xla/xla_black_list.php" title="Black List">BL</a> |
			<a href="/xcl/docs/" title="Documents">Docs</a> |
			<a target=_top href="http://ea.com/" title="Electronic Arts">EA</a> |
			<a href="/cgi-bin/forum.cgi">Forum</a> |
			<a href="/utilities/MF.zip" title="Matching Filter">MF</a> |
			<a href="/xla/xla_white_list.php" title="White List">WL</a> |
			<a target=_top href="http://westwood.ea.com/" title="Westwood Studios">WS</a> |
			<a href="/utilities/XGS.zip" title="XCC Game Spy">XGS</a><br>
			<a href="?hof=" title="Hall of Fame">HoF</a> |
			<a href="?hos=" title="Hall of Shame">HoS</a> |
			<a href="?">Home</a> | <a href="?stats=">Stats</a> |
			<a href="?lid=<?php echo $lid ?>&amp;update_ranks=">Update</a>
</table>
<hr>
<?php
	function cmp2a($v)
	{
		switch ($v)
		{
		case 0x100:
			return "Won";
		case 0x200:
		case 0x210:
			return "Lost";
		case 0x220:
			return "Lost by dc";
		}
		return $v;
	}

	function get_country_name($i)
	{
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
		return $country_names[$i];
	}

	function get_country_flag_url($i)
	{
		$country_flag_urls = array
		(
			"http://xcc.arm-ent.com/xcl/usai.png",
			"http://xcc.arm-ent.com/xcl/japi.png",
			"http://xcc.arm-ent.com/xcl/frai.png",
			"http://xcc.arm-ent.com/xcl/geri.png",
			"http://xcc.arm-ent.com/xcl/gbri.png",
			"http://xcc.arm-ent.com/xcl/djbi.png",
			"http://xcc.arm-ent.com/xcl/arbi.png",
			"http://xcc.arm-ent.com/xcl/lati.png",
			"http://xcc.arm-ent.com/xcl/rusi.png",
			"http://xcc.arm-ent.com/xcl/yrii.png",
		);
		return $country_flag_urls[$i];
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
		case 0x2100:
			return "RA2";
		case 0x2900:
			return "YR";
		}
		return sprintf("%x", $v);
	}

	function pc2a($v)
	{
		return $v > 0 ? '+' . $v : $v;
	}

	function update_ranks($lid)
	{
		$results = db_query(sprintf("select pid, rank from xcl_players where lid = %d order by points desc", $lid));
		$rank = 1;
		while ($result = mysql_fetch_array($results))
		{
			if ($result[rank] != $rank)
				db_query(sprintf("update xcl_players set rank = %d, mtime = mtime where pid = %d", $rank, $result[pid]));
			$rank++;
		}
	}

	function echo_hof($lid, $title)
	{
		printf("<table><tr><th colspan=2>%s<tr><th>Rank<th>Name", $title);
		$results = db_query($lid & 1
			? sprintf("select xcl_players.* from xcl_players inner join wl using (name) where lid = %d order by points desc limit 10", $lid)
			: sprintf("select * from xcl_players where lid = %d order by points desc limit 10", $lid));
		$rank = 1;
		while ($result = mysql_fetch_array($results))
		{
			printf("<tr><td align=right>%d<td>%s", $rank++, $result[name]);
		}
		echo("</table>");
	}

	function echo_games($results, $pid, $cid, $unfair_games)
	{
		echo("<table><tr><th>GID<th colspan=4>Player A<th colspan=4>Player B<th>Duration<th>Scenario<th>WS GID<th>Date");
		if ($result = mysql_fetch_array($results))
		{
			do
			{
				printf("<tr><td align=right><a href=\"?gid=%d\">%d</a>", $result[gid], $result[gid]);
				if ($result[a_pid] == $pid || $result[a_cid] == $cid)
				{
					printf("<td><a href=\"?pid=%d\">%s</a>", $result[a_pid], $result[a_name]);
					if ($result[a_cid])
						printf(" (<a href=\"?cid=%d\">%s</a>)", $result[a_cid], $result[a_cname]);
					printf("<td><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($result[a_cty]), get_country_name($result[a_cty]), cmp2a($result[a_cmp]), pc2a($result[a_pc]));
					printf("<td><a href=\"?pid=%d\">%s</a>", $result[b_pid], $result[b_name]);
					if ($result[b_cid])
						printf(" (<a href=\"?cid=%d\">%s</a>)", $result[b_cid], $result[b_cname]);
					printf("<td><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($result[b_cty]), get_country_name($result[b_cty]), cmp2a($result[b_cmp]), pc2a($result[b_pc]));
				}
				else
				{
					printf("<td><a href=\"?pid=%d\">%s</a>", $result[b_pid], $result[b_name]);
					if ($result[b_cid])
						printf(" (<a href=\"?cid=%d\">%s</a>)", $result[b_cid], $result[b_cname]);
					printf("<td><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($result[b_cty]), get_country_name($result[b_cty]), cmp2a($result[b_cmp]), pc2a($result[b_pc]));
					printf("<td><a href=\"?pid=%d\">%s</a>", $result[a_pid], $result[a_name]);
					if ($result[a_cid])
						printf(" (<a href=\"?cid=%d\">%s</a>)", $result[a_cid], $result[a_cname]);
					printf("<td><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($result[a_cty]), get_country_name($result[a_cty]), cmp2a($result[a_cmp]), pc2a($result[a_pc]));
				}
				printf("<td align=right>%s<td>%s<td align=right>%s<td>%s<td>%d<td>%s<td>%d<td>%d",
					dura2a($result[dura]), $result[scen], $result[gsku] == 0x2100 ? sprintf("<a href=\"http://games2.westwood.com/ra2gamelogs/%d.html\">%d</a>", $result[ws_gid], $result[ws_gid]) : sprintf("%d", $result[ws_gid]), date("H:i d-m-Y", $result[mtime]),
					$result[afps], gsku2a($result[gsku]), $result[oosy], $result[trny]);
				/*
				if ($result[a_pid] == $pid || $result[a_cid] == $cid)
					printf("<td>%s<td>%s", long2ip($result[a_ipa]), long2ip($result[b_ipa]));
				else
					printf("<td>%s<td>%s", long2ip($result[b_ipa]), long2ip($result[a_ipa]));
				*/
				if ($unfair_games)
					printf("<td><a href=\"/xla/admin/xcl_return_points.php?gid=%d\">Return points</a>", $result[gid]);
			}
			while ($result = mysql_fetch_array($results));
		}
		else
			echo("<tr><th colspan=13>-");
		echo("</table>");
	}

	if (isset($_GET[update_ranks]))
	{
		for ($i = 1; $i < 5; $i++)
			update_ranks($i);
	}
	if (isset($_GET[hof]))
	{
		echo("<center><table><tr><td>");
		echo_hof(1, "Red Alert 2");
		echo("<td><td>");
		echo_hof(2, "Clan");
		echo("<td><td>");
		echo_hof(3, "Yuri's Revenge");
		echo("<td><td>");
		echo_hof(4, "Clan");
		echo("</table></center>");
		echo("<hr><center><table><tr><th colspan=8>May<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>xclhenl<tr><td align=right>2<td>israelck<tr><td align=right>3<td>camelsun<tr><td align=right>4<td>urptsrmin<tr><td align=right>5<td>dad0m1n8r<tr><td align=right>6<td>xclmael<tr><td align=right>7<td>samnpete<tr><td align=right>8<td>xclblimp<tr><td align=right>9<td>xtf<tr><td align=right>10<td>xclnova</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>i*e*f<tr><td align=right>2<td>bo-om<tr><td align=right>3<td>dgnf<tr><td align=right>4<td>tanx..<tr><td align=right>5<td>.tc.<tr><td align=right>6<td>cnc.b<tr><td align=right>7<td>@59@<tr><td align=right>8<td>etf.!.<tr><td align=right>9<td>@k.o@<tr><td align=right>10<td>@soad-</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>xclvolkov<tr><td align=right>2<td>imgodsson<tr><td align=right>3<td>xclhenl<tr><td align=right>4<td>me12inch<tr><td align=right>5<td>iraqnoob<tr><td align=right>6<td>wahooooma<tr><td align=right>7<td>tanksh0ck<tr><td align=right>8<td>xclearthy<tr><td align=right>9<td>xcltecboy<tr><td align=right>10<td>xcliraq</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>-.h.-<tr><td align=right>2<td>om3rta<tr><td align=right>3<td>o*t*s<tr><td align=right>4<td>runnwb<tr><td align=right>5<td>r@ptor<tr><td align=right>6<td>*eite*<tr><td align=right>7<td>kapoks<tr><td align=right>8<td>--ba--<tr><td align=right>9<td>adeath<tr><td align=right>10<td>*bbw.r</table></table></center>");
		echo("<hr><center><table><tr><th colspan=8>April<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>jmedran0<tr><td align=right>2<td>cnckn0va<tr><td align=right>3<td>pm3k3p6d<tr><td align=right>4<td>l4yla<tr><td align=right>5<td>kbloodyr<tr><td align=right>6<td>urptsrmin<tr><td align=right>7<td>xtf<tr><td align=right>8<td>ra2ownag3<tr><td align=right>9<td>astr0n4ut<tr><td align=right>10<td>abogeyman</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>dgnf<tr><td align=right>2<td>-ragt-<tr><td align=right>3<td>do-ne<tr><td align=right>4<td>*soad-<tr><td align=right>5<td>he-lp!<tr><td align=right>6<td>-alc-<tr><td align=right>7<td>t*d*e<tr><td align=right>8<td>@soad-<tr><td align=right>9<td>@gw@<tr><td align=right>10<td>*usa_</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>xclseal<tr><td align=right>2<td>me12inch<tr><td align=right>3<td>jonisb4ck<tr><td align=right>4<td>xclrulez<tr><td align=right>5<td>xclezrush<tr><td align=right>6<td>xcljoku<tr><td align=right>7<td>xcltheone<tr><td align=right>8<td>xclmurlaw<tr><td align=right>9<td>xclffs<tr><td align=right>10<td>amikloy</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>*03*<tr><td align=right>2<td>adeath<tr><td align=right>3<td>441644<tr><td align=right>4<td>*ps-e*<tr><td align=right>5<td>o*t*s<tr><td align=right>6<td>team.b<tr><td align=right>7<td>**21**<tr><td align=right>8<td>--ba--<tr><td align=right>9<td>_rnx_<tr><td align=right>10<td>-00-</table></table></center>");
		echo("<hr><center><table><tr><th colspan=2>March<tr><th>Rank<th>Name<tr><td align=right>1<td>cncviking<tr><td align=right>2<td>premierez<tr><td align=right>3<td>serge4nt<tr><td align=right>4<td>m270mlrs<tr><td align=right>5<td>aaai2a2<tr><td align=right>6<td>awazrobbi<tr><td align=right>7<td>wi4israel<tr><td align=right>8<td>xclsovgod<tr><td align=right>9<td>unstop4bl<tr><td align=right>10<td>iluveisso</table></center>");
	}
	else if (isset($_GET[hos]))
	{
		echo("<center><table><tr><th>Name");
		$results = db_query("select xcl_players.* from xcl_players inner join bl using (name) order by xcl_players.name");
		while ($result = mysql_fetch_array($results))
		{
			printf("<tr><td>%s", $result[name]);
			if ($result[points])
				db_query(sprintf("update xcl_players set points = 0 where pid = %d", $result[pid]));
		}
		echo("</table></center>");
	}
	else if (isset($_GET[stats]))
	{
		$results = db_query(sprintf("select gsku, count(*) as count from xcl_games group by gsku order by count desc"));
		if ($result = mysql_fetch_array($results))
		{
			echo("<table><tr><th>Count<th>Game");
			do
			{
				printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
			}
			while ($result = mysql_fetch_array($results));
			echo("</table><hr>");
		}
		/*
		$results = db_query(sprintf("select if(a_pid = %d, a_cty, b_cty) as country, count(*) as count from xcl_games where a_pid = %d or b_pid = %d group by country order by count desc", $pid, $pid, $pid));
		if ($result = mysql_fetch_array($results))
		{
			echo("<table><tr><th>Count<th>Country");
			do
			{
				printf("<tr><td align=right>%d<td>%s<td>%s", $result[count], get_country_name($result[country]), get_country_flag_url($result[country]));
			}
			while ($result = mysql_fetch_array($results));
			echo("</table><hr>");
		}
		*/
		$results = db_query(sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, xcl_games.scen as scen_fname, count(*) as count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname group by scen order by count desc"));
		if ($result = mysql_fetch_array($results))
		{
			echo("<table><tr><th>Count<th>Scenario");
			do
			{
				printf("<tr><td align=right>%d<td>%s", $result[count], $result[scen]);
				/*
				$scen_url = strtolower($result[scen_fname]);
				if (($i = strrpos($scen_url, ".")) !== false)
					$scen_url = substr($scen_url, 0, $i);
				printf("<tr><td align=right>%d<td>%s<td><img src=\"/documents/ra2/multi_maps/%s_pv.png\">", $result[count], $result[scen], $scen_url);
				*/
			}
			while ($result = mysql_fetch_array($results));
			echo("</table><hr>");
		}
		$results = db_query(sprintf("select round(dura / 600) * 10 as dura, count(*) as count from xcl_games group by dura order by dura"));
		if ($result = mysql_fetch_array($results))
		{
			echo("<table><tr><th>Count<th>Duration");
			do
			{
				printf("<tr><td align=right>%d<td align=right>", $result[count]);
				if ($result[dura])
					printf("%d - %d", $result[dura] - 5, $result[dura] + 5);
				else
					printf("< 5");
			}
			while ($result = mysql_fetch_array($results));
			echo("</table>");
		}
	}
	else
	{
		$cid = $_GET[cid];
		$gid = $_GET[gid];
		$pid = $_GET[pid];
		$pname = trim($_GET[pname]);
		$recent_games = $_GET[recent_games];
		if ($cid || $gid || $pid || $recent_games || $unfair_games || $wash_games)
		{
			if ($gid)
				$results = db_query(sprintf("
					select t1.*, t2.name as a_name, t3.name as b_name, t5.name as a_cname, t6.name as b_cname, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname left join xcl_players as t5 on (t5.pid = a_cid) left join xcl_players as t6 on (t6.pid = b_cid)
					where t2.pid = a_pid and t3.pid = b_pid and gid = %d
					", $gid));
			else if ($recent_games)
				$results = db_query(sprintf("
					select t1.*, t2.name as a_name, t3.name as b_name, t5.name as a_cname, t6.name as b_cname, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname left join xcl_players as t5 on (t5.pid = a_cid) left join xcl_players as t6 on (t6.pid = b_cid)
					where t2.pid = a_pid and t3.pid = b_pid
					order by gid desc
					limit 25
					"));
			else if ($unfair_games)
			{
				$results = db_query(sprintf("
					select t1.*, t2.name as a_name, t3.name as b_name, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname, bl
					where trny = 1 && (bl.name = t2.name && b_pc < 0 || bl.name = t3.name && a_pc < 0) and t2.pid = a_pid and t3.pid = b_pid
					order by gid desc
					limit 25
					"));
				echo_games($results, 0, 0, true);
				echo("<hr>");
				$results = db_query(sprintf("
					select t1.*, t2.name as a_name, t3.name as b_name, t5.name as a_cname, t6.name as b_cname, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname left join xcl_players as t5 on (t5.pid = a_cid) left join xcl_players as t6 on (t6.pid = b_cid), bl
					where trny = 2 && (bl.name = t2.name && b_pc < 0 || bl.name = t3.name && a_pc < 0) and t2.pid = a_pid and t3.pid = b_pid
					order by gid desc
					limit 25
					"));
			}
			else if ($wash_games)
				$results = db_query(sprintf("
					select t1.*, t2.name as a_name, t3.name as b_name, t5.name as a_cname, t6.name as b_cname, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname left join xcl_players as t5 on (t5.pid = a_cid) left join xcl_players as t6 on (t6.pid = b_cid)
					where t1.oosy and t2.pid = a_pid and t3.pid = b_pid
					order by gid desc
					"));
			else
			{
				$results = db_query($cid
					? sprintf("select if(a_cid = %d, a_cty, b_cty) as country, count(*) as count from xcl_games where a_cid = %d or b_cid = %d group by country order by count desc", $cid, $cid, $cid)
					: sprintf("select if(a_pid = %d, a_cty, b_cty) as country, count(*) as count from xcl_games where trny = 1 and (a_pid = %d or b_pid = %d) group by country order by count desc", $pid, $pid, $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<table><tr><th>Count<th>Country");
					do
					{
						printf("<tr><td align=right>%d<td><img src=\"%s\" alt=\"%s\">", $result[count], get_country_flag_url($result[country]), get_country_name($result[country]));
					}
					while ($result = mysql_fetch_array($results));
					echo("</table><hr>");
				}
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname where a_cid = %d or b_cid = %d group by scen order by count desc", $cid, $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname where trny = 1 and (a_pid = %d or b_pid = %d) group by scen order by count desc", $pid, $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<table><tr><th>Count<th>Scenario");
					do
					{
						printf("<tr><td align=right>%d<td>%s", $result[count], $result[scen]);
					}
					while ($result = mysql_fetch_array($results));
					echo("</table><hr>");
				}
				// a $results = db_query(sprintf("select *, unix_timestamp(mtime) as mtime from xcl_players where pid = %d", $cid ? $cid : $pid));
				$results = db_query(sprintf("select xcl_players.*, bl.name as bl, wl.name as wl, unix_timestamp(xcl_players.mtime) as mtime from xcl_players left join bl using (name) left join wl on (xcl_players.name = wl.name) where pid = %d", $cid ? $cid : $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<table><tr><th>Rank<th>Name<th colspan=2>Stats<th>Points<th><th><th>Date");
					do
					{
						printf("<tr><td align=right>%d<td>%s<td align=right>%d<td align=right>%d<td align=right>%d<td>%s<td>%s<td>%s", $result[rank], $result[name], $result[win_count], $result[loss_count], $result[points], $result[bl] ? "BL" : "", $result[wl] ? "WL" : "", date("H:i d-m-Y", $result[mtime]));
					}
					while ($result = mysql_fetch_array($results));
					echo("</table><hr>");
				}
				$results = db_query($cid
					? sprintf("select t1.*, t2.name as a_name, t3.name as b_name, t5.name as a_cname, t6.name as b_cname, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname, xcl_players as t5, xcl_players as t6 where t2.pid = a_pid and t3.pid = b_pid and t5.pid = a_cid and t6.pid = b_cid and (a_cid = %d or b_cid = %d) order by gid desc", $cid, $cid)
					: sprintf("select t1.*, t2.name as a_name, t3.name as b_name, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname where t1.trny = 1 and t2.pid = a_pid and t3.pid = b_pid and (a_pid = %d or b_pid = %d) order by gid desc", $pid, $pid));
			}
			echo_games($results, $pid, $cid, $unfair_games);
			if ($gid)
			{
				$results = db_query(sprintf("select t1.*, t2.name as a_name, t3.name as b_name, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1, xcl_players as t2, xcl_players as t3 left join xcl_maps as t4 on t1.scen = t4.fname where t2.pid = a_pid and t3.pid = b_pid and gid = %d order by gid desc", $gid));
				$result = mysql_fetch_array($results);
				echo("<hr><table>");
				printf("<tr><th>%s<th>killed<th>bought<th>left<th>captured", $result[a_name]);
				printf("<tr><td align=right>units<td align=right>%d<td align=right>%d<td align=right>%d", $result[a_unk], $result[a_unb], $result[a_unl]);
				printf("<tr><td align=right>buildings<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d", $result[a_blk], $result[a_blb], $result[a_bll], $result[a_blc]);
				printf("<tr><td align=right>infantry<td align=right>%d<td align=right>%d<td align=right>%d", $result[a_ink], $result[a_inb], $result[a_inl]);
				printf("<tr><td align=right>planes<td align=right>%d<td align=right>%d<td align=right>%d", $result[a_plk], $result[a_plb], $result[a_pll]);
				printf("<tr><th>%s<th>killed<th>bought<th>left<th>captured", $result[b_name]);
				printf("<tr><td align=right>units<td align=right>%d<td align=right>%d<td align=right>%d", $result[b_unk], $result[b_unb], $result[b_unl]);
				printf("<tr><td align=right>buildings<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d", $result[b_blk], $result[b_blb], $result[b_bll], $result[b_blc]);
				printf("<tr><td align=right>infantry<td align=right>%d<td align=right>%d<td align=right>%d", $result[b_ink], $result[b_inb], $result[b_inl]);
				printf("<tr><td align=right>planes<td align=right>%d<td align=right>%d<td align=right>%d", $result[b_plk], $result[b_plb], $result[b_pll]);
				echo("</table>");
			}
		}
		else
		{
?>
<center>
	<table>
		<form>
			<input type=hidden name=lid value=<?php echo($lid) ?>>
			<tr>
				<td>Player:
				<td><input type=text name=pname size=9>
				<td><input type=submit value="Search">
			</tr>
		</form>
	</table>
</center>
<hr>
<?php
			if ($lid || $pname)
			{
				echo("<center><table><tr>");
				if (!$lid)
					echo("<th>Ladder");
				echo("<th>Rank<th><th>Name<th colspan=2>Stats<th>Points<th><th><th>Date");
				$results = db_query($pname
					? $lid
					? sprintf("select xcl_players.*, bl.name as bl, wl.name as wl, unix_timestamp(xcl_players.mtime) as mtime from xcl_players left join bl using (name) left join wl on (xcl_players.name = wl.name) where xcl_players.lid = %d and xcl_players.name like \"%s\" order by points desc", $lid, AddSlashes($pname))
					: sprintf("select xcl_players.*, bl.name as bl, wl.name as wl, unix_timestamp(xcl_players.mtime) as mtime from xcl_players left join bl using (name) left join wl on (xcl_players.name = wl.name) where xcl_players.name like \"%s\" order by points desc", AddSlashes($pname))
					: sprintf("select xcl_players.*, bl.name as bl, wl.name as wl, unix_timestamp(xcl_players.mtime) as mtime from xcl_players left join bl using (name) left join wl on (xcl_players.name = wl.name) where xcl_players.lid = %d and points order by points desc", $lid));
				if ($result = mysql_fetch_array($results))
				{
					do
					{
						echo("<tr>");
						if (!$lid)
							printf("<td><a href=\"?lid=%d\">%s</a>", $result[lid], lid2a($result[lid]));
						printf("<td align=right>%d<td>", $result[rank]);
						if ($lid & 1)
						{
							echo("<img src=\"http://xcl.the-outsiders.net/badges/cooperat.png\">");
							if ($result[points_max] > 1500)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/stargen.png\">");
							else if ($result[points_max] > 1000)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/general.png\">");
							else if ($result[points_max] > 500)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/briggenr.png\">");
							if ($result[rank] && $result[rank] < 26)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/colonel.png\">");
							if ($result[rank] == 1)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/comchief.png\">");
						}
						printf("<td><a href=\"?%s=%d\">%s</a><td align=right>%d<td align=right>%d<td align=right>%d<td>%s<td>%s<td>%s", $result[lid] & 1 ? "pid" : "cid", $result[pid], $result[name], $result[win_count], $result[loss_count], $result[points], $result[bl] ? "BL" : "", $result[wl] ? "WL" : "", date("H:i d-m-Y", $result[mtime]));
						for ($i = 0; $i < 10; $i++)
						{
							if ($result[countries] & 1 << $i)
								printf("<td><img src=\"%s\" alt=\"%s\"> ", get_country_flag_url($i), get_country_name($i));
							else
								echo("<td>");
						}
					}
					while ($result = mysql_fetch_array($results));
				}
				else
					echo("<tr><th colspan=10>-");
				echo("</table></center>");
			}
			else
			{
				echo("<center>");
				echo("<a href=\"?lid=ra2\">Red Alert 2</a><br>");
				echo("<a href=\"?lid=ra2_clan\">Red Alert 2 Clan</a><br>");
				echo("<a href=\"?lid=ra2_yr\">Yuri's Revenge</a><br>");
				echo("<a href=\"?lid=ra2_yr_clan\">Yuri's Revenge Clan</a><br>");
				echo("</center>");
			}
		}
	}
?>
<hr>
<table width="100%">
	<tr>
		<td align=vtop>
			<a href="http://strike-team.net/">Strike Team.Net</a>
		<td align=right valign=top>
			<?php echo(date("H:i d-m-Y", time())); ?>
</table>
</html>