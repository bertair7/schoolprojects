-- Ryan Blair rablair@calpoly.edu

-- # times 'Turid' played 'bass balalaika' on songs
SELECT count(*)
FROM Band b, Instruments i
WHERE b.Id = i.Bandmate
AND b.Firsname = 'Turid'
AND i.Instrument = 'bass balalaika';

-- # times 'Solveig' was center stage while 'Marianne' was playing 'drums'
SELECT count(*)
FROM Band b1, Band b2, Performance p, Instruments i
WHERE b1.Id = p.Bandmate
AND b1.Firsname = 'Solveig'
AND p.StagePosition = 'center'
AND b2.Id = i.Bandmate
AND b2.Firsname = 'Marianne'
AND i.Instrument = 'drums'
AND i.Song = p.Song;

-- # times 'Solveig' sand lead while 'Marianne' performed not in back
SELECT count(*)
FROM Band b1, Band b2, Vocals v, Performance p
WHERE b1.Id = v.Bandmate
AND b1.FirsName = 'Solveig'
AND v.VocalType = 'lead'
AND b2.Id = p.Bandmate
AND b2.Firsname = 'Marianne'
AND p.StagePosition != 'back'
AND v.Song = p.Song;

-- Total # instruments 'Anne-Marit' played
SELECT count(DISTINCT i.Instrument)
FROM Band b, Instruments i
WHERE b.Id = i.Bandmate
AND b.Firsname = 'Anne-Marit';

-- List all instruments 'Marianne' and 'Turid' played
SELECT DISTINCT i1.Instrument
FROM Band b1, Band b2, Instruments i1, Instruments i2
WHERE b1.Id = i1.Bandmate
AND b2.Id = i2.Bandmate
AND b1.Firsname = 'Marianne'
AND b2.Firsname = 'Turid' 
AND i1.Instrument = i2.Instrument;

-- # people that play 'guitar'
SELECT count(DISTINCT b.Firsname)
FROM Band b, Instruments i
WHERE b.Id = i.Bandmate
AND i.Instrument = 'guitar';

-- # songs 2 performers played same instrument
SELECT count(DISTINCT i1.Song)
FROM Instruments i1, Instruments i2
WHERE i1.Song = i2.Song
AND i1.Instrument = i2.Instrument
AND i1.Bandmate != i2.Bandmate;

-- # times lead vocalist played 'bass balalaika'
SELECT count(DISTINCT i.Song)
FROM Instruments i, Vocals v
WHERE i.Song = v.Song
AND i.Bandmate = v.Bandmate
AND i.Instrument = 'bass balalaika'
AND v.VocalType = 'lead';

