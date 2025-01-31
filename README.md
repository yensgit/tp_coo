Ce fichier est un projet scoaire qui avait pour but la conception d'une usine de fabriction e crayon .pour se faire nous avons pris en main l'outil GIT pour la 
création du projet a travers la configuration d’un dépôt distant qui nous apermis de faire la publication du projet;nous avons egalment cree une application grace a django afin de pouvoir
specifier les differentes isntances de notre projet ( usine , l ville , les machines etc...).

# voici  les Pre requis pour effectuer l'installation 

#Cloner le projet

    git clone  https://github.com/yensgit/tp_coo
    cd crayon

## Configurer l’environnement Python

    python -m venv .venv
    source .venv/bin/activate  # Sur Windows : .venv\Scripts\activate
    pip install -U pip
    pip install django
    django-admin startproject crayon

# Créer l’application

    cd crayon
    ./manage.py startapp production

Appliquer les migrations

    ./manage.py makemigrations
    ./manage.py migrate

Créer un super-utilisateur

    ./manage.py createsuperuser

Lancer le serveur

    ./manage.py runserver

    Accédez à l’administration via http://localhost:8000/admin.

## Compilation du projet C++

#Configurer et compiler

    mkdir low_level
    cd low_level
    wget https://gitlab.laas.fr/gsaurel/teach/-/raw/main/src/CMakeLists.txt
    cmake -B build -S .
    cmake --build build

# Exécuter le programme

    ./build/low_level
