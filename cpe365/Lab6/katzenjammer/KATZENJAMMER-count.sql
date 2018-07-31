-- Ryan Blair rablair@calpoly.edu

-- # times each performer sang lead vocals
SELECT b.Firsname, count(v.VocalType)
FROM Band b, Vocals v
WHERE b.Id = v.Bandmate
AND v.VocalType = 'lead'
GROUP BY v.Bandmate
ORDER BY count(v.VocalType) DESC;

-- # different instruments each performer plays in 'Le Pop' album
SELECT b.Firsname, count(DISTINCT i.Instrument)
FROM Albums a, Band b, Instruments i, Tracklists t
WHERE a.AId = t.Album
AND t.Song = i.Song
AND i.Bandmate = b.Id
AND a.Title = 'Le Pop'
GROUP BY i.Bandmate
ORDER BY b.Firsname;

-- # times Turid stood at each stage position when performing
SELECT p.StagePosition, count(*)
FROM Band b, Performance p
WHERE b.Id = p.Bandmate
AND b.Firsname = 'Turid'
GROUP BY p.StagePosition
ORDER BY count(*) ASC;

-- # times performers played 'bass balalaika' when 'Anne-Marit' was stage left
SELECT b.Firsname, count(*)
FROM Band b, Instruments i
WHERE b.Id = i.Bandmate
AND b.Firsname != 'Anne-Marit'
AND i.Instrument = 'bass balalaika'
AND i.Song IN (
   SELECT p.Song
   FROM Band b, Performance p
   WHERE b.Id = p.Bandmate
   AND b.Firsname = 'Anne-Marit'
   AND p.StagePosition = 'left')
GROUP BY b.Firsname
ORDER BY b.Firsname;

-- All instruments played by 3 or more people
SELECT i.Instrument
FROM Band b, Instruments i
WHERE b.Id = i.Bandmate
GROUP BY i.Instrument
HAVING count(i.Bandmate) >= 3
ORDER BY i.Instrument;

-- # times performer played > 1 instrument in same song
SELECT b.Firsname, count(*)
FROM Band b, Instruments i1, Instruments i2
WHERE b.Id = i1.Bandmate
AND b.Id = i2.Bandmate
AND i1.Song = i2.Song
AND i1.Instrument != i2.Instrument
GROUP BY b.Firsname
ORDER BY b.Firsname;

