<table>
	<form action="?a=create" method=post>
		<tr>
			<td align=right>Player name:
			<td><input type=text name=name size=30 value="<?=htmlspecialchars($name)?>">
		<tr>
			<td align=right>Player pass:
			<td><input type=password name=pass maxlength=8 size=30>
		<tr>
			<td align=right>Clan abbreviation:
			<td><input type=text name=cabbrev maxlength=6 size=30 value="<?=htmlspecialchars($cabbrev)?>">
		<tr>
			<td align=right>Clan name:
			<td><input type=text name=cname maxlength=32 size=30 value="<?=htmlspecialchars($cname)?>">
		<tr>
			<td align=right>ICQ:
			<td><input type=text name=icq maxlength=15 size=30 value="<?=htmlspecialchars($icq)?>">
		<tr>
			<td align=right>Email:
			<td><input type=text name=mail maxlength=63 size=30 value="<?=htmlspecialchars($mail)?>">
		<tr>
			<td align=right>MSN:
			<td><input type=text name=msn maxlength=63 size=30 value="<?=htmlspecialchars($msn)?>">
		<tr>
			<td align=right>Site:
			<td><input type=text name=site maxlength=127 size=30 value="<?=htmlspecialchars($site)?>">
		<tr>
			<td>
			<td><input type=submit value="Create">
		</tr>
	</form>
</table>
