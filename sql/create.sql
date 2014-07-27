CREATE TABLE IF NOT EXISTS 'invdata' (
    'id' int(11) NOT NULL AUTO_INCREMENT,
    'whenquery' timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    'UDC' int(11) NOT NULL,
    'IDC' int(11) NOT NULL,
    'UL1' int(11) NOT NULL,
    'IL1' int(11) NOT NULL,
    'PAC' int(11) NOT NULL,
    'PRL' int(11) NOT NULL,
    'TKK' int(11) NOT NULL,
    'TNF' int(11) NOT NULL,
    'KDY' int(11) NOT NULL,
    'KLD' int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

ALTER TABLE 'invdata'
    ADD PRIMARY KEY ('id');
