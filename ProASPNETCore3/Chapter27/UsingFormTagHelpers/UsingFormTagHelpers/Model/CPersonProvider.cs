using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CPersonProvider : IPersonProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CPerson>				MPersons;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPersonProvider()
		{
			MObject=new object();
			MPersons=new Dictionary<int,CPerson>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPerson AddPerson(CPerson Person)
		{
			lock(MObject)
			{
				int												MaxID=0;

				foreach(int ID in MPersons.Keys)
				{
					if (ID>MaxID)
					{
						MaxID=ID;
					}
				}
				
				MaxID++;

				CPerson											ModifiedPerson=new CPerson(MaxID,Person.FirstName,Person.LastName,Person.Age,Person.Psi,Person.Height);

				MPersons.Add(ModifiedPerson.ID,ModifiedPerson);

				return(ModifiedPerson);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson UpdatePerson(CPerson Person)
		{
			lock(MObject)
			{
				if (MPersons.ContainsKey(Person.ID)==true)
				{
					MPersons[Person.ID]=Person;

					return(Person);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void RemovePerson(int ID)
		{
			lock(MObject)
			{
				MPersons.Remove(ID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson GetPerson(int ID)
		{
			lock(MObject)
			{
				CPerson											Person;
					
				MPersons.TryGetValue(ID,out Person);

				return(Person);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson[] GetPersons()
		{
			lock(MObject)
			{
				return(MPersons.Values.ToArray());
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------