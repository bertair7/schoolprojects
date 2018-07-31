-- Ryan Blair rablair@calpoly.edu

-- Tracklist of 'Le Pop'
SELECT s.Title
FROM Albums a, Songs s, Tracklists t
WHERE s.SongId = t.Song
AND a.AId = t.Album
AND a.Title = 'Le Pop'
ORDER BY t.Position;

-- Instruments each performer for 'Rock-Paper-Scissors'
SELECT b.Firsname, i.Instrument
FROM Songs s, Instruments i, Band b
WHERE s.SongId = i.Song
AND b.Id = i.Bandmate
AND s.Title = 'Rock-Paper-Scissors'
ORDER By b.Firsname;

-- All instruments played by 'Anne-Marit' >= once during performances
SELECT DISTINCT i.Instrument
FROM Instruments i, Band b, Performance p
WHERE b.Id = p.Bandmate
AND b.Id = i.Bandmate
AND i.Song = p.Song
AND b.Firsname = 'Anne-Marit'
ORDER BY i.Instrument;

-- All songs with 'ukalele'
SELECT s.Title
FROM Songs s, Instruments i
WHERE s.SongId = i.Song
AND i.Instrument = 'ukalele'
ORDER BY s.Title;

-- Instruments 'Turid' played where she sang lead vocals
SELECT DISTINCT i.Instrument
FROM Instruments i, Band b, Vocals v
WHERE b.Id = i.Bandmate
AND b.Id = v.Bandmate
AND v.Song = i.Song
AND b.Firsname = 'Turid'
AND v.VocalType = 'lead'
ORDER BY i.Instrument;

-- Songs lead vocalist not center stage
SELECT s.Title, b.Firsname, p.StagePosition
FROM Songs s, Band b, Performance p, Vocals v
WHERE s.SongId = p.Song
AND b.Id = p.Bandmate
AND s.SongId = v.Song
AND b.Id = v.Bandmate
AND p.StagePosition != 'center'
AND v.VocalType = 'lead'
ORDER BY s.Title;

-- Songs 'Anne-Marit' plays 3 different instruments
SELECT DISTINCT s.Title
FROM Songs s, Instruments i1, Instruments i2, Instruments i3, Band b
WHERE s.SongId = i1.Song
AND b.Id = i1.Bandmate
AND b.Id = i2.Bandmate
AND b.Id = i3.Bandmate
AND i1.Song = i2.Song
AND i2.Song = i3.Song
AND i1.Song = i3.Song
AND b.Firsname = 'Anne-Marit'
AND i1.Instrument != i2.Instrument
AND i2.Instrument != i3.Instrument
AND i1.Instrument != i3.Instrument;

-- Positioning of band in 'A Bar in Amsterdam' r-c-b-l
SELECT b.Firsname
FROM Band b, Performance p, Songs s
WHERE s.SongId = p.Song
AND b.Id = p.Bandmate
AND s.Title = 'A Bar in Amsterdam'
ORDER BY p.Bandmate DESC;

