<table>
	<form action="?a=create" method=post>
		<tr>
			<td align=right>Player name:
			<td><input type=text name=name value="<?php echo(htmlspecialchars($name))?>">
		<tr>
			<td align=right>Player pass:
			<td><input type=password name=pass maxlength=8>
		<tr>
			<td align=right>Clan name:
			<td><input type=text name=cname maxlength=6 value="<?php echo(htmlspecialchars($cname))?>">
		<tr>
			<td align=right>ICQ:
			<td><input type=text name=icq maxlength=15 value="<?php echo(htmlspecialchars($icq))?>">
		<tr>
			<td align=right>Mail:
			<td><input type=text name=mail maxlength=63 value="<?php echo(htmlspecialchars($mail))?>">
		<tr>
			<td align=right>MSN:
			<td><input type=text name=msn maxlength=63 value="<?php echo(htmlspecialchars($msn))?>">
		<tr>
			<td align=right>Site:
			<td><input type=text name=site maxlength=127 value="<?php echo(htmlspecialchars($site))?>">
		<tr>
			<td>
			<td><input type=submit value="Create">
		</tr>
	</form>
</table>
