SELECT 	*

FROM 	Results

WHERE 	(Results.SeriesID = %d ) AND 
	(Results.EventID = %d )

ORDER BY 
	Results.GrossPerformanceHOUR %s , 
	Results.GrossPerformanceMIN %s , 
	Results.GrossPerformanceSEC %s , 
	Results.Place
