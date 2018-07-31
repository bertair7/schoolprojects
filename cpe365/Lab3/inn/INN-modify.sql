-- Ryan Blair rablair@calpoly.edu

-- Add column for room description
ALTER TABLE rooms
   ADD COLUMN (description VARCHAR(280));

-- Add description for each room 
UPDATE rooms
   SET description = 'Sleep in the stars with antique furniture and a great view of the oocean'
   WHERE RoomId = 'AOB';

UPDATE rooms
   SET description = 'Enjoy the fastest wifi of the hotel'
   WHERE RoomId = 'CAS';

UPDATE rooms
   SET description = 'Our most expensive and lavish room that is worth the price'
   WHERE RoomId = 'FNA';

UPDATE rooms
   SET description = 'Our transformation of the modern hotel room'
   WHERE RoomId = 'HBB';

UPDATE rooms
   SET description = 'Travel to the most immersive interaction with nature'
   WHERE RoomId = 'IBD';

UPDATE rooms
   SET description = 'The cheapest option with the feel of a modern hotel'
   WHERE RoomId = 'IBS';

UPDATE rooms
   SET description = 'Enjoy the aquarium of fish floating underneath the floor'
   WHERE RoomId = 'MWC';

UPDATE rooms
   SET description = 'The best view overlooking the ocean'
   WHERE RoomId = 'RND';

UPDATE rooms
   SET description = 'Best option for any honeymoon'
   WHERE RoomId = 'RTE';

UPDATE rooms
   SET description = 'Experience the luxury of our Bed & Breakfast for half the price! Cozy room overlooking the picturesque garden'
   WHERE RoomId = 'TAA';

-- Finish query
SELECT * FROM rooms
ORDER BY RoomId \G;
