"""
URL configuration for crayon project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""

from django.contrib import admin
from django.urls import path
from high_level.views import VilleJsonDetailView, LocalJsonDetailView ,ObjetJsonDetailView,QuantiteRessourceJsonDetailView,MachineJsonDetailView

urlpatterns = [
    path("admin/", admin.site.urls),
    path('villes/<int:pk>/', VilleJsonDetailView.as_view(), name='ville'),
    path('locaux/<int:pk>/', LocalJsonDetailView.as_view(), name='local'),
    path('objet/<int:pk>/', ObjetJsonDetailView.as_view(), name='objet'),
    path('quantite/<int:pk>/', QuantiteRessourceJsonDetailView.as_view(), name='quantite'),
    path('machine/<int:pk>/', MachineJsonDetailView.as_view(), name='machine')
]
