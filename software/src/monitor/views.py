from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.contrib import auth
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required

import json
import serial

array = []
sr = serial.Serial(port="COM3", baudrate=115200, timeout=1)
  
def user_login(request):
    return render(request, 'login.html')

def signIn(request):
    if request.method == 'POST':
        username = request.POST.get('username')
        password =request.POST.get('password')

        user = authenticate(request, username=username, password=password)

        if user is not None:
            login(request, user)
            return redirect('home')
        else:
            messages.info(request, 'Usuário ou senha incorretos. Tente novamente.')
            return render(request, 'login.html')

@login_required
def user_logout(request):
    auth.logout(request)
    return redirect(user_login)

@login_required
def home(request):
	return render(request, 'imports_home.html')

def getData(request):
    data = {}
    sensorData = sr.readline()
    values = str(sensorData[0:len(sensorData)].decode('utf-8'))
    array = values.split("/")
    if len(values) > 0:
        print(array)
        if array[0] == "1":
            data["id"] = array[0]
            data["temperatura"] = array[1]
            data["umidade"] = array[2]
            data["rssi"] = array[3]
            data = json.dumps(data)
            return HttpResponse(data, content_type='application/json')
        if array[0] == "2":
            data["id"] = array[0]
            data["solo"] = array[1]
            data["rssi"] = array[2]
            data = json.dumps(data)
            return HttpResponse(data, content_type='application/json')
    else:
        return HttpResponse(data, content_type='application/json')