using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Media.Media3D;
//------------------------------------------------------------------------
namespace Graphics3DTest
{
//------------------------------------------------------------------------
	public partial class CubeMesh:Window
	{
//------------------------------------------------------------------------
		public CubeMesh()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private Vector3D CalculateNormal(Point3D P0, Point3D P1, Point3D P2)
        {
            Vector3D			V0=new Vector3D(P1.X - P0.X, P1.Y - P0.Y, P1.Z - P0.Z);
            Vector3D			V1=new Vector3D(P2.X - P1.X, P2.Y - P1.Y, P2.Z - P1.Z);

            return(Vector3D.CrossProduct(V0, V1));
        }
//------------------------------------------------------------------------
        private void Cmd_Click(object Sender, RoutedEventArgs E)
        {
            MCubeGeometry.Geometry=(Geometry3D)((Button) Sender).Tag;
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------