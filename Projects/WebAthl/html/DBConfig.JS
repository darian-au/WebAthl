<script LANGUAGE="Javascript">
	<!--//

	document.onclick = doClick;

	function doClick()
	{	
		CheckDSN(document.DatabaseConfiguration.DSN)
		CheckDriver(document.DatabaseConfiguration.Driver)
	}	

	function CheckDSN(Target) 
	{
		if (Target.value != "(none)" ) 
		{
			document.DatabaseConfiguration.Driver.selectedIndex = 0 
		}
	}
	function CheckDriver(Target) 
	{
		if (Target.value != "DSN" ) 
		{
			document.DatabaseConfiguration.DSN.selectedIndex = 0 
		}
	}


	//-->
</script>
