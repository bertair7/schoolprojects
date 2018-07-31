# Ryan Blair
# TR Section

CREATE TABLE rooms (
   RoomId VARCHAR(3) UNIQUE,
   roomName VARCHAR(30),
   beds INTEGER,
   bedType VARCHAR(10),
   maxOccupancy INTEGER,
   basePrice FLOAT,
   decor VARCHAR(20),
   PRIMARY KEY(RoomId)
);

CREATE TABLE reservations (
   Code VARCHAR(20),
   Room VARCHAR(3),
   CheckIn DATE,
   CheckOut DATE,
   Rate FLOAT,
   LastName VARCHAR(20),
   FirstName VARCHAR(20),
   Adults INTEGER,
   Kids INTEGER,
   FOREIGN KEY(Room) REFERENCES rooms(RoomId)
);
