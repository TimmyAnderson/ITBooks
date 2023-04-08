using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializationFormatsHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST";

			string								Address="net.tcp://localhost:8000/Service";
			Binding								B=new NetTcpBinding();

			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CService), new Uri(Address)))
				{
					try
					{
						SH.AddServiceEndpoint(typeof(IService), B,"");

						// !!!!! Pridam Contract BH.
						foreach(ServiceEndpoint SE in SH.Description.Endpoints)
							SE.Contract.Behaviors.Add(new CMyDispatchMessageInspectorBehavior());

						foreach(OperationDescription OD in SH.Description.Endpoints[0].Contract.Operations)
						{
							Console.WriteLine("");
							Console.WriteLine(string.Format("Operation {0}:",OD.Name));

							if (OD.Behaviors.Find<XmlSerializerOperationBehavior>()!=null)
								Console.WriteLine(string.Format("\tXML - XmlSerializerOperationBehavior !"));

							if (OD.Behaviors.Find<DataContractSerializerOperationBehavior>()!=null)
								Console.WriteLine(string.Format("\tDC - DataContractSerializerOperationBehavior !"));

							Console.WriteLine("");
						}

						SH.Open();

						Console.WriteLine("Service is OPENED !");

						Console.WriteLine("Press any key to CLOSE Service !");
						Console.ReadLine();
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

            Console.WriteLine("Press any key to EXIT !");
            Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------