--
-- CSC 365. Lab 2. Test script for BAKERY dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-BAKERY-output.txt
tee lab2-BAKERY-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - BAKERY            '
# '***********************************************'
source BAKERY-setup.sql

\! echo '***********************************************'
\! echo '          Show BAKERY tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source BAKERY-build-customers.sql
source BAKERY-build-goods.sql
source BAKERY-build-receipts.sql
source BAKERY-build-items.sql


-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-BAKERY-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - customers            '
\! echo '***********************************************'
SELECT count(*) FROM customers;
SELECT * FROM customers;

\! echo '***********************************************'
\! echo '      Counting tuples - goods                  '
\! echo '***********************************************'
SELECT count(*) FROM goods;
SELECT * FROM goods;

\! echo '***********************************************'
\! echo '      Counting tuples - receipts               '
\! echo '***********************************************'
SELECT count(*) FROM receipts;
SELECT * FROM receipts;

\! echo '***********************************************'
\! echo '      Counting tuples - items                  '
\! echo '***********************************************'
SELECT count(*) FROM items;
SELECT * FROM items;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source BAKERY-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
