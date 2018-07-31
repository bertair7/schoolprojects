# Ryan Blair
# TR Section

CREATE TABLE continents (
   ContId INTEGER UNIQUE,
   Continent VARCHAR(20),
   PRIMARY KEY(ContId)
);

CREATE TABLE countries (
   CountryId INTEGER UNIQUE,
   CountryName VARCHAR(20),
   Continent VARCHAR(20) REFERENCES continents(ContId),
   PRIMARY KEY(CountryId)
);

CREATE TABLE car_makers (
   Id INTEGER UNIQUE,
   Maker VARCHAR(20),
   FullName VARCHAR(20),
   Country VARCHAR(20) REFERENCES countries(CountryId),
   PRIMARY KEY(Id)
);

CREATE TABLE model_list (
   ModelId INTEGER UNIQUE,
   Maker VARCHAR(20) REFERENCES car_makers(Id),
   Model VARCHAR(20),
   PRIMARY KEY(ModelId)
);

CREATE TABLE car_names (
   Id INTEGER UNIQUE,
   Model VARCHAR(20) REFERENCES model_list(Model),
   Make VARCHAR(60),
   PRIMARY KEY(Id)
);

CREATE TABLE cars_data (
   Id INTEGER, 
   MPG INTEGER, 
   Cylinders INTEGER,
   Edispl INTEGER,
   Horsepower INTEGER,
   Weight INTEGER,
   Accelerate INTEGER,
   Year INTEGER,
   FOREIGN KEY(Id) REFERENCES car_names(Id)
);

