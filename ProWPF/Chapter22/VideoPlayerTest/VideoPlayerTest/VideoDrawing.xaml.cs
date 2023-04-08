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
using System.Windows.Media.Animation;
//------------------------------------------------------------------------
namespace VideoPlayerTest
{
//------------------------------------------------------------------------
	public partial class VideoDrawing:Window
	{
//------------------------------------------------------------------------
		public VideoDrawing()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdPlayCode_Click(object Sender, RoutedEventArgs E)
        {
            // Create the timeline.
            // This isn't required, but it allows you to configure details that wouldn't otherwise be possible (like repetition).
            MediaTimeline		Timeline = new MediaTimeline(new Uri("Videos/Test.mpg", UriKind.Relative));

            Timeline.RepeatBehavior=RepeatBehavior.Forever;

            // Create the clock, which is shared with the MediaPlayer.
            MediaClock			Clock=Timeline.CreateClock();
            MediaPlayer			Player=new MediaPlayer();

            Player.Clock=Clock;

			/*
            // Create the VideoDrawing.
            VideoDrawing		VideoDrawing=new VideoDrawing();

            VideoDrawing.Rect=new Rect(150, 0, 100, 100);
            VideoDrawing.Player=Player;

            // Assign the DrawingBrush.
            DrawingBrush		Brush=new DrawingBrush(VideoDrawing);

            this.Background=Brush;

            // Start the timeline.
            Clock.Controller.Begin();
			*/
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------