from django.http import HttpResponse
from django.shortcuts import render
from django.template import loader
from onlineapp.models import *
from onlineapp.Serializers.SerializeModule import *
from rest_framework.decorators import api_view
from rest_framework.response import *
from rest_framework import status

@api_view(['GET', 'POST', 'DELETE','PUT'])
def college_serialize_view(request, *args, **kwargs):
    if request.method == 'GET':
        if kwargs:
            clg = college.objects.get(acronym=kwargs['acronym'])
            serializer = CollegeSerializer(clg)
            return Response(serializer.data)
        else:
            colleges = college.objects.all()
            serializer = CollegeSerializer(colleges, many=True)
            return Response(serializer.data)

    if request.method == 'POST':
        serializer = CollegeSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    if request.method == 'DELETE':
        acr = request.data['acronym']
        college.objects.get(acronym=acr).delete()
        return Response({'message': acr + ' deleted'}, status=status.HTTP_200_OK)

    if request.method == 'PUT':
        serializer = CollegeSerializer(data=request.data)
        if kwargs:
            acr = kwargs.get("acronym")
            colleges=college.objects.get(acronym=acr)
            serializer = CollegeSerializer(colleges, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
        return Response(status=status.HTTP_400_BAD_REQUEST)




