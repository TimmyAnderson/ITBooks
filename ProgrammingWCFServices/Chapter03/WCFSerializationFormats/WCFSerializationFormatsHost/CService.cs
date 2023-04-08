using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializationFormatsHost
{
//-------------------------------------------------------------------------------------------------------
	public class CService : IService
	{
//-------------------------------------------------------------------------------------------------------
		public CName1 Method1(CName1 Name1)
		{
			Console.WriteLine("Method1() CALLED !");

			return(Name1);
		}
//-------------------------------------------------------------------------------------------------------
		public CName2 Method2(CName2 Name2)
		{
			Console.WriteLine("Method2() CALLED !");

			return(Name2);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------