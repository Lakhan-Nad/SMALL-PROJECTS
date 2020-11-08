<?php
 function post(){
   $user = $_POST["user"];
   if(strpos($user, "_")){
     echo "Underscore(_) not allowed in username";
     return;
   }
   global $target_dir;
   $target_dir = "profile/";
   $target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
   $uploadOk = 1;
   $imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
   $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
   if($check !== false) {
     $uploadOk = 1;
   } else {
     $uploadOk = 0;
   }
   if($uploadOk == 1){
   $exists = glob($target_dir.$user."_*");
   // Check if file already exists
   global $new_file;
   global $old_file;
   $target_file = $target_dir . $user . "_" .date("Y-m-d") . "_". date("h:i:sa").".".$imageFileType;
   $new_file = $target_file;
   if (!move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
    echo "Sorry, there was an error uploading your file.";
   }
   if ($exists) {
     session_start();
     $old_file = $exists[0];
     $_SESSION["old"] = $old_file;
     $_SESSION["new"] = $new_file;
     echo "Username Already Exists: <form action='delete.php' method='POST'><input type='submit' name='old' value='Keep Old'><input type='submit' name='new' value='Keep New'></form>";
   }
  }
 }
 if(isset($_POST["submit"])) {
   post();
 }
?>



<!DOCTYPE html>
<html lang="en">
    <head>
        <title></title>
    </head>
    <body>
<form method="post" enctype="multipart/form-data">
    Enter your Username: <input type="text" name="user" placeholder="UserName"><br />
    Select image to upload: <input type="file" name="fileToUpload" id="fileToUpload"><br />
    <input type="submit" value="Upload Image" name="submit">
</form>
</body>
</html>
