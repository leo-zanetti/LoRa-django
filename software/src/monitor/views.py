from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.contrib import auth
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required

import json
import serial
import time

# array = []
# sr = serial.Serial(port="COM3", baudrate=115200)

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
            messages.info(request, 'Username OR password is incorrect')

        context = {}
    return render(request, 'login.html')

@login_required
def user_logout(request):
    auth.logout(request)
    return redirect(user_login)

@login_required
def home(request):
	return render(request, 'home.html')

def getData(request):
    while True:
        # sensorData = sr.readline().decode('utf-8') 
        # array = sensorData.split("/")
        # print(array)
        if array[0] == '11':
            data = {}
            data["id"] = array[0]
            data["temperatura"] = array[1]
            data["umidade"] = array[2]
            data = json.dumps(data)
        elif array[0] == '12':
            data = {}
            data["id"] = array[0]
            data["solo"] = array[1]
            data = json.dumps(data)       
        return HttpResponse(data, content_type='application/json')
