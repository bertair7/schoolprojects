-- Ryan Blair rablair@calpoly.edu

-- Time, pace, place of 'Teddy Brasel'
SELECT RunTime, Pace, Place
FROM marathon
WHERE FirstName = 'TEDDY'
AND LastName = 'BRASEL';

-- All female runners from 'Quincy, Ma'
SELECT FirstName, LastName, RunTime, Place, GroupPlace
FROM marathon
WHERE Town = 'QUINCY'
AND State = 'MA'
ORDER By Place;

-- All 34yo female runners from CT
SELECT FirstName, LastName, Town, RunTime
FROM marathon
WHERE Age = 34
AND State = 'CT'
AND Sex = 'F'
ORDER BY RunTime;

-- All duplicate bibs
SELECT DISTINCT m1.BibNumber
FROM marathon m1, marathon m2
WHERE m1.BibNumber = m2.BibNumber
AND m1.Place != m2.Place
ORDER BY m1.BibNumber ASC;

-- All 1st, 2nd place finishers for each age/gender group
SELECT FirstName, LastName, Age
FROM marathon
WHERE GroupPlace = 1
   OR GroupPlace = 2
ORDER BY Sex, AgeGroup;
