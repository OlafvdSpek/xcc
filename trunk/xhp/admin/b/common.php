<?php
	function db_connect()
	{
		global $mysql;
		mysql_pconnect($mysql['host'], $mysql['user'], $mysql['password']) || die(htmlspecialchars(mysql_error()));
		mysql_select_db($mysql['db']) || die(htmlspecialchars(mysql_error()));
	}

	function db_query($query)
	{
		// printf('%s<br>', htmlspecialchars($query));
		$result = mysql_query($query);
		if (!$result)
			die(sprintf('%s<br>%s', htmlspecialchars(mysql_error()), htmlspecialchars($query)));
		return $result;
	}

	function db_query_first($query)
	{
		return mysql_fetch_assoc(db_query($query));
	}

	function flags2a($v)
	{
		$d = '';
		if ($v & 1)
		{
			$d .= 'administrator ';
			$v &=~1;
		}
		if ($v & 2)
		{
			$d .= 'deleted ';
			$v &=~2;
		}
		if ($v & 4)
		{
			$d .= 'moderator ';
			$v &=~4;
		}
		if ($v)
			$d .= 0 + $v;
		return $d;
	}

	function lid2a($v)
	{
		switch ($v)
		{
		case 1:
			return 'RA2';
		case 2:
			return 'RA2 C';
		case 3:
			return 'YR';
		case 4:
			return 'YR C';
		case 7:
			return 'TS';
		case 8:
			return 'TS C';
		case 17:
			return 'RA2 F';
		case 19:
			return 'YR F';
		case 23:
			return 'TS F';
		}
		return 0 + $v;
	}

	function gsku2a($v)
	{
		switch ($v)
		{
		case 0:
			return 'WC';
		case 1:
			return 'TD';
		case 2:
			return 'RA';
		case 3:
			return 'RA CS';
		case 4:
			return 'RA AM';
		case 0xc:
		case 0x30:
			return 'RG';
		case 0xe:
			return 'D2k';
		case 0x10:
		case 0x25:
			return 'Nox';
		case 0x12:
			return 'TS';
		case 0x15:
			return 'RA1 3';
		case 0x18:
			return 'TS FS';
		case 0x1f:
			return 'EBFD';
		case 0x21:
			return 'RA2';
		case 0x29:
			return 'RA2 YR';
		}
		return 0 + $v;
	}
?>
