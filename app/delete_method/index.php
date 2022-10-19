<head>
	<link rel="stylesheet" href="./assets/css/delete_method.css">
</head>
<body>
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
					var url = window.location.href;
					var path = url.substring(0, url.indexof('/', url.indexOf('://') + 4)) + "/file_to_delete/"; 
					console.log(path)
					// 		+ document.getElementById("select_file").value;
					// fetch(path, {
					// 	method: 'DELETE'
					// 	}
					// )
					// .then((response) => response.json())
					// .then((data) => console.log(data));
					// // window.location.reload()
				}
			</script>
			<div class="wrap">
				<button class="button" name="button" onclick="send_del_req()">Send DELETE request</button>
			</div>
		</div>
	</div>
</body>
