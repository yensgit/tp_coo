from .models import Ville
from django.http import JsonResponse
from django.views.generic import DetailView

class VilleJsonDetailView(DetailView): 
  model=Ville
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
