-- Ryan Blair rablair@calpoly.edu

-- Remove Appelation name coln's and Wine table coln
ALTER TABLE wine
   DROP COLUMN Appelation;
ALTER TABLE wine
   DROP COLUMN Name;
ALTER TABLE appellations
   DROP COLUMN Appelation;

-- Keep wines with Syrah score >= 93
DELETE FROM wine
   WHERE Score < 93 OR Grape != 'Syrah';

-- Modify length Winery to 15
ALTER TABLE wine
   MODIFY Winery CHAR(15);

-- Add new coln Revenue
ALTER TABLE wine
   ADD COLUMN (Revenue FLOAT);

-- Calculate Revenue for each wine (12 bottles per case)
UPDATE wine
   SET Revenue = 12 * Cases * Price;

-- Finish query
SELECT * FROM wine
ORDER BY Revenue;
