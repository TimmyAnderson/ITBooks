﻿//-------------------------------------------------------------------------------------------------------
function Pause(MS)
{
	MS+=new Date().getTime();
		
	while (new Date()<MS)
	{
	}
} 
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function SomeThreadFunction()
{
	for (var Counter=0;Counter<10;Counter++)
	{
		postMessage("WORKER THREAD MESSAGE [" + (Counter+1) + "] !");

		Pause(1000);

		if (Counter==5)
		{
			throw("EXCEPTION from WORKER THREAD !");
		}
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
SomeThreadFunction();
//-------------------------------------------------------------------------------------------------------