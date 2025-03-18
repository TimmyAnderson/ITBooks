using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess1
{
//----------------------------------------------------------------------------------------------------------------------
    public sealed class CDBContext : DbContext
    {
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CEntityConventionsOneToManyPrincipal>		MEntitiesConventionsOneToManyPrincipal;
		private DbSet<CEntityConventionsOneToManyDependent>		MEntitiesConventionsOneToManyDependent;
		private DbSet<CEntityDataAnnotationsOneToManyPrincipal>	MEntitiesDataAnnotationsOneToManyPrincipal;
		private DbSet<CEntityDataAnnotationsOneToManyDependent>	MEntitiesDataAnnotationsOneToManyDependent;
		private DbSet<CEntityFluentAPIOneToManyPrincipal>		MEntitiesFluentAPIOneToManyPrincipal;
		private DbSet<CEntityFluentAPIOneToManyDependent>		MEntitiesFluentAPIOneToManyDependent;
		private DbSet<CEntitySeparateConfigurations>			MEntitiesSeparateConfigurations;
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
		public DbSet<CEntityConventionsOneToManyPrincipal>		EntitiesConventionsOneToManyPrincipal
		{
			get
			{
				return(MEntitiesConventionsOneToManyPrincipal);
			}
			set
			{
				MEntitiesConventionsOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityConventionsOneToManyDependent>		EntitiesConventionsOneToManyDependent
		{
			get
			{
				return(MEntitiesConventionsOneToManyDependent);
			}
			set
			{
				MEntitiesConventionsOneToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataAnnotationsOneToManyPrincipal>	EntitiesDataAnnotationsOneToManyPrincipal
		{
			get
			{
				return(MEntitiesDataAnnotationsOneToManyPrincipal);
			}
			set
			{
				MEntitiesDataAnnotationsOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityDataAnnotationsOneToManyDependent>	EntitiesDataAnnotationsOneToManyDependent
		{
			get
			{
				return(MEntitiesDataAnnotationsOneToManyDependent);
			}
			set
			{
				MEntitiesDataAnnotationsOneToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityFluentAPIOneToManyPrincipal>		EntitiesFluentAPIOneToManyPrincipal
		{
			get
			{
				return(MEntitiesFluentAPIOneToManyPrincipal);
			}
			set
			{
				MEntitiesFluentAPIOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityFluentAPIOneToManyDependent>		EntitiesFluentAPIOneToManyDependent
		{
			get
			{
				return(MEntitiesFluentAPIOneToManyDependent);
			}
			set
			{
				MEntitiesFluentAPIOneToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntitySeparateConfigurations>				EntitiesSeparateConfigurations
		{
			get
			{
				return(MEntitiesSeparateConfigurations);
			}
			set
			{
				MEntitiesSeparateConfigurations=value;
			}
		}
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
		private void ConfigureEntityFluentAPIOneToManyPrincipal(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityFluentAPIOneToManyPrincipal>	Entity=ModelBuilder.Entity<CEntityFluentAPIOneToManyPrincipal>();

			Entity.ToTable("EntitiesFluentAPIOneToManyPrincipal");

			Entity.HasKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je CONFIGURED na PRINCIPAL ENTITY.

			// !!!!! Vytvori sa LEFT SIDE RELATIONSHIP.
			CollectionNavigationBuilder<CEntityFluentAPIOneToManyPrincipal,CEntityFluentAPIOneToManyDependent>	LeftSide=Entity.HasMany(P => P.EntitiesDependent);

			// !!!!! Vytvori sa RIGHT SIDE RELATIONSHIP.
			ReferenceCollectionBuilder<CEntityFluentAPIOneToManyPrincipal,CEntityFluentAPIOneToManyDependent>	RightSide=LeftSide.WithOne(P => P.EntityPrincipal);

			// !!!!! Vytvori sa FOREIGN KEY.
			RightSide.HasForeignKey(P => P.EntityPrincipalID);

			// !!!!! RELATIONSHIP je REQUIRED.
			RightSide.IsRequired(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityFluentAPIOneToManyDependent(ModelBuilder ModelBuilder)
		{
			EntityTypeBuilder<CEntityFluentAPIOneToManyDependent>	Entity=ModelBuilder.Entity<CEntityFluentAPIOneToManyDependent>();

			Entity.ToTable("EntitiesFluentAPIOneToManyDependent");

			Entity.HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntitySeparateConfigurations(ModelBuilder ModelBuilder)
		{
			// !!!!! CONFIGURATION je presunuta do separatnej CLASS.
			ModelBuilder.ApplyConfiguration(new CEntitySeparateConfigurationsConfig());
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureEntityNames(ModelBuilder);
			ConfigureEntityFluentAPIOneToManyPrincipal(ModelBuilder);
			ConfigureEntityFluentAPIOneToManyDependent(ModelBuilder);
			ConfigureEntitySeparateConfigurations(ModelBuilder);

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