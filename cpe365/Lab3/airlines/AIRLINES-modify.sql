-- Ryan Blair rablair@calpoly.edu

-- Delete all flights not going to or from 'AKI'
DELETE FROM flights
   WHERE (SourceAirport != 'AKI'
      AND DestAirport != 'AKI');

-- Increase flight no of flights not operated by Continental, AirTran or Virgin
UPDATE flights
   SET FlightNo = FlightNo + 2000
   WHERE Airline != 7
      OR Airline != 10
      OR Airline != 12;

-- Swap FlightNo of To, From flights
ALTER TABLE flights
   ADD COLUMN (newFlightNo INTEGER);

UPDATE flights
   SET newFlightNo = FlightNo + 3001
   WHERE (Airline != 7
      AND Airline != 10
      AND Airline != 12)
   AND MOD(FlightNo, 2) = 0;

UPDATE flights
   SET newFlightNo = FlightNo +  2999
   WHERE (Airline != 7
      AND Airline != 10
      AND Airline != 12)
   AND MOD(FlightNo, 2) = 1;

UPDATE flights
   SET FlightNo = newFlightNo
   WHERE newFlightNo IS NOT NULL;

UPDATE flights
   SET FlightNo = FlightNo - 3000
   WHERE newFlightNo IS NOT NULL;

ALTER TABLE flights
   DROP COLUMN newFlightNo;

SELECT * FROM flights
ORDER BY Airline, FlightNo;

-- Complete takeover by Substituting Continental to flights on 10 or 12
-- that don't flight to or from 'AKI'
UPDATE flights
   SET Airline = 7
   WHERE (Airline != 10 
      AND Airline != 12);

-- finish query
SELECT * FROM flights
ORDER BY Airline, FlightNo;
