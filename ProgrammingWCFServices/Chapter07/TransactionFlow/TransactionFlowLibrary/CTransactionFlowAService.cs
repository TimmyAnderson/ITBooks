using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace TransactionFlowLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Musi byt PerSession, kedze mam aj TransactionAutoComplete=false.
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CTransactionFlowAService : ITransactionFlowAContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CTransactionFlowAService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void CallBService(string Value, int Method)
		{
			CTransactionFlowBProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowBProxy(TCPBinding,"net.tcp://localhost:9002/ITransactionFlowBContract");

				Client.Open();

				Client.Dummy();

				if (Method==1)
					Client.TFAllowed(Value);
				else if (Method==2)
					Client.TFNotAllowed(Value);
				else if (Method==3)
					Client.TFMandatory(Value);
				else if (Method==4)
					Client.TFImplicitVoting(Value);
				else if (Method==5)
					Client.TFImplicitVotingWithException(Value);
				else if (Method==6)
					Client.TFExplicitVoting(Value);
				else if (Method==7)
					Client.TFExplicitVotingWithEnd(Value);
				else if (Method==8)
				{
					Client.TFExplicitVotingStartTransaction(Value);
					Client.TFExplicitVotingEndTransaction(Value);
				}
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
		public void Dummy()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
		}
//-------------------------------------------------------------------------------------------------------
		// TFAllowed() transakcia je zalozena v service A a je promotovana do service B. Kedze transakcia je v dvoch service nad 2 connections je distribuovana. Avsak Distributed ID sa nastavi az po promotingu a tak do DB je zapisany iba ak uz prebehlo volanie service B.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CallBService(Value,1);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		// TFNotAllowed() transakcia je zalozena v service A ale uz nie je promotovana do service B, kedze je nastaveny NotAllowed a teda k promotingu nedochadza. Obe transakcie su na seb nezavisle a obe su lokalne.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFNotAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CallBService(Value,2);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		// TFMandatory() transakcia je zalozena v service A a je promotovana do service B. Kedze transakcia je v dvoch service nad 2 connections je distribuovana. Avsak Distributed ID sa nastavi az po promotingu a tak do DB je zapisany iba ak uz prebehlo volanie service B.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFMandatory(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CallBService(Value,3);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFImplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CallBService(Value,4);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		// TFImplicitVotingWithException() transakcia je zalozena v service A a propagovana do service B, ktory hodi expcetion. Takto sa rollbackne cela transakcia v oboch services. Co vsak je klucove je aby vynimka vratena service B bola vyhodena smerom nahor zo service A. Moze to byt aj ina vynmka obsah je relevantny, ale service A musi hodit vynimku ak zlyha service B, inak by Client dostal vynimku, ze transakcia bola asynchronne zrusena. Ona totizto zanikla a WCF O TOM VRATENIM EXCEPTION MUSI BYT INFORMOVANA. Preto musim vratit EXCEPTION von z metody SERVICE.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFImplicitVotingWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			try
			{
				CallBService(Value,5);
			}
			catch(FaultException<Exception> E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));

				// !!! EXCEPTION MUSI BYT ODOSLANA VYSSIE, INAK DOJDE K VYNIMKE: Transaction was asynchronouslly aborted. KEDZE TRANSAKCIA SA REALNE ZLIKVIDOVALA A JA MAM IMPLICITNY VOTING MUSIM JU PODSUNUT VON Z METODY SERVICE, ABY WCF JU MOHLA KOREKTEN ROLLBACKNUT.
				// !!! Musim vytvorit novu instanciu ak chcem aby ju zachytit handler FaultException<Exception> na klientovi.
				throw(new FaultException<Exception>(E.Detail));

				// Ak ju urobim rethrow potom ju klient chyti ako FaultException aj ked proxy bude zit dalej.
				//throw;
			}

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		// TFExplicitVoting() transakcia sa zacne v service A a je promoteovana do service B. Je nastaveny ako na service A tak aj B explicitny voting a v TFExplicitVotingWithEnd() zacne transackcia v service A, ale service B hodi exception.
		// Ak ma transakcia uspesne skoncit OBE SERVICE musia zahlasovat za uspesne ukoncenie transakcie (SetTransactionComplete()), alebo nehlasoovat a potom dochadza k rollback.
		// ??? POZOR. Kedze obe Service su PerSession tak plati, ze transakcia zije az dokym dany service nezavola SetTransactionComplete() a TA SA MOZE ZAVOLAT NAPRIKALD ZAVOLANIM INEJ METODY SERVICE, KTORA MA V TELE VOLANIE SetTransactionComplete(), alebo sa neskonci zivotnost instancie Service. Ak skonci a nedolo k volaniu SetTransactionComplete() potom dochadza k Rollback, inak sa moze urobit Commit() ak obe service takto hlasovali.
		// Teda pri PerSession transakcia zije pokym zije Service, alebo pokym sa nezavola SetTransactionComplete().
		// Po zavolani SetTransactionComplete() sa uz v DANOM service nesmie volat ziadna transakcna metoda. Ale v inom ano aj ked je sucastou tej istej transakcie. Teda ak service B vola SetTransactionComplete() tak service A este moze robit transakcne operacie az do zavolania SetTransactionComplete().
		// !!! AK SERVICE B zavola exception potom sa konci okamzite aj SESSION a TEDA KEDZE SA SKONCILA SESSION BEZ HLASOVANIA SetTransactionComplete() tak OKAMZITE dochadza k rollback transakcie.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CallBService(Value,6);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			OperationContext.Current.SetTransactionComplete();
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVotingWithEnd(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			try
			{
				CallBService(Value,7);
			}
			catch(FaultException<Exception> E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));

				// !!! EXCEPTION MUSI BYT ODOSLANA VYSSIE, INAK DOJDE K EXCEPTION: Transaction was asynchronouslly aborted. KEDZE TRANSAKCIA SA REALNE ZLIKVIDOVALA A JA MAM IMPLICITNY VOTING MUSIM JU PODSUNUT VON Z METODY SERVICE, ABY WCF JU MOHLA KOREKTEN ROLLBACKNUT.
				// !!! Musim vytvorit novu instanciu ak chcem aby ju zachytit handler FaultException<Exception> na klientovi.
				throw(new FaultException<Exception>(E.Detail));
			}

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		// TFExplicitVotingStartTransaction() a TFExplicitVotingEndTransaction() demonstruju PesSession SERVICE A a SERVICE B. Metoda TFExplicitVotingStartTransaction() Service A zacne transakciu zapisom do DB a zavola TFExplicitVotingStartTransaction() SERVICE B, ktora zapise do DB zaznam, ZAVOLA SetTransactionComplete() ALE IBA PRE SERVCIE B. Metoda  TFExplicitVotingEndTransaction() v SERVICE A NEZAVOLA SetTransactionComplete() a teda TRANSAKCIA JE STALE ZIJUCA. Riadenie sa vracia do klienta a ten nasledne zavola TFExplicitVotingEndTransaction() SERVICE A. Ten zapise do DB a zaroven vola SetTransactionComplete() a kedze ROOT SERVICE transakcie sa ukoncil s votingom pre COMMIT tak cela transakcia spravi COMMIT.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVotingStartTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CallBService(Value,8);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVotingEndTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			OperationContext.Current.SetTransactionComplete();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------