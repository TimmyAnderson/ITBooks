using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace Client
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pri pouziti SQL AUTHENTICATION platia nasledujuce fakty.
	// !!!!! 1. CONNECTION STRING na VALUE [Server=tcp:ta76dbserver.database.windows.net,1433;Initial Catalog=MyDatabase;Persist Security Info=False;User ID=mydbadmin;Password=Qaxwsx123+.;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;].
	// !!!!! 2. NA SQL SERVERI MUSI byt povolena OPTION [Allow Azure services and resources to access this server]. OPTION moze byt povolena aj pomocou COMMAND [az sql server firewall-rule create --name AllowAzureService --resource-group Chapter07 --server ta76dbserver --start-ip-address 0.0.0.0 --end-ip-address 0.0.0.0].
    public sealed class CDBContext : DbContext
    {
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityName>								MEntitiesNames;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext(DbContextOptions<CDBContext> Options)
			: base(Options)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityName>								EntitiesNames
		{
			get
			{
				return(MEntitiesNames);
			}
			set
			{
				MEntitiesNames=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityNames(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityName>().ToTable("NamesEntities");

			ModelBuilder.Entity<CEntityName>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityNames(ModelBuilder);

			EntityTypeBuilder<CEntityName>						Entity=ModelBuilder.Entity<CEntityName>();

			List<CEntityName>									Names=new List<CEntityName>();

			Names.Add(new CEntityName(1,"Timmy","Anderson",12,ESex.E_MALE));
			Names.Add(new CEntityName(2,"Jenny","Thompson",13,ESex.E_FEMALE));

			Entity.HasData(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------