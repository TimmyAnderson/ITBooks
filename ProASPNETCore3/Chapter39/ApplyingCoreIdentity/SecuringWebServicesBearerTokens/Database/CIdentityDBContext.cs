using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using SecuringWebServicesBearerTokens.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Database
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CIdentityDBContext : IdentityDbContext<CCustomUser,CCustomRole,string>
	{
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			base.OnConfiguring(OptionsBuilder);

			OptionsBuilder.UseSqlite("Data Source=MyDatabase.db");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------