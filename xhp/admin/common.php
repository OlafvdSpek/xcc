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

	function db_query_all($query)
	{
		$result = db_query($query);
		$d = array();
		while ($row = mysql_fetch_assoc($result))
			$d[] = $row;
		return $d;
	}

	function db_query_first($query)
	{
		return mysql_fetch_assoc(db_query($query));
	}

	function flags2a($v)
	{
		$d = '';
		if ($v & 1)
			$d .= 'administrator ';
		if ($v & 2)
			$d .= 'deleted ';
		if ($v & 4)
			$d .= 'moderator ';
		if ($v & 8)
			$d .= 'request screenshot ';
		$v &= ~0xf;
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

	function gsku2a($v, $locale = 0)
	{
		$a = array
		(
			0 => 'WC',
			1 => 'TD',
			2 => 'RA',
			3 => 'CS',
			4 => 'AM',
			0xc => 'RG',
			0xe => 'D2k',
			0x10 => 'Nox',
			0x12 => 'TS',
			0x15 => 'RA1 3',
			0x18 => 'FS',
			0x1f => 'EBFD',
			0x21 => 'RA2',
			0x25 => 'Nox',
			0x29 => 'YR',
			0x30 => 'RG',
		);
		$b = array_key_exists($v, $a) ? $a[$v] : 0 + $v;
		switch ($locale & ~0x10)
		{
		case 0: break;
		case 2: $b .= ' de'; break;
		case 3: $b .= ' fr'; break;
		default:
			$b .= ' ' . ($locale & ~0x10);
		}
		if ($locale & 0x10)
			$b .= ' EM';
		return $b;
	}
