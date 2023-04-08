using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CChildProvider : IChildProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CChild>					MChildren;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChildProvider()
		{
			MObject=new object();
			MChildren=new Dictionary<int,CChild>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CChild AddChild(CChild Child)
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

				CChildAddress									ModifiedAddress=null;

				if (Child.Address!=null)
				{
					ModifiedAddress=new CChildAddress(Child.Address.City,Child.Address.Country);
				}

				CChild											ModifiedChild=new CChild(MaxID,Child.FirstName,Child.LastName,Child.Age,Child.Sex,ModifiedAddress);

				MChildren.Add(ModifiedChild.ID,ModifiedChild);

				return(ModifiedChild);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChild UpdateChild(CChild Child)
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
		public CChild GetChild(int ID)
		{
			lock(MObject)
			{
				CChild											Child;
					
				MChildren.TryGetValue(ID,out Child);

				return(Child);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChild[] GetChildren()
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