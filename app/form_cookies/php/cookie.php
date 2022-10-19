<!DOCTYPE html>
<?php
	// $cookie_name = "first_name";
	// $cookie_value = $_POST['input_last_name'];
	function detectRequestBody() {
		$rawInput = fopen('php://input', 'r');
		$tempStream = fopen('php://temp', 'r+');
		stream_copy_to_stream($rawInput, $tempStream);
		rewind($tempStream);
	
		return $tempStream;
	}
	$i = 0;
	echo getenv("SCRIPT_NAME");
	echo "\nfile content: ";
	echo detectRequestBody();
	// var_dump($HTTP_RAW_POST_DATA);

	while ($i < count($_POST))
	{
		echo "$_POST[$i]\n";
	}
	// setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day
?>
<!-- <html>    
    <body>
        <h1>Cookies Setted</h1>
    </body>
</html> -->
