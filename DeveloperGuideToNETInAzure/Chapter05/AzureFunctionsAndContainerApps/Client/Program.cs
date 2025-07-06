//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	internal class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuAzureFunctions								Menu=new CMenuAzureFunctions();
			//CMenuDurableFunctionChaining						Menu=new CMenuDurableFunctionChaining();
			//CMenuDurableFanOutFanIn							Menu=new CMenuDurableFanOutFanIn();
			//CMenuDurableAsyncHttpAPIs							Menu=new CMenuDurableAsyncHttpAPIs();
			//CMenuDurableMonitoring							Menu=new CMenuDurableMonitoring();
			CMenuDurableHumanInteraction						Menu=new CMenuDurableHumanInteraction();
			//CMenuMyContainerApps								Menu=new CMenuMyContainerApps();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------