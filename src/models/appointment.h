#ifndef APPOINTMENT_H
#define APPOINTMENT_H

typedef struct {
    char id[6];
    char date[15];
    char start_hour[15];
    char duration[15];
    char tattoo_description[150];
    char artist_name[50];
    char client_name[50];
    char client_phone[20];
} Appointment;

#endif
