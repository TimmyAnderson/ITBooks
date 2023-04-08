using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Transactions;
using TransactionProtocolService;
//-------------------------------------------------------------------------------------------------------
namespace TransactionProtocolClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_1);
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_2);

			try
			{
				using(ChannelFactory<ITransactionProtocol> ChannelFactory=new ChannelFactory<ITransactionProtocol>("Proxy"))
				{
					try
					{
						ChannelFactory.Open();

						using(IDisposable CF=(IDisposable) ChannelFactory.CreateChannel())
						{
							try
							{
								ICommunicationObject		CO=(ICommunicationObject) CF;
								ITransactionProtocol		TypedCF=(ITransactionProtocol) CF;

								CO.Open();

								using(TransactionScope TS=new TransactionScope())
								{
									TypedCF.DoTransaction("Timmy");

									TS.Complete();
								}

								Console.WriteLine("TRANSACTION COMMITED !");
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
							}
						}
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------