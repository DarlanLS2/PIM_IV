#ifndef SERVICE_H
#define SERVICE_H

#include <stdio.h>
#include "../models/appointment.h"

int handleRecord(Appointment appointment, char *msg, 
    size_t msgSize);

int handleGetAll(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize);

int handleGetById(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize, char *id);

int handleGetByDate(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize, char *date);


int handleGetByArtist(Appointment appointments[], int capacity, 
    char *msg, size_t msgSize, char *artist);

int handleChangeById(Appointment appointment, 
    char *msg, size_t msgSize, char *id);

int handleCancel(char *msg, size_t msgSize, char *id);

#endif
