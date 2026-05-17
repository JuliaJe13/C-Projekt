//vcard
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    char *vorname = NULL;
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
                printf("Hilfe hier:.......")
                break;
            case 3:
                programmer_info = optarg;
                break;
        }
    }

    // Hier kommt die Ausgabe
    
    if (vorname != NULL && nachname != NULL) {
        printf("BEGIN:VCARD\n");
        printf("VERSION:3.0\n");
        printf("N:%s;%s;;;\n", nachname, vorname);
        printf("FN:%s %s\n", vorname, nachname);
        printf("END:VCARD\n");

        return 0;

    } else {
        if (vorname == NULL && nachname == NULL) {
            fprintf(stderr, "Fehler: Kein Vor- und Nachname angegeben!\n");
        } else if (vorname == NULL) {
            fprintf(stderr, "Fehler: Kein Vorname angegeben!\n");
        } else (nachname == NULL) {
            fprintf(stderr, "Fehler: Kein Nachname angegeben!\n");
        }
        return 1;
    }

}