from .models import Ville, Local ,Objet,QuantiteRessource
from django.http import JsonResponse
from django.views.generic import DetailView

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
