ALTER TABLE SeriesSeason ADD

	CONSTRAINT FK_SeriesSeason_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID)
