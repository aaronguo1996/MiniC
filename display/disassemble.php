<html>
<head>
    <title>Assembly Code</title>
    <style type="text/css">
        body{background:#f2f1eb;font-family:"Comic Sans MS";}
        p {font-family:"Adobe 黑体 Std R";font-weight:bolder; font-size:3em; color:#69c7c7;  float:left;}
        p.red {color:#a75781;margin-left:0.3em;}
        div.p {width:100%;top:0;left:0;position:fixed;background:#f2f1eb;}
        div.source {margin-top:10em;margin-left:auto; margin-right:auto;}
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
        table {height:50px;text-align: center;background:#69c7c7;  border-collapse: collapse;   border-radius: 30px; margin-top:3em;margin-left:auto;margin-right:auto; }
        td{min-width:50px; text-align: center; height:50px; padding:0.3em 0.3em;}
        td.head{height:0;font-family:"Adobe 黑体 Std R";font-size:2em;font-weight:bolder; color:#ffffff;background:#a75781;border-radius: 10px 10px 0 0; min-width:650px;padding:0.3em 0;}
        td.little{text-align: left;color:#ffffff;}
        td.inner{border-top:1px solid #a75781;height:0;}
        td.space{min-width:200px;border-radius:0;}
        tr.space{background: #f2f1eb;}
    </style>
    <meta charset="UTF-8"/>
</head>
<body>
<div class="p">
    <p class="red">A</p><p>ssembly </p> <p class="red">C</p><p>ode</p>
</div>
<div class="source">
    <table>
    <?php
    $fp = fopen("disassemble","r");
    $content = "";
    while(!feof($fp)) {
        $content = fgets($fp);
        if($content[0]=='*'){
            echo "</table><table><tr class='space'><td class='space'></td>
                   <td class='head' colspan='10' rowspan='2'>".substr($content,1)."</td>
                   <td class='space'></td></tr><tr><td class='space'></td>
                   <td class='space'></td></tr>";
        }else{
            echo "<tr><td class='space'></td>";
            while($content[0]==' '){
                $content = substr($content,1);
            }
            if(is_numeric($content[0])) {
                /*$data = explode(' ', $content);
                for($i=0;$i<count($data);$i++)
                    if($data[$i]!='')
                        echo "<td>" . $data[$i] . "</td>";*/
                echo "<td colspan='10'>".$content."</td>";
            }elseif(!strcmp($content[0],'[')){
                echo "<td colspan='10' class='little'>" . $content . "</td>";
            }
            else {
                if($data!="") {
                    echo "<td colspan='10' class='little'>" . $content . "</td>";
                    echo "<tr><td colspan='10' class='inner'></td></tr>";
                }
            }
            echo "<td class='space'></td></tr>";
        }
    }
    ?>
    </table>
</div>
</body>
</html>