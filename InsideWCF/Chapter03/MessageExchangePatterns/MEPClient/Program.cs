using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Xml;
using MEPLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MEPClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			COneWayProxy						Client=null;
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			try
			{
				Client=new COneWayProxy(TCPBinding,"net.tcp://localhost:5000/");

				Client.Open();

				Message							Msg=CInsideWCFHelper.GenerateMessage("Timmy","Anderson",12);
				UniqueId						UniqueID=new UniqueId(Guid.NewGuid().ToString());

				Msg.Headers.MessageId=UniqueID;

				Console.WriteLine("SENDING MESSAGE:\n{0}",Msg.ToString());

				Client.SendMessage(Msg);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			CRequestResponseProxy				Client=null;
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CRequestResponseProxy(TCPBinding,"net.tcp://localhost:6000/");

				Client.Open();

				Message							Msg=CInsideWCFHelper.GenerateMessage("Timmy","Anderson",12);
				UniqueId						UniqueID=new UniqueId(Guid.NewGuid().ToString());

				Msg.Headers.MessageId=UniqueID;

				Console.WriteLine("SENDING MESSAGE:\n{0}",Msg.ToString());

				Message							Ret=Client.SendMessage(Msg);

				Console.WriteLine("\n\n\nRETURNED MESSAGE:\n{0}",Msg.ToString());
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			InstanceContext						IC=new InstanceContext(new CCallbackService());
			CDuplexProxy						Client=null;
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDuplexProxy(IC,TCPBinding,"net.tcp://localhost:7000/");

				Client.Open();

				Message							Msg=CInsideWCFHelper.GenerateMessage("Timmy","Anderson",12);
				UniqueId						UniqueID=new UniqueId(Guid.NewGuid().ToString());

				Msg.Headers.MessageId=UniqueID;

				Console.WriteLine("SENDING MESSAGE:\n{0}",Msg.ToString());
				Client.SendMessage(Msg);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test1();
			//Test2();
			//Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------