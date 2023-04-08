using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CNameWithNoteProvider : INameWithNoteProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CNameWithNote>			MNames;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNameWithNoteProvider()
		{
			MObject=new object();
			MNames=new Dictionary<int,CNameWithNote>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNameWithNote AddName(CNameWithNote Name)
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

				CNameWithNote									ModifiedName=new CNameWithNote(MaxID,Name.FirstName,Name.LastName,Name.Age,Name.Note);

				MNames.Add(ModifiedName.ID,ModifiedName);

				return(ModifiedName);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNameWithNote UpdateName(CNameWithNote Name)
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
		public void RemoveName(int ID)
		{
			lock(MObject)
			{
				MNames.Remove(ID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNameWithNote GetName(int ID)
		{
			lock(MObject)
			{
				CNameWithNote									Name;
					
				MNames.TryGetValue(ID,out Name);

				return(Name);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CNameWithNote[] GetNames()
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