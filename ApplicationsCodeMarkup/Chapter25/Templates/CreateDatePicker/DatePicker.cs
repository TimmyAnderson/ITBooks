using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace CreateDatePicker
{
//-------------------------------------------------------------------------------------------------------
	public partial class DatePicker
	{
//-------------------------------------------------------------------------------------------------------
        private UniformGrid										MUnigridMonth;
        private DateTime										MDateTimeSaved=DateTime.Now.Date;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public event RoutedPropertyChangedEventHandler<DateTime?> DateChanged
        {
            add
			{
				AddHandler(DateChangedEvent, value);
			}
            remove
			{
				RemoveHandler(DateChangedEvent, value);
			}
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// DP reprezentujuca vybrany datum.
		// !!! Vola sa CALLBACK DateChangedCallback() vzdy pri zmene hodnoty DP.
        public static readonly DependencyProperty				DateProperty=DependencyProperty.Register("Date", typeof(DateTime?), typeof(DatePicker), new PropertyMetadata(new DateTime(), DateChangedCallback));
//-------------------------------------------------------------------------------------------------------
		// RE volana pri zmene vyberu datumu.
        public static readonly RoutedEvent						DateChangedEvent=EventManager.RegisterRoutedEvent("DateChanged", RoutingStrategy.Bubble, typeof(RoutedPropertyChangedEventHandler<DateTime?>), typeof(DatePicker));
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public DatePicker()
        {
            InitializeComponent();

            Date=MDateTimeSaved;
            Loaded+=DatePickerOnLoaded;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public DateTime?										Date
        {
            get
			{
				return((DateTime?)GetValue(DateProperty));
			}
            set
			{
				SetValue(DateProperty, value);
			}
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private static void DateChangedCallback(DependencyObject Obj, DependencyPropertyChangedEventArgs Args)
        {
            (Obj as DatePicker).OnDateChanged((DateTime?) Args.OldValue, (DateTime?) Args.NewValue);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void DatePickerOnLoaded(object Sender, RoutedEventArgs Args)
        {
            MUnigridMonth = FindUniGrid(MLstboxMonth);

            if (Date!=null)
            {
                DateTime			DT=(DateTime)Date;

                MUnigridMonth.FirstColumn=(int)(new DateTime(DT.Year, DT.Month, 1).DayOfWeek);
            }
        }
//-------------------------------------------------------------------------------------------------------
        private UniformGrid FindUniGrid(DependencyObject Vis)
        {
            if ((Vis is UniformGrid)==true)
                return(Vis as UniformGrid);

            for (int i=0;i<VisualTreeHelper.GetChildrenCount(Vis);i++)
            {
                Visual			VisReturn=FindUniGrid(VisualTreeHelper.GetChild(Vis, i));

                if (VisReturn!=null)
                    return(VisReturn as UniformGrid);
            }

            return(null);
        }
//-------------------------------------------------------------------------------------------------------
        private void ButtonBackOnClick(object Sender, RoutedEventArgs Args)
        {
            FlipPage(true);
        }
//-------------------------------------------------------------------------------------------------------
        private void ButtonForwardOnClick(object Sender, RoutedEventArgs Args)
        {
            FlipPage(false);
        }
//-------------------------------------------------------------------------------------------------------
        private void FlipPage(bool IsBack)
        {
            if (Date==null)
                return;

            DateTime			DT=(DateTime)Date;
            int					NumPages=(IsBack==true) ? -1 : 1;

            if (Keyboard.IsKeyDown(Key.LeftShift)==true || Keyboard.IsKeyDown(Key.RightShift)==true)
                    NumPages*=12;

            if (Keyboard.IsKeyDown(Key.LeftCtrl)==true || Keyboard.IsKeyDown(Key.RightCtrl)==true)
                    NumPages=Math.Max(-1200, Math.Min(1200, 120 * NumPages));

            int					Year=DT.Year+(NumPages/12);
            int					Month=DT.Month+(NumPages%12);

            while (Month<1)
            {
                Month+=12;
                Year-=1;
            }

            while (Month>12)
            {
                Month-=12;
                Year+=1;
            }
           
            if (Year<DateTime.MinValue.Year)
                Date=DateTime.MinValue.Date;
            else if (Year>DateTime.MaxValue.Year)
                Date=DateTime.MaxValue.Date;
            else
                Date=new DateTime(Year, Month, Math.Min(DT.Day, DateTime.DaysInMonth(Year, Month)));
        }
//-------------------------------------------------------------------------------------------------------
        private void CheckBoxNullOnChecked(object Sender, RoutedEventArgs Args)
        {
            if (Date!=null)
            {
                MDateTimeSaved=(DateTime) Date;
                Date=null;
            }
        }
//-------------------------------------------------------------------------------------------------------
        private void CheckBoxNullOnUnchecked(object Sender, RoutedEventArgs Args)
        {
            Date=MDateTimeSaved;
        }
//-------------------------------------------------------------------------------------------------------
        private void ListBoxOnSelectionChanged(object sender, SelectionChangedEventArgs Args)
        {
            if (Date==null)
                return;

            DateTime			DT=(DateTime)Date;

            if (MLstboxMonth.SelectedIndex!=-1)
                Date = new DateTime(DT.Year, DT.Month, int.Parse(MLstboxMonth.SelectedItem as string));
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected override void OnPreviewKeyDown(KeyEventArgs Args)
        {
            base.OnKeyDown(Args);

            if (Args.Key==Key.PageDown)
            {
                FlipPage(true);
                Args.Handled=true;
            }
            else if (Args.Key==Key.PageUp)
            {
                FlipPage(false);
                Args.Handled=false;
            }
        }
//-------------------------------------------------------------------------------------------------------
        protected virtual void OnDateChanged(DateTime? DtOldValue, DateTime? DtNewValue)
        {
            MChkboxNull.IsChecked=(DtNewValue==null);

            if (DtNewValue!=null)
            {
                DateTime		DTNew=(DateTime)DtNewValue;

                MTxtblkMonthYear.Text=DTNew.ToString(DateTimeFormatInfo.CurrentInfo.YearMonthPattern);

                if (MUnigridMonth!=null)
                    MUnigridMonth.FirstColumn=(int)(new DateTime(DTNew.Year, DTNew.Month, 1).DayOfWeek);

                int				IDaysInMonth=DateTime.DaysInMonth(DTNew.Year, DTNew.Month);

                if (IDaysInMonth!=MLstboxMonth.Items.Count)
                {
                    MLstboxMonth.BeginInit();
                    MLstboxMonth.Items.Clear();

                    for (int i=0;i<IDaysInMonth;i++)
                        MLstboxMonth.Items.Add((i+1).ToString());

                    MLstboxMonth.EndInit();
                }

                MLstboxMonth.SelectedIndex=DTNew.Day-1;
            }

            // Now trigger the DateChangedEvent.
            RoutedPropertyChangedEventArgs<DateTime?>	Args=new RoutedPropertyChangedEventArgs<DateTime?>(DtOldValue, DtNewValue, DatePicker.DateChangedEvent);

            Args.Source=this;
            RaiseEvent(Args);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------