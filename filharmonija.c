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

//main functions
void doHigijenicarStrucnaSprema();
void doBlagajnikDodavanje();
void doIzvodjacPoInstrumentu();
void doIzvodjacDirigentKompozicija();
void doDirigentDodavanje();
void doKompozicijaCinDodavanje();
void doOsobljeDodavanje();

//help functions (for queries and printing)
void printIntro();
void printTable();
void printHigijenicar();
void printOrkestar();
void printIzvodjaciDirigenti(char sala[256], char vreme[256]);
void printIzvodjaci(char instrument[256], char sala[256], char vreme[256]);
void insertBlagajnik(char ime[256], char prezime[256], long jmbg, char adresa[256], int id, char radnoVreme[256]);
void insertDirigent(char ime[256], char prezime[256], long jmbg, char adresa[256], int godine, char konzervatorijum[256], int penzija, int orkId);
void insertKompozicija(int *idKomp, char naziv[256], char kompozitor[256], char zemljaPorekla[256], int godinaPorekla, int trajanje, int brojCinova);
void insertCin(int idKomp, int id, char naziv[256]);

static void error_fatal(char *format, ...){
	va_list arguments;

	va_start(arguments, format);
	vfprintf(stderr, format, arguments);
	va_end(arguments);

	if(strcmp(mysql_sqlstate(connection), "70000") == 0)
		return;
	else
		exit(EXIT_FAILURE);	
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
		else if(choice == '1'){
			doHigijenicarStrucnaSprema();
		}
		else if(choice == '2'){
			doBlagajnikDodavanje();
		}
		else if(choice == '3'){
			doIzvodjacPoInstrumentu();
		}
		else if(choice == '4'){
			doIzvodjacDirigentKompozicija();
		}
		else if(choice == '5'){
			doDirigentDodavanje();
		}
		else if(choice == '6'){
			doKompozicijaCinDodavanje();
		}
		else if(choice == '7'){
			doOsobljeDodavanje();
		}
		else{
		    printf("Uneta komanda nije prepoznata! Pokusajte ponovo!\n");
		}
	}

	mysql_close(connection);

	return 0;
}


//REFACTORED
void printIntro(){
	printf("Unosom odgovarajuceg slova, izaberite akciju koju zelite, od navedenih:\n");
	printf("(1) Menjanje strucne spreme higijenicaru\n");
	printf("(2) Dodavanje novog blagajnika\n");
	printf("(3) Dohvatanje podataka o izvodjacu kog ste slusali, po instrumentu\n");
	printf("(4) Dohvatanje podataka o izvodjacima i dirigentu koncerta koji ste slusali\n");
	printf("(5) Dodavanje novog dirigenta\n");
	printf("(6) Unosenje podataka o cinovima kompozicije\n");
	printf("(7) Odredjivanje pozicije novog zaposlenog\n");
	printf("(x) Izlaz\n\n");
}

//REFACTORED
void printHigijenicar(){
	sprintf(query, "SELECT o.id, o.ime, o.prezime, h.strucnaSprema \
									FROM Osoblje o JOIN Higijenicar h ON o.id = h.Osoblje_id;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
	printTable();
}

//REFACTORED
void printTable(){
	result = mysql_use_result(connection);
	columnField = mysql_fetch_field(result);
	int numOfCols = mysql_num_fields(result);
	for (int i = 0; i < numOfCols; i++)
		printf ("%s\t", columnField[i].name);
	printf("\n");
	printf("--------------------------------------------------------------------------\n");
	int numOfFields = mysql_num_fields(result);
	while((row = mysql_fetch_row(result)) != 0){
			for (int i = 0; i < numOfFields; i++)
				printf ("%s\t", row[i]);
			printf ("\n");
	}	
	printf("\n\n");
	
	mysql_free_result(result);
}

//REFACTORED
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
		
	printTable();
}

//REFACTORED
void printIzvodjaciDirigenti(char sala[256], char vreme[256]){
	printf("Spisak izvodjaca: \n");
	sprintf(query, "SELECT o.ime, o.prezime, i.instrument \
									FROM Osoblje o JOIN Izvodjac i ON o.id = i.Osoblje_id \
										JOIN Pripada p ON i.Osoblje_id = p.Izvodjac_Osoblje_id \
										JOIN Nastupa n ON n.Izvodi_Diriguje_Orkestar_id = p.Orkestar_id \
										JOIN KoncertnaSala k on k.id = n.KoncertnaSala_id \
									WHERE k.naziv = \"%s\" and n.vreme = \"%s\";", sala, vreme);
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));								
	printTable();
	
	printf("Dirigent: \n");
	sprintf(query, "SELECT o.ime, o.prezime, d.godineIskustva, d.konzervatorijum \
									FROM Osoblje o join Dirigent d ON d.Osoblje_id = o.id \
										JOIN Nastupa n ON n.Izvodi_Diriguje_Dirigent_Osoblje_id = d.Osoblje_id \
										JOIN KoncertnaSala k on k.id = n.KoncertnaSala_id \
									WHERE k.naziv = \"%s\" and n.vreme = \"%s\";", sala, vreme);
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));									
	printTable();
	
	printf("Kompozicija: \n");
	sprintf(query, "SELECT k.naziv, k.kompozitor, k.zemljaPorekla, k.godinaPorekla, k.trajanje \
									FROM Kompozicija k JOIN Nastupa n ON n.Izvodi_Kompozicija_id = k.id \
										JOIN KoncertnaSala ks on ks.id = n.KoncertnaSala_id \
									WHERE ks.naziv = \"%s\" and n.vreme = \"%s\";", sala, vreme);
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));									
	printTable();	

	printf("Cinovi: \n");
	sprintf(query, "SELECT c.id, c.naziv \
									FROM Cin c JOIN Kompozicija k on c.Kompozicija_id = k.id \
										JOIN Nastupa n ON n.Izvodi_Kompozicija_id = k.id \
										JOIN KoncertnaSala ks on ks.id = n.KoncertnaSala_id \
									WHERE ks.naziv = \"%s\" and n.vreme = \"%s\";", sala, vreme);
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));									
	printTable();	
}

//REFACTORED
void insertBlagajnik(char ime[256], char prezime[256], long jmbg, char adresa[256], int id, char radnoVreme[256]){
	sprintf(query, "SELECT max(id) FROM Osoblje;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
	result = mysql_use_result(connection);
	row = mysql_fetch_row(result);
	int idB = atoi(row[0]) + 1;
	mysql_free_result(result); 	
	
	mysql_autocommit(connection, 0);
		
	sprintf(query, "INSERT INTO Osoblje VALUES (\"%d\", \"%ld\", \"%s\", \"%s\", \"%s\", null);", idB, jmbg, ime, prezime, adresa);
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
  
	sprintf(query, "INSERT INTO Blagajnik VALUES (\"%d\", \"%d\", \"%s\");", idB, id, radnoVreme);
	if(mysql_query(connection, query) != 0){
		error_fatal("Query error %s\n", mysql_error(connection));
		mysql_rollback(connection);
	}
	else
		mysql_commit(connection);
		
	sprintf(query, "SELECT o.ime, o.prezime, b.Blagajna_id, b.preferiranaSmena \
									FROM Osoblje o JOIN Blagajnik b ON o.id = b.Osoblje_id;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
  
	printTable();
	
	mysql_autocommit(connection, 1);
}

//REFACTORED
void doHigijenicarStrucnaSprema(){
	int id;
	char ss[256];
	char waste;
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

	printf("Uspesno ste promenili strucnu spremu izabranog higijenicara.\n");
	printHigijenicar();
}

//REFACTORED
void doBlagajnikDodavanje(){
	printf("Unesite trazene podatke o blagajniku kog zelite da unesete:\n");
	char ime[256];
	char prezime[256];
	long jmbg;
	char adresa[256];
	int id;
	char radnoVreme[256];
	char waste;
	printf("Ime: ");
	fgets (ime, 256, stdin);
	ime[strlen(ime) - 1] = '\0'; //brisanje novog reda 			
	printf("Prezime: ");
	fgets (prezime, 256, stdin);
	prezime[strlen(prezime) - 1] = '\0'; //brisanje novog reda 
	printf("Jmbg: ");
	scanf("%ld", &jmbg);
	scanf("%c", &waste);
	printf("Adresa: ");
	fgets (adresa, 256, stdin);
	adresa[strlen(adresa) - 1] = '\0'; //brisanje novog reda 
	printf("Id blagajne: ");
	scanf("%d", &id);
	scanf("%c", &waste);
	printf("Preferirano radno vreme: ");
	scanf("%s", radnoVreme);
	scanf("%c", &waste);
	
	insertBlagajnik(ime, prezime, jmbg, adresa, id, radnoVreme);	
}

//REFACTORED
void doIzvodjacPoInstrumentu(){
	char instrument[256];
	char sala[256];
	char vreme[256];
	char waste;
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

//REFACTORED
void doIzvodjacDirigentKompozicija(){
	char sala[256];
	char vreme[256];	
	char waste;		
	printf("Unesite vreme izvodjenja i naziv sale da biste dobili detalje o izvodjacima:\n");
	printf("Naziv: "); 
	fgets (sala, 256, stdin);  
	sala[strlen(sala) - 1] = '\0'; //brisanje novog reda 
	printf("Vreme (HH:MM:SS format): "); 
	scanf("%s", vreme);
	scanf("%c", &waste);
	
	printIzvodjaciDirigenti(sala, vreme);	
}

void doDirigentDodavanje(){
	printf("Unesite potrebne podatke za unosenje novog dirigenta kao i orkestar kojim ce dirigent dirigovati:\n");
	char ime[256];
	char prezime[256];
	long jmbg;
	char adresa[256];
	char konzervatorijum[256];
	char waste;
	int godine;
	int penzija;
	int orkId;
	printf("Ime: ");
	fgets (ime, 256, stdin);
	ime[strlen(ime) - 1] = '\0'; //brisanje novog reda 			
	printf("Prezime: ");
	fgets (prezime, 256, stdin);
	prezime[strlen(prezime) - 1] = '\0'; //brisanje novog reda 
	printf("Jmbg: ");
	scanf("%ld", &jmbg);
	scanf("%c", &waste);
	printf("Adresa: ");
	fgets (adresa, 256, stdin);
	adresa[strlen(adresa) - 1] = '\0'; //brisanje novog reda 
	printf("Konzervatorijum: ");
	fgets (konzervatorijum, 256, stdin);
	konzervatorijum[strlen(konzervatorijum) - 1] = '\0'; //brisanje novog reda 
	printf("Godine iskustva: ");	
	scanf("%d", &godine);
	scanf("%c", &waste);
	printf("Penzionisan: ");	
	scanf("%d", &penzija);
	scanf("%c", &waste);
	
	printf("\nIzaberite id orkestra kojim zelite da novi dirigent diriguje: ");
	printOrkestar();
	scanf("%d", &orkId);
	scanf("%c", &waste);
	
	insertDirigent(ime, prezime, jmbg, adresa, godine, konzervatorijum, penzija, orkId);
}

void insertDirigent(char ime[256], char prezime[256], long jmbg, char adresa[256], int godine, char konzervatorijum[256], int penzija, int orkId){
	sprintf(query, "SELECT max(id) FROM Osoblje;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
	result = mysql_use_result(connection);
	row = mysql_fetch_row(result);
	int idB = atoi(row[0]) + 1;
	mysql_free_result(result); 	
	
	mysql_autocommit(connection, 0);
		
	sprintf(query, "INSERT INTO Osoblje VALUES (\"%d\", \"%ld\", \"%s\", \"%s\", \"%s\", null);", idB, jmbg, ime, prezime, adresa);
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
  
	sprintf(query, "INSERT INTO Dirigent VALUES (\"%d\", \"%d\", \"%s\", \"%d\");", idB, godine, konzervatorijum, penzija);
	if(mysql_query(connection, query) != 0){
		error_fatal("Query error %s\n", mysql_error(connection));
		mysql_rollback(connection);
	}
	else
		mysql_commit(connection);
	
	sprintf(query, "INSERT INTO Diriguje VALUES (\"%d\", \"%d\");", idB, orkId);
	if(mysql_query(connection, query) != 0){
		error_fatal("Query error %s\n", mysql_error(connection));
		mysql_rollback(connection);
	}
	else
		mysql_commit(connection);
		
	sprintf(query, "SELECT o.ime, o.prezime, d.godineIskustva, d.konzervatorijum, d.penzija \
									FROM Osoblje o JOIN Dirigent d ON o.id = d.Osoblje_id;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
  
	printTable();
	
	mysql_autocommit(connection, 1);	
}

void printOrkestar(){
	sprintf(query, "SELECT id, naziv FROM Orkestar;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
  printTable();	
}

void doKompozicijaCinDodavanje(){
	printf("Unesite potrebne podatke za kompoziciju, a zatim i za cin:\n");
	//id, naziv, kompozitor, zemljaporekla, godinaporekla, trajanje, brojcinova, id, kompozicija_id, naziv
	char naziv[256];
	char kompozitor[256];
	char zemljaPorekla[256];
	int godinaPorekla;
	int trajanje;
	int brojCinova;
	char waste;
	int id;
	char nazivCina[256];
	printf("Naziv: ");
	fgets (naziv, 256, stdin);
	naziv[strlen(naziv) - 1] = '\0'; //brisanje novog reda 			
	printf("Kompozitor: ");
	fgets (kompozitor, 256, stdin);
	kompozitor[strlen(kompozitor) - 1] = '\0'; //brisanje novog reda 
	printf("Godina porekla dela: ");
	scanf("%d", &godinaPorekla);
	scanf("%c", &waste);
	printf("Zemlja porekla dela: ");
	fgets (zemljaPorekla, 256, stdin);
	zemljaPorekla[strlen(zemljaPorekla) - 1] = '\0'; //brisanje novog reda 
	printf("Trajanje: ");	
	scanf("%d", &trajanje);
	scanf("%c", &waste);
	printf("Broj cinova: ");	
	scanf("%d", &brojCinova);
	scanf("%c", &waste);	
	
	int idKomp;
	insertKompozicija(&idKomp, naziv, kompozitor, zemljaPorekla, godinaPorekla, trajanje, brojCinova);
	
	int i = 0;
	while(i < brojCinova){
		printf("Broj cina u okviru dela: ");	
		scanf("%d", &id);
		scanf("%c", &waste);	
		printf("Naziv cina: ");
		fgets (nazivCina, 256, stdin);
		nazivCina[strlen(nazivCina) - 1] = '\0'; //brisanje novog reda 
		insertCin(idKomp, id, naziv);
		i++;
	}
	sprintf(query, "SELECT * FROM Cin ORDER BY Kompozicija_id;");
	if(mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
	printTable();
	
}

void doOsobljeDodavanje(){
	printf("Unesite naziv pozicije kao i potrebne podatke za osobu kojoj zelite da odredite poziciju:\n");	
}

void insertKompozicija(int *idKomp, char naziv[256], char kompozitor[256], char zemljaPorekla[256], int godinaPorekla, int trajanje, int brojCinova){
	sprintf(query, "SELECT max(id) FROM Kompozicija;");
	if (mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
	result = mysql_use_result(connection);
	row = mysql_fetch_row(result);
	int idB = atoi(row[0]) + 1;
	mysql_free_result(result); 
	
	*idKomp = idB;
	
	sprintf(query, "INSERT INTO Kompozicija VALUES (\"%d\", \"%s\", \"%s\", \"%s\", \"%d\", \"%d\", \"%d\");", idB, naziv, kompozitor, zemljaPorekla, godinaPorekla, trajanje, brojCinova);
	if(mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));

	sprintf(query, "SELECT * FROM Kompozicija;");
	if(mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));
	printTable();
}

void insertCin(int idKomp, int id, char naziv[256]){
	sprintf(query, "INSERT INTO Cin VALUES (\"%d\", \"%d\", \"%s\");", id, idKomp, naziv);
	if(mysql_query(connection, query) != 0)
		error_fatal("Query error %s\n", mysql_error(connection));	
}