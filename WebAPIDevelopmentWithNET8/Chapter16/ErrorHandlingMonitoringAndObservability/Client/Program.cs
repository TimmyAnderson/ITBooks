//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
//			CMenuTestConnection									Menu=new CMenuTestConnection();
//			CMenuUnhandledExceptions							Menu=new CMenuUnhandledExceptions();
//			CMenuValidations									Menu=new CMenuValidations();
//			CMenuHealthChecks									Menu=new CMenuHealthChecks();
//			CMenuObservability									Menu=new CMenuObservability();
//			CMenuTestConnectionRemoteService					Menu=new CMenuTestConnectionRemoteService();
//			CMenuTracing										Menu=new CMenuTracing();
			CMenuHttpLogging									Menu=new CMenuHttpLogging();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------