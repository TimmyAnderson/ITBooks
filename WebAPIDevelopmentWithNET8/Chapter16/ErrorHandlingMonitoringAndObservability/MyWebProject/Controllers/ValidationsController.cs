using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FluentValidation;
using FluentValidation.Results;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class ValidationsController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IValidator<CFluentName1>				MFluentNameValidator1;
		private readonly IValidator<CFluentName2>				MFluentNameValidator2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ValidationsController(IValidator<CFluentName1> FluentNameValidator1, IValidator<CFluentName2> FluentNameValidator2)
		{
			MFluentNameValidator1=FluentNameValidator1;
			MFluentNameValidator2=FluentNameValidator2;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost(nameof(StandardValidation))]
		public IActionResult StandardValidation(CName Name)
		{
			CName												ResponseName=new CName(Name.FirstName.ToUpper(),Name.LastName.ToUpper(),Name.Age+10);

			IActionResult										Result=Ok(ResponseName);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost(nameof(FluentValidation1))]
		public async Task<IActionResult> FluentValidation1(CFluentName1 Name)
		{
			ValidationResult									ValidationResult=await MFluentNameValidator1.ValidateAsync(Name);

			if (ValidationResult.IsValid==true)
			{
				CFluentName1									ResponseName=new CFluentName1(Name.FirstName.ToUpper(),Name.LastName.ToUpper(),Name.Age+10);

				IActionResult									Result=Ok(ResponseName);

				return(Result);
			}
			else
			{
				// !!! Vrati sa PROBLEM DETAILS.
				ValidationProblemDetails						ResponseError=new ValidationProblemDetails(ValidationResult.ToDictionary());

				IActionResult									Result=Ok(ResponseError);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost(nameof(FluentValidation2))]
		public async Task<IActionResult> FluentValidation2(CFluentName2 Name)
		{
			ValidationResult									ValidationResult=await MFluentNameValidator2.ValidateAsync(Name);

			if (ValidationResult.IsValid==true)
			{
				CFluentName2									ResponseName=new CFluentName2(Name.FirstName.ToUpper(),Name.LastName.ToUpper(),Name.Age+10);

				IActionResult									Result=Ok(ResponseName);

				return(Result);
			}
			else
			{
				// !!! Vrati sa PROBLEM DETAILS.
				ValidationProblemDetails						ResponseError=new ValidationProblemDetails(ValidationResult.ToDictionary());

				IActionResult									Result=Ok(ResponseError);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------