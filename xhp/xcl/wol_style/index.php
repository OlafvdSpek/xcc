<?
	require("xcc_common.php");

	$config['ladderdefault'] = "1"; // 1 = RA2 , 2 = YURI

	function get_side($c)
	{
		if (!$c)
			return -1;
		else if (!($c & ~0x1f))
			return 0;
		else if (!($c & ~0x1e0))
			return 1;
		else if (!($c & ~0x200))
			return 2;
		return -2;
	}

	function get_country_flag_url($i)
	{
		switch ($i & ~0xff)
		{
		case 0x100:
			$country_flag_urls = array
			(
				"../images/atreides.png",
				"../images/harkonnen.png",
				"../images/ordos.png",
			);
			break;
		case 0x200:
			$country_flag_urls = array
			(
				"../images/gdi.png",
				"../images/nod.png",
			);
			break;
		default:
			$country_flag_urls = array
			(
				"../images/usai.png",
				"../images/japi.png",
				"../images/frai.png",
				"../images/geri.png",
				"../images/gbri.png",
				"../images/djbi.png",
				"../images/arbi.png",
				"../images/lati.png",
				"../images/rusi.png",
				"../images/yrii.png",
			);
		}
		return $country_flag_urls[$i & 0xff];
	}


	if ($_GET["laddertype"] != "") { $laddertype = $_GET["laddertype"]; } else { $laddertype = $_POST["laddertype"]; }
	if ($_GET["ladr"] != "") { $ladr = $_GET["ladr"]; } else { $ladr = $_POST["ladr"]; }
	if ($_GET["mode"] != "") { $mode = $_GET["mode"]; } else { $mode = $_POST["mode"]; }
	if ($_GET["id"] != "") { $id = $_GET["id"]; } else { $id = $_POST["id"]; }
	if ($_GET["lid"] != "") { $lid = $_GET["lid"]; } else { $lid = $_POST["lid"]; }
	if ($_GET["site"] != "") { $site = $_GET["site"]; } else { $site = $_POST["site"]; }

	db_connect();
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<link rel=stylesheet href="common.css">
<title>XCC Community Ladder</title>
<body text="#BABABA">
<?
	if($laddertype == "")
		$laddertype = $config['ladderdefault'];
	switch ($laddertype)
	{
	case 1:
		include("ra2.php");
		break;
	case 2:
		include("yuri.php");
		break;
	case 3:
		include("ts.php");
		break;
	}
	include('../bottom.php');
?>
