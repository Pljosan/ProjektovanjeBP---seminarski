use filharmonija;
-- izvodjac ima 70k
-- dirigent ima 100k
-- blagajnik ima 40k
-- higijenicar ima 30k
insert into Osoblje values
  (1, 1809995123456, 'Ana', 'Bajic', 'Spanskih boraca 3', null),
  (4, 0803970123456, 'Milos', 'Vesic', 'Omladinskih brigada 103', null),
  (6, 3101978123456, 'Dragana', 'Stojisavljevic', 'Ace Joksimovica 10', null),
  (7, 0705993123456, 'Tatjana', 'Radovanovic', 'Takovska 34', null),
  (11, 1212985123456, 'Marijana', 'Djuric', 'Praska 10', null),
  (2, 0804967123456, 'Miodrag', 'Nemec', 'Kraljice Katarine 20', null),
  (5, 1408960123456, 'Igor', 'Redic', 'Arcibalda Rajsa 114', null),
  (3, 2111986123456, 'Ivan', 'Sivic', 'Vladimira Rolovica 27', null),
  (10, 3006999123456, 'Lazar', 'Lazarevic', 'Frontovska', null),
  (8, 2512975123456, 'Marko', 'Maretic', 'Kneginje Zorke 22', null),
  (12, 150750123456, 'Jovan', 'Lucic', 'Veljka Petrovica 19', null),
  (9, 0112972123456, 'Milica', 'Galetic', 'Trebovicka 1',  null);

insert into Blagajna values
  (1, '09:00:00'),
  (2, '15:00:00');

insert into KoncertnaSala values
  (1, 'Ludvig Van Betoven', 300),
  (2, 'Petar Iljic Cajkovski', 60),
  (3, 'Johan Sebastijan Bah', 150),
  (4, 'Volfgang Amadeus Mocart', 270);

insert into Orkestar values
  (1),
  (2);

insert into Kompozicija values
  (1, 'Deveta simfonija', 'Betoven', 'Nemacka', 1824, 65, 4), -- 4 cina
  (2, 'Tokata i Fuga', 'Bah', 'Nemacka', 1704, 10, 1), -- 1 cin? 0 cinova?
  (3, 'naziv', 'kompozitor', 'zemlja', 1999, 10, 1),
  (4, 'naziv', 'kompozitor', 'zemlja', 1999, 10, 1),
  (5, 'naziv', 'kompozitor', 'zemlja', 1999, 10, 1),
  (6, 'naziv', 'kompozitor', 'zemlja', 1999, 10, 1),
  (7, 'naziv', 'kompozitor', 'zemlja', 1999, 10, 1);

insert into Dirigent values
  (2, 12, 'Becki konzervatorijum', 0),
  (12, 30, 'Moskovski konzervatorijum', 1),
  (5, 13, 'Milanski konzervatorijum', 0);

insert into Izvodjac values
  (1, 'violina'),
  (4, 'kontrabas'),
  (6, 'harfa'),
  (7, 'viola'),
  (11, 'flauta');

insert into Higijenicar values
  (8, 'srednja skola', 'Cistoca'),
  (9, 'osnovna skola', '');

insert into Blagajnik values
  (3, 1, 'jutro'),
  (10, 2, 'podne');

insert into Zaduzen values
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

insert into Diriguje values
  (2, 1),
  (2, 2),
  (5, 1);

insert into Izvodi values
  (1, 2, 1),
  (2, 2, 1),
  (3, 2, 1),
  (2, 2, 2),
  (4, 2, 1),
  (4, 2, 2),
  (5, 2, 2),
  (6, 2, 2),
  (7, 5, 1),
  (2, 5, 1),
  (4, 5, 1);

insert into Nastupa values
  (2, 2, 2, 1, '17:00:00'),
  (4, 2, 1, 2, '20:00:00'),
  (5, 2, 2, 4, '18:00:00'),
  (4, 2, 2, 3, '17:00:00'),
  (6, 2, 2, 1, '18:00:00'),
  (7, 5, 1, 2, '17:00:00'),
  (2, 5, 1, 4, '16:00:00');
