<?php 

require_once "database/Database.php";

class Model extends Database {

    protected $tableName;

    public function all(){
        $result = $this->connection->query("SELECT * FROM $this->tableName");

        return $result->fetch_all(MYSQLI_ASSOC);
    }

    public function readBy($field, $value){
        $result = $this->connection->query("SELECT * FROM $this->tableName WHERE $field = '$value'");
        return $result->fetch_all(MYSQLI_ASSOC);
    }   

    public function delete($id){
        $result = $this->connection->query("DELETE FROM $this->tableName WHERE id = $id");
        return $result;
    }

}
