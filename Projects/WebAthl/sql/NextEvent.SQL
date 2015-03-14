SELECT 	Event.*

FROM 	Event

WHERE 	SeriesID = %s AND 
	EventNo = (

	SELECT 	EventNo
	FROM 	Event
	WHERE 	SeriesID = %s AND 
		EventID = %s
	) + 1
