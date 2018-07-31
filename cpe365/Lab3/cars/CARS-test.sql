--
-- CSC 365. Lab 2. Test script for CARS dataset
-- 
-- Ryan Blair

-- set the destination for the output to lab2-CARS-output.txt
tee lab2-CARS-output.txt

\! echo "select database";
use rablair; 


-- see what tables there are
\! echo '***********************************************'
\! echo '            Current Tables                     '
\! echo '***********************************************'
show tables; 


-- Create tables
# '***********************************************'
# '              Creating tables - CARS            '
# '***********************************************'
source CARS-setup.sql

\! echo '***********************************************'
\! echo '          Show CARS tables                      '
\! echo '***********************************************'
show tables; 


-- Here you will put a line for each build script you have.
\! echo '***********************************************'
\! echo '         Populating tables                     '
\! echo '***********************************************'
source CARS-build-continents.sql
source CARS-build-countries.sql
source CARS-build-car-makers.sql
source CARS-build-model-list.sql
source CARS-build-car-names.sql
source CARS-build-cars-data.sql

-- To count the number of tuples in each of your tables, 
-- uncomment the following lines. Copy the SELECT statement
-- for each of your tables and replace the <my-CARS-table>
-- with your own table names.
\! echo '***********************************************'
\! echo '        Counting tuples - continents           '
\! echo '***********************************************'
SELECT count(*) FROM continents;
SELECT * FROM continents;

\! echo '***********************************************'
\! echo '      Counting tuples - countries              '
\! echo '***********************************************'
SELECT count(*) FROM countries;
SELECT * FROM countries;

\! echo '***********************************************'
\! echo '      Counting tuples - car_makers             '
\! echo '***********************************************'
SELECT count(*) FROM car_makers;
SELECT * FROM car_makers;

\! echo '***********************************************'
\! echo '      Counting tuples - model-list             '
\! echo '***********************************************'
SELECT count(*) FROM model_list;
SELECT * FROM model_list;

\! echo '***********************************************'
\! echo '      Counting tuples - car_names              '
\! echo '***********************************************'
SELECT count(*) FROM car_names;
SELECT * FROM car_names;

\! echo '***********************************************'
\! echo '      Counting tuples - cars_data              '
\! echo '***********************************************'
SELECT count(*) FROM cars_data;
SELECT * FROM cars_data;

\! echo '***********************************************'
\! echo '              Dropping tables                  '
\! echo '***********************************************'
source CARS-cleanup.sql


\! echo '***********************************************'
\! echo '      See if the tables were dropped           '
\! echo '***********************************************'
show tables;


\! echo '***********************************************'
\! echo '        All done                               '
\! echo '***********************************************'

notee
