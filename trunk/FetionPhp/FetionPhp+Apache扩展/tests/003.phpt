--TEST--
test fx_init and fx_terminate
--SKIPIF--
<?php if (!extension_loaded("libfetion")) print "skip"; ?>
--FILE--
<?php 
assert(fx_init());
fx_terminate();
?>
==DONE==
--EXPECT--
==DONE==
