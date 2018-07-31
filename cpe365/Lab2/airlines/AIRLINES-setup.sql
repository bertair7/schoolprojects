# Ryan Blair
# TR Section

CREATE TABLE airlines (
   Id INTEGER UNIQUE,
   Airline VARCHAR(20),
   Abbreviation VARCHAR(20),
   Country VARCHAR(20), 
   PRIMARY KEY(Id)
);

CREATE TABLE airports100 (
   City VARCHAR(20),
   AirportCode VARCHAR(3),
   AirportName VARCHAR(40),
   Country VARCHAR(20),
   CountryAbbrev VARCHAR(3),
   PRIMARY KEY(AirportCode)
);

CREATE TABLE flights (
   Airline VARCHAR(20),
   FlightNo INTEGER,
   SourceAirport VARCHAR(3) REFERENCES airports100(AirportCode),
   DestAirport VARCHAR(3) REFERENCES airports100(AirportCode),
   PRIMARY KEY(Airline, FlightNo)
);

