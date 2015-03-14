SELECT 	Event.*, 
	EventType.*, 
	Groups.*, 
	Location.*, 
	Organisation.*, 
	Person.*, 
	Results.*, 
	Series.*

FROM 	Location INNER JOIN 
	(
		Series INNER JOIN 
		(
			EventType INNER JOIN 
			(
				(
					(
						Person INNER JOIN 
						(
							Results LEFT JOIN 

								Organisation ON 

									Results.OrgID = Organisation.OrgID

						) ON 

							Person.PersonID = Results.PersonID

					) INNER JOIN Groups ON 

						(Results.GroupIDSupposedTo = Groups.GroupID) AND (Results.SeriesID = Groups.SeriesID)

				) INNER JOIN Event ON 

					(Groups.EventTypeID = Event.EventTypeID) AND (Results.SeriesID = Event.SeriesID) AND (Groups.SeriesID = Event.SeriesID) AND (Results.EventID = Event.EventID)

			) ON 

				(EventType.EventTypeID = Event.EventTypeID) AND (EventType.EventTypeID = Groups.EventTypeID)

		) ON 

			(Series.SeriesID = Results.SeriesID) AND (Series.SeriesID = Groups.SeriesID) AND (Series.SeriesID = Event.SeriesID)

	) ON 

		Location.LocationID = Event.LocationID



