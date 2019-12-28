// Fill in  your WiFi networks SSID and password
#define SECRET_SSID "hnew1104"
#define SECRET_PASS "00000000"

// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "a27fcaeo1326fu-ats.iot.us-east-1.amazonaws.com"

// Fill in the boards public certificate
const char SECRET_CERTIFICATE[] = R"(
-----BEGIN CERTIFICATE-----
MIICiDCCAXCgAwIBAgIUbvl38xwccjjwNU/1gq+gvHPkp9UwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MTIxMzA3MDgw
NloXDTQ5MTIzMTIzNTk1OVowGDEWMBQGA1UEAxMNTXlNS1JXaUZpMTAxMDBZMBMG
ByqGSM49AgEGCCqGSM49AwEHA0IABKaXUp+6gYXnUFzYHs6FboQ8yaPT1pf8TBJW
LcnqQ281pZ2TfoK63OwZ/r9h4yHJgUH3cRN94Bs/MNZQfRd9H7mjYDBeMB8GA1Ud
IwQYMBaAFIztOmWOD6Y5kdb/5GfsB8HQuwAMMB0GA1UdDgQWBBQcNnqR2X8wjmDF
nlWVnaNxFUSPVTAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG
9w0BAQsFAAOCAQEAmLpu7wuFAFqHQ/5nuP+mcMw9EnOdwvGUe3Rw72kL7jyKe469
N0CyqLXcRqrmlsVHii/OCvzeKsHqlnMc3VJGADCgnvUdlyc7dms5QCtAuVduJMfB
uhSjt82bCoUUQi1UjNesP3LtGmmXmDX41PrbvzEo97YpBsQ8iGTp1qGvKDcIOoj9
4b3aKyPsyWfy4c+MagTzXrDhsU1mj1zzek4M5E6Jylrc3oqgS0zmQ/Faf7YFWO05
RVTwpjtaZyVr4KNUnWBq+i+Xo0ut5wdE/WKh4HsT94R6Mcyv2Y85NO9POyaJzre9
B4zwMbKLGQ5eptDbsuj0kf2v35R2Bzj1APHJxA==
-----END CERTIFICATE-----
)";