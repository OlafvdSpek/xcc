<table>
	<form method=get>
		<input type=hidden name=a value="motd_submit">
		<input type=hidden name=pid value="<?php printf("%d", $pid) ?>">
		<tr><td align=right>Name:<td><a href="?pid=<?php echo $pid ?>"><?php echo $name ?></a>
		<tr><td align=right>Message:<td><textarea name=motd cols=80 rows=10><?php echo htmlspecialchars($motd) ?></textarea>
		<tr><td><td><input type=submit></tr>
	</form>
</table>
