-- Ryan Blair rablair@calpoly.edu

-- All airports with exactly 17 outgoing flights
SELECT a.Code, a.City, a.Name
FROM airports a, flights f
WHERE a.Code = f.Destination
GROUP BY f.Destination
HAVING count(*) = 17
ORDER BY a.Code;

-- # airports where 'ANP' can be reached with exactly 1 transfer
SELECT count(DISTINCT f1.Source) AS 'ANP'
FROM flights f1, flights f2
WHERE f1.Source != f2.Destination
AND f1.Destination = f2.Source
AND f2.Destination = 'ANP';

-- # airports where 'ATE' can be reached with at most 1 transfer
SELECT count(DISTINCT f1.Source) AS 'ATE'
FROM flights f1, flights f2
WHERE f1.Source != f2.Destination
AND f2.Destination = 'ATE'
AND ((f1.Destination = f2.Source)
 OR (f1.Destination = f2.Destination
 AND f1.Source = f2.Source));

-- Total # airports with at least 1 outgoing flight for each airline
SELECT a.Name, count(DISTINCT f.Source)
FROM airlines a, flights f
WHERE a.Id = f.Airline
GROUP BY f.Airline
ORDER BY count(DISTINCT f.Source) DESC;
