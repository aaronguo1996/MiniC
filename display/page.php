<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Parsing Tree</title>
    <link rel="stylesheet" href='bootstrap.min.css'/>
    <link rel="stylesheet" href='jquery.jOrgChart.css'/>
    <style type="text/css">
        p {font-family:"微软雅黑 Light";font-weight:bolder; font-size:3em; color:#69c7c7;  float:left;}
        p.red {color:#a75781;margin-left:0.3em;}
        div.p {width:100%;top:0;left:0;position:fixed;background:#f2f1eb;}
        div.source {margin-top:10em;float:left;margin-bottom:225px;}
        div.button {position:relative;width:150px;height:50px;margin:1em 2em 0 auto;text-align: center;float:left;
            border-radius:10px;border:1px solid #69c7c7; padding-top:0.5em;color:#69c7c7;font-size:1.5em;}
        div.left {position:relative;width:150px;height:50px;margin:1em 2em 0 37.5em;text-align: center;float:left;
            border-radius:10px;border:1px solid #69c7c7; padding-top:0.5em;color:#69c7c7;font-size:1.5em;}
        div.left:hover,div.button:hover {background:#69c7c7;color:#ffffff;}
        div#jOrgChart {margin-bottom:225px;}
        div.part {position:relative; display: inline;color:#a75781;font-size:2em;padding:0.5em 1em;min-height:50px;}
        div.part:hover {background:#a75781;color:#ffffff;}
        footer {position:fixed;top:775px;left:0;width:100%;background:#69c7c7;min-height:150px;padding:1em 0.5em;text-align: center;}
    </style>
</head>
<body>
<!--显示组织架构图-->
<div class="source">
<div class="p">
    <p class="red">P</p><p>arsing </p> <p class="red">T</p><p>ree</p>
    <div class="left" onclick="jumpInput()">Clear All</div>
    <div class="button right" onclick="jumpIndex()">Exit</div>
</div>

<div id='jOrgChart'>
</div>
</div>
<script type='text/javascript' src='jquery-2.1.4.js'></script>
<script type='text/javascript' src='jquery.jOrgChart.js'></script>
<script language="javascript" src="jump.js"></script>
<script type='text/javascript'>
    $(function(){
        //数据返回
        $.ajax({
            url: "back.php",
            type: 'POST',
            dataType: 'JSON',
            data: {action: 'org_select'},
            success: function(result){
                var showlist = $("<ul id='org' style='display:none'></ul>");
                showall(result, showlist);
                $("#jOrgChart").append(showlist);
                $("#org").jOrgChart( {
                    chartElement : '#jOrgChart',//指定在某个dom生成jorgchart
                    dragAndDrop : false //设置是否可拖动
                });
            }
        });
    });

    //menu_list为json数据
    //parent为要组合成html的容器

    function showall(menu_list, parent) {
        $.each(menu_list, function(index, val) {
            if(val.childrens.length > 0){

                var li = $("<li></li>");

                li.append("<a href='javascript:void(0)' onclick=getOrgId("+val.id+");>"+val.name+"</a>").append("<ul></ul>").appendTo(parent);
                //递归显示
                showall(val.childrens, $(li).children().eq(1));
            }else{
                $("<li></li>").append("<a href='javascript:void(0)' onclick=getOrgId("+val.id+");>"+val.name+"</a>").appendTo(parent);
            }
        });

    }

</script>
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