-- Ryan Blair rablair@calpoly.edu

/* Pomona ID = 14, SLO ID = 20, LB ID = 9, SJS ID = 19
   Eng ID = 9, CIS ID = 7
*/

/* Keep enrollments from:
   1. Eng majors from CPSLO and CPP
   2. LBS for disciplines > 200 grad students
   3. Schools with > 500 CIS undergrads
*/
DELETE FROM discipline_enrollments
   WHERE ((Campus != 20 
          AND Campus != 14)
          OR Discipline != 9)
      AND (Campus != 9
          OR Graduate <= 200)
      AND (Discipline != 7
          OR Undergraduate <= 500);

-- Finish query
SELECT * from discipline_enrollments
ORDER BY Campus, Discipline;

/* Keep fees from:
   1. > $2,500
   2. Year = 2002 or b/w 2004-06
   3. Campus either CPSLO, CPP, or SJSU
*/
DELETE FROM csu_fees
   WHERE (CampusFee <= 2500)
      AND (Year != 2002
          AND Year != 2004
          AND Year != 2005
          AND Year != 2006)
      AND (Campus != 20 
          AND Campus != 14
          AND Campus != 19);

-- Finish query
SELECT * FROM csu_fees
ORDER BY Campus, Year;

