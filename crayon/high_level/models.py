# Create your models here.
 #ville/models.py
from django.db import models
class Ville(models.Model):
  title = models.CharField(max_length=100)
  nom=models.CharField(max_length=100)
  code_postal=models.IntegerField(default=0)
  prix_m2=models.IntegerField(default=0)
 #siegesocial/models.py
 class Siegesocial(models.Model):
 #siegesocial/models.py
 class Ressource(models.Model):
