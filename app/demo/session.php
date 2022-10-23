<?php
	session_start();
	if(!empty($_POST))
	{
		if (isset($_POST['logname']))
			$_SESSION['logname'] = $_POST['logname'];
		if (isset($_POST['logemail']))
			$_SESSION['logemail'] = $_POST['logemail'];
		if (isset($_POST['theme']))
			$_SESSION['theme'] = $_POST['theme'];
	}
?>
<!DOCTYPE html>
<html>
	<head>
		<title>Webserv</title>
		<meta charset="utf-8">
	    <meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css">
		<link rel="stylesheet" href="https://unicons.iconscout.com/release/v2.1.9/css/unicons.css">
		<link rel="stylesheet" href="assets/css/session.css">
		<?php
			if (isset($_SESSION['theme']) && $_SESSION['theme'] === 'true')
				echo '<link rel="stylesheet" href="assets/css/dark_theme.css">';
			else
				echo '<link rel="stylesheet" href="assets/css/delete_method.css">';
		?>
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
		<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
	</head>
	<body>
		<div id="navbar"></div>
		<script>$(function(){ $("#navbar").load("navbar.html"); });</script>
		<div class="section">
			<div class="container">
				<div class="row full-height justify-content-center">
					<div class="col-12 text-center align-self-center py-5">
						<div class="section pb-5 pt-5 pt-sm-2 text-center">
							<div class="card-3d-wrap mx-auto">
								<div class="card-3d-wrapper">
									<div class="card-front">
										<div class="center-wrap">
											<div class="section text-center">
												<?php
													if (!isset($_SESSION['logname']))
													{
														echo '<h4 class="mb-4 pb-3">Subscribe to our pictures newsletter</h4>
														 <div class="form-group">
														 	<input type="text" name="logname" class="form-style" placeholder="Your Full Name" id="logname" autocomplete="off">
														 	<i class="input-icon uil uil-user"></i>
														 </div>
														 <div class="form-group mt-2">
														 	<input type="email" name="logemail" class="form-style" placeholder="Your Email" id="logemail" autocomplete="off">
														 	<i class="input-icon uil uil-at"></i>
														 </div>
														 <a href="#", class="btn mt-4", onclick="send_form()">Subscribe</a>';
													}
													if (isset($_SESSION['logname']))
													{
														echo '<h4 class="mb-4 pb-3">Preferences for ' . $_SESSION['logname'] . '</h4>';
														echo '<br><br>';
														echo '<h4 class="mb-0 pb-3">Theme</h4>';
														echo '<h6 class="mb-0 pb-3"><span>Light </span><span>Dark</span></h6>';
														if (isset($_SESSION['theme']) and $_SESSION["theme"] == "true")
										   		          	 echo '<input class="checkbox" type="checkbox" id="reg-log" name="reg-log" checked="checked"/>';
														else
										   		          	 echo '<input class="checkbox" type="checkbox" id="reg-log" name="reg-log" />';
														echo '<label for="reg-log"></label>';
														echo '<br>';
														echo '<a href="#", class="btn mt-4", onclick="send_pref()">Save</a>';
													}
												?>
					    					</div>
				      					</div>
				      				</div>
				      			</div>
				      		</div>
				      	</div>
			      	</div>
		      	</div>
		    </div>
		</div>
		<script>
			function send_form() {
				var path = 'http://127.0.0.1:8080/session.php' 
				fetch(path, {
					method: 'POST',
					headers: {'Content-Type': "application/x-www-form-urlencoded"},
					body: 'logname=' + document.getElementById('logname').value
						  + '&logemail=' + document.getElementById('logemail').value
				})
				.then(reload_delay())
			}
			function send_pref() {
				var path = 'http://127.0.0.1:8080/session.php' 
				fetch(path, {
					method: 'POST',
					headers: {'Content-Type': "application/x-www-form-urlencoded"},
					body: 'theme=' + document.getElementById('reg-log').checked
				})
				.then(reload_delay())
			}
			function sleep(delay) {
				var start = new Date().getTime();
				while (new Date().getTime() < start + delay);
			}
			function reload_delay() {
				sleep(200)
				document.location.reload(true)
			} 
		</script>
	</body>
</html>
