from django.http import HttpResponse
from django.shortcuts import render
from django.template import loader
from onlineapp.models import *
from onlineapp.Serializers.SerializeModule import *
from rest_framework.decorators import api_view
from rest_framework.response import *
from rest_framework import status
from rest_framework.views import APIView
from django.views import View
from django.http import QueryDict

from rest_framework.authentication import SessionAuthentication, BasicAuthentication

class CsrfExemptSessionAuthentication(SessionAuthentication):

    def enforce_csrf(self, request):
        return  # To not perform the csrf check previously happening

authentication_classes = (CsrfExemptSessionAuthentication, BasicAuthentication)


class student_serialize_view(APIView):
    def get(self,request,**kwargs):
            if  kwargs.get("acronym") and not kwargs.get("db_folder"):
                students = student.objects.filter(college = kwargs.get("acronym"))
                marks = MockTest1.objects.filter(student__college=kwargs.get("acronym"))
            elif kwargs.get("acronym") and kwargs.get("db_folder"):
                students = student.objects.filter(college=kwargs.get("acronym")).filter(db_folder=kwargs.get("db_folder"))
                marks = MockTest1.objects.filter(student__college=kwargs.get("acronym")).filter(student__db_folder=kwargs.get("db_folder"))
            student_serializer = StudentSerializer(students, many=True)
            marks_serializer = MarksSerializer(marks, many=True)
            response_list=[]
            length = marks.count()
            for i in range(length):
                total =  marks_serializer.data[i]['problem1']+ marks_serializer.data[i]['problem2']+ marks_serializer.data[i]['problem3']+marks_serializer.data[i]['problem4']
                response_list.append({
                "name": student_serializer.data[i]['db_folder'],
                "email": student_serializer.data[i]['email'],
                "college": student_serializer.data[i]['college'],
                "problem1": marks_serializer.data[i]['problem1'],
                "problem2": marks_serializer.data[i]['problem2'],
                "problem3": marks_serializer.data[i]['problem3'],
                "problem4": marks_serializer.data[i]['problem4'],
                "total":total
            })
            return Response(response_list,status=status.HTTP_200_OK)

    def delete(self, request, **kwargs):
        if kwargs.get("acronym") and kwargs.get("db_folder"):
            student.objects.filter(college=kwargs.get("acronym")).filter(db_folder=kwargs.get("db_folder")).delete()
            return Response({'message': kwargs.get("db_folder") + ' deleted'}, status=status.HTTP_200_OK)

    def post(self, request,**kwargs):
        if 'acronym' in kwargs.keys():
            student_dict = QueryDict('', mutable=True)
            marks_dict = QueryDict('',mutable=True)
            students = {"name":request.data["name"],"email":request.data["email"],"college":kwargs.get("acronym"),"db_folder":request.data['db_folder'],"dropped_out":request.data["dropped_out"]}
            marks = {"problem1":request.data['problem1'],"problem2":request.data['problem2'],"problem3":request.data['problem3'],"problem4":request.data['problem4'],"total":request.data['total'],"student":request.data['db_folder']}
            student_dict.update(students)
            marks_dict.update(marks)
            student_serializer = StudentSerializer(data=student_dict)
            if student_serializer.is_valid():
                student_serializer.save()
            marks_serializer = MarksSerializer(data=marks_dict)
            if marks_serializer.is_valid() and student_serializer.is_valid():
                student_serializer.save()
                marks_serializer.save()
                return Response({'message': "Data inserted"},status=status.HTTP_201_CREATED)
            if marks_serializer.is_valid() and not student_serializer.is_valid():
                return Response(student_serializer.errors,status=status.HTTP_400_BAD_REQUEST)
            if not marks_serializer.is_valid() and student_serializer.is_valid():
                return Response(marks_serializer.errors, status=status.HTTP_400_BAD_REQUEST)
            if not marks_serializer.is_valid() and not student_serializer.is_valid():
                return Response(student_serializer.errors, status=status.HTTP_400_BAD_REQUEST)





    def put(self, request, *args,**kwargs):
        if 'db_folder' in kwargs.keys():
            dbname =kwargs.get("db_folder")
            college_name =college.objects.filter(student__db_folder=dbname).values("acronym")[0].get("acronym")
            students = {"name": request.data["name"], "email": request.data["email"], "college": college_name,
                        "db_folder":  kwargs.get("db_folder"), "dropped_out": request.data["dropped_out"]}
            marks = {"problem1": int(request.data['problem1']), "problem2": int(request.data['problem2']),
                     "problem3": int(request.data['problem3']), "problem4": int(request.data['problem4']),
                     "total": int(request.data['total']), "student": kwargs.get("db_folder")}
            student_serializer = StudentSerializer(data=students)
            students_query = student.objects.get(db_folder=dbname)
            student_serializer = StudentSerializer(students_query, data=students)

            marks_serializer = MarksSerializer(data=marks)
            marks_query = MockTest1.objects.get(student=dbname)
            marks_serializer = MarksSerializer(marks_query, data=marks)
            print(marks_query)
            if student_serializer.is_valid():
                student_serializer.save()

            if marks_serializer.is_valid() and student_serializer.is_valid():
                student_serializer.save()
                marks_serializer.save()
                return Response({'message': "Data Edited"}, status=status.HTTP_201_CREATED)


            elif marks_serializer.is_valid() and not student_serializer.is_valid():
                return Response(student_serializer.errors, status=status.HTTP_400_BAD_REQUEST)

            elif not marks_serializer.is_valid() and student_serializer.is_valid():
                return Response(marks_serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        return Response({'message': "Error occured in insertion"}, status=status.HTTP_400_BAD_REQUEST)