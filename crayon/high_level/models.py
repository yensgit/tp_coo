# Create your models here.
# ville/models.py
from django.db import models


class Ville(models.Model):
    nom = models.CharField(max_length=100)
    code_postal = models.IntegerField(default=0)
    prix_m2 = models.IntegerField(default=0)
    def __str__(self):
        return self.nom


class Local(models.Model):
    ville = models.ForeignKey(
        Ville,
        on_delete=models.PROTECT,
    )
    nom = models.CharField(max_length=100)
    surface = models.IntegerField(default=0)

class Objet(models.Model):
    nom=models.CharField(max_length=100)
    prix=models.IntegerField(default=0)

class Siegesocial(Local):
    pass

class Ressource(models.Model):
    pass

class QuantiteRessource(Objet):
    ressource= models.ForeignKey(
        Ressource,
        on_delete=models.PROTECT,
    )
    quantite=models.IntegerField(default=0)

class Machine(models.Model):
    nom=models.CharField(max_length=100)
    n_serie=models.IntegerField(default=0)
    prix=models.IntegerField(default=0)

class Usine(Local):
    machines = models.ManyToManyField(Machine)

class Etape(models.Model):
    nom=models.CharField(max_length=100)
    machine= models.ForeignKey(
        Machine,
        on_delete=models.PROTECT,
    )
    quantite_ressource=models.ForeignKey(
        QuantiteRessource,
        on_delete=models.PROTECT,
    )
    duree=models.IntegerField(default=0)
    etape_suivante=models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
    )

class Produit(Objet):
    premiere_etape= models.ForeignKey(
        Etape,
        on_delete=models.PROTECT,
    )
    
class Stock(models.Model):
    objet= models.ForeignKey(
        Objet,
        on_delete=models.PROTECT,
    )
    nombre=models.IntegerField(default=0)
    usine= models.ForeignKey(
        Usine,
        on_delete=models.PROTECT,
    )
