from django.contrib import admin
from .models import college
from .models import student,MockTest1,Teacher
# Register your models here.

admin.site.register(college)
admin.site.register(student)
admin.site.register(MockTest1)
admin.site.register(Teacher)

