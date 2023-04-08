using System;
using System.Collections.Generic;
using System.Linq;
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
using System.Windows.Media.Animation;
//------------------------------------------------------------------------
namespace Graphics3DTest
{
//------------------------------------------------------------------------
	public partial class HitTesting:Window
	{
//------------------------------------------------------------------------
		public HitTesting()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Viewport_MouseDown(object Sender, MouseButtonEventArgs E)
        {
            Viewport3D						Viewport=(Viewport3D) Sender;
            Point							Location=E.GetPosition(Viewport);
            HitTestResult					HitResult=VisualTreeHelper.HitTest(Viewport, Location);
            
            if (HitResult!=null && HitResult.VisualHit==MRingVisual)
            {
                // Hit the ring.
            }
            
            RayMeshGeometry3DHitTestResult	MeshHitResult=HitResult as RayMeshGeometry3DHitTestResult;

            if (MeshHitResult!=null && MeshHitResult.ModelHit==MRingModel)
            {
                // Hit the ring.
            }

            if (MeshHitResult!=null && MeshHitResult.MeshHit==MRingMesh)
            {                
                MAxisRotation.Axis=new Vector3D(-MeshHitResult.PointHit.Y, MeshHitResult.PointHit.X, 0);

                DoubleAnimation				Animation=new DoubleAnimation();

                Animation.To=40;
                Animation.DecelerationRatio=1;
                Animation.Duration=TimeSpan.FromSeconds(0.15);
                Animation.AutoReverse=true;
                MAxisRotation.BeginAnimation(AxisAngleRotation3D.AngleProperty, Animation);
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------