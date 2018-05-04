We used the parser from github:hyrise(reference:https://github.com/hyrise/sql-parser)
The project has to be downloaded and opened in clion and built first.

Next,Run the executable file sql_parser_1_5 from cmake-bild-debug folder.

Input through multiple lines like below is not working. 
"SELECT *
 FROM TABLE
 B WHERE C1="ABC";"

Give inputs using batch or single query
For Batch File Command: ./sql_parser_1_5 script=test.sql
For single query: ./sql_parser_1_5 "QUERY;"

For the input query it should be specified with semicolon else the parser would not accept the syntax.
Example:"Insert into t1 values(1,'abc',3);"
The following queries are implemented:

"CREATE TABLE T(C1 INT,C2 CHAR(8),C3 INT,PRIMARY KEY(C1));"
"INSERT INTO T VALUES (1,'abc'.5);"
"SELECT * FROM T;"
"SELECT A FROM TABLE B;"
"SELECT * FROM TABLE B WHERE C1="ABC";"
"SELECT * FROM T1 JOIN T2 ON T1.B=T2.Y;"

sql_parser_1_5

SHOW TABLE T:
Displays table name and ddl information of the table

SHOW TABLES;
Displays all the tables in the database


A catalog file is generated that has metadata info about all the tables in the database.
For each table a .tbl file is generated when a create command is executed.


Phase 2:

All test cases working except for one query mentioned below:

Query Not Implemented:
SELECT *
FROM account JOIN person ON account.personid = person.personid
WHERE person.yob > 1990;

