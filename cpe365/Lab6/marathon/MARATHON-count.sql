-- Ryan Blair rablair@calpoly.edu

-- Total # runners, max and min overall place for each gender/age group
SELECT AgeGroup, Sex, count(*), min(Place), max(Place)
FROM marathon 
GROUP BY AgeGroup, Sex
ORDER BY AgeGroup, Sex;

-- Total # gender/age groups where 1st and 2nd place runners are from same state
SELECT count(*)
FROM marathon m1, marathon m2
WHERE m1.AgeGroup = m2.AgeGroup
AND m1.Sex = m2.Sex
AND m1.State = m2.State
AND m1.GroupPlace = 1
AND m2.GroupPlace = 2
ORDER BY m1.AgeGroup;

-- Total # runners whose pace was between each full minute and next
SELECT MINUTE(Pace), count(*)
FROM marathon
GROUP BY MINUTE(Pace);

-- # runners in top 10 gender/age group for each state, exclude if 0
SELECT State, count(*)
FROM marathon
WHERE GroupPlace <= 10
GROUP BY State
HAVING count(*) > 0
ORDER BY count(*) DESC;

-- Avg time residents for each 'CT' town with >= 3 participants
SELECT Town, State, avg(TIME_TO_SEC(RunTime))
FROM marathon
WHERE State = 'CT'
GROUP BY Town
HAVING count(*) >= 3
ORDER BY avg(TIME_TO_SEC(RunTime)) ASC;
 
