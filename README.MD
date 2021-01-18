# DESCRIPTION

This project is written in C++ is an executable that permit to have a multi-language dictionary.

It supports the options of adding adding, searching, deleting and importing contents in the application.

It was coded for academic learning purpose so all the specification were given by the teacher in charge of the class INF3105(Structure de données et algorithmes) in UQAM during the session of Winter 2019. 

It was the assignment number two of that session.

Note that it doesn't contains a database so all the added items are relative to the active session only and deleted afterwards.

The goal of this exercice was not to build a complex final executable but more too manipulate complex data structures

# USAGE

## Compiling

Open a terminal, navigate until arriving at the root of the project then run the makefile with the command `make`.

## Running 

Once the project is compiled we can run it by simply typing the command `./tp2`.

## Supported command

We can:

- Add new word by typing: `Ajouter [<language first two digit>] <new word>`.

- Delete a word by typing: `Supprimer [<language first two digit>] <Word>`.

- Search a word by typing: `Chercher [<language first two digit>] <Word>`.

# Stage

The adding, delete, and searching works perfectly. 

Others options like importing, translating, add synonym, delete synonym, delete translation, search translation, exists but should be ameliorated since they don't work as expected.