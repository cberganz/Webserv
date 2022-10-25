<?php
	session_start();
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css">
        <link href="https://fonts.googleapis.com/css?family=Droid+Sans:400,700" rel="stylesheet">
        <link rel="stylesheet" href="https://rawgit.com/LeshikJanz/libraries/master/Bootstrap/baguetteBox.min.css">
        <link rel="stylesheet" href="./assets/css/upload_file.css">
        <link rel="stylesheet" href="./assets/css/form.css">
		<?php
			if (isset($_SESSION['theme']) && $_SESSION['theme'] === 'true')
				echo '<link rel="stylesheet" href="assets/css/dark_theme.css">';
			else
				echo '<link rel="stylesheet" href="assets/css/delete_method.css">';
		?>
		<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
          
            <title>Upload files</title>
        </head>
        <body>                                            

		<div id="navbar"></div>
		<script>$(function(){ $("#navbar").load("navbar.html"); });</script>
        
        <div class="container gallery-container">
			<h1>Delete files</h1>
            <div>
                <p style="text-align:center">Select file to delete:</p>
				<div style="text-align:center">
					<select id="select_file">
						<?php
							if ($handle = opendir('./files')) {
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
                <div class="wrap">
                    <button class="button" name="button" onclick="send_del_req()">Delete</button>
                </div>
            </div>

        </div>        
		<script>
			function sleep(delay) {
				var start = new Date().getTime();
				while (new Date().getTime() < start + delay);
			}
			function send_del_req() {
				var url = window.location.href;
				var path = url.substring(0, url.indexOf('/', url.indexOf('://') + 4)) + "/files/" 
						+ document.getElementById("select_file").value;
				fetch(path, {
					method: 'DELETE'
					}
				)
				.then((response) => response.json())
				.then(file_deleted())
			}
			function file_deleted() {
				sleep(200)
				document.location.reload(true)
			}
		</script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/baguettebox.js/1.8.1/baguetteBox.min.js"></script>

        </body>
        </html>
