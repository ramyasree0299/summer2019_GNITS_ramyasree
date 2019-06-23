from django import forms
from onlineapp.models import *
from django.forms import TextInput
class AddCollege(forms.ModelForm):
    class Meta:
        model = college
        exclude=['id']
        # widgets = {
        #     'name': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter name'}),
        #     'location': forms.TextInput(attrs={'class': 'input is-rounded per', 'placeholder': 'Enter location'}),
        #     'acronym': forms.TextInput(attrs={'class': 'input is-rounded per', 'placeholder': 'Enter acronym'}),
        #     'contact': forms.EmailInput(attrs={'class': 'input is-rounded per'})
        # }

class AddStudent(forms.ModelForm):
    class Meta:
        model = student
        exclude=['id','dob','dropped_out','college']
        # widgets = {
        #     'name': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter name'}),
        #     'email': forms.EmailInput(attrs={'class': 'input is-rounded per'}),
        #     'db_folder': forms.TextInput(attrs={'class': 'input','placeholder': 'Enter db name'}),
        # }

class AddMarks(forms.ModelForm):
    class Meta:
        model = MockTest1
        exclude=['id','student','total']
        # widgets = {
        #     'problem1': forms.IntegerField(attrs={'class': 'input', 'placeholder': 'Enter marks1'}),
        #     'problem2': forms.IntegerField(attrs={'class': 'input', 'placeholder': 'Enter marks2'}),
        #     'problem3': forms.IntegerField(attrs={'class': 'input', 'placeholder': 'Enter marks3'}),
        #     'problem4': forms.IntegerField(attrs={'class': 'input', 'placeholder': 'Enter marks4'}),
        #      }
        #

class Login(forms.Form):
    username = forms.CharField(
        widget=forms.TextInput(attrs={'class':'input','placeholder':"Enter username"}),
        max_length=50,
        required=True
    )
    password = forms.CharField(
        widget=forms.PasswordInput(attrs={'class': 'input', 'placeholder': "Enter username"}),
        max_length=50,
        required=True
    )

class Signup(forms.Form):
    first_name = forms.CharField(
        widget=forms.TextInput(attrs={'class':'input','placeholder':"Enter firstname"}),
        max_length=50,
        required=True
    )
    last_name = forms.CharField(
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': "Enter lastname"}),
        max_length=50,
        required=True
    )
    username = forms.CharField(
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': "Enter username"}),
        max_length=50,
        required=True
    )
    password = forms.CharField(
        widget=forms.PasswordInput(attrs={'class': 'input', 'placeholder': "Enter Password"}),
        max_length=50,
        required=True
    )