-- Ryan Blair rablair@calpoly.edu

-- Total (all), avg revenue (originated in 'Sept', 'Oct', + 'Nov') for each room
SELECT ro.RoomName, round(sum(datediff(r.Checkout, r.CheckIn) * r.Rate), 2) AS 'Total_Rev', 
       round(avg(datediff(r.Checkout, r.CheckIn) * r.Rate), 2) AS 'Avg_Rev'
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND r.CheckIn BETWEEN '2010-09-01' AND '2010-11-30'
AND r.Checkout BETWEEN '2010-09-01' AND '2010-11-30'
GROUP BY r.Room
ORDER BY sum(datediff(r.Checkout, r.CheckIn) * r.Rate) DESC;

-- Total # reservations, total revenue of reservations startomg on Fridays
SELECT count(r.CheckIn), round(sum(datediff(r.Checkout, r.CheckIn) * r.Rate), 2) AS 'Total_Rev'
FROM reservations r
WHERE DAYNAME(r.CheckIn) = 'Friday';

-- Total # reservations, total revenue of reservations starting each day of week
SELECT DAYNAME(r.CheckIn), count(r.CheckIn), 
       round(sum(datediff(r.Checkout, r.CheckIn) * r.Rate), 2) AS 'Total_Rev'
FROM reservations r
GROUP BY DAYNAME(r.CheckIn)
ORDER BY (DAYOFWEEK(r.CheckIn)) % 7;

-- Highest markup, largest markdown for each room 
SELECT ro.RoomName, max(r.Rate-ro.basePrice) AS 'Markup', 
       abs(min(r.Rate-ro.basePrice)) AS 'Markdown'
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
GROUP BY r.Room
ORDER BY Markup DESC;

-- # nights each room was occupied in 2010
SELECT r.Room, ro.RoomName, sum(datediff(
      if(r.Checkout > '2010-12-31', '2010-12-31', r.Checkout), 
      if(r.CheckIn < '2010-01-01', '2010-01-01', r.CheckIn))) AS 'Nights'
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND (r.CheckIn BETWEEN '2010-01-01' AND '2010-12-31'
 OR r.Checkout BETWEEN '2010-01-01' AND '2010-12-31')
GROUP BY r.Room
ORDER BY Nights DESC;
