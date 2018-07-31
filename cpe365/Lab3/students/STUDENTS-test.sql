--
-- CSC 365. Lab 2. Test script for STUDENTS dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-STUDENTS-output.txt
tee lab2-STUDENTS-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - STUDENTS            '
# '***********************************************'
source STUDENTS-setup.sql

\! echo '***********************************************'
\! echo '          Show STUDENTS tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source STUDENTS-build-list.sql
source STUDENTS-build-teachers.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-STUDENTS-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - list                 '
\! echo '***********************************************'
SELECT count(*) FROM list;
SELECT * FROM list;

\! echo '***********************************************'
\! echo '        Counting tuples - teachers             '
\! echo '***********************************************'
SELECT count(*) FROM teachers;
SELECT * FROM teachers;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source STUDENTS-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
