from .models import Ville

class Ville JsonDetailView(DetailView): 
  model=Ville
  def render_to_response(self, context, **response_kwargs):
    return JsonResponse(self.object.json())
