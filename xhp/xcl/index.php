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
		$pnames = explode(",", $_GET[pname]);
		foreach ($pnames as $key => $pname)
			$pnames[$key] = sprintf("\"%s\"", AddSlashes(trim($pname)));
		$results = db_query(sprintf("select * from xcl_players where name in (%s)", implode(",", $pnames)));
		while ($result = mysql_fetch_array($results))
			printf("document.write(\"<a href=\\\"http://xccu.sourceforge.net/xcl/?%s=%d\\\">%s</a>: #%d %d / %d %dp<br>\");", $result[lid] & 1 ? "pid" : "cid", $result[pid], $result[name], $result[rank], $result[win_count], $result[loss_count], $result[points]);
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
<!--
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
<hr>-->
<center>
	<TABLE WIDTH=728 BORDER=0 CELLPADDING=0 CELLSPACING=0>
		<TR>
			<TD COLSPAN=9>
				<IMG SRC="images/greyslices_01.gif" WIDTH=728 HEIGHT=51 ALT=""></TD>
		</TR>
		<TR>
			<TD>    <A title="Westwood Studios" href="http://westwood.ea.com/" target=_top>
				<IMG SRC="images/greyslices_02.gif" WIDTH=140 HEIGHT=34 ALT=""></A></TD>
			<TD>    <A title="Electronic Arts" href="http://ea.com/" target=_top>
				<IMG SRC="images/greyslices_03.gif" WIDTH=88 HEIGHT=34 ALT=""></a></TD>
			<TD>    <A title="Black List" href="http://xccu.sourceforge.net/xla/xla_black_list.php">
				<IMG SRC="images/greyslices_04.gif" WIDTH=83 HEIGHT=34 ALT=""></a></TD>
			<TD>    <A href="http://xccu.sourceforge.net/xcl/?">
				<IMG SRC="images/greyslices_05.gif" WIDTH=103 HEIGHT=34 ALT=""></a></TD>
			<TD>    <A title="White List" href="http://xccu.sourceforge.net/xla/xla_white_list.php">
				<IMG SRC="images/greyslices_06.gif" WIDTH=84 HEIGHT=34 ALT=""></A></TD>
			<TD>    <A title="Matching Filter" href="http://xccu.sourceforge.net/utilities/MF.zip">
				<IMG SRC="images/greyslices_07.gif" WIDTH=82 HEIGHT=34 ALT=""></A></TD>
			<TD>    <A title="XCC Game Spy" href="http://xccu.sourceforge.net/utilities/XGS.zip">
				<IMG SRC="images/greyslices_08.gif" WIDTH=91 HEIGHT=34 ALT=""></A></TD>
			<TD>
				<IMG SRC="images/greyslices_09.gif" WIDTH=56 HEIGHT=34 ALT=""></TD>
			<TD>
				<IMG SRC="images/greyslices_10.gif" WIDTH=1 HEIGHT=34 ALT=""></TD>
		</TR>
		<TR>
			<TD>
				<IMG SRC="images/greyslices_11.gif" WIDTH=140 HEIGHT=39 ALT=""></TD>
			<TD>    <A title=Documents href="http://xccu.sourceforge.net/xcl/docs/">
				<IMG SRC="images/greyslices_12.gif" WIDTH=88 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A title="Hall of Fame" href="http://xccu.sourceforge.net/xcl/?hof=">
				<IMG SRC="images/greyslices_13.gif" WIDTH=83 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A href="http://xccu.sourceforge.net/cgi-bin/forum.cgi">
				<IMG SRC="images/greyslices_14.gif" WIDTH=103 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A title="Hall of Shame" href="http://xccu.sourceforge.net/xcl/?hos=">
				<IMG SRC="images/greyslices_15.gif" WIDTH=84 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A href="http://xccu.sourceforge.net/xcl/?stats=">
				<IMG SRC="images/greyslices_16.gif" WIDTH=82 HEIGHT=39 ALT=""></a></TD>
			<TD COLSPAN=3>
				<IMG SRC="images/greyslices_17.gif" WIDTH=148 HEIGHT=39 ALT=""></TD>
		</TR>
		<TR>
			<TD COLSPAN=3>
				<IMG SRC="images/greyslices_18.gif" WIDTH=311 HEIGHT=39 ALT=""></TD>
			<TD>    <A href="http://xccu.sourceforge.net/xcl/?lid=<?php echo $lid ?>&amp;update_ranks=">
				<IMG SRC="images/greyslices_19.gif" WIDTH=103 HEIGHT=39 ALT=""></a></TD>
			<TD COLSPAN=5>
				<IMG SRC="images/greyslices_20.gif" WIDTH=314 HEIGHT=39 ALT=""></TD>
		</TR>
	</TABLE>
</center>
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
		return $v ? $v > 0 ? '+' . $v : $v : "";
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

	function echo_player($player)
	{
		printf("<td><a href=\"?pid=%d\" title=\"#%d %d / %d %dp\">%s</a><td>", $player[pid], $player[rank], $player[win_count], $player[loss_count], $player[points], $player[name]);
		echo("");
		if ($player[cid])
			printf("<a href=\"?cid=%d\">%s</a>", $player[cid], $player[cname]);
		printf("<td><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($player[cty]), get_country_name($player[cty]), cmp2a($player[cmp]), pc2a($player[pc]));
	}

	function echo_games($results, $pid, $cid, $unfair_games)
	{
		echo($cid
			? "<table><tr><th>GID<th colspan=5>Clan A<th colspan=5>Clan B<th>Duration<th>Scenario<th>WS GID<th>Date"
			: "<table><tr><th>GID<th colspan=5>Player A<th colspan=5>Player B<th>Duration<th>Scenario<th>WS GID<th>Date");
		if ($result = mysql_fetch_array($results))
		{
			do
			{
				printf("<tr><td align=right><a href=\"?gid=%d\">%d</a>", $result[gid], $result[gid]);
				$players_result = db_query(sprintf("select t1.*, t2.*, t3.name as cname from xcl_games_players as t1 inner join xcl_players as t2 using (pid) left join xcl_players as t3 on (t1.cid = t3.pid) where gid = %d order by %s", $result[gid], $cid ? sprintf("cid != %d, t2.pid", $cid) : ($pid ? sprintf("t2.pid != %d", $pid) : "cid, t2.pid")));
				$plrs = mysql_num_rows($players_result) / 2;
				for ($player_i = 0; $players[$player_i] = mysql_fetch_array($players_result); $player_i++)
					;
				$player_a = 0;
				$player_b = $plrs;
				echo_player($players[$player_a++]);
				echo_player($players[$player_b++]);
				printf("<td align=right>%s<td>%s<td align=right>%s<td>%s<td>%d<td>%s<td>%d<td>%d",
					dura2a($result[dura]), $result[scen], $result[gsku] == 0x2100 ? sprintf("<a href=\"http://games2.westwood.com/ra2gamelogs/%d.html\">%d</a>", $result[ws_gid], $result[ws_gid]) : sprintf("%d", $result[ws_gid]), date("H:i d-m-Y", $result[mtime]),
					$result[afps], gsku2a($result[gsku]), $result[oosy], $result[trny]);
				if ($unfair_games)
					printf("<td><a href=\"/xla/admin/xcl_return_points.php?gid=%d\">Return points</a>", $result[gid]);
				for (; $player_a < $plrs; $player_a++, $player_b++)
				{
					echo("<tr><td>");
					echo_player($players[$player_a++]);
					echo_player($players[$player_b++]);
					echo("<td colspan=4>");
				}
			}
			while ($result = mysql_fetch_array($results));
		}
		else
			echo("<tr><th colspan=15>-");
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
		echo("<table><tr><th>Games<th>Game");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
		echo("</table><hr>");
		$results = db_query(sprintf("select gsku, count(distinct pid) as count from xcl_games inner join xcl_games_players using (gid) where trny = 1 group by gsku order by count desc"));
		echo("<table><tr><th>Players<th>Game");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
		echo("</table><hr>");
		$results = db_query(sprintf("select gsku, count(distinct cid) as count from xcl_games inner join xcl_games_players using (gid) where trny = 2 group by gsku order by count desc"));
		echo("<table><tr><th>Clans<th>Game");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
		echo("</table><hr>");
		$results = db_query(sprintf("select cty, count(*) as count from xcl_games_players group by cty order by count desc"));
		echo("<table><tr><th>Count<th>Country");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td><img src=\"%s\" alt=\"%s\">", $result[count], get_country_flag_url($result[cty]), get_country_name($result[cty]));
		echo("</table><hr>");
		$results = db_query(sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, xcl_games.scen as scen_fname, count(*) as count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname group by scen order by count desc"));
		echo("<table><tr><th>Count<th>Scenario");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], $result[scen]);
		echo("</table><hr>");
		$results = db_query(sprintf("select round(dura / 600) * 10 as dura, count(*) as count from xcl_games group by dura order by dura"));
		echo("<table><tr><th>Count<th>Duration");
		while ($result = mysql_fetch_array($results))
		{
			printf("<tr><td align=right>%d<td align=right>", $result[count]);
			if ($result[dura])
				printf("%d - %d", $result[dura] - 5, $result[dura] + 5);
			else
				echo("< 5");
		}
		echo("</table>");
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
					select t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1 left join xcl_maps as t3 on (t1.scen = t3.fname)
					where t1.gid = %d
					order by gid desc
					", $gid));
			else if ($recent_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1 left join xcl_maps as t3 on (t1.scen = t3.fname)
					order by gid desc
					limit 25
					"));
			else if ($unfair_games)
				$results = db_query(sprintf("
					select distinct t1.*, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from bl inner join xcl_players using (name) inner join xcl_games_players as t2 using (pid) inner join xcl_games as t1 using (gid) inner join xcl_games_players as t3 using (gid) left join xcl_maps as t4 on (t1.scen = t4.fname)
					where not t3.cid and t3.pc < 0
					order by gid desc
					"));
			else if ($wash_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1 left join xcl_maps as t3 on (t1.scen = t3.fname)
					where t1.oosy
					order by gid desc
					"));
			else
			{
				$results = db_query($cid
					? sprintf("select cty, count(*) as count from xcl_games_players where cid = %d group by cty order by count desc", $cid)
					: sprintf("select cty, count(*) as count from xcl_games_players where not cid and pid = %d group by cty order by count desc", $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<table><tr><th>Count<th>Country");
					do
					{
						printf("<tr><td align=right>%d<td><img src=\"%s\" alt=\"%s\">", $result[count], get_country_flag_url($result[cty]), get_country_name($result[cty]));
					}
					while ($result = mysql_fetch_array($results));
					echo("</table><hr>");
				}
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where cid = %d group by scen order by count desc", $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where not cid and pid = %d group by scen order by count desc", $pid));
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
					? sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1 inner join xcl_games_players as t2 using (gid) left join xcl_maps as t3 on (t1.scen = t3.fname) where t2.cid = %d order by gid desc", $cid)
					: sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1 inner join xcl_games_players as t2 using (gid) left join xcl_maps as t3 on (t1.scen = t3.fname) where not t2.cid and t2.pid = %d order by gid desc", $pid));
			}
			echo_games($results, $pid, $cid, $unfair_games);
			if ($gid)
			{
				$results = db_query(sprintf("select * from xcl_games_players inner join xcl_players using (pid) where gid = %d", $gid));
				echo("<hr><table>");
				while ($result = mysql_fetch_array($results))
				{
					printf("<tr><th>%s<th>killed<th>bought<th>left<th>captured", $result[name]);
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
							echo("<img src=\"http://xcl.the-outsiders.net/badges/cooperat.png\" alt=\"XCL Founder\">");
							if ($result[points_max] > 1500)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/stargen.png\" alt=\"&gt; 1500p\">");
							else if ($result[points_max] > 1000)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/general.png\"  alt=\"&gt; 1000p\">");
							else if ($result[points_max] > 500)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/briggenr.png\" alt=\"&gt; 500p\">");
							if ($result[rank] == 1)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/comchief.png\" alt=\"#1\">");
							else if ($result[rank] && $result[rank] < 26)
								echo(" <img src=\"http://xcl.the-outsiders.net/badges/colonel.png\" alt=\"< #26\">");
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