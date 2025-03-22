using System;
//----------------------------------------------------------------------------------------------------------------------
namespace OwnedTypes
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			//CMenuOneToOneOperations							Menu=new CMenuOneToOneOperations();
			//CMenuOneToManyOperations							Menu=new CMenuOneToManyOperations();
			//CMenuManyToManyOperations							Menu=new CMenuManyToManyOperations();
			//CMenuOwnedTypeOneToOneOperations					Menu=new CMenuOwnedTypeOneToOneOperations();
			CMenuOwnedTypeOneToManyOperations					Menu=new CMenuOwnedTypeOneToManyOperations();

			Menu.Execute();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------