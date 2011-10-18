--TEST--
Check for libfetion constants
--SKIPIF--
<?php if (!extension_loaded("libfetion")) print "skip"; ?>
--FILE--
<?php 
echo FX_EVENT_BASE ."\n";
echo FX_LOGIN_CONNECTING;
?>
--EXPECT--
0
1
