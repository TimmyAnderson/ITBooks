using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace Animations
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			EnlargeButtonWithTimer					Win=new EnlargeButtonWithTimer();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			EnlargeButtonWithAnimation				Win=new EnlargeButtonWithAnimation();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			EnlargeButtonInXaml						Win=new EnlargeButtonInXaml();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			EnlargeButtonsInXaml					Win=new EnlargeButtonsInXaml();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			TwoAnimations							Win=new TwoAnimations();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			WiggleWaggle							Win=new WiggleWaggle();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			WiggleWaggleAndExplode					Win=new WiggleWaggleAndExplode();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			ColorRadioButtons						Win=new ColorRadioButtons();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			StyleAnimations							Win=new StyleAnimations();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			StyleAnimations_Compose					Win=new StyleAnimations_Compose();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			BeginActionExitActionAnimation			Win=new BeginActionExitActionAnimation();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			ShakingButton							Win=new ShakingButton();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			ControllingTheStoryboard				Win=new ControllingTheStoryboard();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			RenderTransformVersusLayoutTransform	Win=new RenderTransformVersusLayoutTransform();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			TotalEclipseOfTheSun					Win=new TotalEclipseOfTheSun();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			AnimatedTextTransform					Win=new AnimatedTextTransform();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			SquaringTheCircle						Win=new SquaringTheCircle();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			RenderTheAnimation						Win=new RenderTheAnimation();
			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			Pulse									Win=new Pulse();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			PulsatingRectangle						Win=new PulsatingRectangle();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			ExpandingCircles						Win=new ExpandingCircles();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test22()
		{
			InfinityAnimation1						Win=new InfinityAnimation1();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test23()
		{
			InfinityAnimation2						Win=new InfinityAnimation2();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test24()
		{
			XamlClock								Win=new XamlClock();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test25()
		{
			AllXamlClock							Win=new AllXamlClock();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test26()
		{
			FourSidedBounce1						Win=new FourSidedBounce1();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test27()
		{
			FourSidedBounce2						Win=new FourSidedBounce2();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test28()
		{
			BouncingBall							Win=new BouncingBall();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test29()
		{
			BetterBouncingBall						Win=new BetterBouncingBall();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test30()
		{
			PendulumButton							Win=new PendulumButton();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test31()
		{
			SimpleKeyFrameAnimation					Win=new SimpleKeyFrameAnimation();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test32()
		{
			DiscretePointJumps						Win=new DiscretePointJumps();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test33()
		{
			KeyFramePointAnimation					Win=new KeyFramePointAnimation();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test34()
		{
			PacedAnimation							Win=new PacedAnimation();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test35()
		{
			SecondHandSteps							Win=new SecondHandSteps();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test36()
		{
			Diner1									Win=new Diner1();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test37()
		{
			Diner2									Win=new Diner2();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test38()
		{
			ColorAnimation							Win=new ColorAnimation();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test39()
		{
			AnotherBouncingBall						Win=new AnotherBouncingBall();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test40()
		{
			SplineKeyFrameExperiment				Win=new SplineKeyFrameExperiment();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test41()
		{
			NewtonsCradle							Win=new NewtonsCradle();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test42()
		{
			SimplePathAnimation						Win=new SimplePathAnimation();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test43()
		{
			PathAnimatedButton						Win=new PathAnimatedButton();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test44()
		{
			PathAngleAnimatedButton					Win=new PathAngleAnimatedButton();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test45()
		{
			RectangularOpacity						Win=new RectangularOpacity();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test46()
		{
			MatrixAnimatedButton					Win=new MatrixAnimatedButton();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test47()
		{
			UnicycleMan								Win=new UnicycleMan();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				//Test1();
				//Test2();
				//Test3();
				//Test4();
				//Test5();
				//Test6();
				//Test7();
				//Test8();
				//Test9();
				//Test10();
				//Test11();
				//Test12();
				//Test13();
				//Test14();
				//Test15();
				//Test16();
				//Test17();
				//Test18();
				//Test19();
				//Test20();
				//Test21();
				//Test22();
				//Test23();
				//Test24();
				//Test25();
				//Test26();
				//Test27();
				//Test28();
				//Test29();
				//Test30();
				//Test31();
				//Test32();
				//Test33();
				//Test34();
				//Test35();
				//Test36();
				//Test37();
				//Test38();
				//Test39();
				//Test40();
				//Test41();
				//Test42();
				//Test43();
				//Test44();
				//Test45();
				//Test46();
				Test47();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------