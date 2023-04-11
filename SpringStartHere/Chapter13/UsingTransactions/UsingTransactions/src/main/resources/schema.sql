CREATE TABLE Accounts (
    ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Amount INT NOT NULL
);

INSERT INTO Accounts (Name,Amount) VALUES ('Timmy',1000);
INSERT INTO Accounts (Name,Amount) VALUES ('Jenny',1000);