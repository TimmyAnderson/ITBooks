using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.DependencyInjection;
//----------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
{
//----------------------------------------------------------------------------------------------------------------------
    [ApiController]
    [Route("[controller]")]
    public class DependencyInjectionController : ControllerBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly IServiceMyTransient					MMyTransient1;
		private readonly IServiceMyTransient					MMyTransient2;
		private readonly IServiceMyScoped						MMyScoped1;
		private readonly IServiceMyScoped						MMyScoped2;
		private readonly IServiceMySingleton					MMySingleton1;
		private readonly IServiceMySingleton					MMySingleton2;
		private readonly IMyKeyedService						MMyKeyedService1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public DependencyInjectionController(IServiceMyTransient MyTransient1, IServiceMyTransient MyTransient2, IServiceMyScoped MyScoped1, IServiceMyScoped MyScoped2, IServiceMySingleton MySingleton1, IServiceMySingleton MySingleton2, [FromKeyedServices("MY_SERVICE_1")] IMyKeyedService MyKeyedService1)
        {
			MMyTransient1=MyTransient1;
			MMyTransient2=MyTransient2;
			MMyScoped1=MyScoped1;
			MMyScoped2=MyScoped2;
			MMySingleton1=MySingleton1;
			MMySingleton2=MySingleton2;
			MMyKeyedService1=MyKeyedService1;
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("DependencyInjectionConstructor")]
        public CDependencyInjection GetValuesConstructor()
        {
			int													MyTransientValue1=MMyTransient1.GetValue();
			int													MyTransientValue2=MMyTransient2.GetValue();
			int													MyScopedValue1=MMyScoped1.GetValue();
			int													MyScopedValue2=MMyScoped2.GetValue();
			int													MySingletonValue1=MMySingleton1.GetValue();
			int													MySingletonValue2=MMySingleton2.GetValue();
			CDependencyInjection								DependencyInjection=new CDependencyInjection(MyTransientValue1,MyTransientValue2,MyScopedValue1,MyScopedValue2,MySingletonValue1,MySingletonValue2);

			return(DependencyInjection);
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("DependencyInjectionInActionMethod")]
        public CDependencyInjection GetValuesInActionMethodInjection([FromServices] IServiceMyTransient MyTransient1, [FromServices] IServiceMyTransient MyTransient2, [FromServices] IServiceMyScoped MyScoped1, [FromServices] IServiceMyScoped MyScoped2, [FromServices] IServiceMySingleton MySingleton1, [FromServices] IServiceMySingleton MySingleton2)
        {
			int													MyTransientValue1=MyTransient1.GetValue();
			int													MyTransientValue2=MyTransient2.GetValue();
			int													MyScopedValue1=MyScoped1.GetValue();
			int													MyScopedValue2=MyScoped2.GetValue();
			int													MySingletonValue1=MySingleton1.GetValue();
			int													MySingletonValue2=MySingleton2.GetValue();
			CDependencyInjection								DependencyInjection=new CDependencyInjection(MyTransientValue1,MyTransientValue2,MyScopedValue1,MyScopedValue2,MySingletonValue1,MySingletonValue2);

			return(DependencyInjection);
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("DependencyInjectionKeyedServices")]
        public CKeyedServices GetValuesKeyedServices([FromKeyedServices("MY_SERVICE_2")] IMyKeyedService MyKeyedService2)
        {
			string												ValueFromKeyedService1=MMyKeyedService1.GetValue();
			string												ValueFromKeyedService2=MyKeyedService2.GetValue();
			CKeyedServices										KeyedServices=new CKeyedServices(ValueFromKeyedService1,ValueFromKeyedService2);

			return(KeyedServices);
        }
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("CustomScopes")]
        public CCustomScopes GetValuesCustomScopes([FromServices] IServiceProvider ServiceProvider)
        {
			IServiceMyScoped									Service1=ServiceProvider.GetRequiredService<IServiceMyScoped>();
			IServiceMyScoped									Service2=ServiceProvider.GetRequiredService<IServiceMyScoped>();

			int													MyScoped1=Service1.GetValue();
			int													MyScoped2=Service2.GetValue();
			int													MyScopedInCustomScope1;
			int													MyScopedInCustomScope2;
			
			using(IServiceScope Scope=ServiceProvider.CreateScope())
			{
				IServiceMyScoped								ServiceInScope=Scope.ServiceProvider.GetRequiredService<IServiceMyScoped>();

				MyScopedInCustomScope1=ServiceInScope.GetValue();
			}

			using(IServiceScope Scope=ServiceProvider.CreateScope())
			{
				IServiceMyScoped								ServiceInScope=Scope.ServiceProvider.GetRequiredService<IServiceMyScoped>();

				MyScopedInCustomScope2=ServiceInScope.GetValue();
			}

			CCustomScopes										CustomScopes=new CCustomScopes(MyScoped1,MyScoped2,MyScopedInCustomScope1,MyScopedInCustomScope2);

			return(CustomScopes);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------