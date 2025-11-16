using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusPublisher
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyRetryPolicy : ServiceBusRetryPolicy
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! METHOD urcuje cas, ktory ma SERVICE BUS BROKER cakat na vykonanie OPERATION pre dany ATTEMPT.
		public override TimeSpan CalculateTryTimeout(int AttemptCount)
		{
			if (AttemptCount==0 || AttemptCount==1)
			{
				TimeSpan										Span=TimeSpan.FromSeconds(5);

				return(Span);
			}
			else
			{
				TimeSpan										Span=TimeSpan.FromSeconds(10);

				return(Span);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! METHOD urcuje cas, ktory ma SERVICE BUS BROKER cakat na vykonanie dalsieho RETRY pre dany ATTEMPT. Ak METHOD vrati VALUE [null] tak k dalsiemu RETRY nedojde a OPERATION je povazovana za zlyhanu.
		public override TimeSpan? CalculateRetryDelay(Exception LastException, int AttemptCount)
		{
			if (LastException!=null)
			{
				Console.WriteLine($"RETRY EXCEPTION [{LastException.Message}].");
			}
			
			if (AttemptCount==0 || AttemptCount==1)
			{
				TimeSpan										Span=TimeSpan.FromSeconds(2);

				return(Span);
			}
			else if (AttemptCount<=5)
			{
				TimeSpan										Span=TimeSpan.FromSeconds(5);

				return(Span);
			}
			else
			{
				// !!! Ukoncenie RETRIES.
				return(null);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------