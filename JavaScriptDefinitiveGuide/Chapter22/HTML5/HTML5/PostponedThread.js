//-------------------------------------------------------------------------------------------------------
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
	}

	// !!! Ukonci WORKER THREAD. Nie je to nutne, staci aj to, ze THREAD SCRIPT regulerne skonci.
	close();
}
//-------------------------------------------------------------------------------------------------------
this.onmessage=function(Message)
{
	postMessage("MESSAGE [" + Message.data + "] form MAIN THREAD RECEIVED !");

	// !!! Kod sa spusti AZ po PRICHODE MESSAGE.
	for (var Counter=0;Counter<10;Counter++)
	{
		postMessage("WORKER THREAD MESSAGE [" + (Counter+1) + "] !");

		Pause(1000);
	}

	// !!! Ukonci WORKER THREAD. Nie je to nutne, staci aj to, ze THREAD SCRIPT regulerne skonci.
	close();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! UMYSELNE NESPUSTAM v GLOBAL NAMESPACE ZIADEN KOD.
//SomeThreadFunction();
//-------------------------------------------------------------------------------------------------------