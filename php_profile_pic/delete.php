<?php
session_start();
$new_file = $_SESSION["new"];
$old_file = $_SESSION["old"];
if(isset($_POST["old"])){
    unlink($new_file);
}else if (isset($_POST["new"])){
    unlink($old_file);
}
session_destroy();
header("Location: login.php")
?>
