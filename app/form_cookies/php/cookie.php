<!DOCTYPE html>
<?php
	$cookie_name = "first_name";
	$cookie_value = "Robin";
	setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day
?>
<!-- <html>    
    <body>
        <h1>Cookies Setted</h1>
    </body>
</html> -->
