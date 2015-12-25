<html>
<head>
    <title>Token Stream</title>
    <style type="text/css">
        body{background:#f2f1eb;}
        p {font-family:"Adobe 黑体 Std R";font-weight:bolder; font-size:3em; color:#69c7c7;  float:left;}
        p.red {color:#a75781;margin-left:0.3em;}
        div.p {width:100%;top:0;left:0;position:fixed;background:#f2f1eb;}
        div.source {margin-top:10em;}
        /*div.code:hover {background: #0f6499;}*/
        div.code {text-align:center; max-width:10em;  min-height: 2em;font-family:"Comic Sans MS";
            font-size:1em;background:#69c7c7;transition:background 0.3s ease;
            color:#ffffff; margin:5px 5px 5px 5px; border-radius:10px;padding:0.6em 1em 0.3em 1em;}
        /*div.desc:hover {background: #a98955;}*/
        div.desc {text-align:center; max-width:10em;  min-height: 2em;font-family:"Comic Sans MS";
            font-size:1em;background:#a75781;transition:background 0.3s ease;
            color:#ffffff; margin:5px 5px 5px 5px; border-radius:10px;padding:0.6em 1em 0.3em 1em;}
        div.line {clear:both;float:left;}
        div.single {float:left;}
    </style>
    <meta charset="UTF-8"/>
</head>
<body>
<div class="p">
<p class="red">T</p><p>oken </p> <p class="red">S</p><p>tream</p>
</div>
<div class="source">
<?php
$fp = fopen("lex","r");
$content = "";
while(!feof($fp)){
    $content = fgets($fp);
}
$tuple = explode("\t",$content);
$flag = true;
for($index = 0;$index < count($tuple);$index++){
    $code = explode(' ',$tuple[$index]);
    if($flag){
        echo "<div class='line'><div class='code'>" . $code[0] . "</div>";
        echo "<div class='desc'>" . $code[1] . "</div></div>";
    }else {
        echo "<div class='single'><div class='code'>" . $code[0] . "</div>";
        echo "<div class='desc'>" . $code[1] . "</div></div>";
    }
    if(!strcmp($code[1],"NEW_LINE")) {
        $flag = true;
    }else{
        $flag = false;
    }
}
?>
</div>
</body>
</html>