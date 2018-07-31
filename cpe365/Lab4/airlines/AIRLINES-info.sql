-- Ryan Blair rablair@calpoly.edu

-- All airlines w/ at least 1 flight out of 'AXX'
SELECT DISTINCT a.Name, a.Abbr
FROM airlines a, flights f
WHERE a.Id = f.Airline
AND f.Source = 'AXX'
ORDER BY a.Name;

-- All destinations served from 'AXX' by 'Northwest'
SELECT f.FlightNo, air.Code, air.Name
FROM airlines a, airports air, flights f
WHERE a.Id = f.Airline
AND f.Destination = air.Code
AND a.Abbr = 'Northwest'
AND f.Source = 'AXX'
ORDER BY f.FlightNo;

-- Other destinations with exactly one change-over
SELECT f1.FlightNo, f2.FlightNo, f2.Destination, a.Name
FROM airlines a, airports air, flights f1, flights f2
WHERE a.Id = f1.Airline
AND a.Id = f2.Airline
AND f1.Destination = f2.Source
AND a.Abbr = 'Northwest'
AND f1.Source = 'AXX'
AND f2.Destination != 'AXX'
AND air.Code = f2.Destination
ORDER BY f2.Destination;

-- All pairs airports served by 'Frontier', 'JetBlue'; no redundants
SELECT DISTINCT fF.Source, fF.Destination
FROM airlines aF, airlines aJ, flights fF, flights fJ
WHERE aF.Id = fF.Airline
AND aJ.Id - fJ.Airline
AND aF.Abbr = 'Frontier'
AND aJ.Abbr = 'JetBlue'
AND fF.Source = fJ.Source
AND fF.Destination = fJ.Destination
AND fF.Source < fF.Destination
AND fJ.Source < fJ.Destination;

-- All airports served by Delta, Frontier, USAir, UAL, and Southwest
SELECT DISTINCT fF.Source AS 'Airports'
FROM airlines aD, airlines aF, airlines aAir, airlines aUAL, airlines aSW, 
     flights fD, flights fF, flights fAir, flights fUAL, flights fSW
WHERE aD.Id = fD.Airline
AND aF.Id = fF.Airline
AND aAir.Id = fAir.Airline
AND aUAL.Id = fUAL.Airline
AND aSW.Id = fSW.Airline
AND fD.Source = fF.Source
AND fF.Source = fAir.Source
AND fAir.Source = fUAL.Source
AND fUAL.Source = fSW.Source
AND aD.Abbr = 'Delta'
AND aF.Abbr = 'Frontier' 
AND aAir.Abbr = 'USAir' 
AND aUAL.Abbr = 'UAL' 
AND aSW.Abbr = 'Southwest' 
ORDER BY Airports;

-- All airports served by at least 3 Southwest flights
SELECT DISTINCT f1.Source as 'Airports'
FROM airlines a, flights f1, flights f2, flights f3
WHERE a.Id = f1.Airline
AND a.Id = f2.Airline
AND a.Id = f3.Airline
AND a.Abbr = 'Southwest'
AND f1.Source = f2.Source
AND f2.Source = f3.Source
AND f1.FlightNo != f2.FlightNo
AND f2.FlightNo != f3.FlightNo
AND f1.FlightNo != f3.FlightNo
ORDER BY Airports;

