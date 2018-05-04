CREATE TABLE person (personid int,yob int,name char(9),state char(2),PRIMARY KEY(personid));
INSERT INTO person VALUES(1,1987,'Peter','TX');
INSERT INTO person VALUES(2, 1992,'David','NY');
INSERT INTO person VALUES(3, 1988,'Daisy','NY');
INSERT INTO person VALUES(4, 1975,'Matthew','AZ');
INSERT INTO person VALUES(5, 1982,'Nathan', 'TX');
INSERT INTO person VALUES(6, 1991, 'Pamela', 'CO');
INSERT INTO person VALUES(7, 1969, 'Damian', 'WA');
INSERT INTO person VALUES(8, 1977, 'Peter', 'TX');
INSERT INTO person VALUES(9, 1993, 'David', 'CO');
INSERT INTO person VALUES(10, 1991, 'Thomas', 'CO');
SELECT * FROM person ORDER BY personid;
SELECT yob,name FROM person ORDER BY yob;
SELECT state,SUM(personid)
FROM person
GROUP BY state;
SELECT state,SUM(personid)
FROM person
GROUP BY state
ORDER BY state;





