using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS reprezentuje FIXTURE CONNECTION.
	[CollectionDefinition("NonSharedFixtureCollection1")]
	public sealed class CNonSharedFixtureCollection1 : ICollectionFixture<CNonSharedFixture>
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Tento CONSTRUCTOR sa pocas vykonavanie UNIT TESTS nikdy nevola.
		public CNonSharedFixtureCollection1()
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CNonSharedFixtureCollection1)}] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------