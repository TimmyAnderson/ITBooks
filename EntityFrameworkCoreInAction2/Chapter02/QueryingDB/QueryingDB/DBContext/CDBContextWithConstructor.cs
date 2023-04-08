using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Console;
using Microsoft.Extensions.Options;
//----------------------------------------------------------------------------------------------------------------------
namespace QueryingDB
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBContextWithConstructor : DbContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
		private DbSet<CTestEntity>								MTestEntities;
		private DbSet<CEntityOneToOnePrincipal>					MEntitiesOneToOnePrincipal;
		private DbSet<CEntityOneToOneDependent>					MEntitiesOneToOneDependent;
		private DbSet<CEntityOneToManyPrincipal>				MEntitiesOneToManyPrincipal;
		private DbSet<CEntityOneToManyDependent>				MEntitiesOneToManyDependent;
		private DbSet<CEntityManyToManyM>						MEntitiesManyToManyM;
		private DbSet<CEntityManyToManyN>						MEntitiesManyToManyN;
		private DbSet<CEntityManyToManyMN>						MEntitiesManyToManyMN;
		private bool											MDonNotCallUseSqlLite;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// OPTIONS sa nastavuju explicitne v CONSTRUCTOR.
		public CDBContextWithConstructor(DbContextOptions<CDBContextWithConstructor> Options)
			: base(Options)
		{
			MDonNotCallUseSqlLite=true;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CTestEntity>								TestEntities
		{
			get
			{
				return(MTestEntities);
			}
			set
			{
				MTestEntities=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOnePrincipal>					EntitiesOneToOnePrincipal
		{
			get
			{
				return(MEntitiesOneToOnePrincipal);
			}
			set
			{
				MEntitiesOneToOnePrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToOneDependent>					EntitiesOneToOneDependent
		{
			get
			{
				return(MEntitiesOneToOneDependent);
			}
			set
			{
				MEntitiesOneToOneDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyPrincipal>					EntitiesOneToManyPrincipal
		{
			get
			{
				return(MEntitiesOneToManyPrincipal);
			}
			set
			{
				MEntitiesOneToManyPrincipal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityOneToManyDependent>					EntitiesOneToManyDependent
		{
			get
			{
				return(MEntitiesOneToManyDependent);
			}
			set
			{
				MEntitiesOneToManyDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyM>						EntitiesManyToManyM
		{
			get
			{
				return(MEntitiesManyToManyM);
			}
			set
			{
				MEntitiesManyToManyM=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyN>						EntitiesManyToManyN
		{
			get
			{
				return(MEntitiesManyToManyN);
			}
			set
			{
				MEntitiesManyToManyN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DbSet<CEntityManyToManyMN>						EntitiesManyToManyMN
		{
			get
			{
				return(MEntitiesManyToManyMN);
			}
			set
			{
				MEntitiesManyToManyMN=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTestEntity(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CTestEntity>().ToTable("TestEntities");

			ModelBuilder.Entity<CTestEntity>().HasKey(P => P.ID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableOneToOnePrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToOnePrincipal>().ToTable("EntitiesOneToOnePrincipal");

			ModelBuilder.Entity<CEntityOneToOnePrincipal>().HasKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTableOneToOneDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToOneDependent>().ToTable("EntitiesOneToOneDependent");

			ModelBuilder.Entity<CEntityOneToOneDependent>().HasKey(P => P.EntityDependentID);

			EntityTypeBuilder<CEntityOneToOneDependent>			Entity=ModelBuilder.Entity<CEntityOneToOneDependent>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityOneToOneDependent,CEntityOneToOnePrincipal>	LeftSideRelationship=Entity.HasOne(P => P.EntityPrincipal);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceReferenceBuilder<CEntityOneToOneDependent,CEntityOneToOnePrincipal>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityDependent);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey<CEntityOneToOneDependent>(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyPrincipal(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToManyPrincipal>().ToTable("EntitiesOneToManyPrincipal");

			ModelBuilder.Entity<CEntityOneToManyPrincipal>().HasKey(P => P.EntityPrincipalID);

			EntityTypeBuilder<CEntityOneToManyPrincipal>		Entity=ModelBuilder.Entity<CEntityOneToManyPrincipal>();

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			CollectionNavigationBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	LeftSideRelationship=Entity.HasMany(P => P.EntitiesDependent);

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	RightSideRelationship=LeftSideRelationship.WithOne(P => P.EntityPrincipal);

			// !!!!! Definuje sa FOREIGN KEY.
			RightSideRelationship.HasForeignKey(P => P.EntityPrincipalID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityOneToManyDependent(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityOneToManyDependent>().ToTable("EntitiesOneToManyDependent");

			ModelBuilder.Entity<CEntityOneToManyDependent>().HasKey(P => P.EntityDependentID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyM(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyM>().ToTable("EntitiesManyToManyM");

			ModelBuilder.Entity<CEntityManyToManyM>().HasKey(P => P.EntityMID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyN>().ToTable("EntitiesManyToManyN");

			ModelBuilder.Entity<CEntityManyToManyN>().HasKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureEntityManyToManyMN(ModelBuilder ModelBuilder)
		{
			ModelBuilder.Entity<CEntityManyToManyMN>().ToTable("EntitiesManyToManyMN");

			// !!!!! LINK ENTITY v RELATIONSHIP M:N MUSI mat COMPOSITE KEY.
			ModelBuilder.Entity<CEntityManyToManyMN>().HasKey(nameof(CEntityManyToManyMN.EntityMID),nameof(CEntityManyToManyMN.EntityNID));

			EntityTypeBuilder<CEntityManyToManyMN>				Entity=ModelBuilder.Entity<CEntityManyToManyMN>();

			// !!!!! Vytvori sa RELATIONSHIP 1:N medzi LINK ENTITY a ENTITY M.

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityManyToManyMN,CEntityManyToManyM>	RightSideEntityM=Entity.HasOne(P => P.EntityM);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityManyToManyM,CEntityManyToManyMN>	LeftSideEntityM=RightSideEntityM.WithMany(P => P.EntitiesMN);

			// !!!!! Definuje sa FOREIGN KEY.
			LeftSideEntityM.HasForeignKey(P => P.EntityMID);

			// !!!!! Vytvori sa RELATIONSHIP 1:N medzi LINK ENTITY a ENTITY M.

			// !!! Definuje sa RIGHT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceNavigationBuilder<CEntityManyToManyMN,CEntityManyToManyN>	RightSideEntityN=Entity.HasOne(P => P.EntityN);

			// !!! Definuje sa LEFT SIDE RELATIONSHIP s definovanim NAVIGATION PROPERTY.
			ReferenceCollectionBuilder<CEntityManyToManyN,CEntityManyToManyMN>	LeftSideEntityN=RightSideEntityN.WithMany(P => P.EntitiesMN);

			// !!!!! Definuje sa FOREIGN KEY.
			LeftSideEntityN.HasForeignKey(P => P.EntityNID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			if (MDonNotCallUseSqlLite==false)
			{
				OptionsBuilder.UseSqlite(MConnectionString_SQLITE);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnModelCreating(ModelBuilder ModelBuilder)
		{
			ConfigureTestEntity(ModelBuilder);
			ConfigureTableOneToOnePrincipal(ModelBuilder);
			ConfigureTableOneToOneDependent(ModelBuilder);
			ConfigureEntityOneToManyPrincipal(ModelBuilder);
			ConfigureEntityOneToManyDependent(ModelBuilder);
			ConfigureEntityManyToManyM(ModelBuilder);
			ConfigureEntityManyToManyN(ModelBuilder);
			ConfigureEntityManyToManyMN(ModelBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------