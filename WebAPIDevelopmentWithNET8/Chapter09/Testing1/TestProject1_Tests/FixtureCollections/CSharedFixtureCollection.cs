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
	[CollectionDefinition("SharedFixtureCollection")]
	public sealed class CSharedFixtureCollection : ICollectionFixture<CSharedFixture>
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Tento CONSTRUCTOR sa pocas vykonavanie UNIT TESTS nikdy nevola.
		public CSharedFixtureCollection()
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CSharedFixtureCollection)}] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------