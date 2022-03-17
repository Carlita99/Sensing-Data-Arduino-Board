<?php

$connection; 

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    if (!empty($_GET['Temperature'])) {
        insertValue('Temperature', $_GET['Temperature']);     
    } 
    if (!empty($_GET['UV'])) {
        insertValue('UV', $_GET['UV']);     
    } else {
        echo "GET request not working";
    }
}

function insertValue($type, $valuee){
    $hostName = "localhost";
    $userName = "root";
    $password = "root1234";
    $dbName = "pollution_detection";
    $connection = new mysqli($hostName, $userName, $password, $dbName);
    if (!$connection) {
        die("Connection failed: " . mysqli_connect_error());
    }
    echo 'Connected successfully';
    $sql = "SELECT id FROM Flags WHERE valuee='" . $type . "'";
    $result = $connection->query($sql);

    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            echo "received ID";
            $id = $row["id"];
            $date = date('Y-m-d H:i:s');
            
            $sql = "INSERT INTO ValuesReceived (valuee, flagID, timestampp) VALUES ('" . $valuee . "', '" . $id . "', '" . $date . "')";
            echo $sql;
            if (mysqli_query($connection, $sql)) {
                echo "New record created successfully";
            } else {
                echo "Error: " . $sql . "<br>" . $connection->error;
            }             
        }
     } else {
        printf('No record found.<br />');
     }
     mysqli_free_result($result);
     $mysqli→close();
}
?>