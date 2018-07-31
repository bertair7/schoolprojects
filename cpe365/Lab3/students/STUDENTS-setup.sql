# Ryan Blair
# TR Section

CREATE TABLE list (
   LastName VARCHAR(20),
   FirstName VARCHAR(20),
   Grade INTEGER,
   Classroom INTEGER,
   PRIMARY KEY(LastName, FirstName)
);

CREATE TABLE teachers (
   LastName VARCHAR(20),
   FirstName VARCHAR(20),
   Classroom INTEGER,
   PRIMARY KEY(LastName, FirstName)
);
