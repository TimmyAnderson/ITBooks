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
	public sealed class CResolverDataLoaderBatchDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CDataLoaderBatchDependent> FieldResolverDelegateDependent(IResolverContext Context, CDataLoaderDataLoaderBatch DataLoader, CancellationToken CancellationToken, IMyLoggerService MyLoggerService)
		{
			MyLoggerService.LogResolver(nameof(CResolverDataLoaderBatchDependent),nameof(FieldResolverDelegateDependent));
				
			CDataLoaderBatchPrincipal							ParentObject=Context.Parent<CDataLoaderBatchPrincipal>();

			// !!! DATA sa citaju pomocou LOADER, a NIE priamym pristupom k DB.
			CDataLoaderBatchDependent							Result=await DataLoader.LoadAsync(ParentObject.PrincipalID,CancellationToken);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------