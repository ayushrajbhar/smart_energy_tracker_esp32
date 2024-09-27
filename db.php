<?php
$hostname = ""; 
$username = ""; 
$password = ""; 
$database = ""; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) { 
    die("Connection failed: " . mysqli_connect_error()); 
} 

echo "Database connection is OK<br>"; 

if(isset($_POST["voltage"]) && isset($_POST["current"]) && isset($_POST["power"])) {

    $v = $_POST["voltage"];
    $c = $_POST["current"];
    $p = $_POST["power"];

    $sql = "INSERT INTO electricity_consumption (voltage, current, power) VALUES (".$v.", ".$c.", ".$p.")"; 

    if (mysqli_query($conn, $sql)) {
        echo "Record inserted successfully";
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
}

mysqli_close($conn); // Close the connection
?>