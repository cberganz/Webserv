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
			<h1>Upload files</h1>
            <br><br><br><br><br><br><br><br><br><br><br><br><br>
            <form method="post" enctype="multipart/form-data">
                <input type="file" name="file1" multiple>
                <p>Drag your files here or click in this area.</p>
                <br /><br />
                <button type="submit" href="http://127.0.0.1:8080">Submit</button>
            </form>
        </div>
        
        <script src="//cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/baguettebox.js/1.8.1/baguetteBox.min.js"></script>
        <script>
            baguetteBox.run('.tz-gallery');

            $(document).ready(function(){
            $('form input').change(function () {
                $('form p').text(this.files.length + " file(s) selected");
            });
            });
        </script>
        </body>
        </html>
