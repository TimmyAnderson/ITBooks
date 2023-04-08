makecert.exe -r -pe -sky exchange -n "CN=TestCertificate" TestCertificate.cer -sv TestCertificate.pvk
pvk2pfx.exe -pvk TestCertificate.pvk -spc TestCertificate.cer -pfx TestCertificate.pfx