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
	public sealed class CResolverDataLoaderGroupDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDataLoaderGroupDependent[]> FieldResolverDelegateDependentArray(IResolverContext Context, CDataLoaderDataLoaderGroup DataLoader, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverDataLoaderGroupDependent),nameof(FieldResolverDelegateDependentArray));

			CDataLoaderGroupPrincipal							ParentObject=Context.Parent<CDataLoaderGroupPrincipal>();

			// !!! DATA sa citaju pomocou LOADER, a NIE priamym pristupom k DB.
			CDataLoaderGroupDependent[]							Result=await DataLoader.LoadAsync(ParentObject.PrincipalID,CancellationToken);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------