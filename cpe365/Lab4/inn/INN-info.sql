-- Ryan Blair rablair@calpoly.edu

-- 'Modern' rooms price < $160 and 2 beds
SELECT RoomName, RoomCode
FROM rooms
WHERE basePrice < 160
AND decor = 'modern'
AND Beds = 2
ORDER BY RoomCode;

-- July reservations for CAS room
SELECT r.LastName, r.CheckIn, r.Checkout, r.Adults+r.Kids AS 'People', r.Rate
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND ro.RoomName = 'Convoke and sanguine'
AND r.CheckIn LIKE '%-07-%'
AND r.Checkout LIKE '%-07-%'
ORDER BY r.CheckIn, r.Checkout;

-- All rooms occupied on Feb 6, 2010
SELECT ro.RoomName, r.CheckIn, r.Checkout
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND r.CheckIn <= '2010-02-06'
AND r.Checkout >= '2010-02-06'
ORDER BY ro.RoomName;

-- Calculate total money 'Grant Knerien' paid for each stay
SELECT r.CODE, r.CheckIn, r.Checkout, ro.RoomName, 
       datediff(r.Checkout, r.CheckIn) * r.Rate AS 'Cost'
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND r.LastName = 'KNERIEN'
AND r.FirstName = 'GRANT'
ORDER BY r.CheckIn, r.Checkout;

-- Each reservation starting 12/31/10 
SELECT ro.RoomName, r.Rate, datediff(r.Checkout, r.CheckIn) AS 'Nights',
       datediff(r.Checkout, r.CheckIn) * r.Rate AS 'Cost'
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND r.CheckIn = '2010-12-31'
ORDER BY Nights DESC;

-- All reservations in rooms with double beds and accommodate 4 adults
SELECT r.CODE, ro.RoomName, ro.RoomCode, r.CheckIn, r.Checkout
FROM reservations r, rooms ro
WHERE r.Room = ro.RoomCode
AND ro.bedType = 'Double'
AND ro.maxOcc = 4
ORDER BY r.CheckIn, r.Checkout, ro.RoomCode;
