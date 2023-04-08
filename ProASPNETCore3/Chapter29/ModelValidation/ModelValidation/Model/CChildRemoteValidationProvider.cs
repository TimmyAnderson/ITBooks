using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CChildRemoteValidationProvider : IChildRemoteValidationProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CChildRemoteValidation>	MChildren;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidationProvider()
		{
			MObject=new object();
			MChildren=new Dictionary<int,CChildRemoteValidation>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidation AddChild(CChildRemoteValidation Child)
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

				CChildRemoteValidation							ModifiedChild=new CChildRemoteValidation(MaxID,Child.FirstName,Child.LastName,Child.Age,Child.Sex);

				MChildren.Add(ModifiedChild.ID,ModifiedChild);

				return(ModifiedChild);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidation UpdateChild(CChildRemoteValidation Child)
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
		public CChildRemoteValidation GetChild(int ID)
		{
			lock(MObject)
			{
				CChildRemoteValidation											Child;
					
				MChildren.TryGetValue(ID,out Child);

				return(Child);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildRemoteValidation[] GetChildren()
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