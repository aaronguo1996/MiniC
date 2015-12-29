<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>MiniC | Home</title>
    <link rel="stylesheet" href='bootstrap.min.css'/>
    <style type="text/css">
        body {font-family: "Calibri";background: #f2f1eb;  text-align: center;}
        div.head {margin: 18em auto 10em auto;}
        div.img {float:left;margin-left:1em; background-image:url(img/right-red.png);background-size:50px 50px;border-radius:50px;width:50px;height:50px;}
        div.img:hover{border-radius:0;background-image:url(img/right-inverse.png);-webkit-transition:background 0.3s ease;}
        div.button {position:relative;width:150px;height:50px;margin:2em auto 0 auto;
            border-radius:10px;border:1px solid #69c7c7; padding-top:8px;color:#69c7c7;font-size:1.5em;}
        div.button:hover {background:#69c7c7;color:#ffffff;}
        div.submit {float:left;position:relative;width:150px;height:50px;margin:2em auto 0 auto;
            border-radius:10px;border:1px solid #69c7c7; padding-top:8px;color:#69c7c7;font-size:1.5em;}
        div.content {text-align: left; font-size:1.5em;width:80%;margin:2em auto; padding:1em 1em; border:2px solid #69c7c7;}
        div.filename {color:#a75781;font-size:1.5em;margin-top:1em;}
        input.button {position:absolute;opacity:0;top:0;right:0;}
        p {color:#69c7c7;font-family: "微软雅黑 Light";font-weight: 200;font-size:8em; float:left;}
        p.red {color:#a75781;float:left;margin-left:0.5em;}
        p.first {color:#a75781;clear:both; margin-left:3.25em;}
        p.start{font-family:"Calibri";margin-left:18em;clear:both; font-size:2.5em;color:#a75781;}
        label {margin:5em auto 0 auto; font-family: "微软雅黑 Light";text-align: left;font-size:4em;color:#a75781;}
    </style>
</head>
<body>

<div class="input">
    <label for="file">Choose what you want to compile</label>
    <form action="input.php" method="post"
          enctype="multipart/form-data">
        <div class="button">
            <input class="button" type="file" name="file" id="file">Upload File</input>
        </div>
        <div class="filename">
        <?php
            if($_FILES["file"]["name"]!="")
                echo "Uploaded: " . $_FILES["file"]["name"] . "<br />";
        ?>
        </div>
        <div class="button">
            <input class="button" id="submit" type="submit" value="Submit">Check it</input>
        </div>
    </form>
</div>
<div class="content">
    <?php
    if($_FILES["file"]["name"]!="") {
        $flag = false;
        if ($_FILES["file"]["error"] > 0) {
            echo "Error: " . $_FILES["file"]["error"] . "<br />";
        } else {
            $file = fopen($_FILES["file"]["tmp_name"], "r");
            while (!feof($file)) {
                $content = fgets($file);
                if ($flag)
                    echo "\t";
                echo $content;
                echo "<br>";
                if (!strcmp($content[0], '{') || !strcmp($content, " "))
                    $flag = true;
                else
                    $flag = false;
            }
            echo "<br>";
            echo "Type: " . $_FILES["file"]["type"] . "<br />";
            echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
            echo "Stored in: " . $_FILES["file"]["tmp_name"];
            $uploads_dir = "uploads";
            $name = $_FILES["file"]["name"];
            move_uploaded_file($_FILES["file"]["tmp_name"],"$uploads_dir/$name");
        }
        echo "</div><script language='javascript'>
            function jump(){
                window.location = 'upload_file.php?filename=$name';
            }
        </script>
        <div class='button' onclick='jump()'>
                    Confirm
        </div>";
    }
    ?>


</body>
</html>
