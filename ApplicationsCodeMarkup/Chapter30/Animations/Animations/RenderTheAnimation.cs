using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
//-------------------------------------------------------------------------------------------------------
namespace Animations
{
//-------------------------------------------------------------------------------------------------------
	public class RenderTheAnimation : Window
	{
//-------------------------------------------------------------------------------------------------------
        public RenderTheAnimation()
        {
            Title="Render the Animation";

			// Custom ELEMENT, ktory sa animuje anmaciou definovanou v DrawEllipse().
            Content=new AnimatedCircle();
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------