using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Testing1;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CUnitTestsTestConnectionController
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void TestGet()
		{
			TestConnectionController							Controller=new TestConnectionController();

			string												Result=Controller.GetValue();

			Assert.Equal("Hello WORLD !",Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void TestPost()
		{
			TestConnectionController							Controller=new TestConnectionController();

			string												Parameter="Timmy";
			string												Result=Controller.PostValue(Parameter);

			string												ExpectedResult=$"Hello [{Parameter}] !";

			Assert.Equal(ExpectedResult,Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------