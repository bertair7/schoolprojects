# Ryan Blair
# TR Section

CREATE TABLE campuses (
   Id INTEGER UNIQUE,
   Campus VARCHAR(50),
   Location VARCHAR(20),
   County VARCHAR(30),
   Year INTEGER,
   PRIMARY KEY(Id)
);

CREATE TABLE csu_fees (
   Campus INTEGER,
   Year INTEGER,
   CampusFee FLOAT,
   FOREIGN KEY(Campus) REFERENCES campuses(Id)
);

CREATE TABLE degrees (
   Year INTEGER,
   Campus INTEGER,
   Degrees INTEGER,
   FOREIGN KEY(Campus) REFERENCES campuses(Id)
);

CREATE TABLE disciplines (
   Id INTEGER UNIQUE,
   Name VARCHAR(40),
   PRIMARY KEY(Id)
);

CREATE TABLE discipline_enrollments (
   Campus INTEGER,
   Discipline INTEGER REFERENCES disciplines(Id),
   Year INTEGER,
   Undergraduate INTEGER,
   Graduate INTEGER,
   FOREIGN KEY(Campus) REFERENCES campuses(Id)
);

CREATE TABLE enrollments (
   Campus INTEGER,
   Year INTEGER,
   TotalEnrollment_AY INTEGER,
   FTE_AY INTEGER,
   FOREIGN KEY(Campus) REFERENCES campuses(Id)
);

CREATE TABLE faculty (
   Campus INTEGER,
   Year INTEGER,
   Faculty INTEGER,
   FOREIGN KEY(Campus) REFERENCES campuses(Id)
);
