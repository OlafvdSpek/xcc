<table>
	<form action="?a=leave" method=post>
		<tr>
			<td align=right>Player name:
			<td><input type=text name=name value="<?php echo(htmlspecialchars($name))?>">
		<tr>
			<td align=right>Player pass:
			<td><input type=password name=pass maxlength=8>
		<tr>
			<td>
			<td><input type=submit value="Leave">
		</tr>
	</form>
</table>
