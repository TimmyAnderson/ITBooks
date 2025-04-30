using System;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//--------------------------------------------------------------------------------------------------------------------------------
	internal class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuConcurrencyConcurrencyTokensOperations		Menu=new CMenuConcurrencyConcurrencyTokensOperations();
			//CMenuRawSqlOperations								Menu=new CMenuRawSqlOperations();
			//CMenuCRUDOperations								Menu=new CMenuCRUDOperations();
			//CMenuLINQOperations								Menu=new CMenuLINQOperations();
			CMenuBulkOperations									Menu=new CMenuBulkOperations();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------