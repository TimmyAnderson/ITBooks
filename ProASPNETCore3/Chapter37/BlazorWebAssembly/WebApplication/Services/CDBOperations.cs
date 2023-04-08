using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using SharedClasses.Classes;
using WebApplication.Database;
//----------------------------------------------------------------------------------------------------------------------
namespace WebApplication.Services
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBOperations : IDBOperations
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CDBContext								MContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBOperations()
		{
			MContext=new CDBContext();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext										Context
		{
			get
			{
				return(MContext);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPerson AddPerson(CPerson Person)
		{
			CEntityPerson										EntityPerson=new CEntityPerson(Person);

			MContext.Persons.Add(EntityPerson);

			MContext.SaveChanges();

			return(Person);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson UpdatePerson(CPerson Person)
		{
			CEntityPerson										EntityPerson=MContext.Persons.Where(P => P.ID==Person.ID).FirstOrDefault();

			if (EntityPerson!=null)
			{
				EntityPerson.FirstName=Person.FirstName;
				EntityPerson.LastName=Person.LastName;
				EntityPerson.Age=Person.Age;
				EntityPerson.Sex=(int) Person.Sex;

				MContext.SaveChanges();

				return(Person);
			}
			else
			{
				return(null);
			}
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
			List<CPerson>										Persons=new List<CPerson>();

			foreach(CEntityPerson EntityPerson in EntityPersons)
			{
				Persons.Add(EntityPerson.ToPerson());
			}

			return(Persons.ToArray());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------