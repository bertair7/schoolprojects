# Ryan Blair
# TR Section

CREATE TABLE appellations (
   No INTEGER UNIQUE,
   Appelation VARCHAR(30),
   County VARCHAR(20),
   State VARCHAR(20),
   Area VARCHAR(20),
   isAVA VARCHAR(3),
   PRIMARY KEY(No)
);

CREATE TABLE grapes (
   ID INTEGER UNIQUE,
   Grape VARCHAR(20),
   Color VARCHAR(20),
   PRIMARY KEY(ID)
);

CREATE TABLE wine (
   No INTEGER UNIQUE,
   Grape VARCHAR(20) REFERENCES grapes(Grape),
   Winery VARCHAR(20),
   Appelation VARCHAR(30) REFERENCES appellations(Appelation),
   State VARCHAR(20) REFERENCES appellations(State),
   Name VARCHAR(20),
   Year INTEGER,
   Price FLOAT,
   Score INTEGER,
   Cases INTEGER,
   Drink VARCHAR(20),
   PRIMARY KEY(No)
);
