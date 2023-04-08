using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using CallbackFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ClientHelper
{
//-------------------------------------------------------------------------------------------------------
	internal class CClientList<T> : ICallbackFaultsCallback where T : ICallbackFaultsCallback
	{
//-------------------------------------------------------------------------------------------------------
		private	object											MSyn;
		private	List<CClientListItem<T>>						MList;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CClientList()
		{
			MSyn=new object();
			MList=new List<CClientListItem<T>>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add(CClientListItem<T> Client)
		{
			Console.WriteLine("Client ADD() STARTED !");

			lock(MSyn)
			{
				bool		Found=false;

				for(int i=0;i<MList.Count;i++)
					if (EqualityComparer<T>.Default.Equals(MList[i].Client,Client.Client)==true)
					{
						Found=true;
						break;
					}

				if (Found==false)
				{
					MList.Add(Client);
					Console.WriteLine(string.Format("{0} ADDED !",Client.ToString()));
				}
			}

			Console.WriteLine("Client ADD() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Remove(int Index)
		{
			Console.WriteLine("Client REMOVE(int) STARTED !");

			lock(MSyn)
			{
				if (Index>=0 || Index<MList.Count)
				{
					string		Name=MList[Index].ToString();

					MList.RemoveAt(Index);
					Console.WriteLine(string.Format("{0} REMOVED !",Name));
				}
			}

			Console.WriteLine("Client REMOVE(int) FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Remove(T Client)
		{
			Console.WriteLine("Client REMOVE(T) STARTED !");

			lock(MSyn)
			{
				CClientListItem<T>		Item=null;

				for(int i=0;i<MList.Count;i++)
					if (EqualityComparer<T>.Default.Equals(MList[i].Client,Client)==true)
					{
						Item=MList[i];
						break;
					}

				if (Item!=null)
				{
					string		Name=Item.ToString();

					MList.Remove(Item);
					Console.WriteLine(string.Format("{0} REMOVED !",Name));
				}
			}

			Console.WriteLine("Client REMOVE(T) FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void NonFaultCallback(string Message)
		{
			Console.WriteLine("Client NonFaultCallback() STARTED !");

			lock(MSyn)
			{
				for(int i=0;i<MList.Count;i++)
				{
					try
					{
						// Ak zlyha volanie potom sa hodi vynimka. Aj ked sa uzverie klient predcasne potom dostanem vynimku.
						MList[i].Client.NonFaultCallback(Message);
					}
					catch(FaultException<CFaultDetails> E)
					{
						// Proxy prezije.
						Console.WriteLine(string.Format("NonFaultCallback() - FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
					}
					catch(FaultException E)
					{
						// Proxy JE MRTVE - vyradzujem ho.
						Console.WriteLine(string.Format("NonFaultCallback() - FaultException: Msg: {0} !",E.Message));
						Remove(i);
						i--;
					}
					catch(CommunicationException E)
					{
						// Proxy JE MRTVE - vyradzujem ho.
						Console.WriteLine(string.Format("NonFaultCallback() - CommunicationException: Msg: {0} !",E.Message));
						Remove(i);
						i--;
					}
					catch(Exception E)
					{
						// Proxy JE MRTVE - vyradzujem ho.
						Console.WriteLine(string.Format("NonFaultCallback() - EXCEPTION: Msg: {0} !",E.Message));
						Remove(i);
						i--;
					}
				}
			}

			Console.WriteLine("Client NonFaultCallback() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void FaultCallback(string Message)
		{
			Console.WriteLine("Client FaultCallback() STARTED !");

			lock(MSyn)
			{
				for(int i=0;i<MList.Count;i++)
				{
					try
					{
						// Ak zlyha volanie potom sa hodi vynimka. Aj ked sa uzverie klient predcasne potom dostanem vynimku.
						MList[i].Client.FaultCallback(Message);
					}
					catch(FaultException<CFaultDetails> E)
					{
						// Proxy prezije.
						Console.WriteLine(string.Format("FaultCallback() - FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
					}
					catch(FaultException E)
					{
						// Proxy JE MRTVE - vyradzujem ho.
						Console.WriteLine(string.Format("FaultCallback() - FaultException: Msg: {0} !",E.Message));
						Remove(i);
						i--;
					}
					catch(CommunicationException E)
					{
						// Proxy JE MRTVE - vyradzujem ho.
						Console.WriteLine(string.Format("FaultCallback() - CommunicationException: Msg: {0} !",E.Message));
						Remove(i);
						i--;
					}
					catch(Exception E)
					{
						// Proxy JE MRTVE - vyradzujem ho.
						Console.WriteLine(string.Format("FaultCallback() - EXCEPTION: Msg: {0} !",E.Message));
						Remove(i);
						i--;
					}
				}
			}

			Console.WriteLine("Client FaultCallback() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------