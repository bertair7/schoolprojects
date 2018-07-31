-- Ryan Blair rablair@calpoly.edu

-- Delete all pastries expect Cakes
DELETE FROM goods
   WHERE Food != 'Cake';

-- Increase price of chocolate and opera cakes
UPDATE goods
   SET Price = Price * 1.2
   WHERE Flavor = 'Chocolate'
      OR Flavor = 'Opera';

-- Reduce price of Lemon and Napoleon to $2
UPDATE goods
   SET Price = 2.00
   WHERE Flavor = 'Lemon'
      OR Flavor = 'Napoleon';

-- Reduce price all other cakes by 20%
UPDATE goods 
   SET Price = Price * 0.8
   WHERE Flavor != 'Chocolate'
     AND Flavor != 'Opera'
     AND Flavor != 'Lemon'
     AND Flavor != 'Napoleon';

-- Finish query
SELECT * FROM goods
ORDER BY Id;
