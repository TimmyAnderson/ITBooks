using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows.Data;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	public class CTypeToString : IValueConverter
	{
//------------------------------------------------------------------------------
        public object Convert(object Obj, Type Type, object Param, CultureInfo Culture)
        {
            return((Obj as Type).Name);
        }
//------------------------------------------------------------------------------
        public object ConvertBack(object Obj, Type Type, object Param, CultureInfo Culture)
        {
            return(null);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------