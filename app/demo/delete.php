<?php
	session_start();
?>
<head>
	<title>Webserv</title>
	<meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
	<?php
		if ($_SESSION['theme'] == 'true')
			echo '<link rel="stylesheet" href="assets/css/dark_theme.css">';
		else
			echo '<link rel="stylesheet" href="assets/css/delete_method.css">';
	?>
	<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css">
	<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
</head>
<body>
	<div id="navbar"></div>
	<script>$(function(){ $("#navbar").load("navbar.html"); });</script>
	<div class="container">
		<div>
			<h2 style="color:white;text-align: center;">DELETE METHOD !</h2>
			<div class="select">
				<select id="select_file">
					<?php
						if ($handle = opendir('./file_to_delete')) {
							while (false !== ($entry = readdir($handle))) {
						
								if ($entry != "." && $entry != "..") {
									echo "<option value=\"$entry\">$entry</option>\n";
								}
							}
							closedir($handle);
						}
					?>
				</select>
			</div>
			<script>
				function send_del_req() {
					//get ip et port value
					var path = 'http://127.0.0.1:8080/file_to_delete/' 
							+ document.getElementById("select_file").value;
					fetch(path, {
						method: 'DELETE'
						}
					)
					.then((response) => response.json())
					.then((data) => console.log(data));
					// window.location.reload()
				}
			</script>
			<div class="wrap">
				<button class="button" name="button" onclick="send_del_req()">Send DELETE request</button>
			</div>
		</div>
	</div>
</body>
