SELECT 
	Person.*, 
	Financial.*, 
	RegistrationType.*, 
	Organisation.*

FROM
 	(
		RegistrationType INNER JOIN 
		(
			Person INNER JOIN 

				Financial ON 

					Person.PersonID = Financial.PersonID
		) ON 

			RegistrationType.RegistrationTypeID = Financial.RegistrationTypeID

	) LEFT JOIN 

		Organisation ON 

			Financial.OrgID = Organisation.OrgID

WHERE 
	(Person.PersonID=%s)

ORDER BY 
	Financial.Year DESC
