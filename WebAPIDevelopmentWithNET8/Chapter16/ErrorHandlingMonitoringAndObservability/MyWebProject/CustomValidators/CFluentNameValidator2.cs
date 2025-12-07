using FluentValidation;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje CUSTOM VALIDATOR.
	public sealed class CFluentNameValidator2 : AbstractValidator<CFluentName2>
	{
//----------------------------------------------------------------------------------------------------------------------
		public CFluentNameValidator2()
		{
			IRuleBuilderInitial<CFluentName2,string>			FirstNameRule=RuleFor(P => P.FirstName);

			FirstNameRule.NotEmpty().WithMessage("FIRST NAME NOT SPECIFIED.");
			FirstNameRule.MaximumLength(15).WithMessage("FIRST NAME is LONGER than 15 CHARACTERS.");
				
			IRuleBuilderInitial<CFluentName2,string>			LastNameRule=RuleFor(P => P.LastName);

			LastNameRule.NotEmpty().WithMessage("LAST NAME NOT SPECIFIED.");
			LastNameRule.MaximumLength(20).WithMessage("LAST NAME is LONGER than 20 CHARACTERS.");

			IRuleBuilderInitial<CFluentName2,int>				AgeRule=RuleFor(P => P.Age);
				
			AgeRule.InclusiveBetween(0,100).WithMessage("AGE is OUT of RANGE <0,100>.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------