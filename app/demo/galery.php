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
        
            <h1>Photo gallery</h1>
        
            <div class="tz-gallery">
        
                <div class="row">
        
                    <?php 
                    $dirname = "./files/";
                    $images = glob($dirname."*.jpg");
                    
                    foreach($images as $image) {
                        echo "<div class=\"col-sm-12 col-md-4\">";
                        echo '<a class="lightbox" href="'.$image.'">';
                        echo '<img src="'.$image.'">';
                        echo '</a>';
						echo '</div>';
                    }
                    ?>


                    
                    <!-- <div class="col-sm-6 col-md-4">
                        <a class="lightbox" href="https://raw.githubusercontent.com/LeshikJanz/libraries/master/Related%20images/Bootstrap%20example/coast.jpg">
                            <img src="https://raw.githubusercontent.com/LeshikJanz/libraries/master/Related%20images/Bootstrap%20example/coast.jpg" alt="Rails">
                        </a>
                    </div> -->
        
                </div>
        
            </div>
        
        </div>
        
        <script src="https://cdnjs.cloudflare.com/ajax/libs/baguettebox.js/1.8.1/baguetteBox.min.js"></script>
        <script>
            baguetteBox.run('.tz-gallery');
        </script>
        </body>
        </html>
