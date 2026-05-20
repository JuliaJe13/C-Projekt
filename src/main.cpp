//vcard
#include <stdio.h>
#include <string>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    std::string vorname = "";
    char *nachname = NULL;
    char *org = NULL;
    char *email = NULL;
    char *phone_home[5];
    int phone_home_count = 0;
    char *phone_work[5];
    int phone_work_count = 0;
    char *programmer_info = NULL;
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

    while ((opt = getopt_long(argc, argv, "f:s:m:p:h", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'f':
                vorname = optarg;
                break;
            case 's':
                nachname = optarg;
                break;
            case 1:
                org = optarg;
                break;
            case 'm':
                email = optarg;
                break;
            case 'p':
                if (phone_home_count == 4) {
                    fprintf(stderr, "Fehler: Maximal 5 Telefonnumern möglich!");
                } else{
                    phone_home[phone_home_count] = optarg;
                    phone_home_count++;
                }
                break;
            case 2:
                if (phone_work_count == 4) {
                    fprintf(stderr, "Fehler: Maximal 5 Telefonnumern möglich!");
                } else {
                    phone_work[phone_work_count] = optarg;
                    phone_work_count++;
                }
                break;
            case 'h':
                printf("Hilfe hier:.......");
                break;
                return 0;
            case 3:
                printf("Programmer-Info ....");
                break;
                return 0;
        }
    }

    // Hier kommt die Ausgabe
    
    if (vorname != "" && nachname != "") {
        printf("BEGIN:VCARD\n");
        printf("VERSION:3.0\n");
        printf("N:%s;%s;;;\n", nachname, vorname);
        printf("FN:%s %s\n", vorname, nachname);
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