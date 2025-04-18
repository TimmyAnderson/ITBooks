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
	// !!! OBJECT TYPE TYPE [InterfaceType<TRuntineType>] pre INTERFACE TYPE.
	public sealed class CObjectTypeInterfacesMyInterface : InterfaceType<IInterfacesMyInterface>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldID(IInterfaceTypeDescriptor<IInterfacesMyInterface> Descriptor)
		{
			IInterfaceFieldDescriptor							FieldDescriptor=Descriptor.Field(P => P.ID);

			FieldDescriptor.Name("INTERFACE_ID");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldSharedValue1(IInterfaceTypeDescriptor<IInterfacesMyInterface> Descriptor)
		{
			IInterfaceFieldDescriptor							FieldDescriptor=Descriptor.Field(P => P.SharedValue1);

			FieldDescriptor.Name("INTERFACE_SHARED_VALUE_1");
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldSharedValue2(IInterfaceTypeDescriptor<IInterfacesMyInterface> Descriptor)
		{
			IInterfaceFieldDescriptor							FieldDescriptor=Descriptor.Field(P => P.SharedValue2);

			FieldDescriptor.Name("INTERFACE_SHARED_VALUE_2");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	    protected override void Configure(IInterfaceTypeDescriptor<IInterfacesMyInterface> Descriptor)
		{
			Descriptor.Description($"This is OBJECT [{nameof(IInterfacesMyInterface)}].");

			ConfigureFieldID(Descriptor);
			ConfigureFieldSharedValue1(Descriptor);
			ConfigureFieldSharedValue2(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------