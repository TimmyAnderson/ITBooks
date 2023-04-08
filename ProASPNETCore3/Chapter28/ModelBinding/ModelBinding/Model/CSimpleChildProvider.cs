using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSimpleChildProvider : ISimpleChildProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly object									MObject;
		private readonly Dictionary<int,CSimpleChild>			MChildren;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChildProvider()
		{
			MObject=new object();
			MChildren=new Dictionary<int,CSimpleChild>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChild AddChild(CSimpleChild Child)
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

				CSimpleChild											ModifiedChild=new CSimpleChild(MaxID,Child.FirstName,Child.LastName,Child.Age,Child.Sex);

				MChildren.Add(ModifiedChild.ID,ModifiedChild);

				return(ModifiedChild);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChild UpdateChild(CSimpleChild Child)
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
		public CSimpleChild GetChild(int ID)
		{
			lock(MObject)
			{
				CSimpleChild											Child;
					
				MChildren.TryGetValue(ID,out Child);

				return(Child);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleChild[] GetChildren()
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