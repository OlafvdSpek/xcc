<?php
	function apgar_encode($v)
	{
		$a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
		$w = "";
		for ($i = 0; $i < 8; $i++)
		{
			$b = ord($v[$i]);
			$c = ord($v[8 - $i]);
			$w .= $a[($b & 1 ? $b << ($b & 1) & $c : $b ^ $c) & 0x3f];
		}
		return $w;
	}

	function new_security_code()
	{
		$v = '';
		$s = '0123456789ABCDEFGHIJKLMNOPQRSTUVXWXYZabcdefghijklmnopqrstuvxwxyz';
		for ($i = 0; $i < 16; $i++)
			$v .= $s[mt_rand(0, strlen($s) - 1)];
		return $v;
	}

	function get_clan($cid)
	{
		return mysql_fetch_array(db_query(sprintf("select c.*, p0.name creator_name, p1.name leader_name from xwi_clans c left join xwi_players p0 on c.creator = p0.pid left join xwi_players p1 on c.leader = p1.pid where c.cid = %d", $cid)));
	}

	function get_player($name)
	{
		return mysql_fetch_array(db_query(sprintf("select * from xwi_players where name = '%s'", addslashes($name))));
	}

	function get_player2($name, $pass)
	{
		return mysql_fetch_array(db_query(sprintf("select * from xwi_players where name = '%s' and pass = md5('%s')", addslashes($name), apgar_encode($pass))));
	}

	function valid_clan_abbrev($v)
	{
		if (strlen($v) < 2 || strlen($v) > 6)
			return false;
		for ($i = 0; $i < strlen($v); $i++)
		{
			if (stristr('-0123456789@abcdefghijklmnopqrstuvwxyz', $v[$i]) === false)
				return false;
		}
		return true;
	}

	function valid_clan_name($v)
	{
		if (strlen($v) < 3 || strlen($v) > 32)
			return false;
		for ($i = 0; $i < strlen($v); $i++)
		{
			if (stristr(' -0123456789@abcdefghijklmnopqrstuvwxyz', $v[$i]) === false)
				return false;
		}
		return true;
	}

	function valid_mail($v)
	{
		return strlen($v);
	}

	include('templates/top.php');
	require('../xcc_common.php');

	db_connect();

	$name = trim($_REQUEST['name']);
	$pass = trim($_REQUEST['pass']);
	$remote_addr = $_SERVER['REMOTE_ADDR'];
	if ($remote_addr == '212.162.52.233')
		$remote_addr = $_SERVER['HTTP_X_FORWARDED_FOR'];

	switch ($_REQUEST['a'])
	{
	case "edit":
		{
			$cid = trim($_REQUEST['cid']);
			if (strlen($pass))
			{
				if ($clan = mysql_fetch_array(db_query(sprintf("select * from xwi_clans where cid = %d and pass = md5('%s')", $cid, addslashes($pass)))))
				{
					$icq = trim($_REQUEST['icq']);
					$mail = trim($_REQUEST['mail']);
					$msn = trim($_REQUEST['msn']);
					$site = trim($_REQUEST['site']);
					db_query(sprintf("update xwi_clans set icq = %d, mail = '%s', msn = '%s', site = '%s', mtime = unix_timestamp() where cid = %d", $icq, addslashes($mail), addslashes($msn), addslashes($site), $clan['cid']));
				}
				else
					echo("Wrong clan pass<hr>");
			}
			$clan = get_clan($cid);
			require('templates/clans_edit.php');
		}
		break;
	case "create":
		{
			$cabbrev = trim($_REQUEST['cabbrev']);
			$cname = trim($_REQUEST['cname']);
			$icq = trim($_REQUEST['icq']);
			$mail = trim($_REQUEST['mail']);
			$msn = trim($_REQUEST['msn']);
			$site = trim($_REQUEST['site']);
			if (!$site)
				$site = "http://";
			if ($name || $pass || $cname)
			{
				if (!valid_clan_abbrev($cabbrev))
					echo("Invalid clan abbreviation");
				else if (!valid_clan_name($cname))
					echo("Invalid clan name");
				else if (!valid_mail($mail))
					echo("Invalid email address");
				else if (get_player($name))
				{
					if ($player = get_player2($name, $pass))
					{
						if ($clan = mysql_fetch_array(db_query(sprintf("select name, full_name from xwi_clans where name = '%s' or full_name = '%s'", addslashes($cabbrev), addslashes($cname)))))
							printf("Clan %s (%s) already exists", $clan['name'], $clan['full_name']);
						else
						{
							do
							{
								$cpass = new_security_code();
								$results = db_query(sprintf("select count(*) from xwi_clans where pass = md5('%s')", $cpass));
								$result = mysql_fetch_array($results);
							}
							while ($result['0']);
							db_query(sprintf("insert into xwi_clans (creator, leader, name, full_name, pass, icq, mail, msn, site, mtime, ctime) values (%d, %d, lcase('%s'), '%s', md5('%s'), %d, lcase('%s'), lcase('%s'), lcase('%s'), unix_timestamp(), unix_timestamp())",
								$player['pid'], $player['pid'], addslashes($cabbrev), addslashes($cname), $cpass, $icq, addslashes($mail), addslashes($msn), addslashes($site)));
							$cid = mysql_insert_id();
							db_query(sprintf("update xwi_players set cid = %d, mtime = unix_timestamp() where pid = %d", $cid, $player['pid']));
							$clan = get_clan($cid);
							printf("Player %s created clan %s<br>", $player['name'], $clan['name']);
							printf("The clan admin pass is %s", $cpass);
							if (strlen($mail))
							{
								mail($mail,
									sprintf("XWI Clan Manager: Clan %s created", $clan['name']),
									sprintf("Player %s created clan %s with admin pass %s from IP address %s", $player['name'], $clan['name'], $cpass, $remote_addr),
									"from: XWIS <xwis>");
							}
						}
					}
					else
						printf("Invalid pass for player %s", htmlspecialchars($name));
				}
				else
					printf("Player %s not found", htmlspecialchars($name));
				echo("<hr>");
			}
			require('templates/clans_create.php');
		}
		break;
	case "delete_nick":
		{
			if ($name || $pass)
			{
				if (get_player($name))
				{
					if ($player = get_player2($name, $pass))
					{
						if (strtolower(substr($name, 0, 7)) == 'a000000')
							printf("Names starting with a000000 can't be deleted");
						else
						{
							$results = db_query(sprintf("select count(*) from xcl_players where lid & 1 and name = '%s'", $name));
							$result = mysql_fetch_array($results);
							if ($result['0'])
								printf("Player %s is already in ladder", $player['name']);
							else
							{
								$results = db_query(sprintf("select unix_timestamp() - ctime from xwi_players where pid = %d", $player['pid']));
								$result = mysql_fetch_array($results);
								$result['0'] /= 24 * 60 * 60;
								if ($result['0'] < 32)
									printf("Only players that were created more than 32 days ago can be deleted. Player %s was created %d days ago", $player['name'], $result['0']);
								else
								{
									db_query(sprintf("update xwi_players set flags = flags | 2, mtime = unix_timestamp() where pid = %d", $player['pid']));
									printf("Player %s has been deleted", $player['name']);
								}
							}
						}
					}
					else
						printf("Invalid pass for player %s", htmlspecialchars($name));
				}
				else
					printf("Player %s not found", htmlspecialchars($name));
				echo("<hr>");
			}
			require('templates/players_delete.php');
		}
		break;
	case "invite":
		{
			if ($name || $pass)
			{
				if ($player = get_player($name))
				{
					if ($player['cid'])
					{
						$clan = get_clan($player['cid']);
						printf("Player %s is already in clan %s", $player['name'], $clan['name']);
					}
					else if ($clan = mysql_fetch_array(db_query(sprintf("select * from xwi_clans where pass = md5('%s')", addslashes($pass)))))
					{
						$result = mysql_fetch_array(db_query(sprintf("select count(*) from xwi_clan_invites where cid = %d", $clan['cid'])));
						do
						{
							$cpass = new_security_code();
							$results = db_query(sprintf("select count(*) from xwi_clan_invites where pass = md5('%s')", $cpass));
							$result = mysql_fetch_array($results);
						}
						while ($result['0']);
						if ($result['0'] < 10)
							db_query(sprintf("insert into xwi_clan_invites (pid, cid, pass) values (%d, %d, md5('%s'))", $player['pid'], $clan['cid'], $cpass));
						printf("Player %s may join %s with pass %s", $player['name'], $clan['name'], $cpass);
					}
					else
						echo("Wrong clan pass");
				}
				else
					echo("Unknown player");
				echo("<hr>");
			}
			require('templates/clans_invite.php');
		}
		break;
	case "join":
		{
			$cpass = trim($_REQUEST['cpass']);
			if ($name || $pass || $cpass)
			{
				if (get_player($name))
				{
					if ($player = get_player2($name, $pass))
					{
						db_query("delete from xwi_clan_invites where unix_timestamp(ctime) < unix_timestamp() - 3 * 24 * 60 * 60");
						if ($player['cid'])
						{
							$clan = get_clan($player['cid']);
							printf("Player %s is already in clan %s", $player['name'], $clan['name']);
						}
						else if ($clan_invite = mysql_fetch_array(db_query(sprintf("select * from xwi_clan_invites where pass = md5('%s')", addslashes($cpass)))))
						{
							if ($clan_invite['pid'] == $player['pid'])
							{
								db_query(sprintf("delete from xwi_clan_invites where pid = %d and cid = %d", $player['pid'], $clan_invite['cid']));
								db_query(sprintf("update xwi_players set cid = %d, mtime = unix_timestamp() where pid = %d", $clan_invite['cid'], $player['pid']));
								$clan = get_clan($clan_invite['cid']);
								printf("Player %s joined clan %s<br>", $player['name'], $clan['name']);
							}
							else
								echo("Wrong invitation");
						}
						else
							echo("Wrong clan pass");
					}
					else
						printf("Invalid pass for player %s", htmlspecialchars($name));
				}
				else
					printf("Player %s not found", htmlspecialchars($name));
				echo("<hr>");
			}
			require('templates/clans_join.php');
		}
		break;
	case "kick":
		{
			if ($name || $pass)
			{
				if ($player = get_player($name))
				{
					if ($player['cid'])
					{
						if ($clan = mysql_fetch_array(db_query(sprintf("select * from xwi_clans where pass = md5('%s')", addslashes($pass)))))
						{
							if ($player['cid'] == $clan['cid'])
							{
								db_query(sprintf("update xwi_players set cid = 0, mtime = unix_timestamp() where pid = %d", $player['pid']));
								printf("Player %s left clan %s", $player['name'], $clan['name']);
								$result = mysql_fetch_array(db_query(sprintf("select count(*) from xwi_players where cid = %d", $player['cid'])));
								if (!$result['0'])
									db_query(sprintf("delete from xwi_clans where cid = %d", $player['cid']));
							}
							else
								printf("Player %s is not in clan %s", $player['name'], $clan['name']);
						}
						else
							echo("Wrong clan pass");
					}
					else
						printf("Player %s is not in a clan", $player['name']);
				}
				else
					echo("Unknown player");
				echo("<hr>");
			}
			require('templates/clans_kick.php');
		}
		break;
	case 'reset_pass':
		$cname = trim($_REQUEST['cname']);
		$mail = trim($_REQUEST['mail']);
		$pass = substr(trim($_REQUEST['pass']), 0, 16);
		if ($pass)
		{
			$results = db_query(sprintf("select * from xwi_clan_reset_pass_requests where pass = md5('%s')", addslashes($pass)));
			if ($result = mysql_fetch_assoc($results))
			{
				$cpass = new_security_code();
				db_query(sprintf("update xwi_clans set pass = md5('%s'), mtime = unix_timestamp() where cid = %d", $cpass, $result['cid']));
				db_query(sprintf("delete from xwi_clan_reset_pass_requests where id = %d", $result['id']));
				printf("The new clan admin pass is %s", $cpass);

			}
			else
				echo("Wrong reset pass request");
			echo("<hr>");
		}
		else if ($cname && $mail)
		{
			if ($clan = mysql_fetch_array(db_query(sprintf("select cid, name, mail from xwi_clans where name = '%s' and mail = '%s'", addslashes($cname), addslashes($mail)))))
			{
				do
				{
					$cpass = new_security_code();
					$results = db_query(sprintf("select count(*) from xwi_clan_reset_pass_requests where pass = md5('%s')", $cpass));
					$result = mysql_fetch_array($results);
				}
				while ($result['0']);
				db_query(sprintf("insert into xwi_clan_reset_pass_requests (cid, pass, ctime) values (%d, md5('%s'), unix_timestamp())", $clan['cid'], $cpass));
				printf("A link to reset the clan admin pass has been emailed to %s", htmlspecialchars($clan['mail']));
				mail($clan['mail'],
					sprintf("XWI Clan Manager: Reset pass link for clan %s", $clan['name']),
					sprintf("To reset the clan admin pass for clan %s, click on %s?a=reset_pass&pass=%s. The request has been send from IP address %s", $clan['name'], $config['clan_manager_url'], $cpass, $remote_addr),
					"from: XWIS <xwis>");
			}
			else
			{
				echo("Wrong name/mail combo");
			}
			echo("<hr>");
		}
		require('templates/clans_reset_pass.php');
		break;
	case "leave":
		{
			if ($name || $pass)
			{
				if (get_player($name))
				{
					if ($player = get_player2($name, $pass))
					{
						if ($player['cid'])
						{
							db_query(sprintf("update xwi_players set cid = 0, mtime = unix_timestamp() where pid = %d", $player['pid']));
							$clan = get_clan($player['cid']);
							printf("Player %s left clan %s", $player['name'], $clan['name']);
							$result = mysql_fetch_array(db_query(sprintf("select count(*) from xwi_players where cid = %d", $player['cid'])));
							if (!$result['0'])
								db_query(sprintf("delete from xwi_clans where cid = %d", $player['cid']));
						}
						else
							printf("Player %s is not in a clan", $player['name']);
					}
					else
						printf("Invalid pass for player %s", htmlspecialchars($name));
				}
				else
					printf("Player %s not found", htmlspecialchars($name));
				echo("<hr>");
			}
			require('templates/clans_leave.php');
		}
		break;
	default:
		$cid = $_REQUEST['cid'];
		if ($cid && $clan = get_clan($cid))
		{
			echo('<table width=100%>');
			printf('<tr><th colspan=3 align=center>%s [%s]', $clan['full_name'], $clan['name']);
			echo('<tr><td width=40% align=left valign=top>');
			echo('<table>');
			if ($clan['creator_name'])
				printf('<tr><th align=right>Creator<td>%s', htmlspecialchars($clan['creator_name']));
			if ($clan['leader_name'])
				printf('<tr><th align=right>Leader<td>%s', htmlspecialchars($clan['leader_name']));
			if ($clan['icq'])
				printf('<tr><th align=right>ICQ<td><a href="http://wwp.icq.com/%d"><img src="http://wwp.icq.com/scripts/online.dll?icq=%d&img=2"></a>', $clan['icq'], $clan['icq']);
			if ($clan['mail'])
				printf('<tr><th align=right>Mail<td><a href="mailto:%s">%s</a>', htmlspecialchars($clan['mail']), htmlspecialchars($clan['mail']));
			if ($clan['msn'])
				printf('<tr><th align=right>MSN<td><a href="mailto:%s">%s</a>', htmlspecialchars($clan['msn']), htmlspecialchars($clan['msn']));
			if ($clan['site'] && $clan['site'] != 'http://')
			{
				if (!strstr($clan['site'], "://"))
					$clan['site'] = "http://" . $clan['site'];
				printf('<tr><th align=right>Site<td><a href="%s">%s</a>', htmlspecialchars($clan['site']), htmlspecialchars($clan['site']));
			}
			printf('<tr><th align=right>Founded<td>%s', gmdate('jS F, Y', $clan['ctime']));
			$awards = array
			(
				1 => 'trophy_gold.gif',
				2 => 'trophy_silver.gif',
				3 => 'trophy_bronze.gif',
				4 => 'runnerup.gif',
				5 => 'runnerup.gif',
				6 => 'runnerup.gif',
				7 => 'runnerup.gif',
				8 => 'runnerup.gif',
				9 => 'runnerup.gif',
				10 => 'runnerup.gif',
			);
			$ladder = array
			(
				2 => 'RA2',
				4 => 'YR',
				8 => 'TS',
			);
			$results = db_query(sprintf("select * from xcl_players inner join xcl_players_rank using (pid) where name = '%s' and lid in (2, 4, 8)", $clan['name']));
			if (mysql_num_rows($results))
			{
				printf('<tr><th align=right>Current Stats<td>');
				while ($result = mysql_fetch_array($results))
					printf('<a href="%s/ladders/?q=%s">#%d %d / %d %dp (%s)</a><br>', $result['lid'] == 8 ? '/ts' : '', urlencode($result['name']), $result['rank'], $result['win_count'], $result['loss_count'], $result['points'], $ladder[$result['lid']]);
			}
			$results = db_query(sprintf("select date, rank, lid from xcl_hof where name = '%s' and lid in (2, 4, 8) order by rank asc", $clan['name']));
			if (mysql_num_rows($results))
			{
				printf('<tr><th align=right>Awards<td>');
				$this_row = 0;
				while ($result = mysql_fetch_array($results))
				{
					if ($this_row == 5)
					{
						echo('<br>');
						$this_row = 0;
					}
					printf('<img src="images/%s" alt="#%d" title="#%d"> ', $awards[$result['rank']], $result['rank'], $result['rank']);
					$this_row++;
				}
			}
			printf('<tr><th><td><a href="?a=edit&cid=%d">Edit</a>', $clan['cid']);
			echo('</table>');
			echo('<td width=20% align=left valign=top>');
			$results = db_query(sprintf("select name from xwi_players where cid = %d order by name", $cid));
			while ($result = mysql_fetch_array($results))
				printf('<a href="/ladders/?q=%s">%s</a><br>', $result['name'], $result['name']);
			echo('<td width=40% align=right valign=top>');
			echo('<table><tr><td>');
			$results = db_query(sprintf("select date, rank, lid from xcl_hof where name = '%s' and lid in (2, 4, 8) order by date desc", $clan['name']));
			while ($result = mysql_fetch_array($results))
				printf('<img src="images/%s" alt="#%d" title="#%d"> #%d %s, %s<br>', $awards[$result['rank']], $result['rank'], $result['rank'], $result['rank'], $ladder[$result['lid']], gmdate("F Y", gmmktime(0, 0, 0, substr($result['date'], 5, 2), 1, substr($result['date'], 0, 4))));
			echo('</table>');
			echo('</table>');
		}
		else
		{
			include('templates/search.php');
			$text = $_REQUEST['text'];
			if ($text)
				$results = db_query(sprintf("select * from xwi_clans where name like '%s' order by name", addslashes($text)));
			else
				$results = db_query("select * from xwi_clans where player_count > 1 order by name");
			echo("<table><tr><th align=left>Abbrev<th align=left>Name<th align=right>Players<th align=left>Modified<th align=left>Created");
			while ($result = mysql_fetch_array($results))
				printf('<tr><td><a href="?cid=%d">%s</a><td><a href="?cid=%d">%s</a><td align=right>%d<td>%s<td>%s', $result['cid'], $result['name'], $result['cid'], $result['full_name'], $result['player_count'], gmdate("d-m-Y", $result['mtime']), gmdate("d-m-Y", $result['ctime']));
			echo("</table>");
		}
	}
	include('templates/bottom.php');
?>