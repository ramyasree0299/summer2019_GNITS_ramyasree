from django.db import models

# Create your models here.

class college(models.Model):
    name = models.CharField(max_length=128)
    location = models.CharField(max_length=64)
    acronym = models.CharField(max_length=8,unique=True)
    contact = models.EmailField()

    def __str__(self):
        return self.acronym

class student(models.Model):
    name = models.CharField(max_length=128)
    email = models.EmailField()
    db_folder = models.CharField(max_length=50,unique=True)
    dropped_out = models.BooleanField(default=False)
    college = models.ForeignKey(college, on_delete=models.CASCADE,to_field='acronym') #

    def __str__(self):
        return self.name


class MockTest1(models.Model):
    problem1 = models.IntegerField()
    problem2 = models.IntegerField()
    problem3 = models.IntegerField()
    problem4 = models.IntegerField()
    total = models.IntegerField()
    student = models.OneToOneField(student, on_delete=models.CASCADE,to_field = 'db_folder')

    def __str__(self):
        return f"Student {self.student.name} marks"


class Teacher(models.Model):
    name = models.CharField(max_length=40)
    college = models.ForeignKey(college, on_delete=models.CASCADE)