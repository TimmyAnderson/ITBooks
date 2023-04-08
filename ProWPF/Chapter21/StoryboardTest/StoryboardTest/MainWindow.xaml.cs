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
//------------------------------------------------------------------------
// 1. Program demonstruje animaciu pomocou Storyboards.
// 2. Storyboard sluzi na definovanie animacie v XAML. Obsahuje vsetky dolezite properties, ktorym je mozne definovat DP a Element, ktory sa bude animovat.
// 3. Odpalovanie Eventov sa robi pomocou EventTrigger, kde do Actions sa uklada BeginStoryboard, pomocou ktorej mozem spustat animacie. Na spustenie animacie je mozne pouzit aj BEZNY TRIGGER (trieda Trigger), kde vyuzijem property EnterActions (ked sa hodnota zmeni nahodnotu Trigger), alebo property ExitActions (ked sa hodnota zmeni na INU hodnotu aku testuje Trigger).
// !!! 4. Ak v Storyboard nespecifikujem TargetName pouzije sa automaticky Parent Element a na nom sa aplikuej animacia.
// !!! 5. Pomocou property HandoffBehavior nastavenej na Compose MOZEM KOMBINOVAT 2 ANIMATION NA TEJ ISTEJ DP.
// 6. Pomocou StoryBoard je mozne kombinovat aj viacero animacii NAD ROZLICNYMI DP. Staci naplnit do Storyboard viacero animacii. Vyhodou je, ze sa obe spustia v rovnakom case.
// !!! 7. Okrem BeginStoryboard existuje aj velke mnozstvo inych tried (PauseStoryboard, ResumeStoryboard, StopStoryboard, ci RemoveStoryboard) vdaka, ktorym je mozne menit priebeh animacie. NEVYHODOU JE, ZE VSETKY MUSIA BYT V TEJ ISTEJ Triggers COLLECTION. Neda sa jednu definovat v jednej a druhu v inej.
// 8. Storyborad definuje niekolko Events, ktore sa vyvolavaju pri rozlicnych udalostiach. Napriklad sa vola pri ukonceni animacie, pri jej odstraneni, ci pri posune casu.
// !!! 9. Trieda Clock je zodpovedna za realizaciu animacii. Ma niekolko zaujimavych properties, ktore urcuju napriklad poziciu animacie CurrentProgress, cas a podobne.
// 10. Pomocou property Timeline.DesiredFrameRate je mozne menit FPS. Zvysit, alebo znizit frames per second. Zmysel ma najm] znizenie ak ma jednoduchu animaciu, ktora 60 FPS nepotrebuje a nechcem zbytocne zabijat CPU.
//------------------------------------------------------------------------
namespace StoryboardTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			SimpleStoryboard			Win=new SimpleStoryboard();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			APStoryboard				Win=new APStoryboard();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			AnimationByNormalTrigger	Win=new AnimationByNormalTrigger();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			CTAnimation					Win=new CTAnimation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			SimultaneousAnimations		Win=new SimultaneousAnimations();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			ControllingPlayback		Win=new ControllingPlayback();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			DesiredFrameRate		Win=new DesiredFrameRate();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------