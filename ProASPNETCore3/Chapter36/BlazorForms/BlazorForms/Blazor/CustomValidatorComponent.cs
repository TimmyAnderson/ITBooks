using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using BlazorForms.Model;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Forms;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM VALIDATOR BLAZOR COMPONENT.
    public class CustomValidatorComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [EditContext] osahuje MEMBERS, ktore umoznuju vykonat CUSTOM VALIDATION.
		// !!!!! PARAMETER je naplneny BLAZOR COMPONENT [EditForm].
		private EditContext										MCurrentEditContext;
		// !!! FIELD definuje nazov FIELD, ktory ma byt VALIDATED.
		private string											MFieldName;
		// !!! Definuje minimalny pocet CHARACTERS, ktory FIELD musi obsahovat.
		private int												MMinimumLength;
		// !!! FIELD obsahuje STORAGE CLASS do ktorej sa ukladaju VALIDATION ERROR MESSAGES, ktore ma BLAZOR FRAMEWORK zobrazit.
		private ValidationMessageStore							MMessageStore;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAZOV PARAMETER moze byt LUBOVOLNY.
		[CascadingParameter]
		public EditContext										CurrentEditContext
		{
			get
			{
				return(MCurrentEditContext);
			}
			set
			{
				MCurrentEditContext=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public string											FieldName
		{
			get
			{
				return(MFieldName);
			}
			set
			{
				MFieldName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public int												MinimumLength
		{
			get
			{
				return(MMinimumLength);
			}
			set
			{
				MMinimumLength=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! 1. PARAMETER obsahuje FIELD, pre ktory bola VALIDATION spustena.
		// !!! 2. PARAMETER obsahuje MODEL OBJECT s C# PROPERTIES naplnenymi VALUES z BLAZOR FORM COMPONENTNS.
		private void PerformValidation(FieldIdentifier Field, CPerson ModelObject)
		{
			if (MFieldName==Field.FieldName && Field.FieldName=="FirstName")
			{
				if (ModelObject.FirstName.Length<MMinimumLength)
				{
					// !!! Prida sa VALIDATION ERROR MESSAGE.
					MMessageStore.Add(Field,$"FIELD [{MFieldName}] MUST have at least [{MMinimumLength}] CHARACTERS !");
				}
				else
				{
					// !!! Vymazu sa existujuce ERROR MESSAGES.
					MMessageStore.Clear();
				}

				// !!! BLAZOR FRAMEWORK je notifikovany o zmene VALIDATION STATE.
				MCurrentEditContext.NotifyValidationStateChanged();
			}
			else if (MFieldName==Field.FieldName && Field.FieldName=="LastName")
			{
				if (ModelObject.LastName.Length<MMinimumLength)
				{
					// !!! Prida sa VALIDATION ERROR MESSAGE.
					MMessageStore.Add(Field,$"FIELD [{MFieldName}] MUST have at least [{MMinimumLength}] CHARACTERS !");
				}
				else
				{
					// !!! Vymazu sa existujuce ERROR MESSAGES.
					MMessageStore.Clear();
				}

				// !!! BLAZOR FRAMEWORK je notifikovany o zmene VALIDATION STATE.
				MCurrentEditContext.NotifyValidationStateChanged();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private void OnFieldChanged(object Sender, FieldChangedEventArgs E)
		{
			CPerson												Model=(CPerson) E.FieldIdentifier.Model;
			
			PerformValidation(E.FieldIdentifier,Model);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnInitialized()
		{
			MMessageStore=new ValidationMessageStore(MCurrentEditContext);

			// !!! Zaregistruje sa VALIDATION CALLBACK pri zmene hodnoty niektoreho z FIELD.
			MCurrentEditContext.OnFieldChanged+=OnFieldChanged;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------