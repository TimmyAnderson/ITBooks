REM Je to rovnaky RULE, ako RULE 2, aby sa dokazalo, ze AZURE SERVICE BUS RULES bez ACTION zlucuje do 1 MESSAGE.

az servicebus topic subscription rule create --name MySubscriptionTA76Filter2Rule3 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --topic-name MyTopicTA76 --subscription-name MySubscriptionTA76Filter2 --filter-sql-expression "MyProperty2=2"