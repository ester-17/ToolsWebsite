<?php 

class Database {
    private $host = 'localhost';
    private $dbName = 'tools_panel';
    private $username = 'root';
    private $password = '';

    protected $connection;

    public function __construct() {
        $this->connection = new mysqli($this->host, $this->username, $this->password, $this->dbName);

        // Check for connection errors
        if ($this->connection->connect_error) {
            die("Connection failed: " . $this->connection->connect_error);
        }
    }

    public function getConnection() {
        return $this->connection;
    }
}

