#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/include/mysql/mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>

#define QUERY_SIZE 256
#define BUFFER_SIZE 80

MYSQL *connection;
MYSQL_RES *result;
MYSQL_ROW row;
MYSQL_FIELD *columnField;
char query[QUERY_SIZE];
char buffer[BUFFER_SIZE];

void printIntro();
void printHigijenicar();
void printIzvodjaci(char instrument[256], char sala[256], char vreme[256]);

static void error_fatal(char *format, ...){
	va_list arguments;

	va_start (arguments, format);
	vfprintf (stderr, format, arguments);
	va_end (arguments);

	exit (EXIT_FAILURE);
}

int main(int argc, char** argv){

	connection = mysql_init(NULL);

	if (mysql_real_connect(connection, "localhost", "root", "1234", "filharmonija", 0, NULL, 0) == NULL)
	  error_fatal("Connection error. %s\n", mysql_error(connection));

	char choice;
	char waste;
	while(true){
		printIntro();
		printf("Izbor: ");
		scanf("%c", &choice);
		scanf("%c", &waste);

		if(choice == 'x'){
			printf("Hvala sto se koristili aplikaciju! Cao!\n");
			break;
		}
		
		else if(choice == 's'){
			int id;
			char ss[256];
			printf("Izaberite id higijenicara kom zelite da promenite strucnu spremu, od ponudjenih:\n");
			printHigijenicar();
			
			//ucitavanje podataka			
			printf("Id: ");		
			scanf("%d", &id);
			scanf("%c", &waste);
			printf("Strucna sprema: ");
			fgets (ss, 256, stdin);
			ss[strlen(ss) - 1] = '\0'; //brisanje novog reda 
			
			sprintf(query, "UPDATE Higijenicar SET strucnaSprema = \"%s\" WHERE Osoblje_id = \"%d\";", ss, id);
			if (mysql_query(connection, query) != 0)
				error_fatal("Query error %s\n", mysql_error(connection));		
			else{
				printf("\nUspesno ste promenili strucnu spremu izabranog higijenicara.\n");
				printHigijenicar();
			}
			
			printf("\n\n");
		}
		
		else if(choice == 'b'){
			printf("Unesite trazene podatke o blagajniku kog zelite da unesete:\n");
		}
		else if(choice == 'a'){
			char instrument[256];
			char sala[256];
			char vreme[256];
			printf("Unesite instrument izvodjaca i naziv sale, kao i vreme, u kojoj je svirao:\n");
			printf("Instrument: ");
			scanf("%s", instrument); //violina ; kontrabas 
			scanf("%c", &waste);
			printf("Naziv: "); 
			fgets (sala, 256, stdin); //Petar Iljic Cajkovski 
			sala[strlen(sala) - 1] = '\0'; //brisanje novog reda 
			printf("Vreme (HH:MM:SS format): "); //20:00:00
			scanf("%s", vreme);
			scanf("%c", &waste);
			
			printIzvodjaci(instrument, sala, vreme);
			
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

void printIntro(){
	printf("Unosom odgovarajuceg slova, izaberite akciju koju zelite, od navedenih:\n");
	printf("(s) Menjanje strucne spreme higijenicaru\n");
	printf("(b) Dodavanje novog blagajnika\n");
	printf("(a) Dohvatanje podataka o izvodjacu kog ste slusali, po instrumentu\n");
	printf("(n) Dohvatanje podataka o izvodjacima i dirigentu koncerta koji ste slusali\n");
	printf("(d) Dodavanje novog dirigenta\n");
	printf("(c) Unosenje podataka o cinovima kompozicije\n");
	printf("(o) Odredjivanje pozicije novog zaposlenog\n");
	printf("(x) Izlaz\n\n");
}

void printHigijenicar(){
	sprintf(query, "SELECT o.id, o.ime, o.prezime, h.strucnaSprema \
									FROM Osoblje o JOIN Higijenicar h ON o.id = h.Osoblje_id;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
		
	result = mysql_use_result(connection);
	columnField = mysql_fetch_field(result);
	printf("%s\t%s\t%s\t%s\n", columnField[0].name, columnField[1].name, columnField[2].name, columnField[3].name);
	printf("-------------------------------------\n");
	int numOfFields = mysql_num_fields(result);
	while((row = mysql_fetch_row(result)) != 0){
			for (int i = 0; i < numOfFields; i++)
				printf ("%s\t", row[i]);
			printf ("\n");
		}
}

void printIzvodjaci(char instrument[256], char sala[256], char vreme[256]){
	
	sprintf(query, "SELECT o.ime, o.prezime, ork.naziv 'Nazvi orkestra' \
									FROM Osoblje o JOIN Pripada p ON o.id = p.Izvodjac_Osoblje_id \
										JOIN Orkestar ork ON p.Orkestar_id = ork.id \
										JOIN Nastupa n ON n.Izvodi_Diriguje_Orkestar_id = ork.id \
										JOIN KoncertnaSala k ON n.KoncertnaSala_id = k.id \
									WHERE o.id IN (SELECT Osoblje_id FROM Izvodjac WHERE instrument = \"%s\") \
										AND k.naziv = \"%s\" AND n.vreme = \"%s\";", instrument, sala, vreme);
	
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
		
	result = mysql_use_result(connection);
	columnField = mysql_fetch_field(result);
	printf("\n%s\t%s\t%s\n", columnField[0].name, columnField[1].name, columnField[2].name);
	printf("-------------------------------\n");
	int numOfFields = mysql_num_fields(result);
	while((row = mysql_fetch_row(result)) != 0){
			for (int i = 0; i < numOfFields; i++)
				printf ("%s\t", row[i]);
			printf ("\n");
		}	
		
	printf("\n\n");
}