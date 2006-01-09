<?
/* ------------------------------------------------------------------------------------------- */
/* ----------------------------------- RA2 Configuration ------------------------------------- */
/* ------------------------------------------------------------------------------------------- */

$player_lid = 1; // player lid in database
$clan_lid = 2; // clan lid in database

/* ------------------------------------------------------------------------------------------- */
/* ------------------------------- Do not change any lines below ----------------------------- */
/* ------------------------------------------------------------------------------------------- */

if($ladr == "") { $ladr = "player"; }

if($mode == "searchsubmit" && $id != "" && $lid != "") {

$result=db_query("SELECT * FROM xcl_players WHERE name LIKE '%$id%' AND lid='$lid' OR rank LIKE '$id' AND lid='$lid'");
$total=mysql_num_rows($result);
if($total == 0) {
?>
<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2" bgcolor="#000000">
<tr><th class="maintitle" colspan="2" align="left" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;<a href="?laddertype=1">XCC community ladder</a> &raquo; Search Result for <?=$id?></font></th>
</table>
<table bgcolor="#113341" width="100%" cellspacing="0" cellpadding="5" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">
<tr>
<td bgcolor="#113341" width=100%>
<br>
<table bgcolor="#113341" width="70%" cellspacing="0" cellpadding="3" align="center">
<tr>
<td width="100%">
<? if($lid == $player_lid) { $ladr = "player"; } else { $ladr = "clan"; } ?>
<META HTTP-EQUIV=Refresh CONTENT="1; URL=?ladr=<?=$ladr?>&laddertype=1">
<br><div align="center"><font size="2">Clan/Player/rank not found</div><br><br>


</table>



</table>
<?
} else {
?>

<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2" bgcolor="#000000">
<tr><td class="maintitle" colspan="2" align="left" height="30" width="40%"><span class="thnorm"><font face="Tahoma" size="2"><SCRIPT LANGUAGE="JavaScript">
<!--
function jumpTo(URL_List){
   var URL = URL_List.options[URL_List.selectedIndex].value;
   window.location.href = URL;
}
// --->
</SCRIPT>
<select NAME="" style="background-color: #113341; color: #ffffff; width:200;" onChange="jumpTo(this);">
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- Ra2 Ladder</option>
<option value="?laddertype=1&ladr=player" <? if($ladr == "player" && $laddertype == "1") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Player</option>
<option value="?laddertype=1&ladr=clan" <? if($ladr == "clan" && $laddertype == "1" or $ladr == "" && $laddertype == "1") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Clan</option>
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- Yuri Ladder</option>
<option value="?laddertype=2&ladr=player" <? if($ladr == "player" && $laddertype == "2") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Player</option>
<option value="?laddertype=2&ladr=clan"  <? if($ladr == "clan" && $laddertype == "2" or $ladr == "" && $laddertype == "2") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Clan</option>
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- TS Ladder</option>
<option value="?laddertype=3&ladr=player" style="color: #B5B5B5;">XCL - Player</option>
<option value="?laddertype=3&ladr=clan" style="color: #B5B5B5;">XCL - Clan</option>
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- Other options</option>
<option value="http://xwis.net/xcl/?hof=" style="color: #B5B5B5;">Hall of Fame</option>
<option value="http://xwis.net/xcl/?hos=" style="color: #B5B5B5;">Hall of Shame</option>
<option value="http://xwis.net/xcl/?stats=" style="color: #B5B5B5;">Statistics</option>
<option value="http://www.strike-team.net/forums" style="color: #B5B5B5;">ST forum</option>
<option value="http://xwis.net:4005" style="color: #B5B5B5;">Online</option>
</select></font><td class="thnorm" colspan="2" height="30" width="60%" align="right"><a href="http://xwis.net/xwi/" target="_blank"><img src="images/clan-manager.gif" alt="" border="0"></a>&nbsp;<a href="http://strike-team.net/nuke/html/modules.php?op=modload&name=News&file=article&sid=13" target="_blank"><img src="images/rules.gif" alt="" border="0"></a>&nbsp;<a href="http://xwis.net/downloads/XWISC.exe"><img src="images/c-tool.gif" alt="" border="0"></a>&nbsp;<a href="http://xccu.sourceforge.net/utilities/XGS.zip"><img src="images/xgs.gif" alt="" border="0"></a>&nbsp;<a href="http://xwis.net/downloads/XWISB.zip"><img src="images/xwis.gif" alt="" border="0"></a>
</table>

<table width="100%" border="0" cellspacing="0" cellpadding="0" bgcolor="#113341" valign="top" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>

<table width="100%" valign="top">
<tr>
<td width="34%" align="left" valign="top">
&nbsp;

<td width="41%" align="center" valign="top">
<img src="images/ra2/ra2-logo.gif" alt="" border="0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>

<td width="14%" align="right" valign="top">
<img src="images/monitor.gif" alt="" border="0"><br>
<table width="100%" align="center">
<tr>
<td width="100%" align="center">
<form name="beitrag" method="POST">
<input type=hidden name="mode" value="searchsubmit">
<input type=hidden name="lid" value="<? if($ladr == "player") { echo $player_lid; } else { echo $clan_lid; } ?>">
<input type="Text" name="id" size="10" value="<?=$id?>">


<tr>
<td width="100%" align="center">&nbsp;<input type="image" src="images/search.gif" border="0" align="absbottom"></form>

</table>


</table>
<br>
<table width="72%" cellspacing="0" cellpadding="3" align="center">
<?
$query = db_query("SELECT * FROM xcl_players WHERE name LIKE '%$id%' AND lid='$lid' AND points!='0' OR rank LIKE '$id' AND lid='$lid' AND points!='0' ORDER BY points DESC");
while ($data = mysql_fetch_array($query)) {

if(get_side($data[countries]) == 1) {
if($data[points] > 699) { $button = "<img src=\"images/ra2/ra2-red5.gif\" alt=\"\" >"; }
if($data[points] < 700 && $data[points] > 499) { $button = "<img src=\"images/ra2/ra2-red4.gif\" alt=\"\" >"; }
if($data[points] < 500 && $data[points] > 299) { $button = "<img src=\"images/ra2/ra2-red3.gif\" alt=\"\" >"; }
if($data[points] < 300 && $data[points] > 149) { $button = "<img src=\"images/ra2/ra2-red2.gif\" alt=\"\" >"; }
if($data[points] < 150 && $data[points] > 0) { $button = "<img src=\"images/ra2/ra2-red1.gif\" alt=\"\" >"; }
} else {
if($data[points] > 699) { $button = "<img src=\"images/ra2/ra2-blue5.gif\" alt=\"\" >"; }
if($data[points] < 700 && $data[points] > 499) { $button = "<img src=\"images/ra2/ra2-blue4.gif\" alt=\"\" >"; }
if($data[points] < 500 && $data[points] > 299) { $button = "<img src=\"images/ra2/ra2-blue3.gif\" alt=\"\" >"; }
if($data[points] < 300 && $data[points] > 149) { $button = "<img src=\"images/ra2/ra2-blue2.gif\" alt=\"\" >"; }
if($data[points] < 150 && $data[points] > 0) { $button = "<img src=\"images/ra2/ra2-blue1.gif\" alt=\"\" >"; }
}

?>
<tr>
<td bgcolor="#113341" width="100%">
<table bgcolor="#113341" width="100%">
<tr>
<td width="5%"><font size="2"><?=$data[rank]?></font>
<td width="12%"><?=$button?>
<td width="32%"><font size="2"><? if($ladr == "player") { ?><a href="?mode=showplayer&laddertype=1&id=<?=$data[pid]?>"><? } else { ?><a href="?mode=showclan&laddertype=1&id=<?=$data[pid]?>"><? } ?><u><font color="#FFFFB0"><u><b><?=$data[name]?></b></u></font></u></a></font>
<td width="27%"><font size="2"><?=$data[win_count]?> wins / <?=$data[loss_count]?> losses<? if($data[rank] == 1) { echo "</font></b>"; } ?></font>
<td width="20%"><font size="2"><?=$data[points]?> Points<? if($data[rank] == 1) { echo "</font></b>"; } ?></font>
<td width="4%"><font size="2"><img src="images/1.gif" alt="" border="0">&nbsp;&nbsp;</font>

</table>
<table width="100%">
<td width="100%"><hr noshade size="1">

</table>


<?
}
?>
</table>



</table>
<?
}
}

// SITE MODES
if($mode == "showclan" && $id != "") {
$cid = $id;
$id = addslashes($id);
$query = db_query("SELECT * FROM xcl_players WHERE pid='$id' AND lid='$clan_lid'");
while ($data = mysql_fetch_array($query)) {
?>

<table width="100%" border="0" class="maintitle" cellspacing="1" cellpadding="2" bgcolor="#000000">
<tr><th colspan="2" align="left" class="maintitle" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;<a href="?laddertype=1">XCC community ladder</a> &raquo; Clanstats for [<?=$data[name]?>]</font></th>
</table>

<table width="100%" border="0" cellspacing="1" cellpadding="5" bgcolor="#113341" bgcolor="#113341" valign="top" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>

<table width="100%"><tr>
<td width="65%">
<table width="100%" cellspacing="1" cellpadding="3">
<tr>
<td width="16%"><font size="2"><b>Rank:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[rank]?>

<tr>
<td width="10%"><font size="2"><b>Wins:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[win_count]?>

<tr>
<td width="10%"><font size="2"><b>Losses:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[loss_count]?>

<tr>
<td width="10%"><font size="2"><b>Points:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[points]?>

<tr>
<td width="10%"><font size="2"><b>Ladder:</b>
<td width="90%"><font size="2"><font color="#D7D7D7">Clan Ladder

<tr>
<td width="10%" valign="top"><font size="2"><b>Sides:</b>
<td width="90%" valign="top"><font size="2"><font color="#D7D7D7">
<?
$query_sides = db_query("SELECT DISTINCT cty, count(*) as count from xcl_games_players WHERE cid='$id' group by cty order by count desc");
while ($data_sides = mysql_fetch_array($query_sides)) {
$co++;
if($co != 1) { echo "<br>"; }
echo "<img src=\"".get_country_flag_url($data_sides[cty])."\" alt=\"\" > ".$data_sides[count];
}
?>


<tr>
<td width="10%" valign="top"><font size="2"><b>Maps:</b>
<td width="90%" valign="top"><font size="2"><font color="#D7D7D7">
<?
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where cid = %d group by scen order by count desc", $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where not cid and pid = %d group by scen order by count desc", $pid));
				if ($result = mysql_fetch_array($results))
				{
					do
					{
						printf("%d %s <br>", $result[count], $result[scen]);
					}
					while ($result = mysql_fetch_array($results));
				}
?>


</table>

<td width="30%" align="center" valign="top">
<br><a href="http://xccu.sourceforge.net/" target="_blank"><img src="images/xwis-logo.gif" alt="" border="0"></a>


</table>




</table>

<br>

<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2" bgcolor="#000000">
<tr><th class="maintitle" colspan="2" align="left" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;Matches</font></th>
</table>

<table width="100%" border="0" cellspacing="1" cellpadding="5" bgcolor="#113341" bgcolor="#113341" valign="top" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>


<br>
<table width="100%" cellspacing="1" cellpadding="3">
<?
$query3 = db_query("SELECT cid, gid, pid, cty, pc FROM xcl_games_players WHERE cid='$id' ORDER BY gid DESC");
while ($data3 = mysql_fetch_array($query3)) {

$gameid = $data3[gid];
$gameid2 = $data3[gid]+1;

if($used[$gameid] != 1) {
$used[$gameid] = 1;

$query1 = db_query("SELECT name, points, pid FROM xcl_players WHERE pid='$data3[cid]'");
$rows1 = mysql_fetch_array($query1);

$query5 = db_query("SELECT cid, pc FROM xcl_games_players WHERE gid='$data3[gid]' AND cid!='$data3[cid]'");
$rows3 = mysql_fetch_array($query5);

$query2 = db_query("SELECT name, points, pid FROM xcl_players WHERE pid='$rows3[cid]'");
$rows2 = mysql_fetch_array($query2);


$clanid1 = $rows1["pid"];
$query_1_1 = db_query("SELECT DISTINCT gid, cid, SUM(pc) as summe FROM xcl_games_players WHERE cid='$clanid1' AND gid<'$gameid2' AND cid!='0' GROUP BY 'bla1'");
$rows_1_1 = mysql_fetch_array($query_1_1);
$pts_clan1 = $rows_1_1[summe];

$clanid2 = $rows2["pid"];
$query_2_1 = db_query("SELECT DISTINCT gid, cid, SUM(pc) as summe FROM xcl_games_players WHERE cid='$clanid2' AND gid<'$gameid2' AND cid!='0' GROUP BY 'bla2'");
$rows_2_1 = mysql_fetch_array($query_2_1);
$pts_clan2 = $rows_2_1[summe];

if($rows3[pc] == 0 && $data3[pc] == 0) {

$matchtext = "<a href=\"?mode=showplayer&laddertype=1&id=".$rows1["pid"]."\"><Font color=\"FFFF00\">".$rows1["name"]."</a></font> ( ".$pts_clan1." pts ) Plays <a href=\"?mode=showplayer&laddertype=1&id=".$rows2["pid"]."\"><Font color=\"FFFF00\">".$rows2["name"]."</a></font> ( ".$pts_clan2." pts )";

} else {

if($data3[pc] > 1) {

$matchtext = "<a href=\"?mode=showplayer&laddertype=1&id=".$rows1["pid"]."\"><Font color=\"FFFF00\">".$rows1["name"]."</a></font> ( ".$pts_clan1." pts ) Defeats <a href=\"?mode=showplayer&laddertype=1&id=".$rows2["pid"]."\"><Font color=\"FFFF00\">".$rows2["name"]."</a></font> ( ".$pts_clan2." pts )";

} else {

$matchtext = "<a href=\"?mode=showplayer&laddertype=1&id=".$rows2["pid"]."\"><Font color=\"FFFF00\">".$rows2["name"]."</a></font> ( ".$pts_clan2." pts ) Defeats <a href=\"?mode=showplayer&laddertype=1&id=".$rows1["pid"]."\"><Font color=\"FFFF00\">".$rows1["name"]."</a></font> ( ".$pts_clan1." pts )";

}


}

$query6 = db_query("SELECT mtime, scen, ws_gid, gid FROM xcl_games WHERE gid='$data3[gid]' AND trny='2'");
while ($data2 = mysql_fetch_array($query6)) {
?>
<tr>
<td width="100%" height="35px"><font size="2">
<?
$map = explode(".", $data2[scen]);
$map = $map[0];
printf('%s - %s ', gmdate('M d, Y', $data2['mtime']), $matchtext);
?>in game# <a href="?laddertype=1&mode=showmatch&id=<?=$data2[gid]?>"><font color="80FFFF"><u><?=$data2[ws_gid]?></u></font></a>
<hr>


<?
}
}
}
?>
</table>


</table>
<?
}
// END QUERY
}
// END SITE MODE



// SITE MODES
if($mode == "showplayer" && $id != "") {
$pid = $id;
$id = addslashes($id);
$query = db_query("SELECT * FROM xcl_players WHERE pid='$id' AND lid='$player_lid'");
while ($data = mysql_fetch_array($query)) {
?>
<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2" bgcolor="#000000">
<tr><th class="maintitle" colspan="2" align="left" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;<a href="?laddertype=1">XCC community ladder</a> &raquo; Playerstats for <?=$data[name]?></font></th>
</table>

<table width="100%" border="0" cellspacing="1" cellpadding="5" bgcolor="#113341" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>

<table width="100%"><tr>
<td width="65%">

<table width="100%" cellspacing="1" cellpadding="3">
<tr>
<td width="13%"><font size="2"><b>Rank:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[rank]?>

<tr>
<td width="10%"><font size="2"><b>Wins:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[win_count]?>

<tr>
<td width="10%"><font size="2"><b>Losses:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[loss_count]?>

<tr>
<td width="10%"><font size="2"><b>Points:</b>
<td width="90%"><font size="2"><font color="#D7D7D7"><?=$data[points]?>

<tr>
<td width="10%"><font size="2"><b>Ladder:</b>
<td width="90%"><font size="2"><font color="#D7D7D7">Player Ladder

<tr>
<td width="10%" valign="top"><font size="2"><b>Sides:</b>
<td width="90%" valign="top"><font size="2"><font color="#D7D7D7">
<?
$query_sides = db_query("SELECT DISTINCT cty, count(*) as count from xcl_games_players WHERE pid='$id' AND cid='0' group by cty order by count desc");
while ($data_sides = mysql_fetch_array($query_sides)) {
$co++;
if($co != 1) { echo "<br>"; }
echo "<img src=\"".get_country_flag_url($data_sides[cty])."\" alt=\"\" > ".$data_sides[count];
}
?>


<tr>
<td width="10%" valign="top"><font size="2"><b>Maps:</b>
<td width="90%" valign="top"><font size="2"><font color="#D7D7D7">
<?
				$results = db_query($cid
					? sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where cid = %d group by scen order by count desc", $cid)
					: sprintf("select ifnull(xcl_maps.name, xcl_games.scen) as scen, count(*) as count from xcl_games inner join xcl_games_players using (gid) left join xcl_maps on xcl_games.scen = xcl_maps.fname where not cid and pid = %d group by scen order by count desc", $pid));
				if ($result = mysql_fetch_array($results))
				{
					do
					{
						printf("%d %s <br>", $result[count], $result[scen]);
					}
					while ($result = mysql_fetch_array($results));
				}
?>


</table>



<td width="30%" align="center" valign="top">
<br><a href="http://xccu.sourceforge.net/" target="_blank"><img src="images/xwis-logo.gif" alt="" border="0"></a>


</table>

</table>

<br>

<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2">
<tr><th class="maintitle" colspan="2" align="left" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;Matches</font></th>
</table>

<table width="100%" border="0" cellspacing="1" cellpadding="5" bgcolor="#113341" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>

<br>
<table width="100%" cellspacing="1" cellpadding="3">
<?
$query3 = db_query("SELECT gid, pid, cty, pc FROM xcl_games_players WHERE pid='$id' AND cid='0' ORDER BY gid DESC");
while ($data3 = mysql_fetch_array($query3)) {

$gameid = $data3[gid];
$gameid2 = $data3[gid]+1;

if($used[$gameid] != 1) {
$used[$gameid] = 1;

$query1 = db_query("SELECT name, points, pid FROM xcl_players WHERE pid='$data3[pid]'");
$rows1 = mysql_fetch_array($query1);

$query6 = db_query("SELECT pid, pc FROM xcl_games_players WHERE gid='$data3[gid]' AND pid!='$data3[pid]'");
$rows3 = mysql_fetch_array($query6);

$query2 = db_query("SELECT name, points, pid FROM xcl_players WHERE pid='$rows3[pid]'");
$rows2 = mysql_fetch_array($query2);

$clanid1 = $rows1["pid"];
$query_1_1 = db_query("SELECT DISTINCT gid, cid, SUM(pc) as summe FROM xcl_games_players WHERE pid='$clanid1' AND gid<'$gameid2' AND cid='0' GROUP BY 'bla1'");
$rows_1_1 = mysql_fetch_array($query_1_1);
$pts_clan1 = $rows_1_1[summe];

$clanid2 = $rows2["pid"];
$query_2_1 = db_query("SELECT DISTINCT gid, cid, SUM(pc) as summe FROM xcl_games_players WHERE pid='$clanid2' AND gid<'$gameid2' AND cid='0' GROUP BY 'bla2'");
$rows_2_1 = mysql_fetch_array($query_2_1);
$pts_clan2 = $rows_2_1[summe];

if($rows3[pc] == 0 && $data3[pc] == 0) {

$matchtext = "<a href=\"?mode=showplayer&laddertype=1&id=".$rows1["pid"]."\"><Font color=\"FFFF00\">".$rows1["name"]."</a></font> ( ".$pts_clan1." pts ) Plays <a href=\"?mode=showplayer&laddertype=1&id=".$rows2["pid"]."\"><Font color=\"FFFF00\">".$rows2["name"]."</a></font> ( ".$pts_clan2." pts )";

} else {

if($data3[pc] > 1) {

$matchtext = "<a href=\"?mode=showplayer&laddertype=1&id=".$rows1["pid"]."\"><Font color=\"FFFF00\">".$rows1["name"]."</a></font> ( ".$pts_clan1." pts ) Defeats <a href=\"?mode=showplayer&laddertype=1&id=".$rows2["pid"]."\"><Font color=\"FFFF00\">".$rows2["name"]."</a></font> ( ".$pts_clan2." pts )";

} else {

$matchtext = "<a href=\"?mode=showplayer&laddertype=1&id=".$rows2["pid"]."\"><Font color=\"FFFF00\">".$rows2["name"]."</a></font> ( ".$pts_clan2." pts ) Defeats <a href=\"?mode=showplayer&laddertype=1&id=".$rows1["pid"]."\"><Font color=\"FFFF00\">".$rows1["name"]."</a></font> ( ".$pts_clan1." pts )";

}


}




$query7 = db_query("SELECT mtime, scen, ws_gid, gid FROM xcl_games WHERE gid='$data3[gid]' AND trny='1'");
while ($data2 = mysql_fetch_array($query7)) {
?>
<tr>
<td width="100%" height="35px"><font size="2">
<?
$map = explode(".", $data2[scen]);
$map = $map[0];
printf('%s - %s ', gmdate('M d, Y', $data2['mtime']), $matchtext);
?>in game# <a href="?mode=showmatch&laddertype=1&id=<?=$data2[gid]?>"><font color="80FFFF"><u><?=$data2[ws_gid]?></u></font></a>
<hr>


<?
}
}
}
?>
</table>


</table>
<?
}
// END QUERY
}
// END SITE MODE

// SITE MODES
if($mode == "showmatch" && $id != "") {
$id = addslashes($id);
$query = db_query("SELECT * FROM xcl_games WHERE gid='$id'");
while ($data = mysql_fetch_array($query)) {
$gametype = $data[trny];
?>
<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2">
<tr><th class="maintitle" colspan="2" align="left" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;<a href="?laddertype=1">XCC community ladder</a> &raquo; Match #<?=$data[gid]?></font></th>
</table>

<table width="100%" border="0" cellspacing="1" cellpadding="5" bgcolor="#113341" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>

<table width="100%">
<tr>

<td width="70%" valign="top">

<table width="100%" cellspacing="1" cellpadding="3">
<tr><td width="100%"><h3><?

$query_match1 = db_query("SELECT * FROM xcl_games_players WHERE gid='$id' ORDER BY pid ASC, cid ASC");
while ($data_match1 = mysql_fetch_array($query_match1)) {


if($data_match1[cid] != 0) {

$team2 = $data_match1[cid];
if($did[$team2] != 1) {
$query_match2 = db_query("SELECT * FROM xcl_players WHERE pid='$data_match1[cid]' GROUP BY 'bla1'");
while ($data_match2 = mysql_fetch_array($query_match2)) {
$cc++;
$team = $data_match2[pid];
$did[$team] = 1;
$clan[$cc] = $data_match2[name];
}
}

} else {

$team2 = $data_match1[pid];
if($did[$team2] != 1) {
$query_match2 = db_query("SELECT * FROM xcl_players WHERE pid='$data_match1[pid]' GROUP BY 'bla1'");
while ($data_match2 = mysql_fetch_array($query_match2)) {
$cc++;
$team = $data_match2[pid];
$did[$team] = 1;
$clan[$cc] = $data_match2[name];
}
}

}

}
echo "$clan[1] vs. $clan[2]";
?></h3>
</table>
<table width="100%" cellspacing="1" cellpadding="3">
<tr>
<td width="32%"><font size="2"><b>Scenario:</b>
<td width="90%"><font size="2"><font color="#D7D7D7">
<?
$map = explode(".",$data[scen]);
$mapsave = $map[0];
echo $map[0];
?>

<tr>
<td width="10%"><font size="2"><b>Game Duration:</b>
<td width="90%"><font size="2"><font color="#D7D7D7">
<?
$minutes_seconds = intval($data[dura]/60).":".($data[dura]%60);
echo $minutes_seconds;
?> minutes

<tr>
<td width="10%"><font size="2"><b>Type:</b>
<td width="90%"><font size="2"><font color="#D7D7D7">
<? if($data[trny] == "1") { echo "Player tournament"; } ?>
<? if($data[trny] == "2") { echo "Clan tournament"; } ?>
<? if($data[trny] == "0") { echo "FFG"; } ?>


<?
if($gametype == 2) {
$query3 = db_query("SELECT * FROM xcl_games_players WHERE gid='$id' ORDER BY pc DESC");
while ($data3 = mysql_fetch_array($query3)) {
$clancid = $data3[cid];

if($gotclan[$clancid] != 1) {
$gotclan[$clancid] = 1;
$query_nick1 = db_query("SELECT * FROM xcl_players WHERE pid='$data3[cid]'");
while ($data_nick1 = mysql_fetch_array($query_nick1)) {
if($data3[pc] > 0) { $col = "<font color=\"#00DF00\">"; $show = "+".$data3[pc]; }
if($data3[pc] < 1) { $col = "<font color=\"#FF0000\">"; $show = $data3[pc]; }
if($data3[pc] == 0) { $show = "+0"; }
echo "<tr><td width=\"10%\" valign=\"top\"><font size=\"2\"><b>$data_nick1[name]'s point change:</b><td width=\"90%\"><font size=\"2\"><font color=\"#D7D7D7\">$col $show</font>";
}
}

}
} else {
$query3 = db_query("SELECT * FROM xcl_games_players WHERE gid='$id'");
while ($data3 = mysql_fetch_array($query3)) {

$query_nick1 = db_query("SELECT * FROM xcl_players WHERE pid='$data3[pid]'");
while ($data_nick1 = mysql_fetch_array($query_nick1)) {
if($data3[pc] > 0) { $col = "<font color=\"#00DF00\">"; $show = "+".$data3[pc]; }
if($data3[pc] < 1) { $col = "<font color=\"#FF0000\">"; $show = $data3[pc]; }
if($data3[pc] == 0) { $show = "+0"; }
echo "<tr><td width=\"10%\" valign=\"top\"><font size=\"2\"><b>$data_nick1[name]'s point change:</b><td width=\"90%\"><font size=\"2\"><font color=\"#D7D7D7\">$col $show</font>";
}
}
}
?>
</table>

<td width="30%" valign="top" align="top"><br>


</table>
</table>

<br>

<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2">
<tr><th class="maintitle" colspan="2" align="left" height="30"><span class="thnorm"><font face="Tahoma" size="2">&nbsp;Match details</font></th>
</table>
<table width="100%" border="0" cellspacing="1" cellpadding="5" bgcolor="#113341" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">
<tr>
<td width=100%>
<table width="100%" cellspacing="0" cellpadding="5">
<tr>
<td width="100%">
<?
$query3 = db_query("SELECT * FROM xcl_games_players WHERE gid='$id'");
while ($data3 = mysql_fetch_array($query3)) {

$clansh = "";
if($data3[cid] != 0) {
$query_nick3 = db_query("SELECT * FROM xcl_players WHERE pid='$data3[cid]'");
while ($data_nick3 = mysql_fetch_array($query_nick3)) {
$clansh = "[".$data_nick3[name]."]";
}
}

$query_nick1 = db_query("SELECT * FROM xcl_players WHERE pid='$data3[pid]'");
while ($data_nick1 = mysql_fetch_array($query_nick1)) {

if($data3[pc] > 0) { $result = "Won"; } else { $result = "Lost"; }

if($clansh != "") { $alink = "<a href=\"?mode=showclan&laddertype=1&id=$data3[cid]\">"; } else { $alink = "<a href=\"?mode=showplayer&laddertype=1&id=$data_nick1[pid]\">"; }
?>
<?=$alink?><Font size="4"><b><?=$data_nick1[name]?></a> <?=$clansh?></b></font>
<table width="60%" cellspacing="2" cellpadding="3">
<tr>
<td width="37%"><font size="2">Result:</b>
<td width="60%"><font size="2"><font color="#D7D7D7"><?=$result?></font>

<tr>
<td width="20%"><font size="2">Points:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><?=$data_nick1[points]?></font>

<tr>
<td width="20%"><font size="2">Record:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><?=$data_nick1[win_count]?>/<?=$data_nick1[loss_count]?></font>

<tr>
<td width="20%"><font size="2">Side:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><img src="<?=get_country_flag_url($data3[cty])?>" alt="" border="0"></font>

<tr>
<td width="20%"><font size="2">Units Killed/Bought/Left:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><?=$data3[unk]?>/<?=$data3[unb]?>/<?=$data3[unl]?></font>

<tr>
<td width="20%"><font size="2">Buildings Killed/Bought/Left:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><?=$data3[blk]?>/<?=$data3[blb]?>/<?=$data3[bll]?></font>

<tr>
<td width="20%"><font size="2">Infantry Killed/Bought/Left:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><?=$data3[ink]?>/<?=$data3[inb]?>/<?=$data3[inl]?></font>

<tr>
<td width="20%"><font size="2">Planes Killed/Bought/Left:</b>
<td width="80%"><font size="2"><font color="#D7D7D7"><?=$data3[plk]?>/<?=$data3[plb]?>/<?=$data3[pll]?></font>
</table><br>
<?
}
}
?>
</table>

</table>
<?
}
// END QUERY
}
// END SITE MODE


// SITE MODES
if($mode == "") {

if($ladr == "clan") { $showname = "XCC Community Ladder - Clan"; }
if($ladr == "player") { $showname = "XCC Community Ladder - Player"; }

?>

<table class="maintitle" width="100%" border="0" cellspacing="1" cellpadding="2" bgcolor="#000000">
<tr><td class="maintitle" colspan="2" align="left" height="30" width="40%"><span class="thnorm"><font face="Tahoma" size="2"><SCRIPT LANGUAGE="JavaScript">
<!--
function jumpTo(URL_List){
   var URL = URL_List.options[URL_List.selectedIndex].value;
   window.location.href = URL;
}
// --->
</SCRIPT>
<select NAME="" style="background-color: #113341; color: #ffffff; width:200;" onChange="jumpTo(this);">
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- Ra2 Ladder</option>
<option value="?laddertype=1&ladr=player" <? if($ladr == "player" && $laddertype == "1") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Player</option>
<option value="?laddertype=1&ladr=clan" <? if($ladr == "clan" && $laddertype == "1" or $ladr == "" && $laddertype == "1") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Clan</option>
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- Yuri Ladder</option>
<option value="?laddertype=2&ladr=player" <? if($ladr == "player" && $laddertype == "2") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Player</option>
<option value="?laddertype=2&ladr=clan"  <? if($ladr == "clan" && $laddertype == "2" or $ladr == "" && $laddertype == "2") { echo "selected"; } ?> style="color: #B5B5B5;">XCL - Clan</option>
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- TS Ladder</option>
<option value="?laddertype=3&ladr=player" style="color: #B5B5B5;">XCL - Player</option>
<option value="?laddertype=3&ladr=clan" style="color: #B5B5B5;">XCL - Clan</option>
<option value="" disabled="disabled" style="background-color: #164356; color: #FFFFB0;">---- Other options</option>
<option value="http://xwis.net/xcl/?hof=" style="color: #B5B5B5;">Hall of Fame</option>
<option value="http://xwis.net/xcl/?hos=" style="color: #B5B5B5;">Hall of Shame</option>
<option value="http://xwis.net/xcl/?stats=" style="color: #B5B5B5;">Statistics</option>
<option value="http://www.strike-team.net/forums" style="color: #B5B5B5;">ST forum</option>
<option value="http://xwis.net:4005" style="color: #B5B5B5;">Online</option>
</select></font><td class="thnorm" colspan="2" height="30" width="60%" align="right"><a href="http://xwis.net/xwi/" target="_blank"><img src="images/clan-manager.gif" alt="" border="0"></a>&nbsp;<a href="http://strike-team.net/nuke/html/modules.php?op=modload&name=News&file=article&sid=13" target="_blank"><img src="images/rules.gif" alt="" border="0"></a>&nbsp;<a href="http://xwis.net/downloads/XWISC.exe"><img src="images/c-tool.gif" alt="" border="0"></a>&nbsp;<a href="http://xccu.sourceforge.net/utilities/XGS.zip"><img src="images/xgs.gif" alt="" border="0"></a>&nbsp;<a href="http://xwis.net/downloads/XWISB.zip"><img src="images/xwis.gif" alt="" border="0"></a>
</table>

<table width="100%" border="0" cellspacing="0" cellpadding="0" bgcolor="#113341" valign="top" style="border-bottom: 1px solid black; border-right: 1px solid black; border-left: 1px solid black;">

<tr>

<td width=100%>

<table width="100%" valign="top">
<tr>
<td width="34%" align="left" valign="top">
&nbsp;

<td width="41%" align="center" valign="top">
<img src="images/ra2/ra2-logo.gif" alt="" border="0">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
<td width="14%" align="right" valign="top">
<img src="images/monitor.gif" alt="" border="0"><br>
<table width="100%" align="center">
<tr>
<td width="100%" align="center">
<form name="beitrag" method="POST">
<input type=hidden name="mode" value="searchsubmit">
<input type=hidden name="lid" value="<? if($ladr == "player") { echo $player_lid; } else { echo $clan_lid; } ?>">
<input type="Text" name="id" size="10" maxlength="">


<tr>
<td width="100%" align="center">&nbsp;<input type="image" src="images/search.gif" border="0" align="absbottom"></form>

</table>


</table>
<br>
<table width="72%" cellspacing="0" cellpadding="3" align="center">
<?
if($ladr == "clan") { $ladderc = $clan_lid; }
if($ladr == "player") { $ladderc = $player_lid; }

 $prosite = 50;

 $result = mysql_query("SELECT * FROM xcl_players WHERE lid='$ladderc' AND points!='0'");
 $number = mysql_num_rows($result);
 $seiten = floor($number/$prosite)+1;
 $seiten_a = floor($number/$prosite);
 $seiten_a2 = floor($number/$prosite)+1;

 for($i = 0; $i < $number; $i++) {

 if($site == "$i") {

 $huhu = $i-1;
 $start = $huhu*$prosite;

 $akt_seite = $site;
 $nextsite = $i+1;
 $prewsite = $i-1;

 break;

 }

 }


 if($site == "") {
 $start = 0;

 $akt_seite = 1;
 $site = 1;
 $nextsite = 2;
 }


// BEGIN LIST CLAN RANKINGS
$query = db_query("SELECT * FROM xcl_players WHERE lid='$ladderc' AND points!='0' ORDER BY rank ASC LIMIT $start,$prosite");
while ($data = mysql_fetch_array($query)) {

if(get_side($data[countries]) == 1) {
if($data[points] > 699) { $button = "<img src=\"images/ra2/ra2-red5.gif\" alt=\"\" >"; }
if($data[points] < 700 && $data[points] > 499) { $button = "<img src=\"images/ra2/ra2-red4.gif\" alt=\"\" >"; }
if($data[points] < 500 && $data[points] > 299) { $button = "<img src=\"images/ra2/ra2-red3.gif\" alt=\"\" >"; }
if($data[points] < 300 && $data[points] > 149) { $button = "<img src=\"images/ra2/ra2-red2.gif\" alt=\"\" >"; }
if($data[points] < 150 && $data[points] > 0) { $button = "<img src=\"images/ra2/ra2-red1.gif\" alt=\"\" >"; }
} else {
if($data[points] > 699) { $button = "<img src=\"images/ra2/ra2-blue5.gif\" alt=\"\" >"; }
if($data[points] < 700 && $data[points] > 499) { $button = "<img src=\"images/ra2/ra2-blue4.gif\" alt=\"\" >"; }
if($data[points] < 500 && $data[points] > 299) { $button = "<img src=\"images/ra2/ra2-blue3.gif\" alt=\"\" >"; }
if($data[points] < 300 && $data[points] > 149) { $button = "<img src=\"images/ra2/ra2-blue2.gif\" alt=\"\" >"; }
if($data[points] < 150 && $data[points] > 0) { $button = "<img src=\"images/ra2/ra2-blue1.gif\" alt=\"\" >"; }
}

if($ladr != "player") { $data[name] = strtoupper($data[name]); }
?>
<tr>
<td width="100%">
<table width="100%">
<tr>
<td width="5%"><font size="2"><?=$data[rank]?><? if($data[rank] == 1) { echo "</font></b>"; } ?></font>
<td width="12%"><?=$button?>
<td width="32%"><font size="2"><? if($ladr == "player") { ?><a href="?mode=showplayer&laddertype=1&id=<?=$data[pid]?>"><? } else { ?><a href="?mode=showclan&laddertype=1&id=<?=$data[pid]?>"><? } ?><u><font color="#FFFFB0"><u><b><?=$data[name]?></b></u></font></u></a></font>
<td width="27%"><font size="2"><?=$data[win_count]?> wins / <?=$data[loss_count]?> losses<? if($data[rank] == 1) { echo "</font></b>"; } ?></font>
<td width="20%"><font size="2"><?=$data[points]?> Points<? if($data[rank] == 1) { echo "</font></b>"; } ?></font>
<td width="4%"><font size="2"><img src="images/1.gif" alt="" border="0">&nbsp;&nbsp;</font>

</table>
<table width="100%">
<td width="100%"><hr noshade size="1">

</table>


<?
}
// END LIST
?>
</table>
<br>
<div align="center">

<table width="72%">
<tr><td width="20%" align="left">
 <?
 $seitencheck = $seiten;
 $sitehu = $site+1;
 if($site > 1) { ?>

 <font size="2"><a href="?ladr=<?=$ladr?>&laddertype=<?=$laddertype?>&mode=<?=$mode?>&id=<?=$id?>&lid=<?=$lid?>&site=<?=$prewsite?>">&laquo; Previous Page</a></font>


 <? } ?>

 <td width="60%" align="center">
 <font size="2">Page <?=$site?> / <?=$seiten_a2?></font>

 <td width="20%" align="right">
 <?
 if($site < $seitencheck) { ?>

 <font size="2"><a class="text" href="?ladr=<?=$ladr?>&laddertype=<?=$laddertype?>&mode=<?=$mode?>&id=<?=$id?>&lid=<?=$lid?>&site=<?=$nextsite?>">Next Page &raquo</a></font>

 <? } ?>


 </table>

</div>


</table>
<?
}
// END SITE MODE
?>
