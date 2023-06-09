﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CPageNameProvider : IPageNameProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CPageName>				MNames;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPageNameProvider()
		{
			MObject=new object();
			MNames=new Dictionary<int,CPageName>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPageName AddName(CPageName Name)
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

				CPageName										ModifiedName=new CPageName(MaxID,Name.FirstName,Name.LastName,Name.Age);

				MNames.Add(ModifiedName.ID,ModifiedName);

				return(ModifiedName);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPageName UpdateName(CPageName Name)
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
		public CPageName GetName(int ID)
		{
			lock(MObject)
			{
				CPageName										Name;
					
				MNames.TryGetValue(ID,out Name);

				return(Name);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPageName[] GetNames()
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