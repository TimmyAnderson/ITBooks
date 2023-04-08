rem Odosiela HTTP REQUEST s HTTP VERB POST na URL 'localhost:8080/MyWebServicePost'. 
rem HTTP REQUEST ma HTTP REQUEST HEADER [Content-Type: application/json].
rem HTTP REQUEST ma HTTP REQUEST HEADER [MyID: 123456].
rem HTTP REQUEST ma HTTP REQUEST BODY [{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}].
rem HTTP RESPONSE je VERBOSE.
curl -v -X POST localhost:8080/MyWebServicePost -H "Content-Type: application/json" -H "MyID: 123456" -d "{\"value1\":\"Jenny\",\"value2\":\"Thompson\"}"