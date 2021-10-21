from django.contrib import admin
from django.urls import path

from monitor.views import *

urlpatterns = [
    path('', user_login, name='user_login'),
    path('signIn', signIn, name='signIn'),
    path('user_logout', user_logout, name='user_logout'),
    path('home', home, name='home'),
    path('getData/', getData, name='getData'),
    path('admin', admin.site.urls),
]
