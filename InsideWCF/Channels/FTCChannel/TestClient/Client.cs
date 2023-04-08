using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Configuration;
using FTCSharedLibrary;
using FTCChannelLibrary;
using TestLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TestClient
{
//-------------------------------------------------------------------------------------------------------
	class Client
	{
//-------------------------------------------------------------------------------------------------------
		// Cesta k directory, ktory bude mat subdirectory Sender a Receiver.
		// !!! Cesta nesmie obsahovat znaky, ktore nevie Uri parsovat, napriklad '#'.
		private static string									MAddressBase=ConfigurationManager.AppSettings["Path"];
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			try
			{
				Console.Title="Client1";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address=new Uri(MAddressBase + @"/!Packets1");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				while(true)
				{
					// Kvoli callback.
					InstanceContext		InstanceContext=new InstanceContext(new CTestFTCCallback());

					using(CTestFTCProxy Proxy=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address)))
					{
						Console.WriteLine("Press any kedy to OPEN PROXY !");
						Console.ReadLine();

						Proxy.Open();

						string	Text;
						string	Ret;

						Console.WriteLine("Write MESSAGE BODY !");
						Text=Console.ReadLine();

						Console.WriteLine("Press any key to run SomeOperation_BEGIN() !");
						Console.ReadLine();

						Ret=Proxy.SomeOperation_BEGIN(Text);
						Console.WriteLine(string.Format("!!!!!!!!!!! SomeOperation_BEGIN(): '{0}' !",Ret));

						Console.WriteLine("Press any key to run SomeOperation_MIDDLE() !");
						Console.ReadLine();

						Ret=Proxy.SomeOperation_MIDDLE(Text);
						Console.WriteLine(string.Format("!!!!!!!!!!! SomeOperation_MIDDLE(): '{0}' !",Ret));

						Console.WriteLine("Press any key to run SomeOperation_END() !");
						Console.ReadLine();

						Ret=Proxy.SomeOperation_END(Text);
						Console.WriteLine(string.Format("!!!!!!!!!!! SomeOperation_END(): '{0}' !",Ret));

						Console.WriteLine("Press any key to CLOSE PROXY !");
						Console.ReadLine();

						Proxy.Close();
					}

					string	Line;

					Console.WriteLine("Do you want to CONTINUE (Y\\N) ?");
					Line=Console.ReadLine();

					if (Line.Length==0 || Line.ToUpper()[0]!='Y')
						break;
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			try
			{
				Console.Title="Client2";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address=new Uri(MAddressBase + @"/!Packets1");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				while(true)
				{
					// Kvoli callback.
					InstanceContext		InstanceContext=new InstanceContext(new CTestFTCCallback());

					using(CTestFTCProxy Proxy1=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address)))
					{
						using(CTestFTCProxy Proxy2=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address)))
						{
							Console.WriteLine("Press any kedy to OPEN PROXY !");
							Console.ReadLine();

							Proxy1.Open();
							Proxy2.Open();

							string	Text;
							string	Ret;

							Console.WriteLine("Write MESSAGE BODY !");
							Text=Console.ReadLine();

							Console.WriteLine("Press any key to run SomeOperation_BEGIN() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_BEGIN(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_BEGIN(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_BEGIN(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_BEGIN(): '{0}' !",Ret));

							Console.WriteLine("Press any key to run SomeOperation_MIDDLE() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_MIDDLE(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_MIDDLE(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_MIDDLE(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_MIDDLE(): '{0}' !",Ret));

							Console.WriteLine("Press any key to run SomeOperation_END() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_END(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_END(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_END(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_END(): '{0}' !",Ret));

							Console.WriteLine("Press any key to CLOSE PROXY !");
							Console.ReadLine();

							Proxy1.Close();
							Proxy2.Close();
						}
					}

					string	Line;

					Console.WriteLine("Do you want to CONTINUE (Y\\N) ?");
					Line=Console.ReadLine();

					if (Line.Length==0 || Line.ToUpper()[0]!='Y')
						break;
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			try
			{
				Console.Title="Client3";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address1=new Uri(MAddressBase + @"/!Packets1");
				Uri						Address2=new Uri(MAddressBase + @"/!Packets2");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				while(true)
				{
					// Kvoli callback.
					InstanceContext		InstanceContext=new InstanceContext(new CTestFTCCallback());

					using(CTestFTCProxy Proxy1=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address1)))
					{
						using(CTestFTCProxy Proxy2=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address2)))
						{
							Console.WriteLine("Press any kedy to OPEN PROXY !");
							Console.ReadLine();

							Proxy1.Open();
							Proxy2.Open();

							string	Text;
							string	Ret;

							Console.WriteLine("Write MESSAGE BODY !");
							Text=Console.ReadLine();

							Console.WriteLine("Press any key to run SomeOperation_BEGIN() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_BEGIN(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_BEGIN(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_BEGIN(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_BEGIN(): '{0}' !",Ret));

							Console.WriteLine("Press any key to run SomeOperation_MIDDLE() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_MIDDLE(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_MIDDLE(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_MIDDLE(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_MIDDLE(): '{0}' !",Ret));

							Console.WriteLine("Press any key to run SomeOperation_END() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_END(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_END(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_END(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_END(): '{0}' !",Ret));

							Console.WriteLine("Press any key to CLOSE PROXY !");
							Console.ReadLine();

							Proxy1.Close();
							Proxy2.Close();
						}
					}

					string	Line;

					Console.WriteLine("Do you want to CONTINUE (Y\\N) ?");
					Line=Console.ReadLine();

					if (Line.Length==0 || Line.ToUpper()[0]!='Y')
						break;
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test4()
		{
			try
			{
				Console.Title="Client4";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address1=new Uri(MAddressBase + @"/!Packets1");
				Uri						Address2=new Uri(MAddressBase + @"/!Packets2");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				while(true)
				{
					// Kvoli callback.
					InstanceContext		InstanceContext=new InstanceContext(new CTestFTCCallback());

					using(CTestFTCProxy Proxy1=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address1)))
					{
						using(CTestFTCProxy Proxy2=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address2)))
						{
							Console.WriteLine("Press any kedy to OPEN PROXY !");
							Console.ReadLine();

							Proxy1.Open();
							Proxy2.Open();

							string	Text;
							string	Ret;

							Console.WriteLine("Write MESSAGE BODY !");
							Text=Console.ReadLine();

							Console.WriteLine("Press any key to run SomeOperation_BEGIN() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_BEGIN(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_BEGIN(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_BEGIN(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_BEGIN(): '{0}' !",Ret));

							Console.WriteLine("Press any key to run SomeOperation_MIDDLE() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_MIDDLE(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_MIDDLE(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_MIDDLE(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_MIDDLE(): '{0}' !",Ret));

							Console.WriteLine("Press any key to run SomeOperation_END() !");
							Console.ReadLine();

							Ret=Proxy1.SomeOperation_END(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy1.SomeOperation_END(): '{0}' !",Ret));
							Ret=Proxy2.SomeOperation_END(Text);
							Console.WriteLine(string.Format("!!!!!!!!!!! Proxy2.SomeOperation_END(): '{0}' !",Ret));

							Console.WriteLine("Press any key to CLOSE PROXY !");
							Console.ReadLine();

							Proxy1.Close();
							Proxy2.Close();
						}
					}

					string	Line;

					Console.WriteLine("Do you want to CONTINUE (Y\\N) ?");
					Line=Console.ReadLine();

					if (Line.Length==0 || Line.ToUpper()[0]!='Y')
						break;
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test5()
		{
			try
			{
				Console.Title="Client5";

				int		Counter=0;

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address=new Uri(MAddressBase + @"/!Packets1");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				while(true)
				{
					// Kvoli callback.
					InstanceContext		InstanceContext=new InstanceContext(new CTestFTCCallback());

					Counter++;

					using(CTestFTCProxy Proxy=new CTestFTCProxy(InstanceContext, Binding, new EndpointAddress(Address)))
					{
						Console.WriteLine("Press any kedy to OPEN PROXY !");
						Console.ReadLine();

						Proxy.Open();

						string	Text;

						Console.WriteLine("Write MESSAGE BODY !");
						Text=Console.ReadLine();

						if ((Counter % 2)!=0)
						{
							Console.WriteLine("Press any key to run ThrowException() !");
							Console.ReadLine();

							try
							{
								Proxy.ThrowException(Text);
							}
							catch(FaultException<InvalidOperationException> E)
							{
								Console.WriteLine(string.Format("!!! WELL KNOWN FAULT !!! - {0} !",CDebugHelper.GetExceptionString(E)));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("!!! UNKNOWN EXCEPTION !!! - {0} !",CDebugHelper.GetExceptionString(E)));
							}
						}
						else
						{
							Console.WriteLine("Press any key to run SomeOperation_BEGIN() !");
							Console.ReadLine();

							Proxy.SomeOperation_BEGIN(Text);
						}

						Console.WriteLine("Press any key to CLOSE PROXY !");
						Console.ReadLine();

						Proxy.Close();
					}

					string	Line;

					Console.WriteLine("Do you want to CONTINUE (Y\\N) ?");
					Line=Console.ReadLine();

					if (Line.Length==0 || Line.ToUpper()[0]!='Y')
						break;
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();
			//Test5();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------