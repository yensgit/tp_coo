# Create your tests here.

from django.test import TestCase

from .models import Machine Usine


class MachineModelTests(TestCase):
    def test_machine_creation(self):
        self.assertEqual(Machine.objects.count(), 0)
        Machine.objects.create(nom="scie",
                               prix=1_000,
                               n_serie=44365)
        self.assertEqual(Machine.objects.count(), 1)
    def test_usine_costs(self): 
         v=Ville.objects.create(nom="Labège",
                               code_postal=31000,
                               prix_m2=2000
        )
        u=Usine.objects.create(nom="CHEZ MARIAM",
                              ville=v,
                              surface=50
                              )
        m1=Machine.objects.create(nom="m1",
                               prix=1000,
                               n_serie=1)
        u.machines.add(m1)
        m2=Machine.objects.create(nom="m2",
                               prix=2000,
                               n_serie=2)
        u.machines.add(m2) 
        r1=Ressource.objects.create(nom="bois",
                               prix=10,
                                   )

        r2=Ressource.objects.create(nom="mine",
                               prix=15)
        s1=Stock.objects.create(
            ressource=r1,
            quantite=50
        )
        s2=Stock.objects.create(
            ressource=r2,
            quantite=1000
        )
self.assertEqual (Usine.objects.first().costs(), 113750)
       
     
