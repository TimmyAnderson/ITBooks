using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
//----------------------------------------------------------------------------------------------------------------------
namespace NewIdentityAPI
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje DB CONTEXT pre IDENTITY FRAMEWORK DB.
	public sealed class CIdentityContextDB : IdentityDbContext<CIdentityUser,CIdentityRole,string>
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CIdentityContextDB(DbContextOptions<CIdentityContextDB> Options, IConfiguration Configuration)
			: base(Options)
		{
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			base.OnConfiguring(OptionsBuilder);

			string												ConnectionString=MConfiguration.GetConnectionString("MyIdentityDBConnection");

			OptionsBuilder.UseSqlite(ConnectionString);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------