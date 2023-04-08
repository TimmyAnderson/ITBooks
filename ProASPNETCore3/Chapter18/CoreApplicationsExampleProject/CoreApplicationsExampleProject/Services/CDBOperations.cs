using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using CoreApplicationsExampleProject.Database;
using CoreApplicationsExampleProject.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace CoreApplicationsExampleProject.Services
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBOperations : IDBOperations
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBOperations(CDBContext Context)
		{
			MContext=Context;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPerson AddPerson(CPerson Person)
		{
			CEntityPerson										EntityPerson=new CEntityPerson(Person);

			MContext.Persons.Add(EntityPerson);

			MContext.SaveChanges();

			CPerson												AddedPerson=EntityPerson.ToPerson();

			return(AddedPerson);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson UpdatePerson(CPerson Person)
		{
			CEntityPerson										EntityPerson=MContext.Persons.Where(P => P.ID==Person.ID).FirstOrDefault();

			if (EntityPerson==null)
			{
				return(null);
			}

			EntityPerson.FirstName=Person.FirstName;
			EntityPerson.LastName=Person.LastName;
			EntityPerson.Age=Person.Age;
			EntityPerson.Sex=(int) Person.Sex;
			EntityPerson.City=Person.Address.City;
			EntityPerson.Country=Person.Address.Country;

			MContext.SaveChanges();

			CPerson												UpdatedPerson=EntityPerson.ToPerson();

			return(UpdatedPerson);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void RemovePerson(int ID)
		{
			CEntityPerson										EntityPerson=MContext.Persons.Where(P => P.ID==ID).FirstOrDefault();

			if (EntityPerson!=null)
			{
				MContext.Remove(EntityPerson);

				MContext.SaveChanges();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson GetPerson(int ID)
		{
			CEntityPerson										EntityPerson=MContext.Persons.Where(P => P.ID==ID).FirstOrDefault();

			if (EntityPerson!=null)
			{
				CPerson											Person=EntityPerson.ToPerson();

				return(Person);
			}
			else
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson[] GetPersons()
		{
			CEntityPerson[]										EntityPersons=MContext.Persons.ToArray();
			CPerson[]											Persons=EntityPersons.Select(P => P.ToPerson()).ToArray();

			return(Persons);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------