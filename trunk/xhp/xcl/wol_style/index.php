<?
	require("xcc_common.php");

	$PHP_SELF = "http://xwis.net/xcl/ra2/";

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
				"http://xwis.net/xcl/images/atreides.png",
				"http://xwis.net/xcl/images/harkonnen.png",
				"http://xwis.net/xcl/images/ordos.png",
			);
			break;
		case 0x200:
			$country_flag_urls = array
			(
				"http://xwis.net/xcl/images/gdi.png",
				"http://xwis.net/xcl/images/nod.png",
			);
			break;
		default:
			$country_flag_urls = array
			(
				"http://xwis.net/xcl/images/usai.png",
				"http://xwis.net/xcl/images/japi.png",
				"http://xwis.net/xcl/images/frai.png",
				"http://xwis.net/xcl/images/geri.png",
				"http://xwis.net/xcl/images/gbri.png",
				"http://xwis.net/xcl/images/djbi.png",
				"http://xwis.net/xcl/images/arbi.png",
				"http://xwis.net/xcl/images/lati.png",
				"http://xwis.net/xcl/images/rusi.png",
				"http://xwis.net/xcl/images/yrii.png",
			);
		}
		return $country_flag_urls[$i & 0xff];
	}


	function dec2ip($dec)
	{
		return long2ip($dec);
		/*
		if($dec<0) {
		$dec=(double) 4294967296+$dec;
		}
		if($dec>16777215) {
		$ip=$dec-(intval($dec/256)*256);
		$dec=(double) intval($dec/256);
		} else $ip="0";
		if($dec>65535) {
		$ip=($dec-(intval($dec/256)*256)).".".$ip;
		$dec=(double) intval($dec/256);
		} else $ip="0.".$ip;
		if($dec>255) {
		$ip=($dec-(intval($dec/256)*256)).".".$ip;
		$dec=(double) intval($dec/256);
		} else $ip="0.".$ip;
		$ip=$dec.".".$ip;
		return (string) $ip;
		*/
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
<title>XCC Community Ladder</title>
<body text="#BABABA" link="#BABABA" alink="#BABABA" vlink="#BABABA" topmargin="0">
<style type='text/css'>
	body
	{
		font-family: verdana;
		font-size: 10px;
		font-color: #ffffff;
		background-color: #3a3a3a;
	}
	a:link, a:visited, a:active
	{
		color: #d8d8d8;
		text-decoration: none;
	}
	a:hover
	{
		color: #bababa;
		text-decoration: none;
	}
	.maintitle { vertical-align:middle;font-weight:normal; color:#ffffff; padding:8px 0px 8px 5px; background-image: url(images/tile_back.gif) }
</style>
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
