-- Ryan Blair rablair@calpoly.edu

-- Avg price item and # different pastries of flavors found >3 times on menu
SELECT avg(PRICE), count(Food)
FROM goods
GROUP BY Flavor
HAVING count(Food) > 3
ORDER BY avg(PRICE) ASC;

-- Total amt money earned from selling eclairs
SELECT sum(g.PRICE)
FROM goods g, items i
WHERE g.GId = i.Item
AND g.Food = 'Eclair';

-- RNumber, date of purchase, total # items, + amt paid for each purchase
-- by 'Natacha Stenz'
SELECT r.RNumber, r.SaleDate, count(i.Item), round(sum(g.PRICE), 2) AS 'Total_Revenue'
FROM goods g, customers c, items i, receipts r
WHERE g.GId = i.Item
AND i.Receipt = r.RNumber
AND r.Customer = c.CId
AND c.LastName = 'STENZ'
AND c.FirstName = 'NATACHA'
GROUP BY r.RNumber
ORDER BY Total_Revenue;

-- Total # receipts, total # pastries, and overall daily revenue for each day
-- of Week of October 8th (M-Sun)
SELECT r.SaleDate, DAYNAME(r.SaleDate), count(r.RNumber), round(sum(g.PRICE), 2) AS 'Total_Revenue'
FROM goods g, items i, receipts r
WHERE g.GId = i.Item
AND i.Receipt = r.RNumber
AND r.SaleDate BETWEEN '2007-10-08' AND '2007-10-14'
GROUP BY r.SaleDate;

-- All Days >10 tarts purchased
SELECT r.SaleDate
FROM goods g, items i, receipts r
WHERE g.GId = i.Item
AND i.Receipt = r.RNumber
AND g.Food = 'Tart'
GROUP BY r.SaleDate
HAVING count(g.Food) > 10
ORDER BY r.SaleDate;
