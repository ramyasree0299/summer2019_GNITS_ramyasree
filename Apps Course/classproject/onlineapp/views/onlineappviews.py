from django.views import View
from onlineapp.models import *
from django.contrib.auth.models import User
from django.shortcuts import render, redirect
from django.urls import resolve
from django.http import HttpResponse
from onlineapp.forms.FormModule import *
from django.contrib.auth import *
from django.contrib.auth.mixins import *



class DisplayCollegeView(LoginRequiredMixin, View):
    login_url = '/onlineapp/login/'
    def get(self, request, *args, **kwargs):
     c = college.objects.values("name", "acronym").distinct()
     DICT_QUERY_SET = dict()
     DICT_QUERY_SET['result_set'] = c
     DICT_QUERY_SET['permissions']= request.user.get_all_permissions()
     return render(request, 'onlineapp_queries_link.html', DICT_QUERY_SET)



class CollegeView(LoginRequiredMixin, View):
    login_url = '/onlineapp/login/'
    def get(self, request, *args, **kwargs):
        if kwargs:
            resultset = student.objects.filter(college=kwargs.get('acronym')).values("db_folder", "college","mocktest1__total")
            DICT_QUERY_SET = dict()
            DICT_QUERY_SET['result_set'] = resultset
            DICT_QUERY_SET['college_name'] = kwargs.get('acronym')
            DICT_QUERY_SET['title_student'] = "Students from {} college".format(kwargs.get('acronym'))
            DICT_QUERY_SET['permissions'] = request.user.get_all_permissions()
            return render(
                request,
                template_name="onlineapp_queries_students.html",
                context=DICT_QUERY_SET
            )


class AddCollegeView(LoginRequiredMixin, View):
    login_url = '/onlineapp/login/'
    def get(self, request, *args, **kwargs):
        form = AddCollege()
        if resolve(request.path_info).url_name == 'delete_college':
            college.objects.get(acronym=kwargs.get('acronym')).delete()
            return redirect("http://127.0.0.1:8000/onlineapp/collegeret1/")
        if kwargs:
            c = college.objects.filter(**kwargs).first()
            form = AddCollege(instance=c)
        return render(
            request,
            template_name="Create_college.html",
            context=
            {
                'form': form
            }
        )

    def post(self, request, *args, **kwargs):
        if request.method == 'POST':
            if resolve(request.path_info).url_name == 'edit_college':
                c = college.objects.get(acronym=kwargs.get('acronym'))
                form = AddCollege(request.POST, instance=c)
                if form.is_valid():
                    topic = form.save(commit=False)
                    topic.save()
                    return render(
                        request,
                        template_name="Create_college.html",
                        context=
                        {
                            'form': form,
                            'title': "Edited Successfully"
                        }
                    )
            form = AddCollege(request.POST)
            if form.is_valid():
                topic = form.save(commit=False)
                topic.save()
            return render(
                request,
                template_name="Create_college.html",
                context=
                {
                    'form': form,
                    'title': "Inserted Successfully"
                }
            )
        else:
            form = AddCollege()
        return render(
            request,
            template_name="Create_college.html",
            context=
            {
                'form': form,
                'title': "College Insertion"
            }
        )


class AddStudentView(LoginRequiredMixin, View):
    login_url = '/onlineapp/login/'

    def get(self, request, *args, **kwargs):
        form_marks = AddMarks()
        form_student = AddStudent()
        if resolve(request.path_info).url_name == 'delete_student_marks':
            student.objects.get(db_folder=kwargs.get('db_folder')).delete()
            return redirect("http://127.0.0.1:8000/onlineapp/collegeret1/college/" + kwargs.get('acronym') + "/")
        if kwargs and kwargs.get('db_folder'):
            s = student.objects.get(db_folder=kwargs.get('db_folder'))
            form_student = AddStudent(instance=s)
            m = MockTest1.objects.get(student=kwargs.get('db_folder'))
            if m is not None:
                form_marks = AddMarks(instance=m)
        return render(
            request,
            template_name="Create_student_marks.html",
            context=
            {
                'form_student': form_student,
                'form_marks': form_marks,
            }
        )

    def post(self, request, *args, **kwargs):
        form_student = AddStudent()
        form_marks = AddMarks()
        if request.method == 'POST':
            if resolve(request.path_info).url_name == 'edit_student_marks':
                s = student.objects.get(db_folder=kwargs.get('db_folder'))
                m = MockTest1.objects.get(student=s)
                s.name = str(request.POST.get('name'))
                s.email = str(request.POST.get('email'))
                s.college_id = kwargs.get('acronym')
                s.save()
                m.total = int(request.POST.get('problem1')) + int(request.POST.get('problem2')) + int(
                    request.POST.get('problem3')) + int(request.POST.get('problem4'))
                m.problem1 = request.POST.get('problem1')
                m.problem2 = request.POST.get('problem2')
                m.problem3 = request.POST.get('problem3')
                m.problem4 = request.POST.get('problem4')
                m.save()
            return redirect("http://127.0.0.1:8000/onlineapp/collegeret1/college/" + kwargs.get('acronym') + "/")
        else:
            form_student = AddStudent()
            form_marks = AddMarks()
            return render(
                request,
                template_name="Create_student_marks.html",
                context=
                {
                    'form_student': form_student,
                    'form_marks': form_marks
                }
            )



class LoginController(View):
    def get(self, request, *args, **kwargs):
        login = Login()
        return render(
            request,
            template_name="login.html",
            context=
            {
                'login': login
            }
        )

    def post(self, request, *args, **kwargs):
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(request, username=username, password=password)
        if user is not None:
            login(request, user)
            return redirect("http://127.0.0.1:8000/onlineapp/collegeret1/")
        else:
            return redirect("http://127.0.0.1:8000/onlineapp/login/")


class SignUpController(View):
    def get(self, request, *args, **kwargs):
        signup = Signup()
        return render(
            request,
            template_name="signup.html",
            context=
            {
                'signup': signup
            }
        )

    def post(self, request, *args, **kwargs):
        form = Signup(request.POST)
        if form.is_valid():
            user = User.objects.create_user(**form.cleaned_data)
        if user is not None:
            login(request, user)
            return redirect("http://127.0.0.1:8000/onlineapp/collegeret1/")
        else:
            return redirect("http://127.0.0.1:8000/onlineapp/login/")


def logout_user(request):
    logout(request)
    return redirect("http://127.0.0.1:8000/onlineapp/login/")
