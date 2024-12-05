from .models import Ville, Local ,Objet,QuantiteRessource,Machine,Usine,Etape, Produit, Stock
from django.http import JsonResponse
from django.views.generic import DetailView
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status

class VilleJsonDetailView(DetailView): 
  model=Ville
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())

class LocalJsonDetailView(DetailView): 
  model=Local
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
    
class ObjetJsonDetailView(DetailView): 
  model=Objet
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())

class QuantiteRessourceJsonDetailView(DetailView): 
  model=QuantiteRessource
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
    
class MachineJsonDetailView(DetailView): 
  model=Machine
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
    
class UsineJsonDetailView(DetailView): 
  model=Usine
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())

class EtapeJsonDetailView(DetailView): 
  model=Etape
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
    
class ProduitJsonDetailView(DetailView): 
  model=Produit
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())

class StockJsonDetailView(DetailView): 
  model=Stock
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())

class ProjetAPIView(APIView):
  model=Usine
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
    
