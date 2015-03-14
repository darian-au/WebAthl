SELECT 	r.SeriesID, 
	r.EventID, r.PersonID, 
	r.AgeGroup, 
	e.DateDAY, e.DateMONTH, e.DateYEAR,
	e.DateAgeDAY, e.DateAgeMONTH, e.DateAgeYEAR,
	p.dobDAY, p.dobMONTH, p.dobYEAR
FROM 	%s r, Event e, Person p
WHERE	r.PersonID = p.PersonID
AND 	r.SeriesID = e.SeriesID
AND 	r.EventID  = e.EventID
AND 	r.SeriesID = %d
