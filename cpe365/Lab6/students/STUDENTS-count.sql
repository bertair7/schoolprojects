-- Ryan Blair rablair@calpoly.edu

-- Names of teachers w/ 7-8 students in their classes
SELECT t.Last, t.First
FROM teachers t, list l
WHERE t.classroom = l.classroom
GROUP BY t.classroom 
HAVING count(t.classroom) >= 7 
AND count(t.classroom) <= 8
ORDER BY t.Last;

-- # classrooms and # students for each grade
SELECT grade, count(DISTINCT classroom), count(grade)
FROM list l
GROUP BY grade
ORDER BY count(DISTINCT classroom) DESC, grade ASC;

-- total # students for each kindergarten classroom
SELECT classroom, count(*)
FROM list l
WHERE l.grade = 0
GROUP BY classroom
ORDER BY count(*) DESC;

-- last student alphabetically by last name for each 4th grade classroom
SELECT max(l.LastName), l.FirstName, l.classroom
FROM list l
WHERE l.grade = 4
GROUP BY classroom
ORDER BY classroom;
