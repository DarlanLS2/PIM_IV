#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "repository.h"

sqlite3 *setupDB(char *msg, size_t msgSize) {
  sqlite3 *db;

  int returnCode = sqlite3_open("./src/database/database.db", &db);

  if (returnCode != SQLITE_OK) {
    snprintf(msg, msgSize, "Erro: não foi possivel abrir o banco de dados - %s\n", sqlite3_errmsg(db));
   return NULL;
  }

  return db;
};

int record(Appointment appointment, sqlite3 *db, char *msg, size_t msgSize) {

  char sql[256];
  char *errMsg = 0;

  sprintf(sql,
      "INSERT INTO Agendamento ("
      "date, start_hour, duration, "
      "tattoo_description, artist_name, "
      "client_name, client_phone"
      ") VALUES ("
      "'%s', %s, %s, '%s', '%s', '%s', '%s'"
      ");",
      appointment.date,
      appointment.start_hour,
      appointment.duration,
      appointment.tattoo_description,
      appointment.artist_name,
      appointment.client_name,
      appointment.client_phone
      );

  int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize,
        "Erro ao efetuar registro: %s", errMsg);

    sqlite3_free(errMsg);
    return 1;
  }

  snprintf(msg, msgSize,
      "Registro efetuado com sucesso");

  return 0;
};

int getAll(sqlite3 *db, Appointment appointments[], size_t capacity, 
    char *msg, size_t msgSize) {
  sqlite3_stmt *stmt;
  const char *sql = "select * from Agendamento;";
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize,
        "Erro: não foi possivel consultar os agendamentos");

    return 1;
  }

  size_t i = 0;

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {

    if (i >= capacity) {
      snprintf(msg, msgSize, "Limite de agendamentos atingido");
      sqlite3_finalize(stmt);
      return 1;
    }

    Appointment *appointment = &appointments[i];

    snprintf(appointment->id, sizeof(appointment->id),
        "%s", sqlite3_column_text(stmt, 0));

    snprintf(appointment->date, sizeof(appointment->date),
        "%s", sqlite3_column_text(stmt, 1));

    snprintf(appointment->start_hour, sizeof(appointment->start_hour),
        "%s", sqlite3_column_text(stmt, 2));

    snprintf(appointment->duration, sizeof(appointment->duration),
        "%s", sqlite3_column_text(stmt, 3));

    snprintf(appointment->tattoo_description,
        sizeof(appointment->tattoo_description),
        "%s", sqlite3_column_text(stmt, 4));

    snprintf(appointment->artist_name,
        sizeof(appointment->artist_name),
        "%s", sqlite3_column_text(stmt, 5));

    snprintf(appointment->client_name,
        sizeof(appointment->client_name),
        "%s", sqlite3_column_text(stmt, 6));

    snprintf(appointment->client_phone,
        sizeof(appointment->client_phone),
        "%s", sqlite3_column_text(stmt, 7));

    i++;
  }

  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    snprintf(msg, msgSize, "Erro: %s", sqlite3_errmsg(db));
    return 1;
  }

  if (i < capacity) {
    appointments[i].id[0] = '\0';
  }

  return 0;
};

int getById(sqlite3 *db, Appointment appointments[], size_t capacity, 
    char *msg, size_t msgSize, char *id) {

  const char *sql = "SELECT * FROM Agendamento WHERE id = ?;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize, "Erro: %s", sqlite3_errmsg(db));
    return 1;
  }

  if (capacity == 0) {
    snprintf(msg, msgSize, "Capacidade insuficiente");
    sqlite3_finalize(stmt);
    return 1;
  }

  sqlite3_bind_int(stmt, 1, atoi(id));

  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    Appointment *appointment = &appointments[0];

    snprintf(appointment->id, sizeof(appointment->id), "%s",
        (const char *)sqlite3_column_text(stmt, 0));

    snprintf(appointment->date, sizeof(appointment->date), "%s",
        (const char *)sqlite3_column_text(stmt, 1));

    snprintf(appointment->start_hour, sizeof(appointment->start_hour), "%s",
        (const char *)sqlite3_column_text(stmt, 2));

    snprintf(appointment->duration, sizeof(appointment->duration), "%s",
        (const char *)sqlite3_column_text(stmt, 3));

    snprintf(appointment->tattoo_description,
        sizeof(appointment->tattoo_description), "%s",
        (const char *)sqlite3_column_text(stmt, 4));

    snprintf(appointment->artist_name, sizeof(appointment->artist_name), "%s",
        (const char *)sqlite3_column_text(stmt, 5));

    snprintf(appointment->client_name, sizeof(appointment->client_name), "%s",
        (const char *)sqlite3_column_text(stmt, 6));

    snprintf(appointment->client_phone, sizeof(appointment->client_phone), "%s",
        (const char *)sqlite3_column_text(stmt, 7));

  } else if (rc == SQLITE_DONE) {
    appointments[0].id[0] = '\0';

  } else {
    snprintf(msg, msgSize, "Erro: %s", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return 1;
  }

  sqlite3_finalize(stmt);

  return 0;
}


int getByDate(sqlite3 *db, Appointment appointments[], size_t capacity, 
    char *msg, size_t msgSize, char *date) {
  sqlite3_stmt *stmt;
  const char *sql = "select * from Agendamento where date = ?;";
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize,
        "Erro: não foi possivel consultar os agendamentos");

    return 1;
  }

  sqlite3_bind_text(stmt, 1, date, -1, SQLITE_TRANSIENT);

  size_t i = 0;

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {

    if (i >= capacity) {
      snprintf(msg, msgSize, "Limite de agendamentos atingido");
      sqlite3_finalize(stmt);
      return 1;
    }

    Appointment *appointment = &appointments[i];

    snprintf(appointment->id, sizeof(appointment->id),
        "%s", sqlite3_column_text(stmt, 0));

    snprintf(appointment->date, sizeof(appointment->date),
        "%s", sqlite3_column_text(stmt, 1));

    snprintf(appointment->start_hour, sizeof(appointment->start_hour),
        "%s", sqlite3_column_text(stmt, 2));

    snprintf(appointment->duration, sizeof(appointment->duration),
        "%s", sqlite3_column_text(stmt, 3));

    snprintf(appointment->tattoo_description,
        sizeof(appointment->tattoo_description),
        "%s", sqlite3_column_text(stmt, 4));

    snprintf(appointment->artist_name,
        sizeof(appointment->artist_name),
        "%s", sqlite3_column_text(stmt, 5));

    snprintf(appointment->client_name,
        sizeof(appointment->client_name),
        "%s", sqlite3_column_text(stmt, 6));

    snprintf(appointment->client_phone,
        sizeof(appointment->client_phone),
        "%s", sqlite3_column_text(stmt, 7));

    i++;
  }

  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    snprintf(msg, msgSize, "Erro: %s", sqlite3_errmsg(db));
    return 1;
  }

  if (i < capacity) {
    appointments[i].id[0] = '\0';
  }

  return 0;
};

int getByArtist(sqlite3 *db, Appointment appointments[], size_t capacity, 
    char *msg, size_t msgSize, char *artist) {
  sqlite3_stmt *stmt;
  const char *sql = "select * from Agendamento where artist_name = ?;";
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize,
        "Erro: não foi possivel consultar os agendamentos");

    return 1;
  }

  sqlite3_bind_text(stmt, 1, artist, -1, SQLITE_TRANSIENT);

  size_t i = 0;

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {

    if (i >= capacity) {
      snprintf(msg, msgSize, "Limite de agendamentos atingido");
      sqlite3_finalize(stmt);
      return 1;
    }

    Appointment *appointment = &appointments[i];

    snprintf(appointment->id, sizeof(appointment->id),
        "%s", sqlite3_column_text(stmt, 0));

    snprintf(appointment->date, sizeof(appointment->date),
        "%s", sqlite3_column_text(stmt, 1));

    snprintf(appointment->start_hour, sizeof(appointment->start_hour),
        "%s", sqlite3_column_text(stmt, 2));

    snprintf(appointment->duration, sizeof(appointment->duration),
        "%s", sqlite3_column_text(stmt, 3));

    snprintf(appointment->tattoo_description,
        sizeof(appointment->tattoo_description),
        "%s", sqlite3_column_text(stmt, 4));

    snprintf(appointment->artist_name,
        sizeof(appointment->artist_name),
        "%s", sqlite3_column_text(stmt, 5));

    snprintf(appointment->client_name,
        sizeof(appointment->client_name),
        "%s", sqlite3_column_text(stmt, 6));

    snprintf(appointment->client_phone,
        sizeof(appointment->client_phone),
        "%s", sqlite3_column_text(stmt, 7));

    i++;
  }

  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    snprintf(msg, msgSize, "Erro: %s", sqlite3_errmsg(db));
    return 1;
  }

  if (i < capacity) {
    appointments[i].id[0] = '\0';
  }

  return 0;
};

int changeById(Appointment appointment, sqlite3 *db, char *msg, 
    size_t msgSize, char *id) {

  char sql[512];
  char *errMsg = 0;

  sprintf(sql,
      "UPDATE Agendamento SET "
      "date = '%s', "
      "start_hour = %s, "
      "duration = %s, "
      "tattoo_description = '%s', "
      "artist_name = '%s', "
      "client_name = '%s', "
      "client_phone = '%s' "
      "WHERE id = %s;",
      appointment.date,
      appointment.start_hour,
      appointment.duration,
      appointment.tattoo_description,
      appointment.artist_name,
      appointment.client_name,
      appointment.client_phone,
      id
      );

  int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize,
        "Erro ao atualizar registro: %s", errMsg);

    sqlite3_free(errMsg);
    return 1;
  }

  snprintf(msg, msgSize,
      "Registro atualizado com sucesso");

  return 0;
}

int cancel(sqlite3 *db, char *msg, size_t msgSize, char *id) {
  char sql[128];
  char *errMsg = 0;

  sprintf(sql,
      "DELETE FROM Agendamento WHERE id = %s;",
      id
      );

  int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

  if (rc != SQLITE_OK) {
    snprintf(msg, msgSize,
        "Erro ao cancelar agendamento: %s", errMsg);

    sqlite3_free(errMsg);
    return 1;
  }

  if (sqlite3_changes(db) == 0) {
    snprintf(msg, msgSize,
        "Nenhum agendamento encontrado com esse ID");
    return 1;
  }

  snprintf(msg, msgSize,
      "Agendamento cancelado com sucesso");

  return 0;
}
