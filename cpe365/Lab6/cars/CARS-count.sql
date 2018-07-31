-- Ryan Blair rablair@calpoly.edu

-- Best MPG, avg accel for each Japanese car maker
SELECT cm.Maker, max(c.MPG), round(avg(c.Accelerate), 2)
FROM cardata c, carmakers cm, countries cu, makes m, models md
WHERE c.Id = m.Id
AND m.Model = md.Model
AND md.Maker = cm.Id
AND cm.Country = cu.Id
AND cu.Name = 'japan'
GROUP BY cm.Maker
ORDER BY max(c.MPG) ASC;

-- # 4-cyl cars >4000 lbs with accel <14 for each US car maker
SELECT cm.Maker, count(*) 
FROM cardata c, carmakers cm, countries cu, makes m, models md
WHERE c.Id = m.Id
AND m.Model = md.Model
AND md.Maker = cm.Id
AND cm.Country = cu.Id
AND cu.Name = 'usa'
AND c.Weight < 4000
AND c.Cylinders = 4
AND c.Accelerate < 14
GROUP BY cm.Maker;

-- Best, worst, and avg gas mileage for 'toyota' vehicles each year 
-- 'honda' produced > 2 models
SELECT c.Year, max(c.MPG), min(c.MPG), avg(c.MPG)
FROM cardata c, makes m
WHERE c.Id = m.Id
AND m.Model = 'toyota'
AND c.Year IN (
   SELECT c.Year
   FROM cardata c, makes m
   WHERE c.Id = m.Id
   AND m.Model = 'honda'
   GROUP BY c.Year
   HAVING count(*) > 2)
GROUP BY c.Year
ORDER BY c.Year;

-- Max and min EDispl for each year when US-manufactured cars avg <100 horsepower
SELECT c.Year, max(c.EDispl), min(c.EDispl)
FROM cardata c
WHERE c.Year IN (
   SELECT c.Year
   FROM cardata c, carmakers cm, countries cu, makes m, models md
   WHERE c.Id = m.Id
   AND m.Model = md.Model
   AND md.Maker = cm.Id
   AND cm.Country = cu.Id
   AND cu.Name = 'usa'
   GROUP BY c.Year
   HAVING avg(c.Horsepower) < 100)
GROUP BY c.Year;

