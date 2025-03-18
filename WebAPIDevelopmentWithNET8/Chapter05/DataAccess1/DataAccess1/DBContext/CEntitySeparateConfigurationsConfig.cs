using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess1
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! INTERFACE [IEntityTypeConfiguration<TType>] umoznuje presunut ENTITY CONFIGURATION do separatnej CLASS.
	public sealed class CEntitySeparateConfigurationsConfig : IEntityTypeConfiguration<CEntitySeparateConfigurations>
	{
//----------------------------------------------------------------------------------------------------------------------
		public void Configure(EntityTypeBuilder<CEntitySeparateConfigurations> Builder)
		{
			Builder.ToTable("EntitieSeparateConfigurations");

			// !!! Zmeni sa SQL STRING TYPE, aby NEBOL UNICODE.
			Builder.Property(P => P.StringNonUnicodeWithMaxLength).IsUnicode(false);

			// !!! Zmeni sa SQL TYPE na 'DATE'.
			Builder.Property(P => P.DateTimeWithSQLTypeDATEAndIndex).HasColumnType("date");

			// !!! Zmeni sa SQL TYPE DOUBLE, aby mal definovanu PRECISION.
			Builder.Property(P => P.DoubleWithLimitedPrecision).HasPrecision(9,2);

			// !!! Nad PROPERTY sa VYTVORI INDEX.
			Builder.HasIndex(P => P.DateTimeWithSQLTypeDATEAndIndex);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------