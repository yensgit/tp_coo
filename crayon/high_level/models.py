# Create your models here.
# ville/models.py
from django.db import models


class Ville(models.Model):
    title = models.CharField(max_length=100)
    nom = models.CharField(max_length=100)
    code_postal = models.IntegerField(default=0)
    prix_m2 = models.IntegerField(default=0)


class Local(models.Model):
    ville = models.ForeignKey(
        Ville,
        on_delete=models.PROTECT,
    )
    nom = models.CharField(max_length=100)
    surface = models.IntegerField(default=0)


class Siegesocial(models.Model):
    pass


class Ressource(models.Model):
    pass

class Machine(models.Model):
    nom=models.CharField(max_length=100)
    n_serie=models.IntegerField(default=0)
    prix=models.IntegerField(default=0)

class Usine(Local):
    machines = models.ForeignKey(
        Ville,
        on_delete=models.PROTECT,
    )
