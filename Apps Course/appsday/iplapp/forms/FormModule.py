from django import forms
from iplapp.models import *
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
