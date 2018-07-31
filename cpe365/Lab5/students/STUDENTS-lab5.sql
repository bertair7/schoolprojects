-- Ryan Blair rablair@calpoly.edu

-- All students with same first name
SELECT DISTINCT l1.LastName, l1.FirstName, l1.grade, l2.LastName, l2.FirstName, l2.grade
FROM list l1, list l2
WHERE l1.FirstName = l2.FirstName
AND l1.LastName != l2.LastName
AND l1.LastName < l2.LastName;

-- All 1st grade students not taught by 'Otha Moyer'
SELECT l.LastName, l.FirstName
FROM list l, teachers t
WHERE l.classroom = t.classroom
AND l.grade = 1
AND t.First = 'OTHA'
AND t.Last = 'MOYER'
ORDER BY LastName;

-- Total # 3rd + 4th graders
SELECT count(*) AS '3rd/4th'
FROM list
WHERE grade = 3 OR grade = 4;

-- # students taught by 'Loria Ondersma'
SELECT count(*) AS 'Loria #'
FROM list l, teachers t
WHERE l.classroom = t.classroom
AND t.Last = 'ONDERSMA'
AND t.First = 'LORIA';

