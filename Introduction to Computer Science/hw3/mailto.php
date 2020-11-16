<?php

$to = $_POST["email"];
$subject = "有收到嗎???";
$message = "有~";
$headers = "From: pinghe.yeh@gmail.com";

mail("$to","$subject","$message","$headers");