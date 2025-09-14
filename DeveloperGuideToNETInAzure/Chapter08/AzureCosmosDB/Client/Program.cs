using System;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuCosmosDBInfrastrucutre						Menu=new CMenuCosmosDBInfrastrucutre();
			//CMenuCosmosDBItemsSameType						Menu=new CMenuCosmosDBItemsSameType();
			//CMenuCosmosDBItemsDifferentTypes					Menu=new CMenuCosmosDBItemsDifferentTypes();
			//CMenuCosmosDBNamesWebLocal						Menu=new CMenuCosmosDBNamesWebLocal();
			CMenuCosmosDBColdStartProblemAndConnectionModes		Menu=new CMenuCosmosDBColdStartProblemAndConnectionModes();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------