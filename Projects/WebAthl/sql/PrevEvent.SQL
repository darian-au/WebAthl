SELECT 	Event.*

FROM 	Event

WHERE 	SeriesID = %d AND 
	EventNo = (

	SELECT 	EventNo
	FROM 	Event
	WHERE 	SeriesID = %d AND 
		EventID = %d
	) - 1
