from onlineapp.models import *
from rest_framework import serializers

class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model = college
        exclude=['id']

class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model =student
        #exclude =['id']
        fields = ('id','name','email','college','db_folder','dropped_out')

class MarksSerializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        #exclude=['id','total','student']
        fields = ('problem1','problem2','problem3','problem4','total','student')



