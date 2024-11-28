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
from high_level.views import VilleJsonDetailView, LocalJsonDetailView ,ObjetJsonDetailView,QuantiteRessourceJsonDetailView,MachineJsonDetailView,UsineJsonDetailView,EtapeJsonDetailView, ProduitJsonDetailView, StockJsonDetailView
from high_level.views import VilleJson_ExtendedDetailView, LocalJson_ExtendedDetailView ,ObjetJson_ExtendedDetailView,QuantiteRessourceJson_ExtendedDetailView,MachineJson_ExtendedDetailView,UsineJson_ExtendedDetailView,EtapeJson_ExtendedDetailView, ProduitJson_ExtendedDetailView, StockJson_ExtendedDetailView

urlpatterns = [
    path("admin/", admin.site.urls),
    path('villes/<int:pk>/', VilleJsonDetailView.as_view(), name='ville'),
    path('locaux/<int:pk>/', LocalJsonDetailView.as_view(), name='local'),
    path('objet/<int:pk>/', ObjetJsonDetailView.as_view(), name='objet'),
    path('quantite/<int:pk>/', QuantiteRessourceJsonDetailView.as_view(), name='quantite'),
    path('machine/<int:pk>/', MachineJsonDetailView.as_view(), name='machine'),
    path('usine/<int:pk>/', UsineJsonDetailView.as_view(), name='usine'),
    path('etape/<int:pk>/', EtapeJsonDetailView.as_view(), name='etape'),
    path('produit/<int:pk>/', ProduitJsonDetailView.as_view(), name='produit'),
    path('stock/<int:pk>/', StockJsonDetailView.as_view(), name='stock'),

    path('villes/<int:pk>/', VilleJson_ExtendedDetailView.as_view(), name='ville'),
    path('locaux/<int:pk>/', LocalJson_ExtendedDetailView.as_view(), name='local'),
    path('objet/<int:pk>/', ObjetJson_ExtendedDetailView.as_view(), name='objet'),
    path('quantite/<int:pk>/', QuantiteRessourceJson_ExtendedDetailView.as_view(), name='quantite'),
    path('machine/<int:pk>/', MachineJson_ExtendedDetailView.as_view(), name='machine'),
    path('usine/<int:pk>/', UsineJson_ExtendedDetailView.as_view(), name='usine'),
    path('etape/<int:pk>/', EtapeJson_ExtendedDetailView.as_view(), name='etape'),
    path('produit/<int:pk>/', ProduitJson_ExtendedDetailView.as_view(), name='produit'),
    path('stock/<int:pk>/', StockJson_ExtendedDetailView.as_view(), name='stock')
]
