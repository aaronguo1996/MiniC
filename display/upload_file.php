<?php
unset($arr);
$filename = $_SERVER['QUERY_STRING'];
$filename = explode("=",$filename);
exec("del error.info");
exec("minic uploads/".$filename[1],$arr,$var);
$fp = fopen("result","w+");
$i=0;
for($i=0;$i<count($arr);$i++){
    fprintf($fp,"%s\n",$arr[$i]);
}
fclose($fp);
header("Location: lex.php");
?>