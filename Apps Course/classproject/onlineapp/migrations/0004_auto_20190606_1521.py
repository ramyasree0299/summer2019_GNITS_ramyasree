# Generated by Django 2.2.1 on 2019-06-06 09:51

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('onlineapp', '0003_student'),
    ]

    operations = [
        migrations.AlterField(
            model_name='student',
            name='email',
            field=models.EmailField(max_length=256),
        ),
    ]