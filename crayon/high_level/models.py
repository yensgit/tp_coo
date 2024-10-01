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
    def __str__(self):
        return f"{self.nom} {self.ville}"

class Objet(models.Model):
    nom=models.CharField(max_length=100)
    prix=models.IntegerField(default=0)
    def __str__(self):
        return self.nom

class Siegesocial(Local):
    pass

class Ressource(Objet):
    pass

class QuantiteRessource(models.Model):
    ressource= models.ForeignKey(
        Ressource,
        on_delete=models.PROTECT,
    )
    quantite=models.IntegerField(default=0)
    def __str__(self):
        return f"{self.ressource} {self.quantite}"
    def costs(self):
        return self.quantite*self.ressource.prix

class Machine(models.Model):
    nom=models.CharField(max_length=100)
    n_serie=models.IntegerField(default=0)
    prix=models.IntegerField(default=0)
    def __str__(self):
        return f"{self.nom} {self.n_serie}"
    def costs(self):
        prix_machines=0
        for machines in self.machine.all():
            prix_machines=prix_machines+machines.prix
        return prix_machines

class Usine(Local):
    machines = models.ManyToManyField(Machine)
    def costs(self):
        return self.local.surface*self.ville.prix_m2+self.machines.prix

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
    def __str__(self):
        return self.nom

class Produit(Objet):
    premiere_etape= models.ForeignKey(
        Etape,
        on_delete=models.PROTECT,
    )
    
class Stock(models.Model):
    ressource= models.ForeignKey(
        Ressource,
        on_delete=models.PROTECT,
    )
    nombre=models.IntegerField(default=0)
    usine= models.ForeignKey(
        Usine,
        on_delete=models.PROTECT,
    )
    def costs(self):
        return self.nombre*self.quantite*self.ressource.prix
