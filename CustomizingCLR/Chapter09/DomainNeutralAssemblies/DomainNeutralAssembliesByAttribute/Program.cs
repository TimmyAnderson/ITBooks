using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DomainNeutralAssembliesByAttribute
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! ATTRIBUTE sa berie do uvahy IBA ak je aplikovany na Main() METHOD.
		[LoaderOptimization(LoaderOptimization.MultiDomain)]
		static void Main(string[] args)
		{
			Console.WriteLine("APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------