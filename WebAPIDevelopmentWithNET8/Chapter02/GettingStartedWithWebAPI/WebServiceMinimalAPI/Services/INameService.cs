﻿//--------------------------------------------------------------------------------------------------------------------------------
namespace WebServiceMinimalAPI
{
//--------------------------------------------------------------------------------------------------------------------------------
	public interface INameService
	{
//--------------------------------------------------------------------------------------------------------------------------------
		CName[] GetNames();
		CName GetName(int ID);
		CName AddName(string FirstName, string LastName, int Age);
		CName UpdateName(CName Name);
		bool DeleteName(int ID);
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------