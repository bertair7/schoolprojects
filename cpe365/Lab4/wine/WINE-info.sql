-- Ryan Blair rablair@calpoly.edu

-- All AVA's in Monterey county
SELECT Appellation
FROM appellations
WHERE isAVA = 'Yes'
AND County = 'Monterey'
ORDER BY Appellation;

-- White grape varieties w/ >= 1 wine from 2008 rated 90+ points
SELECT DISTINCT g.Grape
FROM grapes g, wine w
WHERE g.Grape = w.Grape 
AND g.Color = 'White'
AND w.Vintage = 2008
AND w.Score >= 90
ORDER BY g.Grape;

-- Sonoma county appellations w/ >= 1 rating for 'Grenache'
SELECT DISTINCT a.Appellation, a.County
FROM appellations a, wine w
WHERE a.Appellation = w.Appellation
AND a.County = 'Sonoma'
AND w.Grape = 'Grenache'
ORDER BY a.County, a.Appellation;

-- All vintage years w/ >= 1 'Zinfandel' from Sonoma County rating > 92
SELECT DISTINCT w.Vintage
FROM appellations a, wine w
WHERE a.Appellation = w.Appellation
AND a.County = 'Sonoma'
AND w.Score > 92
AND w.Grape = 'Zinfandel'
ORDER BY w.Vintage;

-- Total revenue of 'Carlisle' and 'Syrah' wines
SELECT w.Name, w.Vintage, w.Score, (12 * w.Cases * w.Price) AS 'Revenue'
FROM wine w
WHERE w.Winery = 'Carlisle'
AND w.Grape = 'Syrah'
ORDER BY Revenue DESC;

-- Compute prices of:
-- 1) 1 bottle Kosta Browne's Koplen Vineyard 2008 Pinot Noir
-- 2) 2 bottles Darioush's 2007 Darius II Cabernet Sauvingnon
-- 3) 1 bottle Kistler's McCrea Vineyard 2006 Chardonnay
SELECT 1 * w.Price AS 'Koplen Vineyard'
FROM wine w
WHERE w.Winery = 'Kosta Browne'
AND w.Name = 'Koplen Vineyard'
AND w.Vintage = 2008
AND w.Grape = 'Pinot Noir';

SELECT 2 * w.Price AS 'Darius II'
FROM wine w
WHERE w.Winery = 'Darioush'
AND w.Name = 'Darius II'
AND w.Vintage = 2007
AND w.Grape = 'Cabernet Sauvingnon';

SELECT 1 * w.Price AS 'McCrea Vineyard'
FROM wine w
WHERE w.Winery = 'Kistler'
AND w.Name = 'McCrea Vineyard'
AND w.Vintage = 2006
AND w.Grape = 'Chardonnay';

