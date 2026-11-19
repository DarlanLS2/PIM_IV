#include <stdio.h>
#include <sqlite3.h>
#include "../repository/repository.h"
#include "./service.h"

int handleRecord(Appointment appointment, char *msg, 
    size_t msgSize) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }

  rc = record(appointment, db, msg, msgSize);
   
  sqlite3_close(db);

  return rc;
};

int handleGetAll(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }

  rc = getAll(db, appointments, capacity, msg, msgSize);

  sqlite3_close(db);

  return rc;
};

int handleGetById(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize, char *id) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }

  rc = getById(db, appointments, capacity, msg, msgSize, id);

  sqlite3_close(db);

  return rc;
};

int handleGetByDate(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize, char *date) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }

  rc = getByDate(db, appointments, capacity, msg, msgSize, date);

  sqlite3_close(db);

  return rc;
};

int handleGetByArtist(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize, char *artist) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }

  rc = getByArtist(db, appointments, capacity, msg, msgSize, artist);

  sqlite3_close(db);

  return rc;
};

int handleChangeById(Appointment appointment, 
    char *msg, size_t msgSize, char *id) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }
  
  changeById(appointment, db, msg, msgSize, id);

  sqlite3_close(db);

  return rc;
};

int handleCancel(char *msg, size_t msgSize, char *id) {
  int rc;
  sqlite3 *db = setupDB(msg, msgSize);

  if (!db) {
    return 1;
  }

  cancel(db, msg, msgSize, id);

  sqlite3_close(db);

  return rc;
};
