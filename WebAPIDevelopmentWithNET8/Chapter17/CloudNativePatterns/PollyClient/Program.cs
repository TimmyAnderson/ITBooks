//--------------------------------------------------------------------------------------------------------------------------------
namespace PollyClient
{
//--------------------------------------------------------------------------------------------------------------------------------
	internal class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
//			CMenuTestConnectionClient							Menu=new CMenuTestConnectionClient();
//			CMenuTestConnectionServer							Menu=new CMenuTestConnectionServer();
//			CMenuPollyTimeout									Menu=new CMenuPollyTimeout();
//			CMenuDotNetRateLimiter								Menu=new CMenuDotNetRateLimiter();
//			CMenuPollyRateLimiter								Menu=new CMenuPollyRateLimiter();
//			CMenuPollyRetry										Menu=new CMenuPollyRetry();
			CMenuPollyCircuitBreaker							Menu=new CMenuPollyCircuitBreaker();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------