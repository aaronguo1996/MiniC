<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>MiniC | Home</title>
    <link rel="stylesheet" href='bootstrap.min.css'/>
    <style type="text/css">
        body {background: #f2f1eb; text-align:center;}
        div.head {margin: 18em auto 10em auto;}
        div.img {float:left;margin-left:1em; background-image:url(img/right-red.png);background-size:50px 50px;border-radius:50px;width:50px;height:50px;}
        div.img:hover{border-radius:0;background-image:url(img/right-inverse.png);-webkit-transition:background 0.3s ease;}
        p {color:#69c7c7;font-family: "微软雅黑 Light";font-weight: 200;font-size:8em; float:left;}
        p.red {color:#a75781;float:left;margin-left:0.5em;}
        p.first {color:#a75781;clear:both; margin-left:3.25em;}
        p.start{font-family:"Calibri";margin-left:18em;clear:both; font-size:2.5em;color:#a75781;}
    </style>
</head>
<body>
    <div class="head">
        <p class="first">M</p><p>iniC</p> <p class="red">C</p><p>ompiler</p>
        <div>
            <p class="start">Start</p>
            <script language="javascript">
                function jump(){
                    window.location = "input.php";
                }
            </script>
            <div class="img" onclick="jump()"></div>
        </div>
    </div>
<?php
/**
 * Created by PhpStorm.
 * User: Aaron
 * Date: 2015/12/25
 * Time: 20:00
 */?>
</body>
</html>
