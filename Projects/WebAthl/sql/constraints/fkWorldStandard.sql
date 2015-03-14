ALTER TABLE WorldStandard ADD

	CONSTRAINT FK_WorldStandard_EventTypeID 
	FOREIGN KEY (EventTypeID) 
	REFERENCES EventType (EventTypeID)
