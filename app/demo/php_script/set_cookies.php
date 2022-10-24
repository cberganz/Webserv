<!DOCTYPE html>
<?php
	$cookie_name1 = "last_name";
	$cookie_value1 = $_POST['input_last_name'];
	$cookie_name2 = "first_name";
	$cookie_value2 = $_POST['input_first_name'];
	setcookie($cookie_name1, $cookie_value1, time() + (86400 * 30), "/");
	setcookie($cookie_name2, $cookie_value2, time() + (86400 * 30), "/");
?>
<html>    
    <body>
        <h1>Cookies Setted</h1>
    </body>
</html>
