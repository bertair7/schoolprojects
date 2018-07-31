--
-- CSC 365. Lab 2. Test script for AIRLINES dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-AIRLINES-output.txt
tee lab2-AIRLINES-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '         Creating tables - AIRLINES            '
# '***********************************************'
source AIRLINES-setup.sql

\! echo '***********************************************'
\! echo '     Show AIRLINES tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source AIRLINES-build-airlines.sql
source AIRLINES-build-airports100.sql
source AIRLINES-build-flights.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-AIRLINES-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - airlines             '
\! echo '***********************************************'
SELECT count(*) FROM airlines;

-- If you want, you can also display the tuples. Just add
-- whatever SELECT statements you wish, changing AIRLINES to the
-- appropriate table name.
SELECT * FROM airlines;

\! echo '***********************************************'
\! echo '      Counting tuples - airports100            '
\! echo '***********************************************'
SELECT count(*) FROM airports100;
SELECT * FROM airports100;

\! echo '***********************************************'
\! echo '      Counting tuples - flights                '
\! echo '***********************************************'
SELECT count(*) FROM flights;
SELECT * FROM flights;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source AIRLINES-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
