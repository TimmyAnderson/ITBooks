using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Razor;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Net.Http.Headers;
using UsingUrlRouting.CustomConstraints;
using UsingUrlRouting.Endpoints;
using UsingUrlRouting.Midlewares;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting
{
//----------------------------------------------------------------------------------------------------------------------
	public class Startup
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Startup(IConfiguration Configuration)
		{
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IConfiguration									Configuration
		{
			get
			{
				return(MConfiguration);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			// !!!!! Zaregistruje sa CUSTOM ROUTE CONTRAINT [CSelectedValuesRouteConstraint] pre pouzitie pomocou INLINE SYNTAX.
			Services.Configure<RouteOptions>(RouteOptions => RouteOptions.ConstraintMap.Add("SelectedValuesRouteConstraint",typeof(CSelectedValuesRouteConstraint)));
		}
//----------------------------------------------------------------------------------------------------------------------
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)
		{
			// !!!!! Na to, aby boli JAVA SCRIPT FILES korektne nacitane z DIRECTORY 'StaticFiles', je nutne definovat ROOT PATH pre [IWebHostEnvironment.WebRootFileProvider].
			WebHostEnvironment.WebRootFileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));

			ApplicationBuilder.UseDeveloperExceptionPage();
			ApplicationBuilder.UseStatusCodePages();

			ApplicationBuilder.UseStaticFiles();

			StaticFileOptions									Options=new StaticFileOptions();

			Options.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));
			Options.RequestPath="/StaticFiles";

			// !!!!! METHOD pridava do REQUEST PIPELINE MIDDLEWARE COMPONENT [StaticFileMiddleware], ktora zabezpeci spracovanie STATIC FILES. Ak MIDDLEWARE COMPONENT detekuje poziadavku na ziskanie STATIC FILE, tak OKAMZITE GENERUJE HTTP RESPONSE a spracovanie NIE JE ODOSLANE do NASLEDUJUCICH MIDDLEWARE COMPONENTS v REQUEST PIPELINE.
			ApplicationBuilder.UseStaticFiles(Options);

			// !!!!! MIDDLEWARE COMPONENT [EndpointRoutingMiddleware] robi selekciu, ENDPOINT ktorej ROUTE sa ma pouzit. No MIDDLEWARE COMPONENT [EndpointRoutingMiddleware] NEVYKONAVA samotne volanie ENDPOINTS. To robi az MIDDLEWARE COMPONENT [EndpointMiddleware].
			ApplicationBuilder.UseRouting();

			// !!!!! MIDDLEWARE COMPONENT pridany MEDZI MIDDLEWARE COMPONENT [EndpointRoutingMiddleware] a MIDDLEWARE COMPONENT [EndpointMiddleware] ma pristup k informacii ci pre danu URL bol najdeny ENDPOINT.
			ApplicationBuilder.Use(new CCheckEndpointMiddleware().ProcessEndpointRequest);

			// !!!!! MIDDLEWARE COMPONENT [EndpointMiddleware] spusta zaregistrovane ENDPOINT, ktore vybral MIDDLEWARE COMPONENT [EndpointRoutingMiddleware].
			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				// !!! Vytvori sa STATIC ROUTE na zadany ENDPOINT.
				Endpoints.MapGet("STATIC_ROUTE_1",new CStaticRoute1Endpoint().ProcessEndpointRequest);

				// !!! Vytvori sa STATIC ROUTE na zadany ENDPOINT.
				Endpoints.MapGet("STATIC_ROUTE_2",new CStaticRoute2Endpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE s 2 CUSTOM ROUTE VARIABLES.
				Endpoints.MapGet("CUSTOM_ROUTE_VARIABLES/{FirstName}/{LastName}",new CCustomRouteVariablesEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE s 2 CUSTOM ROUTE VARIABLES, ktora ma priradeny NAME.
				// !!! ROUTE sa pouziva na generovanie URLs.
				Endpoints.MapGet("NAMED_ROUTE/{FirstName}/{LastName}",new CNamedRouteEndpoint().ProcessEndpointRequest).WithMetadata(new RouteNameMetadata("MyNamedRoute"));

				// !!! Tento ROUTE sa aplikuje na URL, ktore obsahuju AREA.
				Endpoints.MapControllerRoute("ROUTE AREA","{Area:exists}/{Controller}/{Action}");

				// !!! Vytvori sa ROUTE s 2 CUSTOM ROUTE VARIABLES, ktore su v 1 SEGMENT.
				Endpoints.MapGet("MULTIPLE_ROUTE_VARIABLES_IN_ONE_SEGMENT/{FirstName}.{LastName}",new CMultipleRouteVariablesInOneSegmentEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE s 2 CUSTOM ROUTE VARIABLES, ktore maju nastavene DEFAULT VALUES.
				Endpoints.MapGet("DEFAULT_ROUTE_VARIABLES/{FirstName=XXX}/{LastName=YYY}",new CDefaultRouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE s 2 CUSTOM ROUTE VARIABLES, ktore su OPTIONAL.
				Endpoints.MapGet("OPTIONAL_ROUTE_VARIABLES/{FirstName?}/{LastName?}",new COptionalRouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE s 3 CUSTOM ROUTE VARIABLES, kde 3. CUSTOM ROUTE VARIABLE je CATCH ALL CUSTOM ROUTE VARIABLE.
				Endpoints.MapGet("CATCH_ALL_ROUTE_VARIABLE/{FirstName}/{LastName}/{*CatchAll}",new CCatchAllRouteVariableInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE, ktora obsahuje CONSTRAINTS. ROUTE definuje CUSTOM VARIABLE 'FirstName', CUSTOM VARIABLE 'LastName' a CUSTOM VARIABLE 'Age', pricom CUSTOM VARIABLE 'FirstName' a CUSTOM VARIABLE 'LastName' MUSIA obsahovat IBA CHARACTERS a CUSTOM VARIABLE 'Age' MUSI byt TYPE INTEGER.
				Endpoints.MapGet("CONSTRAINTS_1/{FirstName:alpha}/{LastName:alpha}/{Age:int}",new CConstraint1RouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE, ktora obsahuje CONSTRAINTS. Tato ROUTE definuje CUSTOM VARIABLE 'FirstName', CUSTOM VARIABLE 'LastName' a CUSTOM VARIABLE 'Age', pricom CUSTOM VARIABLE 'FirstName' a CUSTOM VARIABLE 'LastName' MUSIA obsahovat IBA CHARACTERS a CUSTOM VARIABLE 'Age' MUSI byt TYPE INTEGER. ROUTE zaroven obsahuje REGULAR EXPRESSION CONSTRAINT na CUSTOM VARIABLE 'FirstName'.
				Endpoints.MapGet("CONSTRAINTS_2/{FirstName:alpha:regex(^Jenny$|^Timmy$)}/{LastName:alpha}/{Age:int}",new CConstraint2RouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE, ktora obsahuje CONSTRAINTS. Tato ROUTE definuje CUSTOM VARIABLE 'FirstName', CUSTOM VARIABLE 'LastName' a CUSTOM VARIABLE 'Age', pricom CUSTOM VARIABLE 'FirstName' a CUSTOM VARIABLE 'LastName' MUSIA obsahovat IBA CHARACTERS a CUSTOM VARIABLE 'Age' MUSI byt TYPE INTEGER v RANGE <10,15>.
				Endpoints.MapGet("CONSTRAINTS_3/{FirstName:alpha}/{LastName:alpha}/{Age:range(10,15)}",new CConstraint3RouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE, ktora obsahuje CONSTRAINTS. Tato ROUTE definuje CUSTOM VARIABLE 'FirstName', CUSTOM VARIABLE 'LastName' a CUSTOM VARIABLE 'Age', pricom CUSTOM VARIABLE 'FirstName', a zaroven moze mat maximalne 5 CHARACTERS, CUSTOM VARIABLE 'LastName' MUSI obsahovat IBA CHARACTERS a CUSTOM VARIABLE 'Age' MUSI byt TYPE INTEGER.
				Endpoints.MapGet("CONSTRAINTS_4/{FirstName:alpha:maxlength(5)}/{LastName:alpha}/{Age:int}",new CConstraint4RouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvori sa ROUTE, ktora obsahuje CUSTOM CONSTRAINTS. Tato ROUTE definuje CUSTOM VARIABLE 'FirstName', CUSTOM VARIABLE 'LastName' a CUSTOM VARIABLE 'Age', pricom CUSTOM VARIABLE 'FirstName', a zaroven moze mat VALUE z preddefinovanych VALUES, CUSTOM VARIABLE 'LastName' MUSI obsahovat IBA CHARACTERS a CUSTOM VARIABLE 'Age' MUSI byt TYPE INTEGER.
				Endpoints.MapGet("CUSTOM_CONSTRAINTS/{FirstName:SelectedValuesRouteConstraint(Timmy,Anderson,Jenny,Thompson)}/{LastName:alpha}/{Age:int}",new CCustomConstraintRouteVariablesInEndpoint().ProcessEndpointRequest);

				// !!! Vytvoria sa ROUTES, ktora pre INTEGER VALUES su konfliktne, kedze obom ROUTES ROUTING SYSTEM priradi to iste SCORE.
				// !!! Kazda ROUTE ma vsak pridelenu vlastnu PRIORITY.
				Endpoints.MapGet("CONFLICTING_ROUTES/{NumericValue:int}",new CConfictingRouteIntEndpoint().ProcessEndpointRequest).Add(P => ((RouteEndpointBuilder) P).Order=1);
				Endpoints.MapGet("CONFLICTING_ROUTES/{NumericValue:double}",new CConfictingRouteDoubleEndpoint().ProcessEndpointRequest).Add(P => ((RouteEndpointBuilder) P).Order=2);

				// !!! Vytvori sa ROUTE, ktora vracia PLAIN TEXT.
				Endpoints.MapGet("PLAIN_TEXT",new CReturnPlainTextEndpoint().ProcessEndpointRequest);

				// !!! ENDPOINT pre MAIN PAGE.
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				// !!! Prida ROUTING pre RAZOR PAGES.
				Endpoints.MapRazorPages();

				// !!! Vytvori sa FALLBACK ROUTE, ktora vola zadany ENDPOINT, ak sa NENASLA vhodna ROUTE, ktoru by bolo mozne pre danu URL pouzit.
				Endpoints.MapFallback(new CFallbackEndpoint().ProcessEndpointRequest);
			});

			// !!! Tento MIDDLEWARE COMPONENT sa pouzije ak URL ROUTING MIDDLEWARE COMPONENT nanasiel ziadnu ROUTE, ktorej URL by vyhovoval ROUTE PATTERN. V takomto pripade URL ROUTING MIDDLEWARE COMPONENT vola nasledujuci MIDDLEWARE COMPONENT v PIPELINE.
			// !!!!! Pri pouziti FALLBACK ROUTE je tento MIDDLEWARE COMPONENT ZBYTOCNY, pretoze URL ROUTING MIDDLEWARE COMPONENT pri nenajdeny vhodnej ROUTE pouzije FALLBACK ROUTE.
			ApplicationBuilder.Use(new CTerminalMiddleware().ProcessEndpointRequest);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------