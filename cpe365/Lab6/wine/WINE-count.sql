-- Ryan Blair rablair@calpoly.edu

-- Avg price, min price, max price (all vintage years), total # wines, total number cases
-- produced for each wine with score > 88
SELECT Score, round(avg(Price), 2) AS 'Avg Price', min(Price), max(Price), count(*), sum(Cases)
FROM wine 
WHERE Score > 88
GROUP BY Score
ORDER BY Score;

-- Total # red 'Sonoma' county wines w/ score >= 90 for each year
SELECT w.Vintage, count(*)
FROM wine w, appellations a, grapes g
WHERE w.Appellation = a.Appellation
AND w.Grape = g.Grape
AND g.Color = 'Red'
AND a.County = 'Sonoma'
AND w.Score >= 90
GROUP BY w.Vintage
ORDER BY w.Vintage ASC;

-- Name, county, total # 'Cab Sauv' wines in 2008, avg price 2008, total # bottles produced
-- for each appellation producing > 2 'Cab Sauv' wines in 2007
SELECT a.Appellation, a.County, count(w.WineId), avg(w.Price), sum(w.Cases*12)
FROM wine w, appellations a
WHERE w.Appellation = a.Appellation
AND w.Grape = 'Cabernet Sauvingnon'
AND w.Vintage = 2008
GROUP BY a.Appellation
HAVING a.Appellation IN (
   SELECT a.Appellation
   FROM appellations a, wine w
   WHERE w.Appellation = a.Appellation
   AND w.Grape = 'Cabernet Sauvingnon'
   AND w.Vintage = 2007
   GROUP BY a.Appellation
   HAVING count(w.WineId) > 2)
ORDER BY count(w.WineId);

-- Total sales for wines in 2008 for each appellation of 'Central Coast'
SELECT a.Appellation, sum(w.Price*w.Cases*12) AS 'Total_Revenue'
FROM appellations a, wine w
WHERE w.Appellation = a.Appellation
AND a.Area = 'Central Coast'
AND w.Vintage = 2008
GROUP BY a.Appellation
ORDER BY Total_Revenue DESC;

-- Highest score 2009 red wine for each county
SELECT a.County, max(w.Score)
FROM appellations a, grapes g, wine w
WHERE w.Appellation = a.Appellation
AND w.Grape = g.Grape
AND g.Color = 'Red'
AND w.Vintage = 2009
GROUP BY a.County
HAVING a.County NOT LIKE 'N/A'
ORDER BY max(w.Score) DESC;

