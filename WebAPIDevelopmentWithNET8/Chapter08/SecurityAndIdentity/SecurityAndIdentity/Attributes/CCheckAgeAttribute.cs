using System.ComponentModel.DataAnnotations;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCheckAgeAttribute : ValidationAttribute
	{
//----------------------------------------------------------------------------------------------------------------------
		protected override ValidationResult IsValid(object Value, ValidationContext ValidationContext)
		{
			int													TypedValue=(int) Value;

			if (TypedValue>=0 && TypedValue<=18)
			{
				return(ValidationResult.Success);
			}
			else
			{
				ValidationResult								Result=new ValidationResult("Invalid AGE.");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------