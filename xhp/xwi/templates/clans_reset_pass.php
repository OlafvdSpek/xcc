<table>
	<form action="?a=reset_pass" method=post>
		<tr>
			<td align=right>Clan name:
			<td><input type=text name=cname maxlength=6 value="<?php echo(htmlspecialchars($cname))?>">
		<tr>
			<td align=right>Email:
			<td><input type=text name=mail maxlength=63 value="<?php echo(htmlspecialchars($mail))?>">
		<tr>
			<td>
			<td><input type=submit value="Reset pass">
		</tr>
	</form>
</table>
