***WIP***

# Planirani trigeri

### Check trigeri
  - Osoblje: plata > 0
  - Dirigent: godineIskustva > 5
  - Blagajnik: preferiranaSmena in ('Jutarnja', 'Podnevna') //jutro - 9-15; podne - 15-21
  - KoncertnaSala: brojMesta > 0
  
### Ostali trigeri
  - Ako higijeničar završi još jedan nivo stručne spreme, povećava mu se plata
  - Zabranjuje se unos/izmena blagajnika, ako se time ne bi poklapali radno vreme njegovog radnog mesta (tj. blagajne) i njegovo preferirano radno vreme
  
# Planirani upiti

### Aktivacija trigera
  - Upit koji će da promeni stručnu spremu nekom već zaposlenom higijeničaru i samim tim mu poveća platu
    ```sql
        select plata from osoblje
        where id = uneseniId

        update higijenicar
        set strucnaSprema = strucnaSprema + 1
        where id = uneseniId
        //ovo ce biti neki nivoi

        select plata from osoblje
        where id = uneseniId
    ```
  - Upit koji će da unese redove u tabelu Blagajnik. Biće pozvan dva puta, jednom kad će se uneti ispravna vrednost (tj. smena jutro i blagajna koja radi ujutru npr.) i jednom kad će se uneti neispravna vrednost (tj. smena jutro i blagajna koja radi popodne) 
    ```sql
      insert into blagajnik
      values(uneseniId, unesenaBlagajna, unesenoVreme)
    ```
  - Upit koji će da izlista sve izvođače prema instrumentu (i možda još nekim detaljima, ako recimo želi da zna koji je violinista svirao na koncertu koji je on gledao) koji korisnik unese
    
  - Upit koji će korisniku da izlista imena izvođača za izvođenje koje želi da sluša, kao i dirigenta i osnovne informacije o njemu.
 
