from django.http import HttpResponse
from django.shortcuts import render
from django.template import loader
from onlineapp.models import *


def index_print_html(request):
    file = open("onlineapp/index.html", "r")
    string =""
    for line in file:
        string += line
    return HttpResponse(string)
    #return HttpResponse(html)



def hello_world(request):
    return HttpResponse("hello World")

def my_first_view(request):
    return HttpResponse("This is a sample response given")


def query(request):
    c = college.objects.values("name","acronym").distinct()
    string = "<br><br><center><table border=\"1\" font=\"24px\"><tr><th>Acronym</th><th>Name</th></th>"
    count  = 0
    for i in c:
        count+=1
        string+="<tr><td>"
        string+=i['acronym']+"</td><td>"+i['name']+"</td></tr>"
    string+="</table></center>"
    return HttpResponse(string)
    pass


def insert_college_data_into_db(request):
   if request.method == "POST":
    if request.POST.get("college_name") and request.POST.get("college_acronym") and request.POST.get("college_contact"):
        c_name=request.POST.get("college_name")
        c_acro = request.POST.get("college_acronym")
        c_con = request.POST.get("college_contact")
        c = college(name=c_name,acronym=c_acro,contact=c_con)
        c.save()
    return render(request,'Create_college.html')
    pass


def function(request,acronym):
    s = student.objects.filter(college=acronym).values("name","college","mocktest1__total")
    DICT_QUERY_SET = dict()
    DICT_QUERY_SET['result_set'] = s
    return render(request, 'onlineapp_queries_students.html', DICT_QUERY_SET)







































# def query2(request):
#     c = college.objects.values("name","acronym").distinct()
#     string = "<br><br><center><table border=\"1\" font=\"24px\"><tr><th>Acronym</th><th>Name</th></th>"
#     count  = 0
#     for i in c:
#         count+=1
#         string+="<tr><td>"
#         string+=i['acronym']+"</td><td><a href=\"function/{{i['acronym']}}\">college_student_info_"+i['acronym']+"</a></td></tr>"
#     string+="</table></center>"
#     return HttpResponse(string)
#     pass