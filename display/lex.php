
<html>
<head>
    <title>Token Stream</title>
    <style type="text/css">
        body{background:#f2f1eb;font-family:"Calibri";}
        p {font-family:"微软雅黑 Light";font-weight:bolder; font-size:3em; color:#69c7c7;  float:left;}
        p.red {color:#a75781;margin-left:0.3em;}
        div.p {width:100%;top:0;left:0;position:fixed;background:#f2f1eb;}
        div.source {margin-top:10em;width:70%;float:left;margin-left:12.5em;margin-bottom:225px;}
        /*div.code:hover {background: #0f6499;}*/
        div.code {text-align:center; max-width:10em;  min-height: 2em;font-family:"Calibri";
            font-size:1em;background:#69c7c7;transition:background 0.3s ease;
            color:#ffffff; margin:5px 5px 5px 5px; border-radius:10px;padding:1em 1em 0.3em 1em;}
        /*div.desc:hover {background: #a98955;}*/
        div.desc {text-align:center; max-width:10em;  min-height: 2em;font-family:"Calibri";
            font-size:1em;background:#a75781;transition:background 0.3s ease;
            color:#ffffff; margin:5px 5px 5px 5px; border-radius:10px;padding:1em 1em 0.3em 1em;}
        div.line {clear:both;float:left;}
        div.single {float:left;}
        div.right {position:fixed;margin-left:77.5em; margin-top:10em;padding-top:10em; width:10%;height:100%;
            float:left;vertical-align: middle;background-image:url(img/turnright-red.png);
            background-repeat:no-repeat; background-position-y:10em;}
        div.right:hover{background-image:url(img/turnright-green.png);}
        div.left{position:fixed;margin-top:10em; padding-top:10em;width:10%;height:100%;float:left;vertical-align: middle;
            background-image:url(img/turnleft-green.png); background-repeat:no-repeat; background-position-y:10em;}
        div.left:hover{background-image:url(img/turnleft-red.png);}
        div.part {position:relative; display: inline;color:#a75781;font-size:2em;padding:0.5em 1em;min-height:50px;}
        div.part:hover {background:#a75781;color:#ffffff;}
        div.button {position:relative;width:150px;height:50px;margin:2em 2em 0 auto;text-align: center;float:left;
            border-radius:10px;border:1px solid #69c7c7; padding-top:0.8em;color:#69c7c7;font-size:1.5em;}
        div.left {position:relative;width:150px;height:50px;margin:2em 2em 0 27.5em;text-align: center;float:left;
            border-radius:10px;border:1px solid #69c7c7; padding-top:0.8em;color:#69c7c7;font-size:1.5em;}
        div.left:hover,div.button:hover {background:#69c7c7;color:#ffffff;}
        footer {position:fixed;top:775px;left:0;width:100%;background:#69c7c7;min-height:150px;padding:1em 0.5em;text-align: center;}
    </style>
    <meta charset="UTF-8"/>
</head>
<body>
<script language="javascript" src="jump.js"></script>
<div class="source">
    <div class="p">
        <p class="red">T</p><p>oken </p> <p class="red">S</p><p>tream</p>
        <div class="left" onclick="jumpInput()">Clear All</div>
        <div class="button right" onclick="jumpIndex()">Exit</div>
    </div>

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
<footer>
    <div class="part" onclick="jumpLex()">
        Lexical Analysis
    </div>
    <div class="part" onclick="jumpSyn()">
        Syntax Analysis
    </div>
    <div class="part" onclick="jumpCode()">
        Code Generation
    </div>
    <div class="part" onclick="jumpResult()">
        Running Result
    </div>
</footer>
</body>
</html>