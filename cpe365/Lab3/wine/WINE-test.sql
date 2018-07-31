--
-- CSC 365. Lab 2. Test script for WINE dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-WINE-output.txt
tee lab2-WINE-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - WINE            '
# '***********************************************'
source WINE-setup.sql

\! echo '***********************************************'
\! echo '          Show WINE tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source WINE-build-appellations.sql
source WINE-build-grapes.sql
source WINE-build-wine.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-WINE-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - appellations         '
\! echo '***********************************************'
SELECT count(*) FROM appellations;
SELECT * FROM appellations;

\! echo '***********************************************'
\! echo '      Counting tuples - grapes             '
\! echo '***********************************************'
SELECT count(*) FROM grapes;
SELECT * FROM grapes;

\! echo '***********************************************'
\! echo '      Counting tuples - wine             '
\! echo '***********************************************'
SELECT count(*) FROM wine;
SELECT * FROM wine;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source WINE-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
