using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CPipelineBranchWithUseWhen
	{
//----------------------------------------------------------------------------------------------------------------------
		private static async Task UseWhenBranch1NonTerminatingMiddleware1(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(UseWhenBranch1NonTerminatingMiddleware1);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task UseWhenBranch1NonTerminatingMiddleware2(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(UseWhenBranch1NonTerminatingMiddleware2);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task UseWhenTerminatingMiddleware(HttpContext Context)
		{
			string												MethodName=nameof(UseWhenTerminatingMiddleware);

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
		private static async Task UseWhenBranch2NonTerminatingMiddleware1(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(UseWhenBranch2NonTerminatingMiddleware1);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task UseWhenBranch2NonTerminatingMiddleware2(HttpContext Context, RequestDelegate NextMiddleware)
		{
			string												MethodName=nameof(UseWhenBranch2NonTerminatingMiddleware2);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE BRANCH.
			await NextMiddleware(Context);

			// !!!!! MIDDLEWARE COMPONENTS mozu menit HTTP RESPONSE MESSAGE IBA predtym ako je volana dalsia MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE. Ak sa CODE pokusi modifikovat HTTP RESPONSE MESSAGE potom ako jej BODY uz bolo vygenerovane niektorou z MIDDLEWARE COMPONENTS, pri pokuse o modifikaciu HTTP RESPONSE MESSAGE dojde k vzniku EXCEPTION. Dovodom tohto chovania je to, ze po vygenerovani BODY HTTP RESPONSE MESSAGE moze byt HTTP RESPONSE MESSAGE okamzite odosielana na CLIENT. A tym padom jej modifikacia by sposobila narusenie integrity.

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
		public static bool BranchWithUseWhenChildPredicate(HttpContext Context)
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
		public static void BranchWithUseWhenChild(IApplicationBuilder Builder)
		{
			string												MethodName=nameof(BranchWithUseWhenChild);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATING.");

			// !!! Prida sa 1. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(UseWhenBranch2NonTerminatingMiddleware1);

			// !!! Prida sa 2. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(UseWhenBranch2NonTerminatingMiddleware2);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATED.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void BranchWithUseWhen(IApplicationBuilder Builder)
		{
			string												MethodName=nameof(BranchWithUseWhen);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATING.");

			// !!! Prida sa 1. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(UseWhenBranch1NonTerminatingMiddleware1);

			// !!! Prida sa BRANCH pomocou OPERATION [UseWhen].
			// !!!!! Po skonceni USE WHEN BRNACH je HTTP REQUEST odoslany do dalsej MIDDLEWARE COMPONENT, ktora sa nachadza za USE WHEN BRNACH.
			Builder.UseWhen(BranchWithUseWhenChildPredicate,BranchWithUseWhenChild);

			// !!! Prida sa 2. NON-TERMINATING MIDDLEWARE COMPONENT.
			Builder.Use(UseWhenBranch1NonTerminatingMiddleware2);

			// !!! Prida sa TERMINATING MIDDLEWARE COMPONENT.
			Builder.Run(UseWhenTerminatingMiddleware);

			// !!!!! Tento CODE sa vykonava iba pri STARTE PROGRAMU, nie pocas vykonavania HTTP REQUESTS.
			Console.WriteLine($"BRANCH [{MethodName}] - CREATED.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------