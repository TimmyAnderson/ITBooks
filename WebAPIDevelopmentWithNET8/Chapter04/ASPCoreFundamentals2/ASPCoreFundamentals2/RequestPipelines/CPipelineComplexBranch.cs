using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CPipelineComplexBranch
	{
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MyNonTerminatingMiddleware1(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(MyNonTerminatingMiddleware1);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MyNonTerminatingMiddleware2(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(MyNonTerminatingMiddleware2);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task MyTerminatingMiddleware(HttpContext Context)
		{
			string												MethodName=nameof(MyTerminatingMiddleware);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vytvori sa HTTP RESPONSE MESSAGE.
			Context.Response.Headers["Content-Type"]="text/plain;charset=utf-8";

			await Context.Response.WriteAsync("RESPONSE from MIDDLEWARE [MyTerminatingMiddleware].");

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void MyComplexBranch(IApplicationBuilder Builder)
		{
			string												MethodName=nameof(MyComplexBranch);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATING.");

			// !!! Prida sa 1. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(MyNonTerminatingMiddleware1);

			// !!! Prida sa 2. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(MyNonTerminatingMiddleware2);

			// !!! Prida sa TERMINATING MIDDLEWARE COMPONENT.
			Builder.Run(MyTerminatingMiddleware);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------