using System;
using System.Linq;
using System.Threading.Tasks;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! OBJECT TYPE TYPE [UnionType] pre UNION TYPE.
	public sealed class CObjectTypeUnions : UnionType
	{
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IUnionTypeDescriptor Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(CObjectTypeUnions)}].");

			Descriptor.Name("UNIONS");

			// !!! Zaregistruju sa vsetky OBJECT TYPES k TYPES, ktore tvoria UNION TYPE.
			Descriptor.Type<CObjectTypeUnionsMyClass1>();
			Descriptor.Type<CObjectTypeUnionsMyClass2>();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------