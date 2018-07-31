--
-- CSC 365. Lab 2. Test script for KATZENJAMMER dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-KATZENJAMMER-output.txt
tee lab2-KATZENJAMMER-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - KATZENJAMMER            '
# '***********************************************'
source KATZENJAMMER-setup.sql

\! echo '***********************************************'
\! echo '          Show KATZENJAMMER tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source KATZENJAMMER-build-Albums.sql
source KATZENJAMMER-build-Band.sql
source KATZENJAMMER-build-Songs.sql
source KATZENJAMMER-build-Instruments.sql
source KATZENJAMMER-build-Performance.sql
source KATZENJAMMER-build-Tracklists.sql
source KATZENJAMMER-build-Vocals.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-KATZENJAMMER-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - albums               '
\! echo '***********************************************'
SELECT count(*) FROM albums;
SELECT * FROM albums;

\! echo '***********************************************'
\! echo '      Counting tuples - band             '
\! echo '***********************************************'
SELECT count(*) FROM band;
SELECT * FROM band;

\! echo '***********************************************'
\! echo '      Counting tuples - songs             '
\! echo '***********************************************'
SELECT count(*) FROM songs;
SELECT * FROM songs;

\! echo '***********************************************'
\! echo '      Counting tuples - instruments            '
\! echo '***********************************************'
SELECT count(*) FROM instruments;
SELECT * FROM instruments;

\! echo '***********************************************'
\! echo '      Counting tuples - performance            '
\! echo '***********************************************'
SELECT count(*) FROM performance;
SELECT * FROM performance;

\! echo '***********************************************'
\! echo '      Counting tuples - tracklists             '
\! echo '***********************************************'
SELECT count(*) FROM tracklists;
SELECT * FROM tracklists;

\! echo '***********************************************'
\! echo '      Counting tuples - vocals             '
\! echo '***********************************************'
SELECT count(*) FROM vocals;
SELECT * FROM vocals;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source KATZENJAMMER-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
