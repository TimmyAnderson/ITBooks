using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CPipelineBranchWithMapWhen
	{
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MapWhenBranch1NonTerminatingMiddleware1(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(MapWhenBranch1NonTerminatingMiddleware1);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);


			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MapWhenBranch1NonTerminatingMiddleware2(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(MapWhenBranch1NonTerminatingMiddleware2);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MapWhenBranch1TerminatingMiddleware(HttpContext Context)
		{
			string												MethodName=nameof(MapWhenBranch1TerminatingMiddleware);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vytvori sa HTTP RESPONSE MESSAGE.
			Context.Response.Headers["Content-Type"]="text/plain;charset=utf-8";

			await Context.Response.WriteAsync($"RESPONSE from MIDDLEWARE [{MethodName}].");

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MapWhenBranch2NonTerminatingMiddleware1(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(MapWhenBranch2NonTerminatingMiddleware1);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MapWhenBranch2NonTerminatingMiddleware2(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(MapWhenBranch2NonTerminatingMiddleware2);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MapWhenBranch2TerminatingMiddleware(HttpContext Context)
		{
			string												MethodName=nameof(MapWhenBranch2TerminatingMiddleware);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vytvori sa HTTP RESPONSE MESSAGE.
			Context.Response.Headers["Content-Type"]="text/plain;charset=utf-8";

			await Context.Response.WriteAsync($"RESPONSE from MIDDLEWARE [{MethodName}].");

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		public static bool BranchWithMapWhenChildPredicate(HttpContext Context)
		{
			PathString											Path=Context.Request.Path;
			PathString											ExpectedPath="/Child";

			if (Path.StartsWithSegments(ExpectedPath)==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void BranchWithMapWhenChild(IApplicationBuilder Builder)
		{
			string												MethodName=nameof(BranchWithMapWhenChild);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATING.");

			// !!! Prida sa 1. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(MapWhenBranch2NonTerminatingMiddleware1);

			// !!! Prida sa 2. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(MapWhenBranch2NonTerminatingMiddleware2);

			// !!! Prida sa TERMINATING MIDDLEWARE COMPONENT.
			// !!!!! Ak by BRANCH NEOBSAHOVALA na BOTTOM REQUEST PIPELINE TERMINATING MIDDLEWARE COMPONENT a HTTP REQUEST MESSAGE sa dostane na tuto uroven .ASP.NET CORE generuje HTTP RESPONSE MESSAGE s HTTP RESPONSE MESSAGE CODE [404].
			Builder.Run(MapWhenBranch2TerminatingMiddleware);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATED.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void BranchWithMapWhen(IApplicationBuilder Builder)
		{
			string												MethodName=nameof(BranchWithMapWhen);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATING.");

			// !!! Prida sa 1. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(MapWhenBranch1NonTerminatingMiddleware1);

			// !!! Prida sa BRANCH pomocou OPERATION [MapWhen].
			// !!!!! Po skonceni MAP WHEN BRNACH uz MUSI byt HTTP REQUEST SPRACOVANY. Ak by nebol, tak MAP WHEN BRANCH vrati HTTP RESPONSE MESSAGE s HTTP RESPONSE MESSAGE CODE [404].
			Builder.MapWhen(BranchWithMapWhenChildPredicate,BranchWithMapWhenChild);

			// !!! Prida sa 2. NON-TERMINATING MIDDLEWARE COMPONENT.
			// !!!!! Tento MIDDLEWARE COMPONENT sa NEVOLA, ak HTTP REQUEST bol spracovany v MAP WHEN BRANCH.
			Builder.Use(MapWhenBranch1NonTerminatingMiddleware2);

			// !!! Prida sa TERMINATING MIDDLEWARE COMPONENT.
			// !!!!! Tento MIDDLEWARE COMPONENT sa NEVOLA, ak HTTP REQUEST bol spracovany v MAP WHEN BRANCH.
			Builder.Run(MapWhenBranch1TerminatingMiddleware);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------