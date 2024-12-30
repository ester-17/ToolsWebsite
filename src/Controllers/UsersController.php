<?php 

require_once "src/Models/User.php";

class UsersController {

    public function main(){

        $action = $_GET['acao'] ?? null;

        switch($action){
            case 'entrar':
                $this->login();
                break;


            case 'registrar':
                $this->register();
                break;

        }
    }

    public function login(){
        $email = $_POST['email'] ?? null;
        $password = $_POST['password'] ?? null;

        if($email && $password){

            $model = new User();
            $user = $model->readBy('email', $email);

            if($user[0]){
                $logged_user = $user[0];

                if($logged_user['password'] == md5($password) ){
                    header("location: /?pagina=admin");
                }
            }
        }
    }

    public function register(){
        $name = $_POST['name'] ?? null;
        $email = $_POST['email'] ?? null;
        $matricula = $_POST['matricula'] ?? null;
        $password = $_POST['password'] ?? null;
        
        if($name && $email && $matricula && $password){

            $password = md5($password);

            $model = new User();

            $created = $model->insert($name, $email, $matricula, $password);

            if($created){
                $this->login();
            }

        }

    }

}