<table>
	<form action="players.php">
		<input type=hidden name=a value=chat>
		<tr><td>Chat:<td><input type=text name=pname value="<?=$_REQUEST['pname']?>"> <input type=submit value="Search"></tr>
	</form>
	<form action="players.php">
		<input type=hidden name=a value=games>
		<tr><td>Games:<td><input type=text name=pname value="<?=$_REQUEST['pname']?>"> <input type=submit value="Search"></tr>
	</form>
	<form action="logins.php">
		<tr><td>Logins:<td><input type=text name=pname value="<?=$_REQUEST['pname']?>"> <input type=submit value="Search"></tr>
	</form>
	<form action="players.php">
		<tr><td>Players:<td><input type=text name=pname value="<?=$_REQUEST['pname']?>"> <input type=submit value="Search"></tr>
	</form>
</table>
