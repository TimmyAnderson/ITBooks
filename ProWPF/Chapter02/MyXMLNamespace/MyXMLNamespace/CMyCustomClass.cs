using System;
using System.Collections.Generic;
using System.Text;
//------------------------------------------------------------------------
namespace MyXMLNamespace
{
//------------------------------------------------------------------------
	public class CMyCustomClass
	{
//------------------------------------------------------------------------
		private	string						MSomeData="Empty !";
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string						SomeData
		{
			get
			{
				return(MSomeData);
			}
			set
			{
				MSomeData=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("Value='{0}'",MSomeData));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------