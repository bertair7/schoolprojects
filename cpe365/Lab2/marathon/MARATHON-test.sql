--
-- CSC 365. Lab 2. Test script for MARATHON dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-MARATHON-output.txt
tee lab2-MARATHON-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '         Creating tables - MARATHON            '
# '***********************************************'
source MARATHON-setup.sql

\! echo '***********************************************'
\! echo '          Show MARATHON tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source MARATHON-build-marathon.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-MARATHON-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - marathon             '
\! echo '***********************************************'
SELECT count(*) FROM marathon;
SELECT * FROM marathon;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source MARATHON-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
