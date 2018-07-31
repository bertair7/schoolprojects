--
-- CSC 365. Lab 2. Test script for INN dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-INN-output.txt
tee lab2-INN-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - INN            '
# '***********************************************'
source INN-setup.sql

\! echo '***********************************************'
\! echo '          Show INN tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source INN-build-Rooms.sql
source INN-build-Reservations.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-INN-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - rooms                '
\! echo '***********************************************'
SELECT count(*) from rooms;

-- If you want, you can also display the tuples. Just add
-- whatever SELECT statements you wish, changing INN to the
-- appropriate table name.
SELECT * FROM rooms;

\! echo '***********************************************'
\! echo '      Counting tuples - reservations             '
\! echo '***********************************************'
SELECT count(*) from reservations;
SELECT * from reservations;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source INN-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
