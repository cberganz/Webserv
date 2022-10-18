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
					var path = 'http://127.0.0.1:8080/file_to_delete/' 
							+ document.getElementById("select_file").value;
					fetch(path, {
						method: 'DELETE'
						}
					)
					.then((response) => response.json())
					.then((data) => console.log(data));
				}
			</script>
			<div class="wrap">
				<button class="button" name="button" onclick="send_del_req()">Send DELETE request</button>
			</div>
		</div>
	</div>
</body>