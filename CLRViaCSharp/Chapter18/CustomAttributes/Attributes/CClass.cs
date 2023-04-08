using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
// !!! ATTRIBUTE je aplikovany na ASSEMBLY.
[assembly:Attributes.CMySuperAttribute]
// !!! ATTRIBUTE je aplikovany na MODULE.
[module:Attributes.CMySuperAttribute]
//-------------------------------------------------------------------------------------------------------
namespace Attributes
{
//-------------------------------------------------------------------------------------------------------
	// !!! ATTRIBUTE je aplikovany na CLASS.
	[type:CMySuperAttribute]
	// Opakovanie sa ATTRIBUTES.
	[CMySuperAttribute,CMySuperAttribute]
	public sealed class CClass
	{
//-------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE je aplikovany na FIELD.
		[field:CMySuperAttribute]
		private string											MField;
//-------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE je aplikovany na skryty EVENT.
		[event:CMySuperAttribute]
		// !!! ATTRIBUTE je aplikovany na skryty EVENT FIELD.
		[field:CMySuperAttribute]
		// !!! ATTRIBUTE je aplikovany na ADD a REMOVE EVENT METHODS.
		[method:CMySuperAttribute]
		public event EventHandler								SomeEvent;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE je aplikovany na CONSTRUCTOR.
		[method:CMySuperAttribute]
		public CClass()
		{
			MField="Timmy";
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE je aplikovany na PROPERTY.
		[property:CMySuperAttribute]
		public string											SomeProperty
		{
			// !!! ATTRIBUTE je aplikovany na ACCESS METHOD.
			[method:CMySuperAttribute]
			get
			{
				return(MField);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE je aplikovany na METHOD.
		[method:CMySuperAttribute]
		// !!! ATTRIBUTE je aplikovany na RETURN VALUE.
		[return:CMySuperAttribute]
		// !!! ATTRIBUTE je aplikovany na PARAMETER.
		public string SomeMethod([param:CMySuperAttribute] string Param)
		{
			if (SomeEvent!=null)
			{
				SomeEvent=null;
			}

			return(Param);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------