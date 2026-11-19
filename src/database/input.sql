CREATE TABLE Agendamento (
  id INTEGER PRIMARY KEY,
  date DATE NOT NULL,
  start_hour INTEGER NOT NULL,
  duration INTEGER NOT NULL,
  tattoo_description VARCHAR(150) NOT NULL,
  artist_name VARCHAR(50) NOT NULL,
  client_name VARCHAR(50) NOT NULL,
  client_phone TEXT NOT NULL
);

INSERT INTO Agendamento (
    date,
    start_hour,
    duration,
    tattoo_description,
    artist_name,
    client_name,
    client_phone
) VALUES (
  '2026-11-18',
  14,
  3,
  'Mão estilo cyberpunk',
  'Carlos', 
  'João',
  '11987654321'
);
