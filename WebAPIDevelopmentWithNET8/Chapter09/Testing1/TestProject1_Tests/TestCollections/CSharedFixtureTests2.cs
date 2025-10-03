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
	[Collection("SharedFixtureCollection")]
	public sealed class CSharedFixtureTests2 : IDisposable
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! UNIT TEST CLASS [CSharedFixtureTests1] a UNIT TEST CLASS [CSharedFixtureTests2] budu mat SHARED verziu instancie FIXTURE CLASS [CSharedFixture], pretoze su v tej istej CUSTOM UNIT TESTS COLLECTION.
		private readonly CSharedFixture						MFixture;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSharedFixtureTests2(CSharedFixture Fixture)
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CSharedFixtureTests2)}] CALLED.");

			MFixture=Fixture;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void DoTest1()
		{
			Console.WriteLine($"METHOD [{nameof(CSharedFixtureTests2)}.{nameof(DoTest1)}()] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void DoTest2()
		{
			Console.WriteLine($"METHOD [{nameof(CSharedFixtureTests2)}.{nameof(DoTest2)}()] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine($"DISPOSE METHOD [{nameof(CSharedFixtureTests2)}.{nameof(Dispose)}()] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------