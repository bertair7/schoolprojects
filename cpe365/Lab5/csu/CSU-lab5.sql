-- Ryan Blair rablair@calpoly.edu

-- # total degrees granted by 'CP-SLO' b/w 1995-2000
SELECT sum(d.degrees)
FROM campuses c, degrees d
WHERE c.Id = d.CampusId
AND c.Campus = 'California Polytechnic State University-San Luis Obispo'
AND d.year >= 1995
AND d.year <= 2000;

-- Largest, smallest and avg fee on CSU campus in 2005
SELECT max(f.fee), min(f.fee), avg(f.fee)
FROM fees f
WHERE f.Year = 2005;

-- Avg student:faculty ratio in 2004 among campuses w/ FTE > 15000
SELECT avg(e.FTE/f.FTE) AS 'Avg S:F ratio'
FROM enrollments e, faculty f
WHERE e.CampusId = f.CampusId
AND e.Year = 2004
AND f.Year = 2004
AND e.FTE > 15000;

-- Years where 1) > 17000 students on 'CP-SLO' 2) 'CP-SLO' graduated > 3500 students
SELECT DISTINCT d.year
FROM campuses c, degrees d, enrollments e
WHERE c.Id = d.CampusId
AND c.Id = e.CampusId
AND d.year = e.Year
AND c.Campus = 'California Polytechnic State University-San Luis Obispo'
AND (e.Enrolled > 17000
   OR d.degrees > 3500)
ORDER BY d.year;
