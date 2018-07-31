# Ryan Blair
# TR Section

CREATE TABLE marathon (
   Place INTEGER UNIQUE,
   Time TIME,
   Pace TIME,
   GroupPlace INTEGER,
   GroupNum INTEGER,
   Age INTEGER,
   Sex VARCHAR(6),
   BIBNumber INTEGER,
   FirstName VARCHAR(20),
   LastName VARCHAR(20),
   Town VARCHAR(20),
   State VARCHAR(15),
   PRIMARY KEY(Place)
);
