smlgr
=====

SolarMax S3000 DB logger

smlgr (SolarMax LoGgeR) is a little daemon which periodically query a
SolarMax S3000 DC-AC Inverter and collect all informations into a MySQL
database.
It uses a TCP socket to dialogate with the inverted and it uses a
SolarMax proprietary communication protocol.

It's the data collector part of a bigger statistic project which aims
to create a detailed production report on energy production.