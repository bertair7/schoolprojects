-- Ryan Blair rablair@calpoly.edu

-- Cars made after 1980 w/ MPG > 1982 Honda Civic
SELECT m1.Make, c1.Year, cm.FullName
FROM makes m1, makes m2, cardata c1, cardata c2, carmakers cm, models md
WHERE c1.Id = m1.Id
AND m1.Model = md.Model
AND md.Maker = cm.Id
AND c1.Year > 1980
AND c2.Id = m2.Id
AND c2.Year = 1982
AND m2.Make = 'honda civic'
AND c1.MPG > c2.MPG
ORDER BY c1.MPG DESC;

-- Avg, max, min horsepower for 4-cyl cars manufactured by 'renault' b/w 1971-1976
SELECT avg(c.Horsepower), max(c.Horsepower), min(c.Horsepower)
FROM makes m, cardata c, models md
WHERE c.Id = m.Id
AND m.Model = md.Model
AND c.Cylinders = 4
AND c.Year >= 1971
AND c.Year <= 1976
AND md.Model = 'renault';

-- # cars made in 1971 w/ Accel > 1972 'volvo 145e (sw)'
SELECT count(c1.Id) 
FROM makes m1, makes m2, cardata c1, cardata c2, models md
WHERE c1.Id = m1.Id
AND m1.Model = md.Model
AND c1.Year = 1971
AND c2.Id = m2.Id
AND c2.Year = 1972
AND m2.Make = 'volvo 145e (sw)'
AND c1.Accelerate > c2.Accelerate;

-- # manufacturers w/ a vehicle Weight > 4000 
SELECT count(DISTINCT md.Maker)
FROM makes m, cardata c, models md
WHERE c.Id = m.Id
AND m.Model = md.Model 
AND c.Weight > 4000;
