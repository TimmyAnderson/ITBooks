using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using InterceptorSharedHost;
//-------------------------------------------------------------------------------------------------------
namespace InterceptorSharedClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(ChannelFactory<INameService> CF=new ChannelFactory<INameService>("EP"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						try
						{
							INameService			Proxy=Disp as INameService;

							CFullName				FNInput=new CFullName("Timmy","Anderson",12);
							string					SOutput=Proxy.GetFirstName(FNInput);

							Console.WriteLine(string.Format("GetFirstName() - INPUT [{0}] - OUTPUT: [{1}]",FNInput,SOutput));

							string					FirstName="Timmy";
							string					LastName="Anderson";
							int						Age=12;
							CFullName				FNOutput=Proxy.GetFullName(FirstName,LastName,Age);

							Console.WriteLine(string.Format("GetFullName() - INPUT [FN: {0}, LN: {1}, A: {2}] - OUTPUT: [{3}]",FirstName,LastName,Age,FNOutput));

							string					ExFirstName="Timmy";
							string					ExOutput;

							try
							{
								ExOutput=Proxy.JustThrowException(ExFirstName);

								Console.WriteLine(string.Format("JustThrowException() - INPUT [{0}] - OUTPUT: [{1}]",ExFirstName,ExOutput));
								Console.WriteLine("All OK !!!");
							}
							catch
							{
								Console.WriteLine("EXCEPTION !!!");
							}

							ExFirstName="Jenny";

							try
							{
								ExOutput=Proxy.JustThrowException(ExFirstName);

								Console.WriteLine(string.Format("JustThrowException() - INPUT [{0}] - OUTPUT: [{1}]",ExFirstName,ExOutput));
								Console.WriteLine("All OK !!!");
							}
							catch
							{
								Console.WriteLine("EXCEPTION !!!");
							}
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
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

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------