using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
// !!!!! PROJECT reprezentuje [WINDOWS RUNTIME COMPONENT], a preto pre PUBLIC TYPES sa VZTAHUJU obmedzenia WinRT TYPE SYSTEM.
//-------------------------------------------------------------------------------------------------------
// WinRT COMPONENTS musia deklarovat NAMESPACES s menom IDENTICKYM ako je FILE NAME WinRT COMPONENT (bez FILE EXTENSION .WIN), s menom, ktore je SUBNAMESPACE FILE NAME WinRT COMPONENT (bez FILE EXTENSION .WIN).
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	// !!! WinRT CLASSES MUSIA by SEALED.
	public sealed class CName
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFirstName;
		private readonly string									MLastName;
		private readonly int									MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! WinRT COMPONENTS NEMAJU spolocny BASE CLASS. Avsak .NET vykonava PROJECTION kadzeho OBJECT, takze WinRT COMPONENT ziska METHODS, ktore su DERIVED z .NET Object CLASS ako napriklad Object.GetType() ci Object.ToString().
		public override string ToString()
		{
			string												Text=string.Format("Name: [{0} {1}], Age: [{2}]",MFirstName,MLastName,MAge);

			return(Text);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------