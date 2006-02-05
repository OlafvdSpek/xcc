<table>
	<form action="?a=edit_warning_submit" method=post>
		<input type=hidden name=wid value=<?=$wid?>>
		<tr><th align=right>WID<td><?=$wid?>
		<tr><th align=right>SID<td><a href="?sid=<?=$sid?>"><?=$sid?></a>
		<tr><th align=right>Player<td><a href="?pname=<?=$name?>"><?=$name?></a>
		<tr><th align=right>Link<td><input type=text name=link size=60 value="<?=$link?>">
		<tr><th align=right>Duration<td><input type=text name=duration size=60 value="<?=$duration?>">
		<tr><th align=right>Reason<td><input type=text name=reason size=60 value="<?=$reason?>">
		<tr><th align=right>Message<td><textarea name=motd cols=80 rows=10><?=$motd?></textarea>
		<tr><th align=right>Creator<td><?=$creator?>
		<tr><th align=right>Modified<td><?=$mtime?>
		<tr><th align=right>Created<td><?=$ctime?>
		<tr><th align=right><td><input type=submit value="Update"></tr>
	</form>
</table>
