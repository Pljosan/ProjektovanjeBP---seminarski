-- izvodjac ima 70k
-- dirigent ima 100k
-- blagajnik ima 40k
-- higijenicar ima 30k
insert into Osoblje values
  (1, 1809995123456, 'Ana', 'Bajic', 'Spanskih boraca 3', 70000),  
  (4, 0803970123456, 'Milos', 'Vesic', 'Omladinskih brigada 103', 70000),
  (6, 3101978123456, 'Dragana', 'Stojisavljevic', 'Ace Joksimovica 10', 70000), 
  (7, 0705993123456, 'Tatjana', 'Radovanovic', 'Takovska 34', 70000),
  (11, 1212985123456, 'Marijana', 'Djuric', 'Praska 10', 70000),
  (2, 0804967123456, 'Miodrag', 'Nemec', 'Kraljice Katarine 20', 100000),
  (5, 1408960123456, 'Igor', 'Radovic', 'Arcibalda Rajsa 114', 100000),
  (3, 2111986123456, 'Ivan', 'Sivic', 'Vladimira Rolovica 27', 40000),
  (10, 3006999123456, 'Lazar', 'Lazarevic', 'Frontovska', 40000),
  (8, 2512975123456, 'Marko', 'Maretic', 'Kneginje Zorke 22', 30000),  
  (9, 0112972123456, 'Milica', 'Galetic', 'Trebovicka 1', 30000);
 
insert into Blagajna values
  (1, '09:00'),
  (2, '15:00');
  
insert into KoncertnaSala values
  (1, 'Ludvig Van Betoven', 300),
  (2, 'Petar Iljic Cajkovski', 60),
  (3, 'Johan Sebastijan Bah', 150),
  (4, 'Volfgang Amadeus Mocart', 270);
  
insert into Orkestar values
  (1),
  (2);

insert into Kompozicija values
  (1, 'Deveta simfonija', 'Betoven', 'Nemacka', 1824, 65), -- 4 cina
  (2, 'Tokata i Fuga', 'Bah', 'Nemacka', 1704, 10), -- 1 cin? 0 cinova?
  (3, 'naziv', 'kompozitor', 'zemlja', godina, trajanje),
  (4, 'naziv', 'kompozitor', 'zemlja', godina, trajanje),
  (5, 'naziv', 'kompozitor', 'zemlja', godina, trajanje),
  (6, 'naziv', 'kompozitor', 'zemlja', godina, trajanje),
  (7, 'naziv', 'kompozitor', 'zemlja', godina, trajanje);
 
insert into Dirigent values
  (2, 12, 'Becki konzervatorijum'),
  (5, 15, 'Milanski konzervatorijum');
  
insert into Izvođač values
  (1, 'violina'),
  (4, 'kontrabas'),
  (6, 'harfa'),
  (7, 'viola'),
  (11, 'flauta');
  
insert into Higijeničar values
  (8, 'srednja skola', 'Cistoca'),
  (9, 'osnovna skola', '');
  
insert into Blagajnik values
  (3, 1, 'jutro'),
  (10, 2, 'podne');

insert into Zadužen values
  (8, 1),
  (8, 2),
  (9, 1),
  (9, 4),
  (8, 4),
  (9, 3);

insert into Pripada values
  (1, 1),
  (1, 2),
  (4, 1),
  (6, 1),
  (6, 2),
  (7, 1),
  (7, 2),
  (11, 1),
  (11, 2);
  
