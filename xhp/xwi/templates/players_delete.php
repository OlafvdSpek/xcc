<table>
	<form action="?a=delete_nick" method=post>
		<tr>
			<td align=right>Name:
			<td><input type=text name=name value="<?php echo(htmlspecialchars($name))?>">
		<tr>
			<td align=right>Pass:
			<td><input type=password name=pass>
		<tr>
			<td>
			<td><input type=submit value="Delete">
		</tr>
	</form>
</table>
