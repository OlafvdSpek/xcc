<?php
	require_once(dirname(__FILE__) . '/../xcc_common.php');
	db_connect();
	while (1)
	{
		$rows = db_query("select s.sid, sv.serial from xwi_serials s left join xwi_serials_valid sv on unhex(s.serial) = sv.serial where not s.valid limit 100");
		if (!mysql_num_rows($rows))
			break;
		while ($row = mysql_fetch_assoc($rows))
			db_query(sprintf("update xwi_serials set valid = %d where sid = %d", $row['serial'] ? 1 : -1, $row['sid']));
	}
?>