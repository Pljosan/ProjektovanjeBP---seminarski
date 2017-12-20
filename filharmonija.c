#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>

#define QUERY_SIZE 256
#define BUFFER_SIZE 80

static void error_fatal(char *format, ...){
	va_list arguments;

	va_start (arguments, format);
	vfprintf (stderr, format, arguments);
	va_end (arguments);

	exit (EXIT_FAILURE);
}

int main(int argc, char** argv){
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *columnField;
	char query[QUERY_SIZE];
	char buffer[BUFFER_SIZE];
	
	connection = mysql_init(NULL);
	
	if (mysql_real_connect(connection, "localhost", "root", "1234", "_____", 0, NULL, 0) == NULL)
	  error_fatal("Connection error. %s\n", mysql_error(connection));
		
	char choice;
	while(true){
		printf("Unosom odgovarajuceg slova, izaberite akciju koju zelite, od navedenih:\n");
		printf("(s) Menjanje strucne spreme higijenicaru\n");
		printf("(b) Dodavanje novog blagajnika\n");
		printf("(a) Dohvatanje podataka o izvodjacu kog ste slusali, po instrumentu\n");
		printf("(n) Dohvatanje podataka o izvodjacima i dirigentu koncerta koji ste slusali\n");
		printf("(d) Dodavanje novog dirigenta\n");
		printf("(c) Unosenje podataka o cinovima kompozicije\n");
		printf("(o) Odredjivanje pozicije novog zaposlenog\n");
		printf("(x) Izlaz\n");
		scanf("%c", &choice);
		scanf("%c");
		
		if(choice == 'x'){
			printf("Hvala sto se koristili aplikaciju! Cao!\n");
			break;
		}
		else if(choice == 's'){
			printf("Izaberite higijenicara kom zelite da promenite strucnu spremu:\n");
		}
		else if(choice == 'b'){
			printf("Unesite trazene podatke o blagajniku kog zelite da unesete:\n");
		}
		else if(choice == 'a'){
			printf("Unesite instrument izvodjaca i naziv sale, kao i vreme, u kojoj je svirao:\n");
		}
		else if(choice == 'n'){
			printf("Unesite vreme izvodjenja i naziv sale da biste dobili detalje o izvodjacima:\n");
		}
		else if(choice == 'd'){
			printf("Unesite ime i prezime dirigenta kao i orkestar kojim ce dirigent dirigovati:\n");
		}
		else if(choice == 'c'){
			printf("Unesite naziv kompozicije, a zatim i potrebne podatke za cin:\n");
		}
		else if(choice == 'o'){
			printf("Unesite naziv pozicije kao i jmbg osobe kojoj zelite da odredite poziciju:\n");
		}
		else{
		    printf("Uneto slovo nije komanda! Pokusajte ponovo!\n");
		}
	}
		
	mysql_close(connection);
	
	return 0;
}