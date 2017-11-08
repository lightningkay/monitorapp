CREATE DATABASE IF NOT EXISTS device_monitor DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE device_monitor;
create table IF NOT EXISTS device_records (
    id int not null primary key auto_increment,
    name varchar(10) not null,
    time timestamp,
    stress float,
    angle float
) DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

