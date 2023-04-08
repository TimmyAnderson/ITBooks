rem Service certificate.
makecert -sr LocalMachine -ss TrustedPeople -n "CN=TestCC" -sky exchange -pe

rem Client1 certificate.
makecert -sr LocalMachine -ss TrustedPeople -n "CN=Client1CC" -sky exchange -pe

rem Client2 certificate.
makecert -sr LocalMachine -ss TrustedPeople -n "CN=Client2CC" -sky exchange -pe