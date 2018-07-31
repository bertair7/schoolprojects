-- Ryan Blair rablair@calpoly.edu

-- All Renault models
SELECT m.Make, cd.Year
FROM cardata cd, makes m
WHERE m.Id = cd.Id
AND m.Model = 'renault'
ORDER BY cd.Year;

-- 'Volvo' cars b/w 1977-1981
SELECT m.Make, cd.Year
FROM cardata cd, makes m
WHERE m.Id = cd.Id
AND m.Model = 'Volvo'
AND cd.Year > 1976
AND cd.Year < 1982
ORDER BY cd.Year;

-- All Asian automakers
SELECT cm.FullName, cu.Name
FROM carmakers cm, continents ct, countries cu
WHERE cm.Country = cu.Id
AND cu.Continent = ct.Id
AND ct.Name = 'asia'
ORDER BY cm.FullName;

-- Non-4 cyl cars in 1980 w/ >20 MPG + Accel <15 sec
SELECT m.Make, m.Model
FROM cardata cd, makes m
WHERE m.Id = cd.Id
AND cd.Cylinders != 4
AND cd.Year = 1980
AND cd.MPG > 20
AND cd.Accelerate < 15;

-- Non-Euro car makers that have at least 1 car w/ weight <2000 b/w 1979-1981
SELECT DISTINCT cm.FullName, cu.Name
FROM cardata cd, carmakers cm, countries cu, makes m, models md, continents ct
WHERE cd.Id = m.Id
AND (cd.Year >= 1979
 AND cd.Year <= 1981)
AND cd.Weight < 2000
AND m.Model = md.Model
AND md.Maker = cm.Id
AND cm.Country = cu.Id
AND cu.Continent = ct.Id
AND ct.Name != 'europe';

-- Computer ratio weight:horsepower for 'saab' cars after 1978
SELECT m.Make, cd.Year, (cd.Weight/cd.Horsepower) AS 'Ratio W:H'
FROM makes m, cardata cd
WHERE cd.Id = m.Id
AND m.Model = 'saab'
AND cd.Year > 1978
ORDER BY 'Ratio W:H' DESC;

