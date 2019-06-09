from cmd import Cmd
from django.db import connection
from onlineapp.models import *
import os
import sys
import django
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'homeproject.settings')
django.setup()
class MyPrompt(Cmd):
    prompt = '>>>'
    def do_exit(self, inp):
        '''exit the application.'''
        print("Bye")
        return True

    def do_hello(self, inp):
        '''prints hello with name'''
        print("Hello Ramya")

    def do_lq(self,inp):
        '''prints the last queries'''
        return connection.queries[-1]

    def do_add(self, inp):
        print("Adding '{}'".format(inp))

    def help_add(self):
        print("Add a new entry to the system.")

MyPrompt().cmdloop()