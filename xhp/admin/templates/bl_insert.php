<table>
	<form method=post>
		<input type=hidden name=a value="warning">
		<input type=hidden name=pid value="<?php printf("%d", $pid) ?>">
		<tr><td align=right>Name:<td><?php echo $name ?>
		<tr><td align=right>Reason:<td><input type=text name=reason size=60 value="<?php echo htmlspecialchars($reason) ?>">
		<tr><td align=right>Link:<td><input type=text name=link size=60 value="<?php echo htmlspecialchars($link) ?>">
		<tr><td align=right>Duration:<td><input type=text name=dura size=60 value="<?php printf("%d", $dura) ?>"> days
		<tr><td><td><input type=submit></tr>
	</form>
</table>
