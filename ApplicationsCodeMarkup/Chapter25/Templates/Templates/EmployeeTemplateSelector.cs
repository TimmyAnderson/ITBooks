using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
//-------------------------------------------------------------------------------------------------------
namespace Templates
{
//-------------------------------------------------------------------------------------------------------
	// DataTemplateSelector vracia DataTemplate podla OBJEKTU, ktoru chcem MAPOVAT v danom ELEMENTE.
	public class EmployeeTemplateSelector : DataTemplateSelector
	{
//-------------------------------------------------------------------------------------------------------
        public override DataTemplate SelectTemplate(object Item, DependencyObject Container)
        {
            Employee			Emp=Item as Employee;
            FrameworkElement	El=Container as FrameworkElement;

			// Najde RESOURCE na zaklade toho aka je hodnota LeftHanded triedy Employee.
            return((DataTemplate) El.FindResource((Emp.LeftHanded==true) ? "MTemplateLeft" : "MTemplateRight"));
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------