#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdio.h>
#include <sqlite3.h>
#include "../models/appointment.h"

sqlite3 *setupDB(char *msg, size_t msgSize);

int record(Appointment appointment, sqlite3 *db, char *msg, size_t msgSize);

int getAll(sqlite3 *db, Appointment appointments[], size_t capacity, char *msg, size_t msgSize);

int getById(sqlite3 *db, Appointment appointments[], size_t capacity, char *msg, size_t msgSize, char *id);


int getByDate(sqlite3 *db, Appointment appointments[], size_t capacity, char *msg, size_t msgSize, char *date);

int getByArtist(sqlite3 *db, Appointment appointments[], size_t capacity, char *msg, size_t msgSize, char *artist);


int changeById(Appointment appointment, sqlite3 *db, char *msg, size_t msgSize, char *id);

int cancel(sqlite3 *db, char *msg, size_t msgSize, char *id);

#endif
