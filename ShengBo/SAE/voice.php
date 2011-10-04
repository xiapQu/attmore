<?php
$f=$_GET['file'];
$filename="http://test.shengbo.s3.sinaapp.com/".$f;
$mysql = new SaeMysql();
$sql = "SELECT vDescription
FROM  `shengbo_voice` 
WHERE vUrl LIKE  '%".$f."'";
$des=$mysql->getVar($sql);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>收听微博</title>
<link href="css.css" rel="stylesheet" type="text/css" />

</head>

<body>
<div class="tape">
    <div class="text">
       <?=$des?>
    </div>
    <div class="player"><embed autostart="true" loop="-1" width="320px" height="25px" controls="ControlPanel" src="<?=$filename?>";></div>
</div>

</body>
</html>