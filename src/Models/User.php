<?php 

require_once "src/Models/Model.php";

class User extends Model {

    protected $tableName = 'operators';

    public function insert($nome, $email, $matricula, $password){

        $result = $this->connection->query("INSERT INTO $this->tableName (nome, email, matricula, password) VALUES ('$nome', '$email', '$matricula', '$password')");

        return $result;
    }


}