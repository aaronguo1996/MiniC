<html>
<head>
    <title>Assembly Code</title>
    <style type="text/css">
        body{background:#f2f1eb;font-family:"Calibri";}
        p {font-family:"微软雅黑 Light";}
        p.green {font-weight:bolder; font-size:3em; color:#69c7c7;  float:left;}
        p.red {color:#a75781;margin-left:0.3em;float:left;font-size:3em;font-weight:bolder;}
        p.header {color:#a75781;font-size:2em;margin-left:2em;clear:both;padding:0 0;font-weight: normal;}
        p.content {color:#69c7c7;font-size:1.5em;clear:both;margin:0 0 0 3em;padding:0 0;font-weight: normal;max-height:20px;}
        div.p {width:100%;top:0;left:0;position:fixed;background:#f2f1eb;}
        div.source {margin-top:10em;margin-left:auto; margin-right:auto;margin-bottom:225px;}
        /*div.code:hover {background: #0f6499;}*/
        div.code {text-align:center; max-width:10em;  min-height: 2em;font-family:"Calibri";
            font-size:1em;background:#69c7c7;transition:background 0.3s ease;
            color:#ffffff; margin:5px 5px 5px 5px; border-radius:10px;padding:0.6em 1em 0.3em 1em;}
        /*div.desc:hover {background: #a98955;}*/
        div.desc {text-align:center; max-width:10em;  min-height: 2em;font-family:"微软雅黑 Light";clear: both;
            font-size:1em;background:#a75781;transition:background 0.3s ease;
            color:#ffffff; margin:5px 5px 5px 5px; border-radius:10px;padding:0.6em 1em 0.3em 1em;}
        div.line {clear:both;float:left;}
        div.single {float:left;}
        div.button {position:relative;width:150px;height:50px;margin:2em 2em 0 auto;text-align: center;float:left;
            border-radius:10px;border:1px solid #69c7c7; padding-top:0.8em;color:#69c7c7;font-size:1.5em;}
        div.left {position:relative;width:150px;height:50px;margin:2em 2em 0 27.5em;text-align: center;float:left;
            border-radius:10px;border:1px solid #69c7c7; padding-top:0.8em;color:#69c7c7;font-size:1.5em;}
        div.left:hover,div.button:hover {background:#69c7c7;color:#ffffff;}
        div.part {position:relative; display: inline;color:#a75781;font-size:2em;padding:0.5em 1em;min-height:50px;}
        div.part:hover {background:#a75781;color:#ffffff;}
        footer {position:fixed;top:775px;left:0;width:100%;background:#69c7c7;min-height:150px;padding:1em 0.5em;text-align: center;}
        table {height:50px;text-align: center;border:2px solid #a75781; border-collapse: collapse;   border-radius: 30px; margin-top:3em;margin-left:auto;margin-right:auto; }
        td{min-width:50px; text-align: center; height:50px; padding:0.3em 0.3em;font-size:1.5em;border:2px solid #a75781;}
        td.head{height:0;text-align:center; font-family: "微软雅黑 Light";font-size:2em;font-weight:bolder; color:#69c7c7;border-radius: 10px 10px 0 0; min-width:650px;padding:0.3em 0;}
        td.little{text-align: left;color:#69c7c7;}
        td.space{min-width:200px;border-radius:0;}
        tr.space{background: #f2f1eb;}
    </style>
    <meta charset="UTF-8"/>
</head>
<body>
<script language="JavaScript" src="jump.js"></script>
<div class="p">
    <div><p id="A" class="red">R</p><p id="ssembly"class="green">unning </p> <p id="C" class="red">R</p><p id="ode" class="green">esult</p></div>
    <div class="left" onclick="jumpInput()">Clear All</div>
    <div class="button right" onclick="jumpIndex()">Exit</div>
</div>
<div class="source">
    <?php
        error_reporting(0);
        $fp = fopen("result","r");
    //echo $fp;
        if($fp != false){
            echo "<p class='header'>The output of the program is...</p>";
            while(!feof($fp)){
                $content = fgets($fp);
                echo "<p class='content'>".$content."</p>";
                echo "<br>";
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