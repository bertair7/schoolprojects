-- Ryan Blair rablair@calpoly.edu

-- Classroom 111
SELECT LastName, FirstName
FROM list
WHERE classroom = 111
ORDER BY LastName;

-- Report grade for each classroom
SELECT DISTINCT grade, classroom
FROM list
ORDER BY classroom DESC;

-- All 5th grade teachers
SELECT DISTINCT t.Last, t.First, t.classroom
FROM teachers t, list l
WHERE t.classroom = l.classroom
AND l.grade = 5
ORDER BY t.classroom;

-- All students taught by 'Otha Moyer'
SELECT l.FirstName, l.LastName
FROM teachers t, list l
WHERE t.classroom = l.classroom
AND t.Last = 'MOYER'
AND t.First = 'OTHA'
ORDER BY l.LastName;

-- Teachers of grades K-3rd
SELECT DISTINCT t.Last, t.First, l.grade
FROM teachers t, list l
WHERE t.classroom = l.classroom
AND l.grade < 4
ORDER BY l.grade, t.Last;
