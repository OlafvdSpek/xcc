<table>
	<form action="?a=join" method=post>
		<tr>
			<td align=right>Player name:
			<td><input type=text name=name value="<?php echo(htmlspecialchars($name))?>">
		<tr>
			<td align=right>Player pass:
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
