<?php
	session_start();
?>
<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="./assets/css/cookies.css">
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css">

		<script src="https://code.jquery.com/jquery-1.10.2.js"></script>

		<?php
				if (isset($_SESSION['theme']) && $_SESSION['theme'] === 'true')
				echo '<link rel="stylesheet" href="assets/css/dark_theme.css">';
				else
				echo '<link rel="stylesheet" href="assets/css/delete_method.css">';
				?>
	</head>
	<body>
		<script>
			function sleep(delay) {
				var start = new Date().getTime();
				while (new Date().getTime() < start + delay);
			}
			function reload_delay() {
				sleep(200)
				document.location.reload(true)
			} 
			window.onload = function() {
				var name = "";
				var first_name = "";
				
				var match = document.cookie.match(new RegExp('(^| )' + 'last_name' + '=([^;]+)'));
				if (match)
				name = match[2];
				match = document.cookie.match(new RegExp('(^| )' + 'first_name' + '=([^;]+)'));
				if (match)
				first_name = match[2];
				
				document.getElementById('last_name').innerHTML = name;
				document.getElementById('first_name').innerHTML = first_name;
			}
			function send_del_req() {
				var url = window.location.href;
				var path = url.substring(0, url.indexOf('/', url.indexOf('://') + 4)) + "/set_cookies"; 
				fetch(path, 
				{
					method: 'POST',
					headers: {'Content-Type': "application/x-www-form-urlencoded"},
					body: document.getElementById('input_last_name').name
					+ '=' + document.getElementById('input_last_name').value
					+ '&' +
					document.getElementById('input_first_name').name
					+ '=' + document.getElementById('input_first_name').value
				})
				.then(reload_delay())
			}
		</script>
		<div id="navbar"></div>
		<script>$(function(){ $("#navbar").load("navbar.html"); });</script>
		<div class="login-box">
			<h2> 👋 Hello <span id="first_name"></span> <span id="last_name"></span></h2>
			<form action="http://127.0.0.1:8080/set_cookies" method="POST">
				<div class="user-box">
					<input id="input_last_name", type="text" name="input_last_name" required="">
					<label>Last Name</label>
				</div>
				<div class="user-box">
					<input id="input_first_name", type="text" name="input_first_name" required="">
					<label>First Name</label>
				</div>
				<a  href="#", id="button_post", onclick='send_del_req()'>
					<span></span>
					<span></span>
					<span></span>
					<span></span>
					Submit
				</a>
			</form>
		</div>
	</body>
</html>
