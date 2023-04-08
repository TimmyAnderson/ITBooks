using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SharedLibrary1;
using SharedLibrary2;
using SharedLibrary3;
//-------------------------------------------------------------------------------------------------------
namespace DataContractResolversService
{
//-------------------------------------------------------------------------------------------------------
	public class CTestService : ITestService
	{
//-------------------------------------------------------------------------------------------------------
		public void ConnectionTest()
		{
			Console.WriteLine("TEST SUCCEEDED !");
		}
//-------------------------------------------------------------------------------------------------------
		public CNameBase ReceiveName(int Version)
		{
			if (Version==1)
			{
				CNameBase								Name=new CNameBase("Timmy");

				return(Name);
			}
			else if (Version==2)
			{
				CName									Name=new CName("Timmy","Anderson");

				return(Name);
			}
			else
			{
				CNameInfo								Name=new CNameInfo("Timmy","Anderson",12);

				return(Name);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CNameBaseGenerics<string> ReceiveGenericsName(int Version)
		{
			if (Version==1)
			{
				CNameBaseGenerics<string>				Name=new CNameBaseGenerics<string>("Timmy");

				return(Name);
			}
			else if (Version==2)
			{
				CNameGenerics<string,string>			Name=new CNameGenerics<string,string>("Timmy","Anderson");

				return(Name);
			}
			else
			{
				CNameInfoGenerics<string,string,int>	Name=new CNameInfoGenerics<string,string,int>("Timmy","Anderson",12);

				return(Name);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void SendName(CNameBase Name)
		{
			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendGenericsName(CNameBaseGenerics<string> Name)
		{
			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------