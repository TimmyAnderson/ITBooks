using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DCEnumsLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CDCEnumsService : IDCEnumsContract
	{
//-------------------------------------------------------------------------------------------------------
		public CName GetName1()
		{
			return(new CName("Timmy","Anderson",ESex.E_S_MALE,ERace.E_R_HUMAN));
		}
//-------------------------------------------------------------------------------------------------------
		public CName GetName2()
		{
			return(new CName("Quazy","XB179",ESex.E_S_MALE,ERace.E_R_NON_HUMAN));
		}
//-------------------------------------------------------------------------------------------------------
		public CName GetName3()
		{
			// Hodi excpetion, lebo ERace.E_R_ROBOT ne neserializovatelny.
			return(new CName("Tina","Ming",ESex.E_S_FEMALE,ERace.E_R_ROBOT));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendName(CName Name)
		{
			Console.WriteLine(string.Format("From client: {0}",Name.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------