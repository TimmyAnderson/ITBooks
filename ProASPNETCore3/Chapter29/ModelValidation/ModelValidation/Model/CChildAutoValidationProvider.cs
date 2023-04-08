using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CChildAutoValidationProvider : IChildAutoValidationProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CChildAutoValidation>	MChildren;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildAutoValidationProvider()
		{
			MObject=new object();
			MChildren=new Dictionary<int,CChildAutoValidation>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildAutoValidation AddChild(CChildAutoValidation Child)
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

				CChildAutoValidation							ModifiedChild=new CChildAutoValidation(MaxID,Child.FirstName,Child.LastName,Child.Age,Child.Sex);

				MChildren.Add(ModifiedChild.ID,ModifiedChild);

				return(ModifiedChild);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildAutoValidation UpdateChild(CChildAutoValidation Child)
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
		public CChildAutoValidation GetChild(int ID)
		{
			lock(MObject)
			{
				CChildAutoValidation											Child;
					
				MChildren.TryGetValue(ID,out Child);

				return(Child);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChildAutoValidation[] GetChildren()
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