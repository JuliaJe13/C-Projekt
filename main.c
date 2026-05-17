//vcard
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    char *vorname = NULL;
    char *nachname = NULL;

    while ((opt = getopt(argc, argv, "f:s:")) != -1) {
        switch (opt) {
            case 'f':
                vorname = optarg;
                break;
            case 's':
                nachname = optarg;
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