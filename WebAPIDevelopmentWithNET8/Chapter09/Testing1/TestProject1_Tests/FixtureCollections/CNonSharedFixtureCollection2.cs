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
	[CollectionDefinition("NonSharedFixtureCollection2")]
	public sealed class CNonSharedFixtureCollection2 : ICollectionFixture<CNonSharedFixture>
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Tento CONSTRUCTOR sa pocas vykonavanie UNIT TESTS nikdy nevola.
		public CNonSharedFixtureCollection2()
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CNonSharedFixtureCollection2)}] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------