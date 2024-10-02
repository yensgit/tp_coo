# Register your models here.
# Ville/admin.py
from django.contrib import admin
from . import models

admin.site.register(models.Ville)
admin.site.register(models.Local)
admin.site.register(models.Objet)
admin.site.register(models.Siegesocial)
admin.site.register(models.Ressource)
admin.site.register(models.QuantiteRessource)
admin.site.register(models.Machine)
admin.site.register(models.Usine)
admin.site.register(models.Etape)
admin.site.register(models.Produit)
admin.site.register(models.Stock)
