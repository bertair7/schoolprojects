-- Ryan Blair rablair@calpoly.edu

-- Chocolate items under $5
SELECT Flavor, Food, PRICE
FROM goods
WHERE Flavor = 'Chocolate'
AND PRICE < 5.00
ORDER BY PRICE DESC;

-- Show cookies price > 1.10, lemon products, and apple products (except pies)
SELECT Flavor, Food, PRICE
FROM goods
WHERE (Food = 'Cookie'
  AND PRICE > 1.10)
   OR Flavor = 'Lemon'
   OR (Flavor = 'Apple'
  AND Food != 'Pie')
ORDER BY Flavor, Food;

-- Customers purchased on Oct 3, 2007
SELECT DISTINCT c.LastName, c.FirstName
FROM customers c, receipts r
WHERE c.CId = r.Customer
AND r.SaleDate = '2007-10-03'
ORDER BY c.LastName;

-- Cakes purchased on Oct 4, 2007
SELECT DISTINCT g.Flavor, g.Food
FROM goods g, receipts r, items i
WHERE i.Receipt = r.RNumber
AND i.Item = g.GId
AND r.SaleDate = '2007-10-04'
AND g.Food = 'Cake'
ORDER BY g.Flavor;

-- Pastries purchased by 'Ariane Cruzen' on Oct 25, 2007
SELECT DISTINCT g.Flavor, g.Food, g.PRICE
FROM goods g, receipts r, items i, customers c
WHERE i.Receipt = r.RNumber
AND i.Item = g.GId
AND r.Customer = c.CId
AND c.LastName = 'CRUZEN'
AND c.FirstName = 'ARIANE'
AND r.SaleDate = '2007-10-25'
ORDER BY i.Ordinal;

-- Cookies purchaed by 'Kip Arnn' during month of Oct 07
SELECT DISTINCT g.Flavor, g.Food
FROM goods g, receipts r, items i, customers c
WHERE i.Receipt = r.RNumber
AND i.Item = g.GId
AND r.Customer = c.CId
AND c.LastName = 'ARNN'
AND c.FirstName = 'KIP'
AND g.Food = 'Cookie'
ORDER BY g.Flavor;

