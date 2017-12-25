CC = gcc
CFLAGS	= -lmysqlclient

.PHONY: all create insert progs

all: create insert progs

progs: filharmonija.c
	$(CC) $< $(CFLAGS) 

create:
	mysql -u root -p1234 -D mysql <createScript.sql

insert:
	mysql -u root -p1234 -D mysql <insertScript.sql
