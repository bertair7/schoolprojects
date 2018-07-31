-- Ryan Blair rablair@calpoly.edu

-- Rooms occupied on all dates: 1) 05-15-2010 2) 08-18-2010 3) 12-12-2010
SELECT DISTINCT rm.RoomName, rm.RoomCode
FROM reservations r1, reservations r2, reservations r3, rooms rm
WHERE r1.Room = rm.RoomCode
AND r2.Room = rm.RoomCode
AND r3.Room = rm.RoomCode
AND (('2010-05-15' BETWEEN r1.CheckIn AND r1.Checkout)
 AND ('2010-08-18' BETWEEN r2.CheckIn AND r2.Checkout)
 AND ('2010-12-12' BETWEEN r3.CheckIn AND r3.Checkout))
ORDER BY rm.RoomName;

-- Names of people staying at inn at same time as 'Herbert Fryday'
SELECT r1.LastName, r1.FirstName
FROM reservations r1, reservations r2
WHERE r1.CODE = r2.CODE
AND r2.LastName = 'FRYDAY'
AND r2.FirstName = 'HERBERT'
AND ((r1.CheckIn <= r2.CheckIn AND r1.Checkout >= r2.CheckIn)
  OR (r1.CheckIn <= r2.Checkout AND r1.Checkout >= r2.Checkout)
  OR (r1.CheckIn <= r2.CheckIn AND r1.Checkout >= r2.Checkout))
ORDER BY r1.LastName; 

-- # August reservations w/ 2 adults and 1 child
SELECT count(*)
FROM reservations r
WHERE r.Adults = 2
AND r.Kids = 2
AND r.CheckIn LIKE '%-08-%'
AND r.Checkout LIKE '%-08-%';

-- Avg # nights of stay in IBS room starting 5-1-2010 or later and ended before 8-31-2010
SELECT Avg(datediff(r.Checkout, r.CheckIn))
FROM reservations r, rooms rm
WHERE r.Room = rm.RoomCode
AND rm.RoomName = 'Interim but salutary'
AND r.CheckIn >= '2010-05-01'
AND r.Checkout < '2010-08-31';

-- # July reservations in IBS room
SELECT count(datediff(r.Checkout, r.CheckIn))
FROM reservations r, rooms rm
WHERE r.Room = rm.RoomCode
AND rm.RoomName = 'Interim but salutary'
AND r.CheckIn LIKE '%-07-%'
AND r.Checkout LIKE '%-07-%';
