-- Ryan Blair rablair@calpoly.edu

-- replace instruments names
ALTER TABLE instruments
   MODIFY Instrument VARCHAR(40);

UPDATE instruments
   SET Instrument = 'awesome bass balalaika'
   WHERE Instrument = 'bass balalaika';

UPDATE instruments
   SET Instrument = 'acoustic guitar'
   WHERE Instrument = 'guitar';

-- Keep info of instruments about acoustic guitar
DELETE FROM instruments
   WHERE Instrument != 'acoustic guitar'
     AND BandmateID != 4;

-- Finish query
SELECT * FROM instruments
ORDER BY SongId, BandmateId;

-- Add column describing total # songs in albumn
ALTER TABLE albums
   ADD COLUMN (numSongs CHAR(10));

UPDATE albums
   SET numSongs = '13'
   WHERE AId = 1;

UPDATE albums
   SET numSongs = '12'
   WHERE AId = 2;

UPDATE albums
   SET numSongs = '19'
   WHERE AId = 3;

UPDATE albums
   SET numSongs = '11'
   WHERE AId = 4;

-- Finish query
SELECT * FROM albums
ORDER BY Year;
