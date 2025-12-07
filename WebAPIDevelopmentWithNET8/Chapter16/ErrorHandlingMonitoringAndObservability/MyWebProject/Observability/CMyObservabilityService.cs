using System.Diagnostics.Metrics;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyObservabilityService
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										METER_NAME="MyWebProject.Observability";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly Counter<long>							MCounter1;
		private readonly Counter<long>							MCounter2;
		private readonly UpDownCounter<long>					MUpDownCounter1;
		private readonly UpDownCounter<long>					MUpDownCounter2;
		private readonly Gauge<double>							MGauge1;
		private readonly Gauge<double>							MGauge2;
		private readonly Histogram<double>						MHistogram1;
		private readonly Histogram<double>						MHistogram2;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyObservabilityService(IMeterFactory MeterFactory)
		{
			Meter												Meter=MeterFactory.Create(METER_NAME);

			MCounter1=Meter.CreateCounter<long>("MyWebProject.Observability.Counter1");
			MCounter2=Meter.CreateCounter<long>("MyWebProject.Observability.Counter2");
			MUpDownCounter1=Meter.CreateUpDownCounter<long>("MyWebProject.Observability.UpDownCounter1");
			MUpDownCounter2=Meter.CreateUpDownCounter<long>("MyWebProject.Observability.UpDownCounter2");
			MGauge1=Meter.CreateGauge<double>("MyWebProject.Observability.Gauge1");
			MGauge2=Meter.CreateGauge<double>("MyWebProject.Observability.Gauge2");
			MHistogram1=Meter.CreateHistogram<double>("MyWebProject.Observability.Histogram1");
			MHistogram2=Meter.CreateHistogram<double>("MyWebProject.Observability.Histogram2");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public void IncrementCounter1()
		{
			MCounter1.Add(1);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void IncrementCounter2()
		{
			MCounter2.Add(1);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void IncrementUpDownCounter1()
		{
			MUpDownCounter1.Add(1);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void DecrementUpDownCounter1()
		{
			MUpDownCounter1.Add(-1);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void IncrementUpDownCounter2()
		{
			MUpDownCounter2.Add(1);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void DecrementUpDownCounter2()
		{
			MUpDownCounter2.Add(-1);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void RecordGauge1(double Value)
		{
			MGauge1.Record(Value);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void RecordGauge2(double Value)
		{
			MGauge2.Record(Value);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void RecordHistogram1(double Value)
		{
			MHistogram1.Record(Value);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public void RecordHistogram2(double Value)
		{
			MHistogram2.Record(Value);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------