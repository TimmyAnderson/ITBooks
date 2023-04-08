using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.JsonPatch;
using DocumentationUsingOpenAPI.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace DocumentationUsingOpenAPI.Database
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMemoryNameProvider : INameProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CName>					MNames;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CMemoryNameProvider()
		{
			MObject=new object();
			MNames=new Dictionary<int,CName>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CName AddName(CName Name)
		{
			lock(MObject)
			{
				int												MaxID=0;

				foreach(int ID in MNames.Keys)
				{
					if (ID>MaxID)
					{
						MaxID=ID;
					}
				}
				
				MaxID++;

				CName											ModifiedName=new CName(MaxID,Name.FirstName,Name.LastName,Name.Age);

				MNames.Add(ModifiedName.ID,ModifiedName);

				return(ModifiedName);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CName UpdateName(CName Name)
		{
			lock(MObject)
			{
				if (MNames.ContainsKey(Name.ID)==true)
				{
					MNames[Name.ID]=Name;

					return(Name);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public bool PatchName(int ID, JsonPatchDocument<CName> Patch)
		{
			lock(MObject)
			{
				CName											Name;
					
				if (MNames.TryGetValue(ID,out Name)==true)
				{
					Patch.ApplyTo(Name);

					return(true);
				}
				else
				{
					return(false);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void RemoveName(int ID)
		{
			lock(MObject)
			{
				MNames.Remove(ID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CName GetName(int ID)
		{
			lock(MObject)
			{
				CName											Name;
					
				MNames.TryGetValue(ID,out Name);

				return(Name);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CName[] GetNames()
		{
			lock(MObject)
			{
				return(MNames.Values.ToArray());
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------