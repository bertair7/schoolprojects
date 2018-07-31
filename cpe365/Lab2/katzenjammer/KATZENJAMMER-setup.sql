# Ryan Blair
# TR Section

CREATE TABLE albums (
   AId INTEGER UNIQUE,
   Title VARCHAR(40),
   Year INTEGER,
   Label VARCHAR(20),
   Type VARCHAR(10),
   PRIMARY KEY(Aid)
);

CREATE TABLE band (
   Id INTEGER UNIQUE,
   Firstname VARCHAR(20),
   Lastname VARCHAR(20),
   PRIMARY KEY(Id)
);

CREATE TABLE songs (
   SongId INTEGER UNIQUE,
   Title VARCHAR(40),
   PRIMARY KEY(SongId)
);

CREATE TABLE instruments (
   SongId INTEGER,
   BandmateId INTEGER REFERENCES band(Id),
   Instrument VARCHAR(20),
   FOREIGN KEY(SongId) REFERENCES songs(SongId)
);

CREATE TABLE performance (
   SongId INTEGER, 
   Bandmate INTEGER REFERENCES band(Id),
   StagePosition VARCHAR(20),
   FOREIGN KEY(SongId) REFERENCES songs(SongId)
);

CREATE TABLE tracklists (
   AlbumId INTEGER REFERENCES albums(AId),
   Position VARCHAR(20),
   SongId INTEGER,
   FOREIGN KEY(SongId) REFERENCES songs(SongId)
);

CREATE TABLE vocals (
   SongId INTEGER,
   Bandmate INTEGER REFERENCES band(Id),
   Type VARCHAR(20),
   FOREIGN KEY(SongId) REFERENCES songs(SongId)
);
