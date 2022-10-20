<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
        <link href="https://fonts.googleapis.com/css?family=Droid+Sans:400,700" rel="stylesheet">
        <link rel="stylesheet" href="https://rawgit.com/LeshikJanz/libraries/master/Bootstrap/baguetteBox.min.css">
        <link rel="stylesheet" href="./assets/css/upload_file.css">
        <link rel="stylesheet" href="./assets/css/form.css">
          
            <title>Upload files</title>
        </head>
        <body>                                            
        
        <div class="container gallery-container">
        
            <h1>Delete files</h1>
        
            <p class="page-description text-center">
                <a href="index.php"><u>Photo gallery</u></a>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <a href="upload.html"><u>Upload files</u></a>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <a href="file_list.php"><u>File list</u></a>
            </p>
            
            <div style="align:center;">
                <br>
                <p>Select file to delete:</p>
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
                <script>
                    function sleep(delay) {
                        var start = new Date().getTime();
                        while (new Date().getTime() < start + delay);
                    }
                    function send_del_req() {
                        //get ip et port value
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
                        sleep(3)
                        document.location.reload(true)
                    }
                </script>
                <div class="wrap">
                <br>
                    <button class="button" name="button" onclick="send_del_req()">Delete</button>
                </div>
            </div>

        </div>
        
        <script src="https://cdnjs.cloudflare.com/ajax/libs/baguettebox.js/1.8.1/baguetteBox.min.js"></script>

        </body>
        </html>