<?php

    $page = $_GET['pagina'] ?? null;

    switch($page){
        case 'relatorios':
            require "src/Controllers/ReportsController.php";
            $controller = new ReportsController();
            break;

        case 'clientes':
            require "src/Controllers/CustomersController.php";
            $controller = new CustomersController();
            break;

        case 'pedidos':
            require "src/Controllers/OrdersController.php";
            $controller = new OrdersController();
            break;

        case 'admin':
            require "src/Controllers/AdminController.php";
            $controller = new AdminController();
            break;

        case 'usuario':
            require 'src/Controllers/UsersController.php';
            $controller = new UsersController();
            break;
        
        case 'desenvolvedores':
            require 'src/Controllers/DesenvolvedoresController.php';
            $controller = new DesenvolvedoresController();
            break;
        
        case 'contato':
            require 'src/Controllers/ContatoController.php';
            $controller = new ContatoController();
            break;

        case 'produtos':
            require 'src/Controllers/ProdutosController.php';
            $controller = new ProdutosController();
            break;


        default:
            require 'src/Controllers/StaticController.php';
            $controller = new StaticController();
    }


$controller->main();