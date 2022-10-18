<!-- Head -->
<head>

	<title>Webserv</title>
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">

	<!-- Stylesheet -->
	<link rel="stylesheet" href="assets/css/bootstrap.min.css" />
	<link rel="stylesheet" href="assets/css/delete_method.css">
	<link rel="stylesheet" href="assets/css/main.css" />

	<!-- Scripts -->
	<script src="assets/js/bootstrap.bundle.min.js"></script>

</head>

<!-- Body -->
<body>

	<!-- Navbar -->
	<nav class="navbar navbar-expand-lg navbar-light bg-light fixed-top">
	  <div class="container">
	    <a class="navbar-brand" href="/">Webserv-42</a>
	    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
	      <span class="navbar-toggler-icon"></span>
	    </button>
	    <div class="collapse navbar-collapse" id="navbarResponsive">
	      <ul class="navbar-nav ms-auto">
	        <li class="nav-item active">
	          <a class="nav-link" href="#">Get</a>
	        </li>
	        <li class="nav-item">
	          <a class="nav-link" href="#">Post</a>
	        </li>
	        <li class="nav-item">
	          <a class="nav-link" href="/delete.php">Delete</a>
	        </li>
	        <li class="nav-item">
	          <a class="nav-link" href="#">Session</a>
	        </li>
	      </ul>
	    </div>
	  </div>
	</nav>

	<!-- Delete page -->
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
