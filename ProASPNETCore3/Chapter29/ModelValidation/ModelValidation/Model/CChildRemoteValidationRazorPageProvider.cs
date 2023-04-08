using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CChildRemoteValidationRazorPageProvider : IChildRemoteValidationRazorPageProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CChildRemoteValidationRazorPage>	MChildren;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationRazorPageProvider()
		{
			MObject=new object();
			MChildren=new Dictionary<int,CChildRemoteValidationRazorPage>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationRazorPage AddChild(CChildRemoteValidationRazorPage Child)
		{
			lock(MObject)
			{
				int												MaxID=0;

				foreach(int ID in MChildren.Keys)
				{
					if (ID>MaxID)
					{
						MaxID=ID;
					}
				}
				
				MaxID++;

				CChildRemoteValidationRazorPage					ModifiedChild=new CChildRemoteValidationRazorPage(MaxID,Child.FirstName,Child.LastName,Child.Age,Child.Sex);

				MChildren.Add(ModifiedChild.ID,ModifiedChild);

				return(ModifiedChild);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationRazorPage UpdateChild(CChildRemoteValidationRazorPage Child)
		{
			lock(MObject)
			{
				if (MChildren.ContainsKey(Child.ID)==true)
				{
					MChildren[Child.ID]=Child;

					return(Child);
				}
				else
				{
					return(null);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void RemoveChild(int ID)
		{
			lock(MObject)
			{
				MChildren.Remove(ID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationRazorPage GetChild(int ID)
		{
			lock(MObject)
			{
				CChildRemoteValidationRazorPage											Child;
					
				MChildren.TryGetValue(ID,out Child);

				return(Child);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationRazorPage[] GetChildren()
		{
			lock(MObject)
			{
				return(MChildren.Values.ToArray());
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------