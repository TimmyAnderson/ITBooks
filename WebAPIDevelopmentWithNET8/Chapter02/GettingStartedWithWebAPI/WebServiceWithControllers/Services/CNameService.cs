using System.Linq;
using System.Collections.Generic;
//--------------------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CNameService : INameService
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly static object							MLock;
		private static int										MCurrentID;
		private readonly static List<CName>						MStorage;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		static CNameService()
		{
			MLock=new object();

			MCurrentID=1;

			MStorage=new List<CName>();

			MStorage.Add(new CName(MCurrentID++,"Timmy","Anderson",12));
			MStorage.Add(new CName(MCurrentID++,"Jenny","Thompson",13));
			MStorage.Add(new CName(MCurrentID++,"Lucas","Jones",13));
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CName[] GetNames()
		{
			CName[]												Names=MStorage.ToArray();

			return(Names);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CName GetName(int ID)
		{
			CName												ExistingName=MStorage.Where(P => P.ID==ID).FirstOrDefault();

			return(ExistingName);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CName AddName(string FirstName, string LastName, int Age)
		{
			lock(MLock)
			{
				CName											Name=new CName(MCurrentID++,FirstName,LastName,Age);

				MStorage.Add(Name);

				return(Name);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CName UpdateName(CName Name)
		{
			CName												ExistingName=MStorage.Where(P => P.ID==Name.ID).FirstOrDefault();

			if (ExistingName!=null)
			{
				ExistingName.FirstName=Name.FirstName;
				ExistingName.LastName=Name.LastName;
				ExistingName.Age=Name.Age;
			}

			return(ExistingName);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public bool DeleteName(int ID)
		{
			int													ExistingNameIndex=MStorage.FindIndex(P => P.ID==ID);

			if (ExistingNameIndex>=0)
			{
				MStorage.RemoveAt(ExistingNameIndex);

				return(true);
			}
			else
			{
				return(false);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------