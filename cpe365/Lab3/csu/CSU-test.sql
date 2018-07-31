--
-- CSC 365. Lab 2. Test script for CSU dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-CSU-output.txt
tee lab2-CSU-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - CSU            '
# '***********************************************'
source CSU-setup.sql

\! echo '***********************************************'
\! echo '          Show CSU tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source CSU-build-Campuses.sql
source CSU-build-csu-fees.sql
source CSU-build-degrees.sql
source CSU-build-disciplines.sql
source CSU-build-discipline-enrollments.sql
source CSU-build-enrollments.sql
source CSU-build-faculty.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-CSU-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - Campuses             '
\! echo '***********************************************'
SELECT count(*) FROM campuses;
SELECT * FROM campuses;

\! echo '***********************************************'
\! echo '      Counting tuples - csu-fees               '
\! echo '***********************************************'
SELECT count(*) FROM csu_fees;
SELECT * FROM csu_fees;

\! echo '***********************************************'
\! echo '      Counting tuples - degrees                '
\! echo '***********************************************'
SELECT count(*) FROM degrees;
SELECT * FROM degrees;

\! echo '***********************************************'
\! echo '      Counting tuples - disciplines            '
\! echo '***********************************************'
SELECT count(*) FROM disciplines;
SELECT * FROM disciplines;

\! echo '***********************************************'
\! echo '   Counting tuples - discipline_enrollments    '
\! echo '***********************************************'
SELECT count(*) FROM discipline_enrollments;
SELECT * FROM discipline_enrollments;

\! echo '***********************************************'
\! echo '      Counting tuples - enrollments            '
\! echo '***********************************************'
SELECT count(*) FROM enrollments;
SELECT * FROM enrollments;

\! echo '***********************************************'
\! echo '      Counting tuples - faculty                '
\! echo '***********************************************'
SELECT count(*) FROM faculty;
SELECT * FROM faculty;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source CSU-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
