<?php 

require_once "src/Models/Model.php";

class User extends Model {

    protected $tableName = 'users';

    public function insert($nome, $email, $matricula, $password){

        $result = $this->connection->query("INSERT INTO $this->tableName (name, email, phone, password) VALUES ('$nome', '$email', '$matricula', '$password')");

        return $result;
    }


}