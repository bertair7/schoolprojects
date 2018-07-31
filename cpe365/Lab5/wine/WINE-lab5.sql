-- Ryan Blair rablair@calpoly.edu

-- 2006 wines from 'Napa' whose total revenue > 2006 'Appelation Series' 'Paso Robles' 
--                                                   'Zinfandel' from 'Rosenblum'
SELECT w1.Grape, w1.Winery, w1.Name, w1.Score, (w1.Price*w1.Cases*12) AS 'Revenue'
FROM wine w1, wine w2, appellations a
WHERE w1.Appellation = a.Appellation
AND w1.Vintage = 2006
AND a.County = 'Napa'
AND w2.Vintage = 2006
AND w2.Name = 'Appelation Series'
AND w2.Appellation = 'Paso Robles'
AND w2.Winery = 'Rosenblum'
AND w2.Grape = 'Zinfandel'
AND (12*w1.Price*w1.Cases) > (12*w2.Price*w2.Cases)
ORDER BY Revenue;

-- Avg score of a 'Paso Robles' 'Zinfandel'
SELECT avg(w.Score)
FROM wine w
WHERE w.Grape = 'Zinfandel'
AND w.Appellation = 'Paso Robles';

-- Total revenue from all red wines by 'Kosta Browne'
SELECT sum((12*w.Price*w.Cases))
FROM wine w, grapes g
WHERE w.Grape = g.Grape
AND w.Winery = 'Kosta Browne'
AND g.Color = 'Red';

-- Avg # cases of 'Pinot Noir' from grapes sourced from 'Central Coast'
SELECT avg(w.Cases)
FROM wine w, appellations a
WHERE w.Appellation = a.Appellation
AND w.Grape = 'Pinot Noir'
AND a.Area = 'Central Coast';

-- # different red wines produced in 'Russian River Valley' during year when AVA
-- had a wine w/ score = 98
SELECT count(DISTINCT w1.WineId)
FROM wine w1, wine w2, appellations a, grapes g
WHERE w1.Appellation = a.Appellation
AND w1.Grape = g.Grape
AND g.Color = 'Red'
AND a.Appellation = 'Russian River Valley'
AND w2.Appellation = a.Appellation
AND w2.Score = 98
AND w2.Vintage = w1.Vintage;
