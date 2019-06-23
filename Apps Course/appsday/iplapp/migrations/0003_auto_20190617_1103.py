# Generated by Django 2.2.1 on 2019-06-17 05:33

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('iplapp', '0002_auto_20190617_1050'),
    ]

    operations = [
        migrations.RenameField(
            model_name='match',
            old_name='toss_lost',
            new_name='toss_decision',
        ),
        migrations.RenameField(
            model_name='match',
            old_name='venue_of_match',
            new_name='venue',
        ),
        migrations.AddField(
            model_name='match',
            name='winner',
            field=models.CharField(default='tie', max_length=64),
        ),
    ]