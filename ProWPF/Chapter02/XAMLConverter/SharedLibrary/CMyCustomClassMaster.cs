using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
//------------------------------------------------------------------------
namespace SharedLibrary
{
//------------------------------------------------------------------------
	public class CMyCustomClassMaster
	{
//------------------------------------------------------------------------
		private CMyCustomClassSlave1	MSlaveValue1;
		private CMyCustomClassSlave2	MSlaveValue2;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyCustomClassSlave1		SlaveValue1
		{
			get
			{
				return(MSlaveValue1);
			}
			set
			{
				MSlaveValue1=value;
			}
		}
//------------------------------------------------------------------------
		[TypeConverter(typeof(CMyCustomClassSlaveConverter2))]
		public CMyCustomClassSlave2		SlaveValue2
		{
			get
			{
				return(MSlaveValue2);
			}
			set
			{
				MSlaveValue2=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override string ToString()
		{
			string		Ret=string.Format("Slave Value 1: ({0}), Slave Value 2: ({1}) !",MSlaveValue1,MSlaveValue2);

			return(Ret);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------