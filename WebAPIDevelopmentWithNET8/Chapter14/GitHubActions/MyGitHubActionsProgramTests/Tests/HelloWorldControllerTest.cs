using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using MyGitHubActionsProgram;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MyGitHubActionsProgramTests
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class HelloWorldControllerTest
	{
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void GetValueOK()
		{
		    HelloWorldController								Controller=new HelloWorldController();
			string												Result=Controller.GetValue();

			Assert.NotNull(Result);
			Assert.Equal("Hello WORLD !",Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------