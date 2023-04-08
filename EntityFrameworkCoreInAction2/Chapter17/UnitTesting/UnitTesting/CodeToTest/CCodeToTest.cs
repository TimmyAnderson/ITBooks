﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UnitTesting
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCodeToTest
	{
//----------------------------------------------------------------------------------------------------------------------
		public CTestEntity[] Method1(CDBContext Context)
		{
			CTestEntity[]										Entities=Context.TestEntities.ToArray();

			return(Entities);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CTestEntity[] Method2(CDBContext Context, int Skip, int Take)
		{
			CTestEntity[]										Entities=Context.TestEntities.Skip(Skip).Take(Take).ToArray();

			return(Entities);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------