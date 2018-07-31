-- Ryan Blair rablair@calpoly.edu

-- Give GPA to each student
ALTER TABLE list
   ADD COLUMN (GPA FLOAT);

-- Keep database only students grades 5 and 6
DELETE FROM list
   WHERE Grade < 5;

-- Add new classroom 120 w/ teacher GAWAIN AP-MAWR
INSERT INTO teachers(LastName, FirstName, Classroom)
   VALUES ('AP-MAWR', 'GAWAIN', 120);

-- Move Jeffrey, Tawanna, and Emile to 120
UPDATE list
   SET Classroom = 120
   WHERE LastName ='FLACHS' AND FirstName = 'JEFFREY';

UPDATE list
   SET Classroom = 120
   WHERE LastName ='HUANG' AND FirstName = 'TAWANNA';

UPDATE list
   SET Classroom = 120
   WHERE LastName ='GRUNIN' AND FirstName = 'EMILE';

-- Set GPA of 6th graders to 3.25
UPDATE list
   SET GPA = 3.25
   WHERE Grade = 6;

-- Set GPA of 5th graders in 109 to 2.9
UPDATE list
   SET GPA = 2.9
   WHERE Grade = 5 AND Classroom = 109;

-- Set GPA of 5th graders in 120 to 3.5
UPDATE list
   SET GPA = 3.5
   WHERE Grade = 5 AND Classroom = 120;

-- Update GPA of Chet Maciag
UPDATE list
   SET GPA = 4.0
   WHERE LastName = 'MACIAG' AND FirstName = 'CHET';

-- Update GPA of Al Gerstein
UPDATE list
   SET GPA = GPA + 0.3
   WHERE LastName = 'GERSTEIN' AND FirstName = 'AL';

-- Update GPA of Tawanna Huang and Elvira Jagneux 
UPDATE list
   SET GPA = GPA * 1.1
   WHERE LastName = 'HUANG' AND FirstName = 'TAWANNA';

UPDATE list
   SET GPA = GPA * 1.1
   WHERE LastName = 'JAGNEUX' AND FirstName = 'ELVIRA';

-- Complete query
SELECT * FROM list
ORDER BY GPA, Grade, LastName;

SELECT *
FROM teachers;
