<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>jOrgChart</title>
    <link rel="stylesheet" href='bootstrap.min.css'/>
    <link rel="stylesheet" href='jquery.jOrgChart.css'/>
</head>

<body>
<?php
    $myfile = fopen("test.txt", "r") or die("Unable to open file!");
    echo fread($myfile, filesize("test.txt"));
    fclose($myfile);
?>
</body>
</html>