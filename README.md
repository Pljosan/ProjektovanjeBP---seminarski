# Baza podataka za Filharmoniju

Baza za filharmoniju sadrži sve zaposlene, listu sala, blagajni kao i kompozicija koje se izvode.

Nezavisni objekti koji se nalaze u bazi su:

//TODO: smisli još atributa
* Blagajna
  * ID
  * Radno vreme
  * Redni broj blagajne
* Kompozicija
  * ID
  * Naziv
  * Kompozitor
  * Trajanje
  * Zemlja porekla
  * Broj činova
* Koncertna sala
  * ID
  * Broj mesta
  * Naziv
  * Adresa
* Osoblje
  * Generalizacija u:
    * Izvođač
    * Dirigent
    * Blagajnik
    * Higijeničar
  * Ime
  * Prezime
  * Datum rođenja
  * Jmbg
