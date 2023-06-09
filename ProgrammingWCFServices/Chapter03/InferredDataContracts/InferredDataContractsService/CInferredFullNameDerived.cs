﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace InferredDataContractsService
{
//-------------------------------------------------------------------------------------------------------
	public class CInferredFullNameDerived : CInferredFullName
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSomeInfo;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInferredFullNameDerived()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CInferredFullNameDerived(string FirstName, string LastName, int Age, string SomeInfo)
			: base(FirstName, LastName, Age)
		{
			MSomeInfo=SomeInfo;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											SomeInfo
		{
			get
			{
				Console.WriteLine("SomeInfo - get !");

				return(MSomeInfo);
			}
			set
			{
				Console.WriteLine("SomeInfo - set !");

				MSomeInfo=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("FN: {0}, SomeInfo: {1}",base.ToString(),MSomeInfo));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------