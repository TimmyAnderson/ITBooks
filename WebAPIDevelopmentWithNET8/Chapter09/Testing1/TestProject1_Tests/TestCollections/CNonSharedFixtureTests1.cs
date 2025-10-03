using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ATTRIBUTE [Collection] urcuje do akej UNIT TESTS COLLECTION bude dana UNIT TEST CLASS patrit.
	// !!!!! NAME sa MUSI zhodovat s NAME definovanom v ATTRIBUTE [CollectionDefinition].
	[Collection("NonSharedFixtureCollection1")]
	public sealed class CNonSharedFixtureTests1 : IDisposable
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! UNIT TEST CLASS [CNonSharedFixtureTests1] a UNIT TEST CLASS [CNonSharedFixtureTests2] budu mat vlastne verzie instancie FIXTURE CLASS [CNonSharedFixture], pretoze NIE su v tej istej CUSTOM UNIT TESTS COLLECTION.
		private readonly CNonSharedFixture						MFixture;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNonSharedFixtureTests1(CNonSharedFixture Fixture)
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CNonSharedFixtureTests1)}] CALLED.");

			MFixture=Fixture;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void DoTest1()
		{
			Console.WriteLine($"METHOD [{nameof(CNonSharedFixtureTests1)}.{nameof(DoTest1)}()] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void DoTest2()
		{
			Console.WriteLine($"METHOD [{nameof(CNonSharedFixtureTests1)}.{nameof(DoTest2)}()] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine($"DISPOSE METHOD [{nameof(CNonSharedFixtureTests1)}.{nameof(Dispose)}()] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------