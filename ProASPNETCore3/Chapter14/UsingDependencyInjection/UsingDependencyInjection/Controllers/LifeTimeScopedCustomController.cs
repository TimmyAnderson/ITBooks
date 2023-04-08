using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.DependencyInjection;
using UsingDependencyInjection.Model;
using UsingDependencyInjection.Service;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class LifeTimeScopedCustomController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Guid									MID1;
		private readonly Guid									MID2;
		private readonly Guid									MID3;
		private readonly Guid									MID4;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public LifeTimeScopedCustomController(IServiceProvider ServiceProvider, ILifeCycleScoped LifeCycleScoped1InScope1)
		{
			// !!! Hodnoty GUIDs ('MID1' a 'MID2') budu ROVNAKE, no po kazdom REFRESH sa ZMENIA, pretoze novy HTTP REQUEST znamena vytvorenie noveho SCOPE.

			ILifeCycleScoped									LifeCycleScoped2InScope1=(ILifeCycleScoped) ServiceProvider.GetService(typeof(ILifeCycleScoped));

			MID1=LifeCycleScoped1InScope1.ID;
			MID2=LifeCycleScoped2InScope1.ID;

			// !!!!! Vytvori sa NOVY SCOPE.
			IServiceScope										Scope2=ServiceProvider.CreateScope();

			// !!! Hodnoty GUIDs ('MID3' a 'MID4') budu ROVNAKE, no po kazdom REFRESH sa ZMENIA, pretoze novy HTTP REQUEST znamena vytvorenie noveho SCOPE.

			// !!! Vytvori SERVICES v NOVOM SCOPE.
			ILifeCycleScoped									LifeCycleScoped1InScope2=(ILifeCycleScoped) Scope2.ServiceProvider.GetService(typeof(ILifeCycleScoped));
			ILifeCycleScoped									LifeCycleScoped2InScope2=(ILifeCycleScoped) Scope2.ServiceProvider.GetService(typeof(ILifeCycleScoped));

			MID3=LifeCycleScoped1InScope2.ID;
			MID4=LifeCycleScoped2InScope2.ID;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowGuids()
		{
			CGuids4												Model=new CGuids4(MID1,MID2,MID3,MID4);
			ViewResult											Result=View("ShowGuids4",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------