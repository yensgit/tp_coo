# Create your models here.
 #ville/models.py
from django.db import models
class Ville(models.Model):
    title = models.CharField(max_length=100)
    nom=models.CharField(max_length=100)
    code_postal=models.IntegerField(default=0)
    prix_m2=models.IntegerField(default=0)
class Local(models.Model):
    ville= models.ForeignKey(
    Ville,
    on_delete=models.PROTECT,
    )
    nom=models.CharField(max_length=100)
    surface=models.IntegerField(default=0)
class Siegesocial(models.Model):
class Ressource(models.Model):
