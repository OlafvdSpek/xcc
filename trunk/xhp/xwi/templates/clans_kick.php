<table>
	<form action="?a=kick" method=post>
		<tr>
			<td align=right>Player name:
			<td><input type=text name=name value="<?php echo(htmlspecialchars($name))?>">
		<tr>
			<td align=right>Clan admin pass:
			<td><input type=password name=pass>
		<tr>
			<td>
			<td><input type=submit value="Kick">
		</tr>
	</form>
</table>
