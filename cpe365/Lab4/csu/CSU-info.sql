-- Ryan Blair rablair@calpoly.edu

-- All 'Los Angeles' campuses
SELECT Campus
FROM campuses
WHERE County = 'Los Angeles'
ORDER BY Campus;

-- # students graduated from Cal Maritime Academy b/w 1994-2000
SELECT d.degrees, d.year
FROM campuses c, degrees d
WHERE d.CampusId = c.Id
AND c.Campus = 'California  Maritime Academy'
AND d.year >= 1994
AND d.year <= 2000
ORDER BY d.year;

-- Grad + Undergrad enrollments in Math, Eng, and CIS for 'Polytechnic' universities in 2004
SELECT c.Campus, dsc.Name, de.Ug, de.Gr
FROM campuses c, disciplines dsc, discEnr de
WHERE c.Id = de.CampusId
AND de.Discipline = dsc.Id
AND c.Campus LIKE '%Polytechnic%'
AND de.Year = 2004
AND (dsc.Name = 'Mathematics'
  OR dsc.Name = 'Engineering'
  OR dsc.Name = 'Computer and Info. Sciences')
ORDER BY c.Campus, dsc.Name;

-- Grad enrollments in Ag and BioSci for universities that offer both in 2004
SELECT c.Campus, deA.Gr AS 'Agr Gr', deB.Gr AS 'Bio Gr'
FROM campuses c, disciplines dscA, disciplines dscB, discEnr deA, discEnr deB
WHERE c.Id = deA.CampusId
AND c.Id = deB.CampusId
AND deA.Discipline = dscA.Id
AND deB.Discipline = dscB.Id
AND deA.Year = 2004
AND deB.Year = 2004
AND dscA.Name = 'Agriculture'
AND dscB.Name = 'Biological Sciences'
ORDER BY deA.Gr;

-- All disciplines and campuses w/ grad enrollment > 3x undergrad enrollment in 2004
SELECT c.Campus, dsc.Name
FROM campuses c, disciplines dsc, discEnr de
WHERE c.Id = de.CampusId
AND de.Discipline = dsc.Id
AND de.Gr > (3 * de.Ug)
AND de.Year = 2004
ORDER BY c.Campus, dsc.Name;

-- Total fees collected by Fresno State each year b/w 2002-2004 + total fees/1 FT equv faculty
SELECT e.Year, e.Enrolled * f.fee AS 'Total Fees', 
       (e.Enrolled * f.fee / fy.FTE) AS 'Fee per Faculty'
FROM campuses c, enrollments e, fees f, faculty fy
WHERE c.Id = e.CampusId
AND c.Id = f.CampusId
AND c.Id = fy.CampusId
AND e.Year = f.Year
AND fy.Year = e.Year
AND e.Year >= 2002
AND e.Year <= 2004
AND c.Campus = 'Fresno State University'
ORDER BY e.Year;

-- Any Campus' FTE 2003 > SJSU FTE 2003
SELECT c.Campus, e.FTE AS 'Enroll.FTE', fy.FTE AS 'Faculty.FTE', 
       (e.FTE / fy.FTE) AS 'Ratio FTE'
FROM campuses c, campuses cSJSU, enrollments e, enrollments eSJSU, faculty fy
WHERE c.Id = e.CampusId
AND cSJSU.Id = eSJSU.CampusId
AND c.Id = fy.CampusId
AND e.Year = fy.Year
AND cSJSU.Campus = 'San Jose State University'
AND e.Year = 2003
AND eSJSU.Year = 2003
AND e.FTE > eSJSU.FTE
ORDER BY 'Ratio FTE Enrollment';

