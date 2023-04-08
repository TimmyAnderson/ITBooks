using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------
namespace DataProvidersTestLibrary
{
//------------------------------------------------------------------------
	// Sluzi ako Class Factory pre CName. Pouziva ju DataProvider.
	public class CNameClassFactory
	{
//------------------------------------------------------------------------
		private bool							MTimmy;
		private bool							MAtreyu;
		private bool							MJenny;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CNameClassFactory()
		{
		}
//------------------------------------------------------------------------
		public CNameClassFactory(bool Timmy, bool Atreyu, bool Jenny)
		{
			MTimmy=Timmy;
			MAtreyu=Atreyu;
			MJenny=Jenny;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CNameCollection CreateCollection1()
		{
			CNameCollection		Ret=new CNameCollection();

			if (MTimmy==true)
				Ret.Add(new CName("Timmy","Anderson",12));

			if (MAtreyu==true)
				Ret.Add(new CName("Atreyu","",12));

			if (MJenny==true)
				Ret.Add(new CName("Jenny","Thompson",13));

			return(Ret);
		}
//------------------------------------------------------------------------
		public CNameCollection CreateCollection2(bool Timmy, bool Atreyu, bool Jenny)
		{
			CNameCollection		Ret=new CNameCollection();

			if (Timmy==true)
				Ret.Add(new CName("Timmy","Anderson",12));

			if (Atreyu==true)
				Ret.Add(new CName("Atreyu","",12));

			if (Jenny==true)
				Ret.Add(new CName("Jenny","Thompson",13));

			return(Ret);
		}
//------------------------------------------------------------------------
		// Demonstruje pomale volanie - asynchro.
		public CNameCollection CreateCollection3(bool Timmy, bool Atreyu, bool Jenny)
		{
			Thread.Sleep(5*1000);

			CNameCollection		Ret=new CNameCollection();

			if (Timmy==true)
				Ret.Add(new CName("Timmy","Anderson",12));

			if (Atreyu==true)
				Ret.Add(new CName("Atreyu","",12));

			if (Jenny==true)
				Ret.Add(new CName("Jenny","Thompson",13));

			return(Ret);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------