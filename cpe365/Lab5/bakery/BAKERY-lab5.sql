-- Ryan Blair rablair@calpoly.edu

-- All customers who purchased 2 different croissants
SELECT DISTINCT c.LastName, c.FirstName
FROM customers c, receipts r, items i, goods g
WHERE g.Food = 'Croissant'
AND g.GId = i.Item
AND r.Customer = c.CId
AND i.Receipt = r.RNumber
GROUP BY c.LastName, c.FirstName, r.RNumber
HAVING count(DISTINCT g.Flavor) > 1
ORDER BY c.LastName;

-- All days 1) 'Almeta Domkowski' made purchase or 2) someone purchased 'Gongolais Cookie'
SELECT DISTINCT r.SaleDate
FROM receipts r, goods g, items i, customers c
WHERE r.RNumber = i.Receipt
AND r.Customer = c.CId
AND i.Item = g.GId
AND ((c.LastName = 'DOMKOWSKI'
  AND c.FirstName = 'ALMETA')
  OR (g.Food = 'Cookie'
  AND g.Flavor = 'Gongolais'))
ORDER BY r.SaleDate;

-- Total amt money 'Natacha Stenz' spent during 10/2007
SELECT sum(g.PRICE)
FROM receipts r, goods g, items i, customers c
WHERE r.RNumber = i.Receipt
AND r.Customer = c.CId
AND i.Item = g.GId
AND c.LastName = 'STENZ'
AND c.FirstName = 'NATACHA';

-- Total amt money customers spent on Chocolate items
SELECT sum(g.PRICE)
FROM receipts r, goods g, items i, customers c
WHERE r.RNumber = i.Receipt
AND r.Customer = c.CId
AND i.Item = g.GId
AND g.Flavor = 'Chocolate';


