# Ryan Blair
# TR Section

CREATE TABLE customers (
   Id INTEGER UNIQUE,
   LastName VARCHAR(20),
   FirstName VARCHAR(20),
   PRIMARY KEY(Id)
);

CREATE TABLE goods (
   Id VARCHAR(20) UNIQUE,
   Flavor VARCHAR(20),
   Food VARCHAR(30),
   Price FLOAT,
   PRIMARY KEY(Id)
);

CREATE TABLE receipts (
   RecieptNumber INTEGER UNIQUE,
   Date DATE, 
   CustomerId INTEGER,
   FOREIGN KEY(CustomerId) REFERENCES customers(Id)
);

CREATE TABLE items (
   Reciept INTEGER, 
   Ordinal INTEGER,
   Item VARCHAR(20) REFERENCES goods(Id),
   FOREIGN KEY(Reciept) REFERENCES receipts(RecieptNumber)
);

