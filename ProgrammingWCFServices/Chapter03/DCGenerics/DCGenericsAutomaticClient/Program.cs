using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCGenericsAutomaticClient.CDCGenericsProxy;
//-------------------------------------------------------------------------------------------------------
// Mena tried v Proxy: CGenericClass1Ofint, CGenericClass1OfCNamemd1vdT_PP, CGenericClass2, CGenericClass3_CName, CGenericClass4_CName_Hash_md1vdT_PP.
//-------------------------------------------------------------------------------------------------------
namespace DCGenericsAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static string CFullNameToString(CName Name)
		{
			return(string.Format("CName - FirstName: {0}, LastName: {1} !",Name.FirstName, Name.LastName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			DCGenericsContractOf_StringClient	Client=null;
			int									IntIn=987;
			CGenericClass1Ofstring				GenericsIn=new CGenericClass1Ofstring(){Data="Timmy Anderson"};
			CName								NameIn1=new CName();
			CName								NameIn2=new CName();
			CName								NameIn3=new CName();
			CName								NameIn4=new CName();
			CGenericClass1Ofint					ParamInt=new CGenericClass1Ofint();
			CGenericClass1OfCNamemd1vdT_PP		ParamName1=new CGenericClass1OfCNamemd1vdT_PP();
			CGenericClass2						ParamName2=new CGenericClass2();
			CGenericClass3_CName				ParamName3=new CGenericClass3_CName();
			CGenericClass4_CName_Hash_md1vdT_PP	ParamName4=new CGenericClass4_CName_Hash_md1vdT_PP();

			NameIn1.FirstName="Timmy";
			NameIn1.LastName="Anderson";

			NameIn2.FirstName="Jenny";
			NameIn2.LastName="Thompson";

			NameIn3.FirstName="Quazy";
			NameIn3.LastName="XB179";

			NameIn4.FirstName="Tina";
			NameIn4.LastName="Ming";

			ParamInt.Data=IntIn;
			ParamName1.Data=NameIn1;
			ParamName2.Data=NameIn2;
			ParamName3.Data=NameIn3;
			ParamName4.Data=NameIn4;

			try
			{
				Client=new DCGenericsContractOf_StringClient("NetTcpBinding_IDCGenericsContractOf_String");

				Client.SendInt(ParamInt);
				Console.WriteLine(string.Format("Client send IntIn: {0} !",IntIn.ToString()));
				Console.WriteLine();

				Client.SendGenerics(GenericsIn);
				Console.WriteLine(string.Format("Client send GenericsIn: {0} !",GenericsIn.Data));
				Console.WriteLine();

				Client.SendCName1(ParamName1);
				Console.WriteLine(string.Format("Client send NameIn1: {0} !",CFullNameToString(NameIn1)));
				Console.WriteLine();

				Client.SendCName2(ParamName2);
				Console.WriteLine(string.Format("Client send NameIn2: {0} !",CFullNameToString(NameIn2)));
				Console.WriteLine();

				Client.SendCName3(ParamName3);
				Console.WriteLine(string.Format("Client send NameIn3: {0} !",CFullNameToString(NameIn3)));
				Console.WriteLine();

				Client.SendCName4(ParamName4);
				Console.WriteLine(string.Format("Client send NameIn4: {0} !",CFullNameToString(NameIn4)));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------