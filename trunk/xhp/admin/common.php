<?php
	ob_start('ob_gzhandler');

	require_once('../xcc_common.php');

	db_connect();
?>
<link rel=stylesheet href="/xcc.css">
<title>XWI Admin</title>