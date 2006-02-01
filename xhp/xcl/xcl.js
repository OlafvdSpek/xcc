function i2(v)
{
	return v < 10 ? '0' + v : v;
}

function cmp2a(v)
{
	switch (v)
	{
	case 0x100:
		return 'W';
	case 0x200:
	case 0x210:
	case 0x220:
		return 'L';
	}
	return v;
}

function date2a(v)
{
	date = new Date(1000 * v);
	return i2(date.getHours()) + ':' + i2(date.getMinutes()) + ' ' + i2(date.getDate()) + '-' + i2(date.getMonth() + 1) + '-' + date.getFullYear();
}

function dura2a(v)
{
	r = i2(v % 60);
	v -= v % 60;
	v /= 60;
	if (v)
	{
		r = i2(v % 60) + ':' + r;
		v -= v % 60;
		v /= 60;
		if (v)
			r = v + ':' + r;

	}
	return r;
}

function eiz(v)
{
	return v ? v : '';
}

function gsku2a(v)
{
	switch (v)
	{
	case 0:
		return 'WC';
	case 1:
		return 'TD';
	case 2:
		return 'RA';
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
	return v;
}

function pc2a(v)
{
	return v ? v > 0 ? '+' + v : v : '';
}

function page_xwis_top()
{
	document.write('<link rel=stylesheet href="/egx.css">');
	document.write('<title>XCC WOL IRC Server</title>');
	document.write('<table width="100%"><tr><td valign=bottom><p class=page_title>XCC WOL IRC Server<td align=right valign=bottom>');
	document.write('<a href="?">Clans</a> | ');
	document.write('<a href="http://strike-team.net/forums/">Forum</a> | ');
	document.write('<a href="?">Online</a> | ');
	document.write('<a href="http://strike-team.net/nuke/html/modules.php?op=modload&amp;name=News&amp;file=article&amp;sid=13">Rules</a> | ');
	document.write('<a href="http://xccu.sourceforge.net/utilities/XGS.exe" title="XCC Game Spy">XGS</a> | ');
	document.write('<a href="/downloads/XWISC.exe" title="XCC WOL IRC Server Client">XWISC</a><br>');
	document.write('<a href="?hof=" title="Hall of Fame">HoF</a> | ');
	document.write('<a href="?hos=" title="Hall of Shame">HoS</a> | ');
	document.write('<a href="?">Home</a> | ');
	document.write('<a href="?recent_games=">Recent</a> | ');
	document.write('<a href="?stats=">Stats</a>');
	document.write('</table>');
}

function page_top(frozen)
{
	document.write('<link rel=stylesheet href="/egx.css">');
	document.write('<title>XCC Community Ladder', frozen ? ' (frozen)' : '', '</title>');
	document.write('<table width="100%"><tr><td valign=bottom><p class=page_title>XCC Community Ladder<td align=right valign=bottom>');
	document.write('<a href="?">Clans</a> | ');
	document.write('<a href="http://strike-team.net/forums/">Forum</a> | ');
	document.write('<a href="?">Online</a> | ');
	document.write('<a href="http://strike-team.net/nuke/html/modules.php?op=modload&amp;name=News&amp;file=article&amp;sid=13">Rules</a> | ');
	document.write('<a href="http://xccu.sourceforge.net/utilities/XGS.exe" title="XCC Game Spy">XGS</a> | ');
	document.write('<a href="/downloads/XWISC.exe" title="XCC WOL IRC Server Client">XWISC</a><br>');
	document.write('<a href="?hof=" title="Hall of Fame">HoF</a> | ');
	document.write('<a href="?hos=" title="Hall of Shame">HoS</a> | ');
	document.write('<a href="?">Home</a> | ');
	document.write('<a href="?recent_games=">Recent</a> | ');
	document.write('<a href="?stats=">Stats</a>');
	document.write('</table><hr>');
}

function page_bottom(date)
{
	document.write('<hr><table width="100%"><tr><td valign=top>');
	document.write('<a href="http://communityteam.de/">Community Team</a> | ');
	document.write('<a href="http://dune2k.com/">FED2k</a> | ');
	document.write('<a href="http://strike-team.net/">Strike Team</a> | ');
	document.write('<a href="http://xccu.sourceforge.net/">XCC Home Page</a>');
	document.write('<td align=right valign=top>', date2a(date));
	document.write('<tr><td align=center colspan=3>');
	document.write('<p><a href="https://www.paypal.com/xclick/business=st_xcl%40hotmail.com&amp;item_name=XCL+Fund&amp;image_url=http%3A//xccu.sourceforge.net/button.gif&amp;no_shipping=1&amp;no_note=1&amp;cs=1&amp;tax=0&amp;currency_code=GBP"><img src="https://www.paypal.com/images/x-click-but04.gif" alt="PayPal Donate"></a>');
	document.write('<p>');
	nedstatbasic("ACYaRA5mKkSNw9DcBlC+vYnGi83A", 0);
	document.write('<p><a href="http://communityteam.de/"><img src="http://communityteam.de/images/banner/ct_banner.gif" alt="Community Team"></a>');
	document.write('<p>');
	google_ad_client = "pub-1982327992445962";
	google_ad_width = 728;
	google_ad_height = 90;
	google_ad_format = "728x90_as";
	google_ad_channel ="4775308317";
	google_alternate_ad_url = "http://strike-team.net/forums/uploads/post-13-1096106502.gif";
	document.write('<script type="text/javascript" src="http://pagead2.googlesyndication.com/pagead/show_ads.js"></script>');
}

function page_search(lid)
{
	document.write('<center><form><table><tr>');
	document.write('<td>Player:<input type=hidden name=lid value=', lid, '><td><input type=text name=pname size=9>');
	if (lid)
	{
		document.write('<td>Countries:<select name=cty>');
		document.write('<option value=0>All</option>');
		if (lid == 7 || lid == 8)
		{
			document.write('<option value=2>GDI</option>');
			document.write('<option value=1>Nod</option>');
		}
		else
		{
			document.write('<option value=992>Allied</option>');
			document.write('<option value=543>Soviet</option>');
			if (lid == 3 || lid == 4)
				document.write('<option value=511>Yuri</option>');
			document.write('<option value=1022>America</option>');
			document.write('<option value=1021>Korea</option>');
			document.write('<option value=1019>France</option>');
			document.write('<option value=1015>Germany</option>');
			document.write('<option value=1007>Great Britain</option>');
			document.write('<option value=991>Libya</option>');
			document.write('<option value=959>Iraq</option>');
			document.write('<option value=895>Cuba</option>');
			document.write('<option value=767>Russia</option>');
			if (lid == 3 || lid == 4)
				document.write('<option value=511>Yuri</option>');
		}
		document.write('</select>');
	}
	document.write('<td><input type=submit value="Search"></tr></table></form></center><hr>');
}

function page_ladders(frozen)
{
	ts_prefix = '/ts/xcl/';
	ra2_prefix = '/xcl/';
	ra2_yr_prefix = '/xcl/';
	if (frozen)
	{
		ts_prefix += 'prev.php';
		ra2_prefix += 'prev.php';
		ra2_yr_prefix += 'prev.php';
	}
	document.write('<center><table>');
	document.write('<tr><td align=right>Tiberian Dawn<td><td><td><td><a href="/td/online">Online</a>');
	document.write('<tr><td align=right>Red Alert<td><td><td><td><a href="/ra/online">Online</a>');
	document.write('<tr><td align=right>Tiberian Sun<td><a href="', ts_prefix, '?lid=ts">Player</a><td><a href="', ts_prefix, '?lid=ts_clan">Clan</a><td><a href="/ts/xwi/">Clan Manager</a><td><a href="/ts/online">Online</a>');
	document.write('<tr><td align=right>Red Alert 2<td><a href="', ra2_prefix, '?lid=ra2">Player</a><td><a href="', ra2_prefix, '?lid=ra2_clan">Clan</a><td><a href="/xwi/">Clan Manager</a><td><a href="/ra2/online">Online</a>');
	document.write('<tr><td align=right>Yuri\'s Revenge<td><a href="', ra2_yr_prefix, '?lid=ra2_yr">Player</a><td><a href="', ra2_yr_prefix, '?lid=ra2_yr_clan">Clan</a><td><a href="/xwi/">Clan Manager</a><td><a href="/yr/online">Online</a>');
	document.write('<tr><td align=right>Renegade<td><td><td><a href="/rg/xwi/">Clan Manager</a><td><a href="/rg/online">Online</a>');
	document.write('<tr><td align=right>Nox<td><td><td><td><a href="/nox/online">Online</a>');
	document.write('<tr><td align=center colspan=5><a href="ra2">Westwood Studios Style Ladder</a>');
	if (frozen)
		document.write('<tr><td align=center colspan=5><a href=".">Current Month</a>');
	else
		document.write('<tr><td align=center colspan=5><a href="prev.php">Previous Month</a>');
	document.write('</table></center>');
}

function get_country_name(i)
{
	switch (i & ~0xff)
	{
	case 0x100:
		country_names = new Array
		(
			'Atreides',
			'Harkonnen',
			'Ordos'
		);
		break;
	case 0x200:
		country_names = new Array
		(
			'GDI',
			'Nod'
		);
		break;
	default:
		country_names = new Array
		(
			'America',
			'Korea',
			'France',
			'Germany',
			'Great Britain',
			'Libya',
			'Iraq',
			'Cuba',
			'Russia',
			'Yuri'
		);
	}
	return country_names[i & 0xff];
}

function get_country_flag_url(i)
{
	switch (i & ~0xff)
	{
	case 0x100:
		country_flag_urls = new Array
		(
			'images/atreides.png',
			'images/harkonnen.png',
			'images/ordos.png'
		);
		break;
	case 0x200:
		country_flag_urls = new Array
		(
			'images/gdi.png',
			'images/nod.png'
		);
		break;
	default:
		country_flag_urls = new Array
		(
			'images/usai.png',
			'images/japi.png',
			'images/frai.png',
			'images/geri.png',
			'images/gbri.png',
			'images/djbi.png',
			'images/arbi.png',
			'images/lati.png',
			'images/rusi.png',
			'images/yrii.png'
		);
	}
	return country_flag_urls[i & 0xff];
}

function get_country_img(i)
{
	return '<img src="' + get_country_flag_url(i) + '" alt="' + get_country_name(i) + '" title="' + get_country_name(i) + '">';
}

function lid2a(v)
{
	names = new Array
	(
		'', 'ra2', 'ra2 clan', 'yr', 'yr clan', 'ebfd', 'ebfd clan', 'ts',
		'ts clan', '', '', '', '', '', '', '',
		'', 'ra2 non-tournament', '', 'yr non-tournament', '', '', '', 'ts non-tournament'
	);
	return names[v];
}

function tr0(rank, lid, pid, name, wins, losses, points, points_max, date, countries, echo_lid)
{
	document.write('<tr>');
	if (echo_lid)
		document.write('<td><a href="?lid=', lid, '">', lid2a(lid), '</a>');
	document.write('<td align=right>', rank, '<td>');
	if (lid & 1)
	{
		document.write('<img src="images/cooperat.png" alt="XCL Founder" title="XCL Founder">');
		if (points_max > 1500)
			document.write(' <img src="images/stargen.png" alt="&gt; 1500p" title="&gt; 1500p">');
		else if (points_max > 1000)
			document.write(' <img src="images/general.png" alt="&gt; 1000p" title="&gt; 1000p">');
		else if (points_max > 500)
			document.write(' <img src="images/briggenr.png" alt="&gt; 500p" title="&gt; 500p">');
		if (rank == 1)
			document.write(' <img src="images/comchief.png" alt="#1" title="#1">');
		else if (rank && rank < 26)
			document.write(' <img src="images/colonel.png" alt="< #26" title="< #26">');
	}
	document.write('<td><a href="?', (lid & 1 ? 'pid=' : 'cid='), pid, '">', name, '</a>');
	document.write('<td align=right>', wins);
	document.write('<td align=right>', losses);
	document.write('<td align=right>', points);
	date = new Date(1000 * date);
	document.write('<td>', i2(date.getHours()), ':', i2(date.getMinutes()), ' ', i2(date.getDate()), '-', i2(date.getMonth() + 1), '-', date.getFullYear());
	for (var i = 0; i < 10; i++)
	{
		document.write('<td>');
		if (countries & 1 << i)
		{
			switch (lid)
			{
			case 5:
			case 6:
				document.write(get_country_img(0x100 | i));
				break;
			case 7:
			case 8:
				document.write(get_country_img(0x200 | i));
				break;
			default:
				document.write(get_country_img(i));
			}
		}
	}
}

function t0(v, echo_lid)
{
	document.write('<center><table><tr>');
	if (echo_lid)
		document.write('<th>Ladder');
	document.write('<th>Rank<th><th>Name<th colspan=2>Stats<th>Points<th>Date<th colspan=10>Countries');
	if (v.length >= 10)
	{
		for (var i = 0; i + 10 <= v.length; i += 10)
			tr0(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9], echo_lid);
	}
	else
		document.write('<tr><th colspan=18>-');
	document.write('</table></center>');
}

function tr1a(gid, ws_gid, v, dura, scen, date, afps, oosy, trny, echo_return_points)
{
	document.write('<tr>');
	document.write('<td align=right><a href="?gid=', gid, '" title=', ws_gid, '>', gid, '</a>');
	tr1bv(v);
	date = new Date(1000 * date);
	document.write('<td align=right>', dura2a(dura), '<td>', scen);
	document.write('<td align=right>', i2(date.getHours()), ':', i2(date.getMinutes()), ' ', i2(date.getDate()), '-', i2(date.getMonth() + 1));
	document.write('<td>', afps, '<td>', oosy, '<td>', trny);
	if (echo_return_points)
		document.write('<td><a href="/admin/xcl_return_points.php?gid=', gid, '">Return points</a>');
}

function tr1b(rank, pid, name, wins, losses, points, crank, cid, cname, cwins, closses, cpoints, cty, cmp, pc)
{
	document.write(cid != 0 ? '<td>' : '<td colspan=2>');
	document.write('<a href="?pid=', pid, '" title="#', rank, ' ', wins, ' / ', losses, ' ', points, 'p">', name, '</a>');
	if (cid != 0)
		document.write('<td><a href="?cid=', cid, '" title="#', crank, ' ', cwins, ' / ', closses, ' ', cpoints, 'p">', cname, '</a>');
	document.write('<td align=center>', get_country_img(cty), '<td>', cmp2a(cmp), '<td align=right>', pc2a(pc));
}

function tr1bv(v)
{
	for (var i = 0; i + 15 <= v.length; i += 15)
		tr1b(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9], v[i + 10], v[i + 11], v[i + 12], v[i + 13], v[i + 14]);
}

function tr1d(v)
{
	document.write('<tr><td>');
	tr1bv(v);
	document.write('<td colspan=6>');
}

function tr1f(cid)
{
	document.write(cid
		? '<table><tr><th>GID<th colspan=5>Clan A<th colspan=5>Clan B<th colspan=1>Duration<th>Scenario<th>Date'
		: '<table><tr><th>GID<th colspan=5>Player A<th colspan=5>Player B<th colspan=1>Duration<th>Scenario<th>Date');
}

function tr1g()
{
	document.write('<tr><th colspan=17>-');
}

function tr1h()
{
	document.write('</table>');
}

function tr2(name, wins, losses, points_won, points_lost, points)
{
	document.write('<tr><td>', name, '<td align=right>', wins, '<td align=right>', losses);
	document.write('<td align=right>', points_won, '<td align=right>', points_lost, '<td align=right>', points);
}

function t2(v)
{
	document.write('<hr><table><tr><th>Player<th>W<th>L<th>W<th>L<th>P');
	for (var i = 0; i + 6 <= v.length; i += 6)
		tr2(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5]);
	document.write('</table>');
}

function tr3(count, cty)
{
	document.write('<tr><td align=right>', count, '<td align=center>', get_country_img(cty));
}

function t3(v)
{
	document.write('<hr><table><tr><th>Count<th>Country');
	for (var i = 0; i + 2 <= v.length; i += 2)
		tr3(v[i + 0], v[i + 1]);
	document.write('</table>');
}

function tr4(count, scen)
{
	document.write('<tr><td align=right>', count, '<td>', scen);
}

function t4(v)
{
	document.write('<hr><table><tr><th>Count<th>Scenario');
	for (var i = 0; i + 2 <= v.length; i += 2)
		tr4(v[i + 0], v[i + 1]);
	document.write('</table>');
}

function tr5(name, unk, unb, unl, blk, blb, bll, blc, ink, inb, inl, plk, plb, pll)
{
	document.write('<tr><th>', name, '<th>killed<th>bought<th>left<th>captured');
	document.write('<tr><td align=right>units<td align=right>', unk, '<td align=right>', unb, '<td align=right>', unl);
	document.write('<tr><td align=right>buildings<td align=right>', blk, '<td align=right>', blb, '<td align=right>', bll, '<td align=right>', blc);
	document.write('<tr><td align=right>infantry<td align=right>', ink, '<td align=right>', inb, '<td align=right>', inl);
	document.write('<tr><td align=right>planes<td align=right>', plk, '<td align=right>', plb, '<td align=right>', pll);
}

function t5(v)
{
	document.write('<hr><table>');
	for (var i = 0; i + 14 <= v.length; i += 14)
		tr5(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9], v[i + 10], v[i + 11], v[i + 12], v[i + 13]);
	document.write('</table>');
}

function tr6(gsku, a, b, c, d, e, f, g)
{
	document.write('<tr><td>');
	if (gsku)
		document.write(gsku2a(gsku));
	document.write('<td align=right>', a, '<td align=right>', b, '<td align=right>', c, '<td align=right>', a + b + c);
	document.write('<td align=right>', d, '<td align=right>', e, '<td align=right>', f, '<td align=right>', d + e + f);
	document.write('<td align=right>', g);
}

function t6(v)
{
	document.write('<table>');
	document.write('<tr><th><th colspan=4>Games<th colspan=4>Players<th>Clans');
	document.write('<tr><th><th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>Clan');
	for (var i = 0; i + 8 <= v.length; i += 8)
		tr6(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7]);
	document.write('</table><hr>');
}

function p6(a6, a8, a18, a9, a10, a11, a12)
{
	t6(a6);
	t8(a8);
	t18(a18);
	t9(a9);
	t10(a10);
	t11(a11);
	t12(a12);
}

function tr8(cty, count_ts_0, count_ts_1, count_ts_2, count_ra2_0, count_ra2_1, count_ra2_2, count_ra2_yr_0, count_ra2_yr_1, count_ra2_yr_2)
{
	document.write('<tr><td align=center>', get_country_img(cty));
	document.write('<td align=right>', eiz(count_ts_0), '<td align=right>', eiz(count_ts_1), '<td align=right>', eiz(count_ts_2), '<td align=right>', eiz(count_ts_0 + count_ts_1 + count_ts_2));
	document.write('<td align=right>', eiz(count_ra2_0), '<td align=right>', eiz(count_ra2_1), '<td align=right>', eiz(count_ra2_2), '<td align=right>', eiz(count_ra2_0 + count_ra2_1 + count_ra2_2));
	document.write('<td align=right>', eiz(count_ra2_yr_0), '<td align=right>', eiz(count_ra2_yr_1), '<td align=right>', eiz(count_ra2_yr_2), '<td align=right>', eiz(count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
	document.write('<td align=right>', eiz(count_ts_0 + count_ts_1 + count_ts_2 + count_ra2_0 + count_ra2_1 + count_ra2_2 + count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
}

function t8(v)
{
	document.write('<table><tr><th>Country<th colspan=4>TS<th colspan=4>RA2<th colspan=4>RA2 YR<th>Total<tr><th><th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>');
	for (var i = 0; i + 10 <= v.length; i += 10)
		tr8(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9]);
	document.write('</table><hr>');
}

function tr9(scen, count_ts_0, count_ts_1, count_ts_2, count_ra2_0, count_ra2_1, count_ra2_2, count_ra2_yr_0, count_ra2_yr_1, count_ra2_yr_2)
{
	document.write('<tr><td>', scen);
	document.write('<td align=right>', eiz(count_ts_0), '<td align=right>', eiz(count_ts_1), '<td align=right>', eiz(count_ts_2), '<td align=right>', eiz(count_ts_0 + count_ts_1 + count_ts_2));
	document.write('<td align=right>', eiz(count_ra2_0), '<td align=right>', eiz(count_ra2_1), '<td align=right>', eiz(count_ra2_2), '<td align=right>', eiz(count_ra2_0 + count_ra2_1 + count_ra2_2));
	document.write('<td align=right>', eiz(count_ra2_yr_0), '<td align=right>', eiz(count_ra2_yr_1), '<td align=right>', eiz(count_ra2_yr_2), '<td align=right>', eiz(count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
	document.write('<td align=right>', eiz(count_ts_0 + count_ts_1 + count_ts_2 + count_ra2_0 + count_ra2_1 + count_ra2_2 + count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
}

function t9(v)
{
	document.write('<table><tr><th>Scenario<th colspan=4>TS<th colspan=4>RA2<th colspan=4>RA2 YR<th>Total<tr><th><th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>');
	for (var i = 0; i + 10 <= v.length; i += 10)
		tr9(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9]);
	document.write('</table>');
}

function tr10(dura, count_ts_0, count_ts_1, count_ts_2, count_ra2_0, count_ra2_1, count_ra2_2, count_ra2_yr_0, count_ra2_yr_1, count_ra2_yr_2)
{
	document.write('<tr><td align=right>', dura ? (dura - 5) + ' - ' + (dura + 5) : '< 5');
	document.write('<td align=right>', eiz(count_ts_0), '<td align=right>', eiz(count_ts_1), '<td align=right>', eiz(count_ts_2), '<td align=right>', eiz(count_ts_0) + eiz(count_ts_1) + eiz(count_ts_2));
	document.write('<td align=right>', eiz(count_ra2_0), '<td align=right>', eiz(count_ra2_1), '<td align=right>', eiz(count_ra2_2), '<td align=right>', eiz(count_ra2_0 + count_ra2_1 + count_ra2_2));
	document.write('<td align=right>', eiz(count_ra2_yr_0), '<td align=right>', eiz(count_ra2_yr_1), '<td align=right>', eiz(count_ra2_yr_2), '<td align=right>', eiz(count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
	document.write('<td align=right>', eiz(count_ts_0 + count_ts_1 + count_ts_2 + count_ra2_0 + count_ra2_1 + count_ra2_2 + count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
}

function t10(v)
{
	document.write('<table><tr><th>Duration<th colspan=4>TS<th colspan=4>RA2<th colspan=4>RA2 YR<th>Total<tr><th><th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>');
	for (var i = 0; i + 10 <= v.length; i += 10)
		tr10(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9]);
	document.write('</table><hr>');
}

function tr11(afps, count_ts_0, count_ts_1, count_ts_2, count_ra2_0, count_ra2_1, count_ra2_2, count_ra2_yr_0, count_ra2_yr_1, count_ra2_yr_2)
{
	document.write('<tr><td align=right>', afps);
	document.write('<td align=right>', eiz(count_ts_0), '<td align=right>', eiz(count_ts_1), '<td align=right>', eiz(count_ts_2), '<td align=right>', eiz(count_ts_0) + eiz(count_ts_1) + eiz(count_ts_2));
	document.write('<td align=right>', eiz(count_ra2_0), '<td align=right>', eiz(count_ra2_1), '<td align=right>', eiz(count_ra2_2), '<td align=right>', eiz(count_ra2_0 + count_ra2_1 + count_ra2_2));
	document.write('<td align=right>', eiz(count_ra2_yr_0), '<td align=right>', eiz(count_ra2_yr_1), '<td align=right>', eiz(count_ra2_yr_2), '<td align=right>', eiz(count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
	document.write('<td align=right>', eiz(count_ts_0 + count_ts_1 + count_ts_2 + count_ra2_0 + count_ra2_1 + count_ra2_2 + count_ra2_yr_0 + count_ra2_yr_1 + count_ra2_yr_2));
}

function t11(v)
{
	document.write('<table><tr><th>Average FPS<th colspan=4>TS<th colspan=4>RA2<th colspan=4>RA2 YR<th>Total<tr><th><th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>Free<th>Player<th>Clan<th>Total<th>');
	for (var i = 0; i + 10 <= v.length; i += 10)
		tr11(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9]);
	document.write('</table><hr>');
}

function tr12(d, v)
{
	if (d == 32)
		document.write('<tr><th>');
	else
		document.write('<tr><th align=right>', d);
	for (h = 0; h < 25; h++)
	{
		if (v[h])
			document.write('<td align=right>', v[h]);
		else
			document.write('<td>');
	}
}

function t12(v)
{
	document.write('<table><tr><td>');
	var column_totals = new Array();
	for (h = 0; h < 24; h++)
	{
		column_totals[h] = 0;
		document.write('<th align=right>', h);
	}
	for (var i = 0; i + 25 <= v.length; i += 25)
	{
		document.write('<tr><th align=right>', v[i]);
		var row_total = 0;
		for (var h = 0; h < 24; h++)
		{
			var f = v[h + i + 1];
			column_totals[h] += f;
			row_total += f;
			if (f)
				document.write('<td align=right>', f);
			else
				document.write('<td>');
		}
		document.write('<td align=right>', row_total);
	}
	document.write('<tr><th>');
	var row_total = 0;
	for (var h = 0; h < 24; h++)
	{
		var f = column_totals[h];
		row_total += f;
		if (f)
			document.write('<td align=right>', f);
		else
			document.write('<td>');
	}
	document.write('<td align=right>', row_total);
	document.write('</table>');
}

function tr13(rank, name)
{
	document.write('<tr><td align=right>', rank, '<td>', name);
}

function t13(lid, v)
{
	var title = '';
	switch (lid)
	{
	case 1:
		title = 'Red Alert 2';
		break;
	case 2:
	case 4:
	case 6:
	case 8:
		title = 'Clan';
		break;
	case 3:
		title = 'Yuri\'s Revenge';
		break;
	case 7:
		title = 'Tiberian Sun';
		break;
	}
	document.write('<td><table><tr><th colspan=2>', title);
	var rank = 1;
	for (var i = 0; i < v.length && v[i]; i++)
		tr13(rank++, v[i]);
	document.write('</table>');
}

function t13a()
{
	document.write('<center><table><tr>');
}

function t13c()
{
	document.write('</table></center>');
}

function t13d(title, v)
{
	document.write('<hr><center><table><tr><th colspan=12>', title, '<tr>');
	for (var i = 0; i + 2 <= v.length; i += 2)
		t13(v[i + 0], v[i + 1]);
	document.write('</table></center>');
}

function t14(v)
{
	document.write('<center><table><tr><th>Name');
	for (var i = 0; i < v.length && v[i]; i++)
		document.write('<tr><td><a href="?pname=', v[i], '">', v[i], '</a>');
	document.write('</table></center>');
}

function t15(v)
{
	document.write('<table><tr><th>Rank<th><th>Name<th colspan=2>Stats<th>Points<th>Date<th colspan=10>Countries');
	for (var i = 0; i + 10 <= v.length; i += 10)
		tr0(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7], v[i + 8], v[i + 9], false);
	document.write('</table><hr>');
}

function tr16(name, topic, gsku)
{
	document.write('<tr><td>', name, '<td>', topic, '<td>', gsku2a(gsku));
}

function t16(v)
{
	document.write('<hr><table align=center>');
	for (var i = 0; i + 3 <= v.length; i += 3)
		tr16(v[i + 0], v[i + 1], v[i + 2]);
	document.write('</table>');
}

function tr17(rank, name, wins, losses, points, cname, channel, gsku)
{
	document.write('<tr>');
	document.write('<td><a href="?pname=', name, '">', name, '</a>');
	document.write('<td>');
	if (cname)
		document.write('<a href="?pname=', cname, '">', cname, '</a>');
	if (wins || losses)
		document.write('<td align=right>', rank, '<td align=right>', wins, '<td align=right>', losses, '<td align=right>', points);
	else
		document.write('<td colspan=4>');
	document.write('<td>');
	if (channel)
		document.write(channel);
	document.write('<td>', gsku2a(gsku));
}

function t17(v)
{
	document.write('<hr><table align=center>');
	for (var i = 0; i + 8 <= v.length; i += 8)
		tr17(v[i + 0], v[i + 1], v[i + 2], v[i + 3], v[i + 4], v[i + 5], v[i + 6], v[i + 7]);
	document.write('</table>');
}

function p16(games, players, date)
{
	page_xwis_top();
	if (games.length > 1)
		t16(games);
	if (players.length > 1)
		t17(players);
	page_bottom(date);
}

function tr18(count, lid, name)
{
	document.write('<tr><td align=right>', count, '<td><a href="?pname=', name, '">', name, '</a><td><a href="?lid=', lid, '">', lid2a(lid), '</a>');
}

function t18(v)
{
	document.write('<table><tr><th>Count<th align=left>Name<th>Ladder');
	for (var i = 0; i + 3 <= v.length; i += 3)
		tr18(v[i + 0], v[i + 1], v[i + 2]);
	document.write('</table><hr>');
}

document.write('<script type="text/javascript" src="http://m1.nedstatbasic.net/basic.js"></script>');
