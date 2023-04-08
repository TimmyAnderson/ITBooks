using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CIdentityDbContext : IdentityDbContext<IdentityUser,IdentityRole,string>
	{
//----------------------------------------------------------------------------------------------------------------------
		public CIdentityDbContext()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
        public CIdentityDbContext(DbContextOptions<CIdentityDbContext> Options)
            : base(Options)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			base.OnConfiguring(OptionsBuilder);

			OptionsBuilder.UseSqlite("Data Source=MyIdentityDatabase.db");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------