using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using ModelValidation.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class RemoteErrorCheckingRazorPageController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD MUSI mat rovnaky NAME ako nazov PROPERTY, ktora ma byt VALIDATED.
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD by MAL byt TYPE [string]. To preto, lebo ak by napriklad sa jednalo o PROPERTY TYPE [int] a USER by do prislusneho INPUT HTML ELEMENT zadal NON-INTEGER VALUE, tak by sa SERVER SIDE VALIDATION METHOD VOBEC NEZAVOLALA. Preto sa odporuca ako PARAMETER TYPE VZDY pouzivat TYPE [string].
		// !!! RETURN VALUE SERVER SIDE VALIDATION METHOD MUSI byt TYPE [JsonResult], kde v pripade, ze VALIDATION presla uspesne, tak je potrebne vratit VALUE 'true' a v pripade, ze VALIDATION ZLYHALA, vratit MESSAGE obsahujucu popis ERROR.
		// !!!!! Pri REMOTE VALIDATION je volana SERVER SIDE VALIDATION METHOD, ktorej QUERY STRING pouziva nazov PARAMETER [XXX.YYY], kde VALUE 'XXX' je nazov RAZOR PAGE MODEL OBJECT PROPERTY a VALUE 'YYY' je nazov PROPERTY MODEL OBJECT.
		// !!!!! Na spravne mapovanie QUERY STRING PARAMETER musi mat SERVER SIDE VALIDATION METHOD ako PARAMETER TYPE [string], ktory moze mat LUBOVLNY NAME, no MUSI nan byt aplikovany ATTRIBUTE [BindAttribute] s hodnotou PROPERTY [BindAttribute.Prefix] nastavenou na VALUE [XXX.YYY].
		public JsonResult ValidateFirstName([Bind(Prefix="Child.FirstName")] string Parameter)
		{
			string												Value=Parameter;

			if (string.IsNullOrEmpty(Value)==false)
			{
				if (Value.Length>0)
				{
					if (char.IsUpper(Value[0])==true)
					{
						return(new JsonResult(true));
					}
				}
			}

			return(new JsonResult("WARNING - FIRST NAME must start with UPPER CASE CHARACTER !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD MUSI mat rovnaky NAME ako nazov PROPERTY, ktora ma byt VALIDATED.
		// !!! PARAMETER SERVER SIDE VALIDATION METHOD by MAL byt TYPE [string]. To preto, lebo ak by napriklad sa jednalo o PROPERTY TYPE [int] a USER by do prislusneho INPUT HTML ELEMENT zadal NON-INTEGER VALUE, tak by sa SERVER SIDE VALIDATION METHOD VOBEC NEZAVOLALA. Preto sa odporuca ako PARAMETER TYPE VZDY pouzivat TYPE [string].
		// !!! RETURN VALUE SERVER SIDE VALIDATION METHOD MUSI byt TYPE [JsonResult], kde v pripade, ze VALIDATION presla uspesne, tak je potrebne vratit VALUE 'true' a v pripade, ze VALIDATION ZLYHALA, vratit MESSAGE obsahujucu popis ERROR.
		// !!!!! Pri REMOTE VALIDATION je volana SERVER SIDE VALIDATION METHOD, ktorej QUERY STRING pouziva nazov PARAMETER [XXX.YYY], kde VALUE 'XXX' je nazov RAZOR PAGE MODEL OBJECT PROPERTY a VALUE 'YYY' je nazov PROPERTY MODEL OBJECT.
		// !!!!! Na spravne mapovanie QUERY STRING PARAMETER musi mat SERVER SIDE VALIDATION METHOD ako PARAMETER TYPE [string], ktory moze mat LUBOVLNY NAME, no MUSI nan byt aplikovany ATTRIBUTE [BindAttribute] s hodnotou PROPERTY [BindAttribute.Prefix] nastavenou na VALUE [XXX.YYY].
		public JsonResult ValidateLastName([Bind(Prefix="Child.LastName")] string Parameter)
		{
			string												Value=Parameter;

			if (string.IsNullOrEmpty(Value)==false)
			{
				if (Value.Length>0)
				{
					if (char.IsUpper(Value[0])==true)
					{
						return(new JsonResult(true));
					}
				}
			}

			return(new JsonResult("WARNING - LAST NAME must start with UPPER CASE CHARACTER !"));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------