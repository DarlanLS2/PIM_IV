#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cli.h"
#include "../models/appointment.h"
#include "../utils/terminal.h"
#include "../service/service.h"

int handleRegisterMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  Appointment appointment;

  setbuf(stdin, NULL);

  printf("  Digite a data [ano-mes-dia]: ");
  fgets(appointment.date, sizeof(appointment.date), stdin);
  formatInput(appointment.date);

  printf("  Digite o horario [14]: ");
  fgets(appointment.start_hour, sizeof(appointment.start_hour), stdin);
  formatInput(appointment.start_hour);

  printf("  Digite a duração [3]: ");
  fgets(appointment.duration, sizeof(appointment.duration), stdin);
  formatInput(appointment.duration);

  printf("  Digite a descrição da tattoo: ");
  fgets(appointment.tattoo_description, sizeof(appointment.tattoo_description), stdin);
  formatInput(appointment.tattoo_description);

  printf("  Digite o nome do tatuador: ");
  fgets(appointment.artist_name, sizeof(appointment.artist_name), stdin);
  formatInput(appointment.artist_name);

  printf("  Digite o nome do cliente: ");
  fgets(appointment.client_name, sizeof(appointment.client_name), stdin);
  formatInput(appointment.client_name);

  printf("  Digite o telefone do cliente: ");
  fgets(appointment.client_phone, sizeof(appointment.client_phone), stdin);
  formatInput(appointment.client_phone);

  handleRecord(appointment, msg, msgSize);

  printf("\n  %s\n", msg);

  return 0;
};

int handleSearchAllMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  Appointment appointments[30] = {0};
  int capacity = sizeof(appointments) / sizeof(appointments[0]);

  handleGetAll(appointments, capacity, msg, msgSize);
  printf("\n  > RESULTADOS:\n");

  for (int i = 0; i < capacity && appointments[i].id[0] != '\0'; i++) { 
    printf("  -----------------------------------------\n");
    printf("  ▪ Id = %s\n", appointments[i].id);
    printf("  ▪ Data = %s\n", appointments[i].date);
    printf("  ▪ Horario = %s\n", appointments[i].start_hour);
    printf("  ▪ Duração = %s\n", appointments[i].duration);
    printf("  ▪ Descrição %s\n", appointments[i].tattoo_description);
    printf("  ▪ Tatuador = %s\n", appointments[i].artist_name);
    printf("  ▪ Nome do cliente = %s\n", appointments[i].client_name);
    printf("  ▪ Tel. do cliente = %s\n", appointments[i].client_phone);
  }

  return 0;
};

int handleSearchByIdMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  Appointment appointments[30] = {0};
  int capacity = sizeof(appointments) / sizeof(appointments[0]);
  char *id;
  int rc;

  printf("  Digite o id: ");
  scanf(" %s", id);

  rc = handleGetById(appointments, capacity, msg, msgSize, id);

  if (rc != 0) {
    printf(" %s", msg);
  }

  printf("\n  > RESULTADO:\n");

  for (int i = 0; i < capacity && appointments[i].id[0] != '\0'; i++) { 
    printf("  -----------------------------------------\n");
    printf("  ▪ Id = %s\n", appointments[i].id);
    printf("  ▪ Data = %s\n", appointments[i].date);
    printf("  ▪ Horario = %s\n", appointments[i].start_hour);
    printf("  ▪ Duração = %s\n", appointments[i].duration);
    printf("  ▪ Descrição %s\n", appointments[i].tattoo_description);
    printf("  ▪ Tatuador = %s\n", appointments[i].artist_name);
    printf("  ▪ Nome do cliente = %s\n", appointments[i].client_name);
    printf("  ▪ Tel. do cliente = %s\n", appointments[i].client_phone);
  }

  return 0;
};

int handleSearchByArtistMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  Appointment appointments[30] = {0};
  int capacity = sizeof(appointments) / sizeof(appointments[0]);
  char *artist;
  int rc;

  printf("  Digite o nome do tatuador: ");
  scanf(" %s", artist);

  rc = handleGetByArtist(appointments, capacity, msg, msgSize, artist);

  if (rc != 0) {
    printf(" %s", msg);
  }

  printf("\n  > RESULTADOS:\n");

  for (int i = 0; i < capacity && appointments[i].id[0] != '\0'; i++) { 

    printf("  -----------------------------------------\n");
    printf("  ▪ Id = %s\n", appointments[i].id);
    printf("  ▪ Data = %s\n", appointments[i].date);
    printf("  ▪ Horario = %s\n", appointments[i].start_hour);
    printf("  ▪ Duração = %s\n", appointments[i].duration);
    printf("  ▪ Descrição %s\n", appointments[i].tattoo_description);
    printf("  ▪ Tatuador = %s\n", appointments[i].artist_name);
    printf("  ▪ Nome do cliente = %s\n", appointments[i].client_name);
    printf("  ▪ Tel. do cliente = %s\n", appointments[i].client_phone);
  }

  return 0;
};

int handleSearchByDateMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  Appointment appointments[30] = {0};
  int capacity = sizeof(appointments) / sizeof(appointments[0]);
  char *date;
  int rc;

  printf("  Digite a data [ano-mes-dia]: ");
  scanf(" %s", date);

  rc = handleGetByDate(appointments, capacity, msg, msgSize, date);

  if (rc != 0) {
    printf(" %s", msg);
  }

  printf("\n  > RESULTADOS:\n");

  for (int i = 0; i < capacity && appointments[i].id[0] != '\0'; i++) { 

    printf("  -----------------------------------------\n");
    printf("  ▪ Id = %s\n", appointments[i].id);
    printf("  ▪ Data = %s\n", appointments[i].date);
    printf("  ▪ Horario = %s\n", appointments[i].start_hour);
    printf("  ▪ Duração = %s\n", appointments[i].duration);
    printf("  ▪ Descrição %s\n", appointments[i].tattoo_description);
    printf("  ▪ Tatuador = %s\n", appointments[i].artist_name);
    printf("  ▪ Nome do cliente = %s\n", appointments[i].client_name);
    printf("  ▪ Tel. do cliente = %s\n", appointments[i].client_phone);
  }

  return 0;
};

int handleSearchMenu() {
  int option = 1;

  while (option != 0) {
    usleep(100000);
    clearTerminal();
    printf(" ┌─────────────────────────────┐\n"); 
    printf(" │            Busca            │\n"); 
    printf(" └─────────────────────────────┘\n\n"); 
    printf("  ▪  Buscar todos         [1]\n"); 
    printf("  ▪  Buscar por Id        [2]\n"); 
    printf("  ▪  Buscar por Tatuador  [3]\n"); 
    printf("  ▪  Buscar por Data      [4]\n"); 
    printf("  ▪  Voltar               [0]\n\n"); 

    printf("  Digite a opção: ");
    scanf(" %i", &option);

    if (option == 1) {
      handleSearchAllMenu();
      break;
    }
    else if (option == 2) {
      handleSearchByIdMenu();
      break;
    }
    else if (option == 3) {
      handleSearchByArtistMenu();
      break;
    }
    else if (option == 4) {
      handleSearchByDateMenu();
      break;
    }
    else if (option == 0) {
      return 1;
    } else
      printError();
  };

  return 0;
};

int handleChangeMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  Appointment appointment;
  char *id;

  printf("  Digite o id:");
  scanf(" %s", id);

  setbuf(stdin, NULL);

  printf("  Data [ano-mes-dia]: ");
  fgets(appointment.date, sizeof(appointment.date), stdin);
  formatInput(appointment.date);

  printf("  Horario: ");
  fgets(appointment.start_hour, sizeof(appointment.start_hour), stdin);
  formatInput(appointment.start_hour);

  printf("  Duração: ");
  fgets(appointment.duration, sizeof(appointment.duration), stdin);
  formatInput(appointment.duration);

  printf("  Descrição: ");
  fgets(appointment.tattoo_description, sizeof(appointment.tattoo_description), stdin);
  formatInput(appointment.tattoo_description);

  printf("  Nome do tatuador: ");
  fgets(appointment.artist_name, sizeof(appointment.artist_name), stdin);
  formatInput(appointment.artist_name);

  printf("  Nome do cliente: ");
  fgets(appointment.client_name, sizeof(appointment.client_name), stdin);
  formatInput(appointment.client_name);

  printf("  Tel. do cliente: ");
  fgets(appointment.client_phone, sizeof(appointment.client_phone), stdin);
  formatInput(appointment.client_phone);

  handleChangeById(appointment, msg, msgSize, id);

  printf("\n  %s\n", msg);

  return 0;
};

int handleCancelMenu() {
  char msg[100];
  size_t msgSize = sizeof(msg);
  char *id;

  printf("  Digite o id: ");
  scanf(" %s", id);

  handleCancel(msg, msgSize, id);

  printf("\n  %s\n", msg);

  return 0;
};

int handleMainMenu() {
  int option = 1;

  while (option != 0) {
    clearTerminal();
    printf(" ┌─────────────────────────────┐\n"); 
    printf(" │            Menu             │\n"); 
    printf(" └─────────────────────────────┘\n\n"); 
    printf("  ▪  Registrar agendamento [1]\n"); 
    printf("  ▪  Buscar agendamentos   [2]\n"); 
    printf("  ▪  Alterar agendamentos  [3]\n"); 
    printf("  ▪  Cancelar agendamento  [4]\n"); 
    printf("  ▪  Sair                  [0]\n\n"); 

    printf("  Digite a opção: ");
    scanf(" %i", &option);

    if (option == 1) 
      return handleRegisterMenu();
    else if (option == 2) {
      int result = handleSearchMenu();
      if (result == 0) 
        return 0;
      else 
        continue;
    }
    else if (option == 3) 
      return handleChangeMenu();
    else if (option == 4)
      return handleCancelMenu();
    else if (option == 0)
      continue;
    else
      printError();
  }

  return 0;
};
