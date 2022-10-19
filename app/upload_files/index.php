<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
        <link href="https://fonts.googleapis.com/css?family=Droid+Sans:400,700" rel="stylesheet">
        <link rel="stylesheet" href="https://rawgit.com/LeshikJanz/libraries/master/Bootstrap/baguetteBox.min.css">
        <link rel="stylesheet" href="./assets/css/upload_file.css">
          
            <title>Upload files</title>
        </head>
        <body>                                            
        
        <div class="container gallery-container">
        
            <h1>Photo gallery</h1>
        
            <p class="page-description text-center">
                <a href="upload.html"><u>Upload files</u></a>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <a href="delete_files.php"><u>Delete files</u></a>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <a href="file_list.php"><u>File list</u></a>
            </p>
            
            <div class="tz-gallery">
        
                <div class="row">
        
                    <?php 
                    $dirname = "./files/";
                    $images = glob($dirname."*.jpg");
                    
                    foreach($images as $image) {
                        echo "<div class=\"col-sm-12 col-md-4\">";
                        echo '<a class="lightbox" href="'.$image.'">';
                        echo '<img src="'.$image.'">';
                        echo "</a></div>";
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