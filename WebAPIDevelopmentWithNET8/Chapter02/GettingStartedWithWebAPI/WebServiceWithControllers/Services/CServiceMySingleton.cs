﻿using System;
//--------------------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CServiceMySingleton : IServiceMySingleton
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly int									MValue;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CServiceMySingleton()
		{
			Random												Random=new Random();

			MValue=Random.Next(1000);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public int GetValue()
		{
			return(MValue);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------