<?php
$target_dir = "profile/";
$exists = glob($target_dir. "*");
$no = count($exists);
$file = FALSE;
$user = FALSE;
$file = $exists[array_rand($exists)];
$sepPos = strpos($file, "/");
$sepPos += 1;
$dashpos= strpos($file, "_");
$user = substr($file,$sepPos, $dashpos - $sepPos);
?>


<!DOCTYPE html>
<html lang="en">
    <head>
        <title></title>
    </head>
    <body>
        <p>Random User:</p>
        <img src='<?php echo $file ?>' alt="No user Found" />
        &nbsp; &nbsp; &nbsp;
        &nbsp;<strong><?php if($user){ echo "Username: ". $user; } ?></strong>
        <br /> <br />
        <a href="login.php">Enter a New User and Profile Pic</a>
    </body>
</html>