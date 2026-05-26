//vcard
#include <ctime>
#include <stdio.h>
#include <string>
#include <getopt.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int opt;
    string vorname = "";
    string nachname = "";
    string org = "";
    char *email[5];
    int email_count = 0;
    char *phone_home[5];
    int phone_home_count = 0;
    char *phone_work[5];
    int phone_work_count = 0;
    struct option long_opts[] = {
        {"firstname", required_argument, 0, 'f'},
        {"surname", required_argument, 0, 's'},
        {"org", required_argument, 0, 1},
        {"email", required_argument, 0, 'm'},
        {"phone-home", required_argument, 0, 'p'},
        {"phone-work", required_argument, 0, 2},
        {"help", no_argument, 0, 'h'},
        {"programmer-info", no_argument, 0, 3},
        {0, 0, 0, 0}
    };

    time_t now = time(NULL);
    struct tm *timeNow = localtime(&now);
    char rev[20];
    strftime(rev, sizeof(rev), "%Y%m%dT%H%M%SZ", timeNow);

    while ((opt = getopt_long(argc, argv, "f:s:m:p:h", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'f':
                vorname = optarg;
                break;
            case 's':
                nachname = optarg;
                break;
            case 1:
                if (org.empty()) {
                    org = optarg; 
                } else {
                    org = org + ";" + optarg;
                }
                break;
            case 'm':
                if (email_count == 5) {
                    fprintf(stderr, "Fehler: Maximal 5 E-Mails möglich!");
                } else{
                    email[email_count] = optarg;
                    email_count++;
                }
                break;
            case 'p':
                if (phone_home_count == 5) {
                    fprintf(stderr, "Fehler: Maximal 5 Telefonnumern möglich!");
                } else{
                    phone_home[phone_home_count] = optarg;
                    phone_home_count++;
                }
                break;
            case 2:
                if (phone_work_count == 5) {
                    fprintf(stderr, "Fehler: Maximal 5 Telefonnumern möglich!");
                } else {
                    phone_work[phone_work_count] = optarg;
                    phone_work_count++;
                }
                break;
            case 'h':
                printf("Hilfe hier:.......\n");
                return 0;
            case 3:
                printf("Programmer-Info ....\n");
                return 0;
        }
    }

    // Hier kommt die Ausgabe
    
    if (!vorname.empty() && !nachname.empty()) {
        printf("BEGIN:VCARD\n");
        printf("VERSION:3.0\n");
        printf("N:%s;%s;;;\n", nachname.c_str(), vorname.c_str());
        printf("FN:%s %s\n", vorname.c_str(), nachname.c_str());
        if (!org.empty()) {
            printf("ORG:%s\n", org.c_str());
        }
        for (int i = 0; i < phone_work_count; i++) {
            printf("TEL;TYPE=WORK,VOICE:%s\n", phone_work[i]);
        }   
        for (int i = 0; i < phone_home_count; i++) {
            printf("TEL;TYPE=HOME,VOICE:%s\n", phone_home[i]);
        }   
        for (int i = 0; i < email_count; i++) {
            printf("EMAIL;TYPE=PREF,INTERNET:%s\n", email[i]);
        }    
        printf("REV:%s\n", rev);
        printf("END:VCARD\n");

        return 0;

    } else {
        if (vorname.empty() && nachname.empty()) {
            fprintf(stderr, "Fehler: Kein Vor- und Nachname angegeben!\n");
        } else {
            if (vorname.empty()) {
                fprintf(stderr, "Fehler: Kein Vorname angegeben!\n");
            }else if (nachname.empty()) {
                fprintf(stderr, "Fehler: Kein Nachname angegeben!\n");
            }
        }
        return 1;

    }

}