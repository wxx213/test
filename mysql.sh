#!/bin/bash

mysql -uroot -p -e "
DROP DATABASE db_students;
CREATE DATABASE db_students;
USE db_students;

#Student
CREATE TABLE IF NOT EXISTS Student(
	SId VARCHAR(20) NOT NULL PRIMARY KEY,
	SKey VARCHAR(40) NULL,
	SName VARCHAR(20) NULL,
	SSex VARCHAR(10) NULL,
	SAge TINYINT NULL,
	SCredit FLOAT NULL,
	SAddress VARCHAR(50) NULL,
	SPhone VARCHAR(50) NULL,
	SEmail VARCHAR(20) NULL
);

INSERT INTO Student (SId,SKey,SName,SSex,SAge,SCredit,SAddress,SPhone,SEmail)
	VALUES('1','key','name','male',23,90.5,'address','phone','email');
show databases;
SELECT * FROM Student;

"


