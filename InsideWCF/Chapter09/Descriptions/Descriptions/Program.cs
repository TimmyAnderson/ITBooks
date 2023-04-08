using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace Descriptions
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WindowWidth=100;
			Console.Title="Description";

			ContractDescription		CDescription=ContractDescription.GetContract(typeof(IRestaurantService));

			foreach(OperationDescription OpDesc in CDescription.Operations)
			{
				Console.WriteLine("\nOperation Name: [{0}] !", OpDesc.Name);

				foreach(MessageDescription MsgDesc in OpDesc.Messages)
				{
					Console.WriteLine("  Message Direction: [{0}] !", MsgDesc.Direction);
					Console.WriteLine("  Message Action: [{0}] !", MsgDesc.Action);
					Console.WriteLine("  Message Type: [{0}] !", (MsgDesc.MessageType!=null) ? MsgDesc.MessageType.ToString() : "Untyped");
				}
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------