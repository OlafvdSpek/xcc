<table>
	<form action="?a=edit" method=post>
		<input type=hidden name=cid value=<?php printf($cid) ?>>
		<tr>
			<td align=right>Clan pass:
			<td><input type=password name=pass>
		<tr>
			<td align=right>ICQ:
			<td><input type=text name=icq maxlength=15 value="<?php if ($clan[icq]) echo(htmlspecialchars($clan[icq]))?>">
		<tr>
			<td align=right>Mail:
			<td><input type=text name=mail maxlength=63 value="<?php echo(htmlspecialchars($clan[mail]))?>">
		<tr>
			<td align=right>MSN:
			<td><input type=text name=msn maxlength=63 value="<?php echo(htmlspecialchars($clan[msn]))?>">
		<tr>
			<td align=right>Site:
			<td><input type=text name=site maxlength=127 value="<?php echo(htmlspecialchars($clan[site]))?>">
		<tr>
			<td>
			<td><input type=submit value="Edit">
		</tr>
	</form>
</table>
