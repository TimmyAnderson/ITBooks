using System;
using System.Collections.Generic;
using System.Text;
using ConcurrencyReentrantLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ClientHelper
{
//-------------------------------------------------------------------------------------------------------
	internal class CClientList<T> : IConcurrencyReentrantCallback where T : IConcurrencyReentrantCallback
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
		public void OnCallback1(string Message)
		{
			Console.WriteLine("Client OnCallback() STARTED !");

			lock(MSyn)
			{
				for(int i=0;i<MList.Count;i++)
				{
					try
					{
						// Ak zlyha volanie potom sa hodi vynimka. Aj ked sa uzverie klient predcasne potom dostanem vynimku.
						MList[i].Client.OnCallback1(Message);
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("CALLBACK EXCEPTION: {0} !",E.Message));
						Remove(i);
						i--;
					}
				}
			}

			Console.WriteLine("Client OnCallback() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void OnCallback2(string Message)
		{
			Console.WriteLine("Client OnCallback() STARTED !");

			lock(MSyn)
			{
				for(int i=0;i<MList.Count;i++)
				{
					try
					{
						// Ak zlyha volanie potom sa hodi vynimka. Aj ked sa uzverie klient predcasne potom dostanem vynimku.
						MList[i].Client.OnCallback2(Message);
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("CALLBACK EXCEPTION: {0} !",E.Message));
						Remove(i);
						i--;
					}
				}
			}

			Console.WriteLine("Client OnCallback() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------