'''create 2 models todolist (name string, created autofilled to current datetime))  and todoitem (description, due_date optional field, completed bool)
create a new tododata.py tool which will populate the database with some test data 5 todolists (todolist1, todolist2....) and each with 5 items (list1item1, list1item2 etc...)'''

from django.db import models
class todolist(models.Model):
    name = models.CharField(max_length=128)
    datetime = models.DateTimeField(auto_now_add=True)
    def __str__(self):
        return self.name

class todoitem(models.Model):
    description = models.CharField(max_length=256)
    due_date =  models.DateField(null=True, blank=True)
    completed = models.BooleanField(default=False)
    def __str__(self):
        return self.description