# Create your models here.
# ville/models.py
from django.db import models


class Ville(models.Model):
    nom = models.CharField(max_length=100)
    code_postal = models.IntegerField(default=0)
    prix_m2 = models.IntegerField(default=0)

    def __str__(self):
        return self.nom

    def json(self):
        return {
            "nom": self.nom,
            "code postal": self.code_postal,
            "prix m2": self.prix_m2,
        }
    def json_extended(self):
        return {
        "nom": self.nom,
        "code postal": self.code_postal,
        "prix m2": self.prix_m2,
    }


class Local(models.Model):
    ville = models.ForeignKey(
        Ville,
        on_delete=models.PROTECT,
    )
    nom = models.CharField(max_length=100)
    surface = models.IntegerField(default=0)

    def __str__(self):
        return f"{self.nom} {self.ville}"

    def json(self):
        return {"ville": self.ville.id, "nom": self.nom, "surface": self.surface}
    def json_extended(self):
        return {"ville": self.ville.id, "nom": self.nom, "surface": self.surface}

class Objet(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField(default=0)

    def __str__(self):
        return self.nom

    def json(self):
        return {"nom": self.nom, "prix": self.prix}
    def json_extended(self):
        return {"nom": self.nom, "prix": self.prix}

class Siegesocial(Local):
    pass


class Ressource(Objet):
    pass


class QuantiteRessource(models.Model):
    ressource = models.ForeignKey(
        Ressource,
        on_delete=models.PROTECT,
    )
    quantite = models.IntegerField(default=0)

    def __str__(self):
        return f"{self.ressource} {self.quantite}"

    def costs(self):
        return self.quantite * self.ressource.prix

    def json(self):
        return {"quantite": self.quantite, "ressource": self.ressource.id}
    def json_extended(self):
        return {"quantite": self.quantite, "ressource": self.ressource.id}


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    n_serie = models.IntegerField(default=0)
    prix = models.IntegerField(default=0)

    def __str__(self):
        return f"{self.nom} {self.n_serie}"
    def costs(self):
        return self.prix
    def json(self):
        return {"nom": self.nom, "n_serie": self.n_serie, "prix": self.prix}
    def json_extended(self):
        return {"nom": self.nom, "n_serie": self.n_serie, "prix": self.prix}
   # def costs(self):
        #prix_machines = 0
        #for machines in self.machine.all():
           # prix_machines = prix_machines + machines.prix
       # return prix_machines 
class Usine(Local):
    machines = models.ManyToManyField(Machine)

    #def costs(self):
        #return self.local.surface * self.ville.prix_m2 + self.machines.prix
    def json(self):
        liste_machines=[]
        
        for machines in self.machines.all():
            liste_machines.append(machines.id)
            return {"machines": liste_machines,
                    **super().json()}
    def json_extended(self):
        liste_machines=[]
    
        for machines in self.machines.all():
            liste_machines.append(machines.json_extended())
            return {"machines": liste_machines,
                   **super().json_extended()}
    def costs(self):
        prix_machine = 0
        prix_stock = 0
        for machines in Machine.objects.all():
            prix_machine = prix_machine + machines.prix
        for stock in Stock.objects.all():
            prix_stock = prix_stock + stock.ressource.prix * stock.nombre
            prix_local = self.surface * self.ville.prix_m2
        return prix_machine + prix_stock + prix_local

class Etape(models.Model):
    nom = models.CharField(max_length=100)
    machine = models.ForeignKey(
        Machine,
        on_delete=models.PROTECT,
    )
    quantite_ressource = models.ForeignKey(
        QuantiteRessource,
        on_delete=models.PROTECT,
    )
    duree = models.IntegerField(default=0)
    etape_suivante = models.ForeignKey(
        "self",
        blank=True,
        null=True,
        on_delete=models.PROTECT,
    )

    def __str__(self):
        return self.nom

    def json(self):
        d = {
            "nom": self.nom,
            "machine": self.machine.id,
            "quantite_ressource": self.quantite_ressource.id,
            "duree": self.duree,
        }

        if self.etape_suivante:
            d["etape_suivante"] = self.etape_suivante.id

        return d
    def json_extended(self):
        d = {
            "nom": self.nom,
            "machine": self.machine.id,
            "quantite_ressource": self.quantite_ressource.id,
            "duree": self.duree,
        }

        if self.etape_suivante:
            d["etape_suivante"] = self.etape_suivante.id

        return d

class Produit(Objet):
    premiere_etape = models.ForeignKey(
        Etape,
        on_delete=models.PROTECT,
    )
    def json(self):
        return {"premiere etape": self.premiere_etape.id}
    def json_extended(self):
        return {"premiere etape": self.premiere_etape.id}


class Stock(models.Model):
    ressource = models.ForeignKey(
        Ressource,
        on_delete=models.PROTECT,
    )
    nombre = models.IntegerField(default=0)
    usine = models.ForeignKey(
        Usine,
        on_delete=models.PROTECT,
    )

    def costs(self):
        return self.nombre * self.quantite * self.ressource.prix
    def json(self):
        return {"ressource": self.ressource.id,"nombre":self.nombre, "usine": self.usine.id}
    def json_extended(self):
        return {"ressource": self.ressource.id,"nombre":self.nombre, "usine": self.usine.id}
