-- Ryan Blair rablair@calpoly.edu

-- Total cost fees for each campus that avg fee > $2500 b/w 2000-2005
SELECT c.Campus, sum(f.fee)
FROM campuses c, fees f
WHERE f.CampusId = c.Id
AND f.Year BETWEEN 2000 AND 2005
GROUP BY c.Id
HAVING avg(f.fee) > 2500
ORDER BY sum(f.fee) ASC;

-- Avg, max, and min enrollment for campuses with enrollment data for > 60 yrs
SELECT c.Campus, round(avg(e.Enrolled), 2) AS 'Avg Enrolled', max(e.Enrolled), min(e.Enrolled)
FROM campuses c, enrollments e
WHERE e.CampusId = c.Id
GROUP BY e.CampusId
HAVING count(e.Year) > 60
ORDER BY avg(e.Enrolled);

-- Total # degrees granted b/w 1998-2002 for 'LA' and 'Orange' county campuses
SELECT c.Campus, c.County, sum(d.degrees)
FROM campuses c, degrees d
WHERE d.CampusId = c.Id
AND d.year BETWEEN 1998 AND 2002
AND (c.County = 'Los Angeles'
  OR c.County = 'Orange')
GROUP BY d.CampusId
ORDER BY sum(d.degrees) DESC;

-- # disciplines w/ > 0 graduate enrollment for each campus > 20000 enrolled in 2004
SELECT c.Campus, count(de.Discipline)
FROM campuses c, enrollments e, discEnr de
WHERE e.CampusId = c.Id
AND de.CampusId = c.Id
AND de.Year = e.Year
AND e.Year = 2004
AND e.Enrolled > 20000
AND de.Gr > 0
GROUP BY de.CampusId
ORDER BY c.Campus;
