using System.Linq;
using System.Security.Claims;
using Microsoft.AspNetCore.SignalR;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingSignalR
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyUserIdProvider : IUserIdProvider
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public string GetUserId(HubConnectionContext Connection)
		{
			if (Connection.User!=null)
			{
				// !!! Hlada sa CLAIM [Name].
				Claim											Claim=Connection.User.Claims.Where(P => P.Type==ClaimTypes.Name).FirstOrDefault();

				if (Claim!=null)
				{
					string										ClaimValue=Claim.Value;

					if (ClaimValue!=null)
					{
						return(ClaimValue);
					}
				}
			}

			return("");
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------