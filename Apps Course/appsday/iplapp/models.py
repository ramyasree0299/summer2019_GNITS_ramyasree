from django.db import models
from django.contrib.auth.models import User
# Create your models here.

class match(models.Model):
    season = models.CharField(max_length=64,null=True)
    city = models.CharField(max_length=64,null=True)
    team1 = models.CharField(max_length=64,null=True)
    team2 = models.CharField(max_length=64,null=True)
    toss_won = models.CharField(max_length=64,null=True)
    toss_decision = models.CharField(max_length=64,null=True)
    result = models.CharField(max_length=64,null=True)
    dl_applied = models.IntegerField()
    winner = models.CharField(max_length=64,null=True)
    win_by_runs = models.IntegerField()
    win_by_wickets = models.IntegerField()
    player_of_match = models.CharField(max_length=64,null=True)
    venue = models.CharField(max_length=64,null=True)
    umpire1 = models.CharField(max_length=64,null=True)
    umpire2 = models.CharField(max_length=64,null=True)
    umpire3 = models.CharField(max_length=64,null=True)

class deliveries(models.Model):
    mid = models.ForeignKey(match,on_delete=models.CASCADE)
    inning = models.IntegerField()
    batting_team = models.CharField(max_length=128, null=True)
    bowling_team = models.CharField(max_length=128, null=True)
    over = models.IntegerField()
    ball = models.IntegerField()
    batsman = models.CharField(max_length=128, null=True)
    non_striker = models.CharField(max_length=128, null=True)
    bowler = models.CharField(max_length=128, null=True)
    is_super_over = models.BooleanField()
    wide_runs = models.IntegerField()
    bye_runs = models.IntegerField()
    legbye_runs = models.IntegerField()
    noball_runs = models.IntegerField()
    penalty_runs = models.IntegerField()
    batsman_runs = models.IntegerField()
    extra_runs = models.IntegerField()
    total_runs = models.IntegerField()
    player_dismissed = models.CharField(max_length=128, null=True)
    dismissal_kind = models.CharField(max_length=128, null=True)
    fielder = models.CharField(max_length=128, null=True)

    def __str__(self):
        return self.match

