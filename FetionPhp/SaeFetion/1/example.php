﻿<?php
require 'PHPFetion.php';

$tel=$_REQUEST['tel'];
$pwd=$_REQUEST['pwd'];
$to=$_REQUEST['to'];
$context=$_REQUEST['context'];

$fetion = new PHPFetion($tel, $pwd);	// 手机号、飞信密码
$fetion->send($to, $context);	// 接收人手机号、飞信内容



echo '==========================================';
echo '==========================================';
echo '===========      查看用户信息      =========';
echo '==========================================';
echo '==========================================';
$r=$fetion->GetUserInfoByTel($to);
echo $r;