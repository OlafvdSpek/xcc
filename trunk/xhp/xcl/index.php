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
		if ($cid)
		{
			$results = db_query(sprintf("select p.name, sum(pc > 0) as w,  sum(pc < 0) as l, sum(greatest(pc, 0)) as pw, sum(least(pc, 0)) as pl, sum(pc) as pc from xcl_games_players gp inner join xcl_players p using (pid) where cid = %d group by p.pid order by name", $cid));
			while ($result = mysql_fetch_array($results))
				printf("%s %d %d %d %d %d\n", $result[name], $result[w], $result[l], $result[pw], $result[pl], $result[pc]);
		}
		else if ($lid)
		{
			if ($pname)
				$results = db_query(sprintf("select * from xcl_players where lid = %d and name = \"%s\"", $lid, AddSlashes($_GET[pname])));
			else
				$results = db_query(sprintf("select * from xcl_players where lid = %d and points", $lid));
			while ($result = mysql_fetch_array($results))
				printf("%d %d %d %d %s\n", $result[rank], $result[win_count], $result[loss_count], $result[points], $result[name]);
		}
		return;
	}
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
	<link rel=stylesheet href="/xcl.css">
	<meta http-equiv=content-type content="text/html; charset=us-ascii">
	<title>XCC Community Ladder<?php if (gmdate("d") == 1) echo (" (frozen)") ?></title>
<!--
<table width="100%">
	<tr>
		<td valign=bottom>
			<p class=page_title>
				XCC Community Ladder
		<td align=right valign=bottom>
			<a href="/xla/xla_black_list.php" title="Black List">BL</a> |
			<a href="docs/" title="Documents">Docs</a> |
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
			<TD>    <A title="Black List" href="/xla/xla_black_list.php">
				<IMG SRC="images/greyslices_04.gif" WIDTH=83 HEIGHT=34 ALT=""></a></TD>
			<TD>    <A href="?">
				<IMG SRC="images/greyslices_05.gif" WIDTH=103 HEIGHT=34 ALT=""></a></TD>
			<TD>    <A title="White List" href="/xla/xla_white_list.php">
				<IMG SRC="images/greyslices_06.gif" WIDTH=84 HEIGHT=34 ALT=""></A></TD>
			<TD>    <A title="Matching Filter" href="/utilities/MF.zip">
				<IMG SRC="images/greyslices_07.gif" WIDTH=82 HEIGHT=34 ALT=""></A></TD>
			<TD>    <A title="XCC Game Spy" href="/utilities/XGS.zip">
				<IMG SRC="images/greyslices_08.gif" WIDTH=91 HEIGHT=34 ALT=""></A></TD>
			<TD>
				<IMG SRC="images/greyslices_09.gif" WIDTH=56 HEIGHT=34 ALT=""></TD>
			<TD>
				<IMG SRC="images/greyslices_10.gif" WIDTH=1 HEIGHT=34 ALT=""></TD>
		</TR>
		<TR>
			<TD>
				<IMG SRC="images/greyslices_11.gif" WIDTH=140 HEIGHT=39 ALT=""></TD>
			<TD>    <A title=Documents href="docs/">
				<IMG SRC="images/greyslices_12.gif" WIDTH=88 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A title="Hall of Fame" href="?hof=">
				<IMG SRC="images/greyslices_13.gif" WIDTH=83 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A href="/cgi-bin/forum.cgi">
				<IMG SRC="images/greyslices_14.gif" WIDTH=103 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A title="Hall of Shame" href="?hos=">
				<IMG SRC="images/greyslices_15.gif" WIDTH=84 HEIGHT=39 ALT=""></A></TD>
			<TD>    <A href="?stats=">
				<IMG SRC="images/greyslices_16.gif" WIDTH=82 HEIGHT=39 ALT=""></a></TD>
			<TD COLSPAN=3>
				<IMG SRC="images/greyslices_17.gif" WIDTH=148 HEIGHT=39 ALT=""></TD>
		</TR>
		<TR>
			<TD COLSPAN=3>
				<IMG SRC="images/greyslices_18.gif" WIDTH=311 HEIGHT=39 ALT=""></TD>
			<TD>    <A href="?lid=<?php echo $lid ?>&amp;update_ranks=">
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
		default:
			$country_flag_urls = array
			(
				"http://www.liacs.nl/~ovdspek/xcl/images/usai.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/japi.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/frai.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/geri.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/gbri.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/djbi.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/arbi.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/lati.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/rusi.png",
				"http://www.liacs.nl/~ovdspek/xcl/images/yrii.png",
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
		if ($player[cid])
			printf("<a href=\"?cid=%d\" title=\"#%d %d / %d %dp\">%s</a>", $player[cid], $player[crank], $player[cwin_count], $player[closs_count], $player[cpoints], $player[cname]);
		printf("<td><img src=\"%s\" alt=\"%s\"><td>%s<td align=right>%s", get_country_flag_url($player[cty]), get_country_name($player[cty]), cmp2a($player[cmp]), pc2a($player[pc]));
	}

	function echo_games($results, $pid, $cid, $unfair_games)
	{
		echo($cid
			? "<table><tr><th>GID<th colspan=5>Clan A<th colspan=4>Clan B<th colspan=2>Duration<th>Scenario<th>Date"
			: "<table><tr><th>GID<th colspan=5>Player A<th colspan=4>Player B<th colspan=2>Duration<th>Scenario<th>Date");
		if ($result = mysql_fetch_array($results))
		{
			do
			{
				printf("<tr><td align=right><a href=\"?gid=%d\" title=%d>%d</a>", $result[gid], $result[ws_gid], $result[gid]);
				$players_result = db_query(sprintf("select t1.*, t2.*, t3.rank as crank, t3.name as cname, t3.win_count as cwin_count, t3.loss_count as closs_count, t3.points as cpoints from xcl_games_players as t1 inner join xcl_players as t2 using (pid) left join xcl_players as t3 on (t1.cid = t3.pid) where gid = %d order by %s", $result[gid], $cid ? sprintf("cid != %d, t2.pid", $cid) : ($pid ? sprintf("t2.pid != %d", $pid) : "cid, t2.pid")));
				$plrs = mysql_num_rows($players_result) / 2;
				for ($player_i = 0; $players[$player_i] = mysql_fetch_array($players_result); $player_i++)
					;
				$player_a = 0;
				$player_b = $plrs;
				echo_player($players[$player_a++]);
				echo_player($players[$player_b++]);
				printf("<td align=right>%s<td>%s<td align=right>%s<td>%d<td>%d<td>%d",
					dura2a($result[dura]), $result[scen], gmdate("H:i d-m", $result[mtime]), $result[afps], $result[oosy], $result[trny]);
				if ($unfair_games)
					printf("<td><a href=\"/xla/admin/xcl_return_points.php?gid=%d\">Return points</a>", $result[gid]);
				for (; $player_a < $plrs; $player_a++, $player_b++)
				{
					echo("<tr><td>");
					echo_player($players[$player_a]);
					echo_player($players[$player_b]);
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
		for ($i = 1; $i < 9; $i++)
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
		echo("<hr><center><table><tr><th colspan=8>August<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>unstop4bl<tr><td align=right>2<td>cyaandbye<tr><td align=right>3<td>canminzz<tr><td align=right>4<td>lnstopabl<tr><td align=right>5<td>klr0v<tr><td align=right>6<td>d1sc1pl1n<tr><td align=right>7<td>intagrand<tr><td align=right>8<td>xown4no1x<tr><td align=right>9<td>xclispo0p<tr><td align=right>10<td>xclyoni</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>g@work<tr><td align=right>2<td>g@w0rk<tr><td align=right>3<td>image*<tr><td align=right>4<td>penl$<tr><td align=right>5<td>forum-<tr><td align=right>6<td>farmz<tr><td align=right>7<td>masiv<tr><td align=right>8<td>@s-s@<tr><td align=right>9<td>gamovr<tr><td align=right>10<td>tribe*</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>dron3t4nk<tr><td align=right>2<td>cyaandbye<tr><td align=right>3<td>dr0n3t4nk<tr><td align=right>4<td>tanyab0mb<tr><td align=right>5<td>klr0v<tr><td align=right>6<td>syocikelx<tr><td align=right>7<td>prizes4me<tr><td align=right>8<td>iwin4prep<tr><td align=right>9<td>k3tchup<tr><td align=right>10<td>perottti</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>@dps@<tr><td align=right>2<td>-auf-<tr><td align=right>3<td>myrulz<tr><td align=right>4<td>-svt*p<tr><td align=right>5<td>@dpsb@<tr><td align=right>6<td>oktron<tr><td align=right>7<td>*-gd-*<tr><td align=right>8<td>om3rta<tr><td align=right>9<td>dps*e<tr><td align=right>10<td>penl$</table></table></center>");
		echo("<hr><center><table><tr><th colspan=8>July<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>th3rush3r<tr><td align=right>2<td>cyaandbye<tr><td align=right>3<td>rapyst<tr><td align=right>4<td>xclkong<tr><td align=right>5<td>xclmael<tr><td align=right>6<td>rush4awaz<tr><td align=right>7<td>kirov8234<tr><td align=right>8<td>bigchen11<tr><td align=right>9<td>a1xcl4ra2<tr><td align=right>10<td>xclchen</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>-g3r-<tr><td align=right>2<td>.strm.<tr><td align=right>3<td>wouf<tr><td align=right>4<td>-4some<tr><td align=right>5<td>adida$<tr><td align=right>6<td>jonrim<tr><td align=right>7<td>-1rank<tr><td align=right>8<td>@nrg@<tr><td align=right>9<td>*evo*<tr><td align=right>10<td>*-now-</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>xclxclxcl<tr><td align=right>2<td>why2g00d<tr><td align=right>3<td>xclearthy<tr><td align=right>4<td>nojkovoi<tr><td align=right>5<td>libyapowr<tr><td align=right>6<td>mybush<tr><td align=right>7<td>lutz99999<tr><td align=right>8<td>jokujak<tr><td align=right>9<td>bombnbomb<tr><td align=right>10<td>xcltr00pa</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>*-gd-*<tr><td align=right>2<td>om3rta<tr><td align=right>3<td>-mef-<tr><td align=right>4<td>@dream<tr><td align=right>5<td>oktron<tr><td align=right>6<td>-m@nz-<tr><td align=right>7<td>@tde@<tr><td align=right>8<td>**21**<tr><td align=right>9<td>-dteam<tr><td align=right>10<td>#ud*e#</table></table></center>");
		echo("<hr><center><table><tr><th colspan=8>June<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>xclkane<tr><td align=right>2<td>isovz<tr><td align=right>3<td>ul2ukhai<tr><td align=right>4<td>dimins1on<tr><td align=right>5<td>xclchen<tr><td align=right>6<td>micnbenny<tr><td align=right>7<td>lordofxcl<tr><td align=right>8<td>xclstyle<tr><td align=right>9<td>visyvisy<tr><td align=right>10<td>camelflre</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>*evo*<tr><td align=right>2<td>n0blet<tr><td align=right>3<td>workin<tr><td align=right>4<td>scandi<tr><td align=right>5<td>i*e*f<tr><td align=right>6<td>dash<tr><td align=right>7<td>@nrg@<tr><td align=right>8<td>_dub*<tr><td align=right>9<td>-cope-<tr><td align=right>10<td>tribe*</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>lordofxcl<tr><td align=right>2<td>xcltommi<tr><td align=right>3<td>xclhenl<tr><td align=right>4<td>riplea<tr><td align=right>5<td>lkillyuri<tr><td align=right>6<td>ukdinger<tr><td align=right>7<td>threemwin<tr><td align=right>8<td>wahooooma<tr><td align=right>9<td>me12inch<tr><td align=right>10<td>realmgap</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>-m4e-<tr><td align=right>2<td>-auf-<tr><td align=right>3<td>*temo*<tr><td align=right>4<td>@tde2@<tr><td align=right>5<td>g-dogz<tr><td align=right>6<td>w*4*g<tr><td align=right>7<td>-bbw.r<tr><td align=right>8<td>jud²<tr><td align=right>9<td>oktron<tr><td align=right>10<td>tr1ade</table></table></center>");
		echo("<hr><center><table><tr><th colspan=8>May<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>xclhenl<tr><td align=right>2<td>israelck<tr><td align=right>3<td>camelsun<tr><td align=right>4<td>urptsrmin<tr><td align=right>5<td>dad0m1n8r<tr><td align=right>6<td>xclmael<tr><td align=right>7<td>samnpete<tr><td align=right>8<td>xclblimp<tr><td align=right>9<td>xtf<tr><td align=right>10<td>xclnova</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>i*e*f<tr><td align=right>2<td>bo-om<tr><td align=right>3<td>dgnf<tr><td align=right>4<td>tanx..<tr><td align=right>5<td>.tc.<tr><td align=right>6<td>cnc.b<tr><td align=right>7<td>@59@<tr><td align=right>8<td>etf.!.<tr><td align=right>9<td>@k.o@<tr><td align=right>10<td>@soad-</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>xclvolkov<tr><td align=right>2<td>imgodsson<tr><td align=right>3<td>xclhenl<tr><td align=right>4<td>me12inch<tr><td align=right>5<td>iraqnoob<tr><td align=right>6<td>wahooooma<tr><td align=right>7<td>tanksh0ck<tr><td align=right>8<td>xclearthy<tr><td align=right>9<td>xcltecboy<tr><td align=right>10<td>xcliraq</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>-.h.-<tr><td align=right>2<td>om3rta<tr><td align=right>3<td>o*t*s<tr><td align=right>4<td>runnwb<tr><td align=right>5<td>r@ptor<tr><td align=right>6<td>*eite*<tr><td align=right>7<td>kapoks<tr><td align=right>8<td>--ba--<tr><td align=right>9<td>adeath<tr><td align=right>10<td>*bbw.r</table></table></center>");
		echo("<hr><center><table><tr><th colspan=8>April<tr><td><table><tr><th colspan=2>Red Alert 2<tr><th>Rank<th>Name<tr><td align=right>1<td>jmedran0<tr><td align=right>2<td>cnckn0va<tr><td align=right>3<td>pm3k3p6d<tr><td align=right>4<td>l4yla<tr><td align=right>5<td>kbloodyr<tr><td align=right>6<td>urptsrmin<tr><td align=right>7<td>xtf<tr><td align=right>8<td>ra2ownag3<tr><td align=right>9<td>astr0n4ut<tr><td align=right>10<td>abogeyman</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>dgnf<tr><td align=right>2<td>-ragt-<tr><td align=right>3<td>do-ne<tr><td align=right>4<td>*soad-<tr><td align=right>5<td>he-lp!<tr><td align=right>6<td>-alc-<tr><td align=right>7<td>t*d*e<tr><td align=right>8<td>@soad-<tr><td align=right>9<td>@gw@<tr><td align=right>10<td>*usa_</table><td><td><table><tr><th colspan=2>Yuri's Revenge<tr><th>Rank<th>Name<tr><td align=right>1<td>xclseal<tr><td align=right>2<td>me12inch<tr><td align=right>3<td>jonisb4ck<tr><td align=right>4<td>xclrulez<tr><td align=right>5<td>xclezrush<tr><td align=right>6<td>xcljoku<tr><td align=right>7<td>xcltheone<tr><td align=right>8<td>xclmurlaw<tr><td align=right>9<td>xclffs<tr><td align=right>10<td>amikloy</table><td><td><table><tr><th colspan=2>Clan<tr><th>Rank<th>Name<tr><td align=right>1<td>*03*<tr><td align=right>2<td>adeath<tr><td align=right>3<td>om3rta<tr><td align=right>4<td>*ps-e*<tr><td align=right>5<td>o*t*s<tr><td align=right>6<td>team.b<tr><td align=right>7<td>**21**<tr><td align=right>8<td>--ba--<tr><td align=right>9<td>_rnx_<tr><td align=right>10<td>-00-</table></table></center>");
		echo("<hr><center><table><tr><th colspan=2>March<tr><th>Rank<th>Name<tr><td align=right>1<td>cncviking<tr><td align=right>2<td>premierez<tr><td align=right>3<td>serge4nt<tr><td align=right>4<td>m270mlrs<tr><td align=right>5<td>aaai2a2<tr><td align=right>6<td>awazrobbi<tr><td align=right>7<td>wi4israel<tr><td align=right>8<td>xclsovgod<tr><td align=right>9<td>unstop4bl<tr><td align=right>10<td>iluveisso</table></center>");
	}
	else if (isset($_GET[hos]))
	{
		echo("<center><table><tr><th>Name");
		$results = db_query("select xcl_players.pid from xcl_players inner join bl using (name) where points");
		while ($result = mysql_fetch_array($results))
			db_query(sprintf("update xcl_players set points = 0 where pid = %d", $result[pid]));
		$results = db_query("select distinct xcl_players.name from xcl_players inner join bl using (name) order by xcl_players.name");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td>%s", $result[name]);
		echo("</table></center>");
	}
	else if (isset($_GET[stats]))
	{
		$results = db_query("select gsku, count(*) as count from xcl_games group by gsku order by count desc");
		echo("<table><tr><th>Games<th>Game");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
		echo("</table><hr>");
		$results = db_query("select gsku, count(distinct pid) as count from xcl_games inner join xcl_games_players using (gid) where not cid group by gsku order by count desc");
		echo("<table><tr><th>Players<th>Game");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
		echo("</table><hr>");
		$results = db_query("select gsku, count(distinct cid) as count from xcl_games inner join xcl_games_players using (gid) where cid group by gsku order by count desc");
		echo("<table><tr><th>Clans<th>Game");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], gsku2a($result[gsku]));
		echo("</table><hr>");
		$results = db_query("select cty, count(*) as count from xcl_games_players group by cty order by count desc");
		echo("<table><tr><th>Count<th>Country");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td><img src=\"%s\" alt=\"%s\">", $result[count], get_country_flag_url($result[cty]), get_country_name($result[cty]));
		echo("</table><hr>");
		$results = db_query("select ifnull(xcl_maps.name, xcl_games.scen) as scen, xcl_games.scen as scen_fname, count(*) as count from xcl_games left join xcl_maps on xcl_games.scen = xcl_maps.fname group by scen order by count desc");
		echo("<table><tr><th>Count<th>Scenario");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%s", $result[count], $result[scen]);
		echo("</table><hr>");
		$results = db_query("select round(dura / 600) * 10 as dura, count(*) as count from xcl_games group by dura order by dura");
		echo("<table><tr><th>Count<th>Duration");
		while ($result = mysql_fetch_array($results))
		{
			printf("<tr><td align=right>%d<td align=right>", $result[count]);
			if ($result[dura])
				printf("%d - %d", $result[dura] - 5, $result[dura] + 5);
			else
				echo("< 5");
		}
		echo("</table><hr>");
		$results = db_query("select afps, count(*) as count from xcl_games group by afps order by afps");
		echo("<table><tr><th>Count<th>Average FPS");
		while ($result = mysql_fetch_array($results))
			printf("<tr><td align=right>%d<td>%d", $result[count], $result[afps]);
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
			{
				$results = db_query(sprintf("
					select distinct t1.*, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from bl inner join xcl_players using (name) inner join xcl_games_players as t2 using (pid) inner join xcl_games as t1 using (gid) inner join xcl_games_players as t3 using (gid) left join xcl_maps as t4 on (t1.scen = t4.fname)
					where t2.pid != t3.pid and not t3.cid and t3.pc < 0
					order by gid desc
					"));
				echo_games($results, 0, 0, true);
				echo("<hr>");
				$results = db_query(sprintf("
					select distinct t1.*, ifnull(t4.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from bl inner join xcl_players p using (name) inner join xcl_games_players as t2 on p.pid = t2.cid inner join xcl_games as t1 using (gid) inner join xcl_games_players as t3 using (gid) left join xcl_maps as t4 on (t1.scen = t4.fname)
					where t2.cid != t3.cid and t3.pc < 0
					order by gid desc
					"));
			}
			else if ($wash_games)
				$results = db_query(sprintf("
					select t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime
					from xcl_games as t1 left join xcl_maps as t3 on (t1.scen = t3.fname)
					where oosy
					order by gid desc
					"));
			else
			{
				$results = db_query(sprintf("select xcl_players.*, bl.name as bl, wl.name as wl, unix_timestamp(xcl_players.mtime) as mtime from xcl_players left join bl using (name) left join wl on (xcl_players.name = wl.name) where pid = %d", $cid ? $cid : $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<table><tr><th>Rank<th>Name<th colspan=2>Stats<th>Points<th><th><th>Date");
					do
					{
						printf("<tr><td align=right>%d<td>%s<td align=right>%d<td align=right>%d<td align=right>%d<td>%s<td>%s<td>%s", $result[rank], $result[name], $result[win_count], $result[loss_count], $result[points], $result[bl] ? "BL" : "", $result[wl] ? "WL" : "", gmdate("H:i d-m-Y", $result[mtime]));
					}
					while ($result = mysql_fetch_array($results));
					echo("</table><hr>");
				}
				$results = db_query($cid
					? sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1 inner join xcl_games_players as t2 using (gid) left join xcl_maps as t3 on (t1.scen = t3.fname) where t2.cid = %d order by gid desc", $cid)
					: sprintf("select distinct t1.*, ifnull(t3.name, t1.scen) as scen, unix_timestamp(t1.mtime) as mtime from xcl_games as t1 inner join xcl_games_players as t2 using (gid) left join xcl_maps as t3 on (t1.scen = t3.fname) where not t2.cid and t2.pid = %d order by gid desc", $pid));
			}
			echo_games($results, $pid, $cid, $unfair_games);
			if ($cid || $pid)
			{
				if ($cid)
				{
					$results = db_query(sprintf("select p.name, sum(pc > 0) as w,  sum(pc < 0) as l, sum(greatest(pc, 0)) as pw, sum(least(pc, 0)) as pl, sum(pc) as pc from xcl_games_players gp inner join xcl_players p using (pid) where cid = %d group by p.pid order by name", $cid));
					echo("<hr><table>");
					while ($result = mysql_fetch_array($results))
					{
						printf("<tr><td>%s<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d<td align=right>%d", $result[name], $result[w], $result[l], $result[pw], $result[pl], $result[pc]);
					}
					echo("</table>");
				}
				$results = db_query($cid
					? sprintf("select cty, count(*) as count from xcl_games_players where cid = %d group by cty order by count desc", $cid)
					: sprintf("select cty, count(*) as count from xcl_games_players where not cid and pid = %d group by cty order by count desc", $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<hr><table><tr><th>Count<th>Country");
					do
					{
						printf("<tr><td align=right>%d<td><img src=\"%s\" alt=\"%s\">", $result[count], get_country_flag_url($result[cty]), get_country_name($result[cty]));
					}
					while ($result = mysql_fetch_array($results));
					echo("</table>");
				}
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where cid = %d group by scen order by count desc", $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where not cid and pid = %d group by scen order by count desc", $pid));
				if ($result = mysql_fetch_array($results))
				{
					echo("<hr><table><tr><th>Count<th>Scenario");
					do
					{
						printf("<tr><td align=right>%d<td>%s", $result[count], $result[scen]);
					}
					while ($result = mysql_fetch_array($results));
					echo("</table>");
				}
			}
			else if ($gid)
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
					: sprintf("select xcl_players.*, bl.name as bl, wl.name as wl, unix_timestamp(xcl_players.mtime) as mtime from xcl_players left join bl using (name) left join wl on (xcl_players.name = wl.name) where xcl_players.lid = %d and points order by points desc limit 250", $lid));
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
						printf("<td><a href=\"?%s=%d\">%s</a><td align=right>%d<td align=right>%d<td align=right>%d<td>%s<td>%s<td>%s", $result[lid] & 1 ? "pid" : "cid", $result[pid], $result[name], $result[win_count], $result[loss_count], $result[points], $result[bl] ? "BL" : "", $result[wl] ? "WL" : "", gmdate("H:i d-m-Y", $result[mtime]));
						for ($i = 0; $i < 10; $i++)
						{
							if ($result[countries] & 1 << $i)
							{
								if ($result[lid] == 5 || $result[lid] == 6)
									printf("<td><img src=\"%s\" alt=\"%s\"> ", get_country_flag_url(0x100 | $i), get_country_name(0x100 | $i));
								else
									printf("<td><img src=\"%s\" alt=\"%s\"> ", get_country_flag_url($i), get_country_name($i));
							}
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
	</table>
</center>
<?php
			}
		}
	}
?>
<hr>
<table width="100%">
	<tr>
		<td valign=top>
			<a href="http://strike-team.net/">Strike Team</a> | <a href="/">XCC Home Page</a>
		<td align=center valign=top>
			<a href="http://www.strike-team.net/nuke/html/modules.php?op=modload&name=News&file=article&sid=14"><img src="https://www.paypal.com/images/x-click-but04.gif"></a>

			<script language="JavaScript" type="text/javascript" src="http://m1.nedstatbasic.net/basic.js">
			</script>
			<script language="JavaScript" type="text/javascript">
			<!--
				nedstatbasic("ACYaRA5mKkSNw9DcBlC+vYnGi83A", 0);
			// -->
			</script>
			<noscript>
				<a target="_blank" href="http://v1.nedstatbasic.net/stats?ACYaRA5mKkSNw9DcBlC+vYnGi83A"><img src="http://m1.nedstatbasic.net/n?id=ACYTXwDHntQULdYZIrOjZRmDVgjQ"	border="0" nosave width="18" height="18"></a>
			</noscript>
		<td align=right valign=top>
			<?php echo(gmdate("H:i d-m-Y")) ?>
</table>
<?php
	@include("bottom.php");
?>