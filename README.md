# Baza podataka za Filharmoniju

Baza za filharmoniju sadrži sve zaposlene, listu sala, blagajni kao i kompozicija koje se izvode.

&nbsp;

U bazi se čuvaju informacije o zaposlenima - njihov identifikacioni broj, jmbg, ime, prezime, adresa i plata. U filharmoniji trenutno rade:
* Izvođači, koje dodatno opisuju instrumenti koje sviraju.
* Dirigenti, koje opisuju godine iskustva kao i konzervatorijum (tj. škola) na kom su se školovali.
* Higijeničari, osobolje koje je zaduženo za održavanje higijene u salama, koje karakteriše i stručna sprema, sindikat kojem pripadaju.
* Blagajnici, koji su zaduženi za blagajnu i imaju svoje preferirano vreme rada.

Svaku blagajnu karakteriše njen identifikacioni broj i radno vreme. Na jednoj blagajni, u toku dana, može da radi više blagajnika, a sa druge strane jedan blagajnik je zadužen za tačno jednu blagajnu.

U okviru zgrade filharmonije postoji više sala a svaka je okarakterisana svojim identifikacionim brojem, brojem mesta i nazivom (prema nekom poznatom kompozitoru). Za održavanje higijene jedne sale mora biti zadužen bar jedan higijeničar a ako je sala veća, može ih biti i više. Svaki higijeničar je zadužen za čišćenje bar jedne sale a može biti zadužen i za više.

Čuvaju se i kompozicije koje se izvode. Njih karakteriše naziv, kompozitor, zemlja i godina porekla, trajanje. Kompoziciju takođe karakterišu i činovi. Jedan čin pripada samo jednoj kompoziciji a kompozicija može imati i više činova.

Kompoziciju izvodi više izvođača, dok izvođač može izvoditi više kompozicija (naravno, ne u istom trenutku). Dirigent, u toku vremena, može biti zadužen za dirigovanje više izvođenja a jednim konkretnim izvođenjem diriguje samo jedan dirigent.

Jedno izvođenje kompozicije se održava u samo jednoj sali, dok se u sali može izvoditi i više kompozicija (ne u istom trenutku).

&nbsp;

Nezavisni entiteti:
* Osoblje
* Koncertne sale
* Blagajne
* Kompozicije
* Orkestar

Zavisni entiteti:
* Čin
* Generalizacija:
  * Izvođač
  * Dirigent
  * Higijeničar
  * Blagajink

Agregirani entiteti:
* Pripada
* Diriguje
* Izvodi
* Nastupa
* Zadužen
