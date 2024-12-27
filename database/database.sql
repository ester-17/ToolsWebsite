create database tools_panel;

use tools_panel;

create table operators (
    id integer auto_increment primary key,
    nome varchar(32),
    email varchar(128),
    matricula char(5), /* the value will always be the specified number, padding with spaces if necessary */
    password varchar(256)
);

create table tools (
    id integer auto_increment primary key,
    rotulo varchar(32),
    marca varchar(32),
    preço float,
    especificacao integer
);

create table team_leaders (
    id integer auto_increment primary key,
    nome varchar(32),
    email varchar(128),
    matricula char(5), /* the value will always be the specified number, padding with spaces if necessary */
    password varchar(256)
);

create table maintenance (
    id integer auto_increment primary key,
    nome varchar(32),
    email varchar(128),
    matricula char(5), /* the value will always be the specified number, padding with spaces if necessary */
    sector varchar(64),
    password varchar(256)
);

create table reports (
    id integer auto_increment primary key,
    nome varchar(64),
    setor varchar(64),
    email varchar(128),
    matricula char(5),
    data datetime

);