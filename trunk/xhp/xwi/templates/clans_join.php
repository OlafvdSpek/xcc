<table>
	<form action="?a=join" method=post>
		<tr>
			<td align=right>Name:
			<td><input type=text name=name value="<?php echo(htmlspecialchars($name))?>">
		<tr>
			<td align=right>Pass:
			<td><input type=password name=pass>
		<tr>
			<td align=right>Clan join pass:
			<td><input type=password name=cpass>
		<tr>
			<td>
			<td><input type=submit value="Join">
		</tr>
	</form>
</table>
