-- Ryan Blair rablair@calpoly.edu

-- Teachers who teach most amt of students
SELECT t.Last, t.First, count(t.classroom)
FROM teachers t, list l
WHERE t.classroom = l.classroom
GROUP BY t.classroom
HAVING count(t.classroom) IN (
   SELECT * FROM (
      SELECT count(*)
      FROM teachers t1, list l1
      WHERE t1.classroom = l1.classroom
      GROUP BY t1.classroom
      ORDER BY count(*) DESC
      LIMIT 1)
   AS s)
ORDER BY t.Last;

-- Grades with largest # students w/ last name starting with 'A', 'B', or 'C'
SELECT l.grade, count(*)
FROM list l
WHERE l.LastName LIKE 'A%'
   OR l.LastName LIKE 'B%'
   OR l.LastName LIKE 'C%'
GROUP BY l.grade
HAVING count(*) IN (
   SELECT * FROM (
      SELECT count(*)
      FROM list l1
      WHERE l1.LastName LIKE 'A%'
         OR l1.LastName LIKE 'B%'
         OR l1.LastName LIKE 'C%'
      GROUP BY l1.grade
      ORDER BY count(*) DESC
      LIMIT 1)
   AS s)
;
 
-- Classrooms with < avg # students
SELECT t.classroom, count(*)
FROM teachers t, list l
WHERE t.classroom = l.classroom
GROUP BY t.classroom
HAVING count(*) < (
   SELECT avg(*)
   FROM list l1
   GROUP BY l1.classroom)
ORDER BY t.classroom ASC;

-- Pairs classrooms with same # stsudents
SELECT l1.classroom, l2.classroom
FROM list l1, list l2
WHERE l1.classroom < l2.classroom
GROUP BY l1.classroom, l2.classroom
HAVING count(l1.LastName) = count(l2.LastName);

-- teacher w/ most students for each grade with >1 classroom
SELECT l.grade, t.Last, t.First
FROM list l, teachers t
WHERE t.classroom = l.classroom



