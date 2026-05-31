// vCard
#include <ctime>
#include <stdio.h>
#include <string>
#include <getopt.h>
#include <iostream>
#include "list.h"
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
    opterr = 0;
    int opt;
    string firstname = "";
    string lastname = "";
    string org = "";
    string email[5];
    int email_count = 0;
    string phone_home[5];
    int phone_home_count = 0;
    string phone_work[5];
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
    char rev[25];
    strftime(rev, sizeof(rev), "%Y-%m-%dT%H:%M:%SZ", timeNow);

    // Verkettete Liste initialisieren und Rahmenstruktur einfügen
    Element *head = NULL;
    insert(&head, 1, "BEGIN:VCARD");
    insert(&head, 2, "VERSION:3.0");
    insert(&head, 9, string("REV:") + rev);
    insert(&head, 10, "END:VCARD");

    // Kommandozeilenoptionen parsen
    while ((opt = getopt_long(argc, argv, "f:s:m:p:h", long_opts, NULL)) != -1) {
        switch (opt) {
        case 'f':
            firstname = optarg;
            break;
        case 's':
            lastname = optarg;
            if (lastname.find(' ') != string::npos) {
                fprintf(stderr, "Fehler: Nur ein Nachname erlaubt!\n");
                freeList(head);
                return 1;
            }
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
                fprintf(stderr, "Fehler: Maximal 5 E-Mails möglich!\n");
            } else {
                email[email_count] = optarg;
                email_count++;
            }
            break;
        case 'p':
            if (phone_home_count == 5) {
                fprintf(stderr, "Fehler: Maximal 5 Telefonnumern möglich!\n");
            } else {
                phone_home[phone_home_count] = optarg;
                phone_home_count++;
            }
            break;
        case 2:
            if (phone_work_count == 5) {
                fprintf(stderr, "Fehler: Maximal 5 Telefonnumern möglich!\n");
            } else {
                phone_work[phone_work_count] = optarg;
                phone_work_count++;
            }
            break;
        case 'h':
            printf(
                "Benutzung: vcard [OPTIONEN] [DATEINAME]\n"
                "\n"
                "Optionen:\n"
                "  -f, --firstname NAME    Vorname angeben (mehrere Vornamen: -f \"Hans Peter\")\n"
                "  -s, --surname NAME      Nachname angeben\n"
                "  -m, --email EMAIL       E-Mail angeben, bis zu 5 möglich\n"
                "  -p, --phone-home TEL    Private Telefonnummer, bis zu 5 möglich\n"
                "      --phone-work TEL    Dienstliche Telefonnummer, bis zu 5 möglich\n"
                "      --org ORG           Organisation angeben, mehrere möglich\n"
                "      --programmer-info   Autor anzeigen\n"
                "  -h, --help              Hilfe anzeigen\n"
                "\n"
                "Dateiname                 Ausgabe in Datei speichern in (z.B. kontakt.vcf)\n"
                "\n"
                "Beispiele:\n"
                "  vcard -f Max -s Muster\n"
                "  vcard -f \"Hans Peter\" -s Muster\n"
                "  vcard -f Max -s Muster -m max@mail.de kontakt.vcf\n"
            );
            return 0;
        case 3:
            printf("BEGIN:VCARD\n");
            printf("VERSION:3.0\n");
            printf("N:Jerg;Julia;Ramona;;\n");
            printf("FN:Julia Ramona Jerg\n");
            printf("ORG:TIA;Aktive MV Fronhofen;Jugenleiterin MV Fronhofen\n");
            printf("EMAIL;TYPE=PREF,INTERNET:julia.r.jerg@t-online.de\n");
            printf("REV:%s\n", rev);
            printf("END:VCARD\n");

            return 0;
        default:
            if (optopt == 's' || optopt == 'f' || optopt == 'm' || optopt == 'p') {
                fprintf(stderr, "Fehler: Option -%c braucht ein Argument!\n", optopt);
            } else {
                fprintf(stderr, "Fehler: Unbekannte Option!\nHilfe mit der Option -h oder --help\n");
            }
            freeList(head);
            return 1;
        }
    }

    // Ungültige Namen überprüfen
    if (!firstname.empty() && firstname[0] == '-') {
        fprintf(stderr, "Fehler: Ungültiger oder fehlender Vorname!\n");
        freeList(head);
        return 1;
    }
    if (!lastname.empty() && lastname[0] == '-') {
        fprintf(stderr, "Fehler: Ungültiger Nachname!\n");
        freeList(head);
        return 1;
    }

    // Vornamen aufteilen in Hauptname und Zusatznamen
    stringstream ss(firstname);
    string part;
    bool first = true;

    string fullFirstname = firstname;
    string mainFirstname = "";
    string additionalFirstnames = "";

    while (getline(ss, part, ' ')) {
        if (first) {
            mainFirstname = part;
            first = false;
        } else {
            if (!additionalFirstnames.empty()) {
                additionalFirstnames += ",";
            }
            additionalFirstnames += part;
        }
    }

    // vCard Elemente in Liste einfügen
    insert(&head, 3, "N:" + lastname + ";" + mainFirstname + ";" + additionalFirstnames + ";;");
    insert(&head, 4, "FN:" + fullFirstname + " " + lastname);
    if (!org.empty()) {
        insert(&head, 5, "ORG:" + org);
    }
    for (int i = 0; i < phone_work_count; i++) {
        insert(&head, 6, "TEL;TYPE=WORK,VOICE:" + phone_work[i]);
    }
    for (int i = 0; i < phone_home_count; i++) {
        insert(&head, 7, "TEL;TYPE=HOME,VOICE:" + phone_home[i]);
    }
    for (int i = 0; i < email_count; i++) {
        insert(&head, 8, "EMAIL;TYPE=PREF,INTERNET:" + email[i]);
    }

    // Ausgabe in Datei oder stdout
    if (!firstname.empty() && !lastname.empty()) {
        if (optind < argc) {
            FILE *file = fopen(argv[optind], "w");
            if (file == NULL) {
                fprintf(stderr, "Fehler: Datei konnte nicht geöffnet werden!\n");
                freeList(head);
                return 1;
            }
            printList(head, file);
            fclose(file);
        } else {
            printList(head, stdout);
        }
        freeList(head);
        return 0;
    } else {
        freeList(head);
        if (firstname.empty() && lastname.empty()) {
            fprintf(stderr, "Fehler: Kein Vor- und Nachname angegeben!\n");
        } else if (firstname.empty()) {
            fprintf(stderr, "Fehler: Kein Vorname angegeben!\n");
        } else if (lastname.empty()) {
            fprintf(stderr, "Fehler: Kein Nachname angegeben!\n");
        } else {
            //Alle anderen Fälle sind bereits abgedeckt
        }
        return 1;
    }

}