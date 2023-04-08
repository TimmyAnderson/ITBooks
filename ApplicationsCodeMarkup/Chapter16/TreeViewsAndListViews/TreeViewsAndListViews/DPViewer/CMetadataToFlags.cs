using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Data;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CMetadataToFlags : IValueConverter
	{
//------------------------------------------------------------------------------
        public object Convert(object Obj, Type Type, object Param, CultureInfo Culture)
        {
            FrameworkPropertyMetadataOptions	Flags=0;
            FrameworkPropertyMetadata			Metadata=Obj as FrameworkPropertyMetadata;

            if (Metadata==null)
                return(null);

            if (Metadata.AffectsMeasure)
                Flags|=FrameworkPropertyMetadataOptions.AffectsMeasure;

            if (Metadata.AffectsArrange)
                Flags|=FrameworkPropertyMetadataOptions.AffectsArrange;

            if (Metadata.AffectsParentMeasure)
                Flags|=FrameworkPropertyMetadataOptions.AffectsParentMeasure;

            if (Metadata.AffectsParentArrange)
                Flags|=FrameworkPropertyMetadataOptions.AffectsParentArrange;

            if (Metadata.AffectsRender)
                Flags|=FrameworkPropertyMetadataOptions.AffectsRender;

            if (Metadata.Inherits)
                Flags|=FrameworkPropertyMetadataOptions.Inherits;

            if (Metadata.OverridesInheritanceBehavior)
                Flags|=FrameworkPropertyMetadataOptions.OverridesInheritanceBehavior;

            if (Metadata.IsNotDataBindable)
                Flags|=FrameworkPropertyMetadataOptions.NotDataBindable;

            if (Metadata.BindsTwoWayByDefault)
                Flags|=FrameworkPropertyMetadataOptions.BindsTwoWayByDefault;

            if (Metadata.Journal)
                Flags|=FrameworkPropertyMetadataOptions.Journal;

            return(Flags);
        }
//------------------------------------------------------------------------------
        public object ConvertBack(object Obj, Type Type, object Param, CultureInfo Culture)
        {
            return(new FrameworkPropertyMetadata(null, (FrameworkPropertyMetadataOptions) Obj));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------