using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Collections.ObjectModel;
//------------------------------------------------------------------------
namespace SharedLibrary
{
//------------------------------------------------------------------------
	public class CMyCollectionClass : IList
	{
//------------------------------------------------------------------------
		private ArrayList			MAL=new ArrayList();
		private string				MName;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		public CMyCollectionClass()
		{
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string				Name
		{
			get
			{
				return(MName);
			}
			set
			{
				MName=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public bool					IsFixedSize
		{
			get
			{
				ShowMethodName();
				return(MAL.IsFixedSize);
			}
		}
//------------------------------------------------------------------------
		public bool					IsReadOnly
		{
			get
			{
				ShowMethodName();
				return(MAL.IsReadOnly);
			}
		}
//------------------------------------------------------------------------
		public int					Count
		{
			get
			{
				ShowMethodName();
				return(MAL.Count);
			}
		}
//------------------------------------------------------------------------
		public bool					IsSynchronized
		{
			get
			{
				ShowMethodName();
				return(MAL.IsSynchronized);
			}
		}
//------------------------------------------------------------------------
		public object				SyncRoot
		{
			get
			{
				ShowMethodName();
				return(MAL.SyncRoot);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public object				this[int Index]
		{
			get
			{
				ShowMethodName();
				return(MAL[Index]);
			}
			set
			{
				ShowMethodName();
				MAL[Index]=value;
			}
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private string GetTypeNameWOArity(string Name)
		{
			int		Position;

			if ((Position=Name.LastIndexOf('`'))!=-1)
				return(Name.Remove(Position));
			else
				return(Name);
		}
//-----------------------------------------------------------------------------
		// Vrati meno triedy s generic parametrami, alebo iba do urovne 1.
		private string GetTypeName(Type Type)
		{
			Type[]				GenericTypes=Type.GetGenericArguments();

			if (GenericTypes.Length==0)
				return(Type.Name);

			StringBuilder		SB=new StringBuilder();

			SB.Append(GetTypeNameWOArity(Type.Name));
			SB.Append("<");

			for (int i=0;i<GenericTypes.Length;i++)
			{
				if (i!=0)
					SB.Append(",");

				SB.Append(GenericTypes[i].Name);
			}

			SB.Append(">");

			return(SB.ToString());
		}
//------------------------------------------------------------------------
		private void ShowMethodName()
		{
			StackFrame		SF=new StackFrame(1);

			Debug.WriteLine(string.Format("!!! {0}.{1}() CALLED !",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public int Add(object Value)
		{
			ShowMethodName();

			Debug.WriteLine(string.Format("!!! Value: ({0}) ADDED to {1} !",Value,MName));

			return(MAL.Add(Value));
		}
//------------------------------------------------------------------------
		public void Clear()
		{
			ShowMethodName();
			MAL.Clear();
		}
//------------------------------------------------------------------------
		public bool Contains(object Value)
		{
			ShowMethodName();
			return(MAL.Contains(Value));
		}
//------------------------------------------------------------------------
		public int IndexOf(object Value)
		{
			ShowMethodName();
			return(MAL.IndexOf(Value));
		}
//------------------------------------------------------------------------
		public void Insert(int Index, object Value)
		{
			ShowMethodName();
			MAL.Insert(Index, Value);
		}
//------------------------------------------------------------------------
		public void Remove(object Value)
		{
			ShowMethodName();
			MAL.Remove(Value);
		}
//------------------------------------------------------------------------
		public void RemoveAt(int Index)
		{
			ShowMethodName();
			MAL.RemoveAt(Index);
		}
//------------------------------------------------------------------------
		public void CopyTo(Array Array, int Index)
		{
			ShowMethodName();
			MAL.CopyTo(Array,Index);
		}
//------------------------------------------------------------------------
		public IEnumerator GetEnumerator()
		{
			ShowMethodName();
			return(MAL.GetEnumerator());
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("There are: {0} ITEMS !",Count));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------