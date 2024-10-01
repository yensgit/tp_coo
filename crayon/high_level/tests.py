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
        u=Usine.objects.create()
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
        u.ressource.add(r1)
         r1=Ressource.objects.create(nom="mine",
                               prix=15,
                                    )
        u.ressource.add(r2)
      
