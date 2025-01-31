# Introduction 

Ce fichier est un projet universitaire qui avait pour but la conception d'une usine de fabrication de crayon.
Pour se faire nous avons pris en main l'outil GIT pour la création du projet à travers la configuration d’un dépôt distant 
qui nous a permis de faire la publication du projet. Nous avons également crée une application grace à django afin de pouvoir
spécifier les différentes instances de notre projet ( usine, villes, les machines etc...).

# voici  les Pre requis pour effectuer l'installation :
Il vous faudra installer les outils suivants :

    Git : git --version
    Python : python -V
    Pip : python -m pip -V
    Virtualenv : python -m venv
    CMake (pour la partie C++) : pip install cmake

Ensuite il vous faudra cloner le projet :

    git clone  https://github.com/yensgit/tp_coo
    cd crayon

## Configurer l’environnement Python

    python -m venv .venv
    source .venv/bin/activate  # Sur Windows : .venv\Scripts\activate
    pip install -U pip
    pip install django
    django-admin startproject crayon

# Accès à l’application

Appliquer les migrations

    cd crayon
    ./manage.py makemigrations
    ./manage.py migrate

Créer un super-utilisateur

    ./manage.py createsuperuser

Lancer le serveur

    ./manage.py runserver

    Accédez à l’administration via http://localhost:8000/admin.

# Données de tests et résultats finaux 
## Données de tests :
- une Usine de 50 m²
- dans la Ville Labège à 2 000 €/m² 
- avec une Machine à 1 000 €, et une autre à 2 000 €
 en stock
- 1000 kg de bois à 10 €/kg
- 50 m de mine à 15 €/m

Les ressources sont donc : le bois et la mine.

## Résultats obtenus 
### Partie Django

Pour l'usine

![image](https://github.com/user-attachments/assets/d14bed04-08a4-4084-a12a-091afb2a4ebc)

Pour une de nos villes (car nous en avons crée 2)

![image](https://github.com/user-attachments/assets/b3237fb2-3e78-473e-b98d-1dcb1b4ed7b8)

Pour l'une de nos ressources

![image](https://github.com/user-attachments/assets/957dad43-9ef9-44a3-b331-aa3c5664bcae)

#### Liste de nos éléments :

Pour accéder aux autres modèles, il vous faudra aller sur ce lien :

    http://127.0.0.1:8000/
    
en rajoutant à la suite :

    villes/id/ 
    locaux/id/
    objet/id/ 
    quantite/id/ 
    machine/id/ 
    usine/id/ 
    etape/id/ 
    produit/id/ 
    stock/id/ 
    api/id/ 
    
### Partie C++

## Compilation du projet C++

Configurer et compiler

    cd crayon/low_level
    cmake -B build -S .
    cmake --build build
    ./build/low_level


![image](https://github.com/user-attachments/assets/136eb7f9-7813-416d-a50a-73c9524fea74)

#### Autrices : Zoe VILLEMUR  & Mariam M L YENA 
