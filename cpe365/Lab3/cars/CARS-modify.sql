-- Ryan Blair rablair@calpoly.edu

-- Excluding cars w/o one of following conditions
DELETE FROM cars_data 
   WHERE ((Year != 1979 AND Year != 1980) OR MPG < 20)
   AND (MPG < 26 OR Horsepower <= 110)
   AND (Cylinders != 8 OR Accelerate >= 10);

-- Prompted query
SELECT * FROM cars_data
ORDER BY Year, Id;

-- Remove Edispl, Horsepower, and Weight attrib's 
ALTER TABLE cars_data
   DROP COLUMN Edispl;
ALTER TABLE cars_data
   DROP COLUMN Horsepower;
ALTER TABLE cars_data
   DROP COLUMN Weight;

-- Drop car data about cars < 5 cyl
DELETE FROM cars_data
   WHERE Cylinders < 5;

-- Prompted query
SELECT * from cars_data
ORDER BY Year, id;
