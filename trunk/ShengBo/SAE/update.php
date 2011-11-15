<?php 
require_once('saes3.ex.class.php');//for sina s3
$s = new SaeS3();
$url;
if ($_FILES['file']['size'] > 0) { //注意，SAE runtime 存在 10MB 的限额
	$url=$s->upload('test', $_FILES['file']['name'], $_FILES['file']['tmp_name']);
}else{
	
}
$des=$_POST['des'];
$pwd=$_POST['pwd'];
$isPwd=$_POST['isPwd'];
$mysql = new SaeMysql();
$sql = "INSERT INTO `app_shengbo`.`shengbo_voice` (`vID`, `vDescription`, `vPass`, `vUrl`, `vIsPass`) VALUES (NULL, '$des', '$pwd', '$url', '$isPwd');";
$mysql->runSql( $sql );
?>