# Generated by Django 2.2.1 on 2019-06-07 09:17

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('onlineapp', '0008_remove_student_dob'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='student',
            name='dob',
        ),
    ]