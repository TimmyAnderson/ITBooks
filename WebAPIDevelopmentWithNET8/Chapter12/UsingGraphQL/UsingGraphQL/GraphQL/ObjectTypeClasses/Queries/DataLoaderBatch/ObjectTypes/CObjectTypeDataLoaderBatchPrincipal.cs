using System;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using HotChocolate.Resolvers;
using HotChocolate.Types;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CObjectTypeDataLoaderBatchPrincipal : ObjectType<CDataLoaderBatchPrincipal>
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFieldDependents(IObjectTypeDescriptor<CDataLoaderBatchPrincipal> Descriptor)
		{
			IObjectFieldDescriptor								FieldDescriptor=Descriptor.Field(P => P.Dependent);

			FieldDescriptor.Name("Dependent");

			FieldDescriptor.Description($"This is FIELD [{nameof(CDataLoaderBatchPrincipal.Dependent)}].");

			FieldDescriptor.Type<CObjectTypeDataLoaderBatchDependent>();

			FieldDescriptor.ResolveWith<CResolverDataLoaderBatchDependent>(P => P.FieldResolverDelegateDependent(default,default,default,default));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void Configure(IObjectTypeDescriptor<CDataLoaderBatchPrincipal> Descriptor)
		{
			Descriptor.Name("myDataLoaderBatchPrincipal");

			Descriptor.Description($"This is OBJECT [{nameof(CDataLoaderBatchPrincipal)}].");

			ConfigureFieldDependents(Descriptor);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------