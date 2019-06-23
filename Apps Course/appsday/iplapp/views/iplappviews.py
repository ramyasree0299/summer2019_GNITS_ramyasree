from django.core.paginator import Paginator
from django.views import View
from iplapp.models import *
from django.contrib.auth.models import User
from django.shortcuts import render, redirect
from django.urls import resolve
from django.http import HttpResponse
from iplapp.forms.FormModule import *
from django.contrib.auth import *
from django.contrib.auth.mixins import *
from django.db.models import Count,Sum

class DisplaySeasonView(View):
    def get(self, request, *args, **kwargs):
        DICT_QUERY_SET = dict()
        DICT_QUERY_SET['flag'] = 0
        if not kwargs.get("season"):
            m1 = match.objects.values("id","season","team1","team2","toss_won","toss_decision","result","player_of_match","venue")
        if kwargs.get("season"):
            m1 = match.objects.filter(season = kwargs.get('season')).values("id","season","team1","team2","toss_won","toss_decision","result","player_of_match","venue")
            DICT_QUERY_SET['flag'] = 1
            DICT_QUERY_SET['season']=kwargs.get('season')
        m2 = match.objects.values("season").distinct().order_by('season')
        paginator = Paginator(m1, 8)
        page = request.GET.get('page')
        m1 = paginator.get_page(page)
        DICT_QUERY_SET['result_set'] = m1
        DICT_QUERY_SET['seasons']=m2
        DICT_QUERY_SET['permissions']= request.user.get_all_permissions()
        if request.user:
            DICT_QUERY_SET['user'] = request.user
        return render(request, 'iplapp_matches_list.html', DICT_QUERY_SET)


class DisplayMatchView(LoginRequiredMixin,View):
    login_url = '/iplapp/login/'
    def get(self, request, *args, **kwargs):
            match_id1 = deliveries.objects.filter(mid=kwargs.get("id")).filter(inning='1').values("inning","batting_team","bowling_team","batsman","bowler","total_runs","over")
            match_id2 = deliveries.objects.filter(mid=kwargs.get("id")).filter(inning='2').values("inning",
                                                                                                  "batting_team",
                                                                                                  "bowling_team",
                                                                                                  "batsman", "bowler",
                                                                                                  "total_runs", "over")

            toprunners = deliveries.objects.values('batsman','batting_team').filter(mid=kwargs.get("id")).annotate(Sum('total_runs')).order_by('-total_runs__sum')[:3]
            topbowlers = deliveries.objects.values('bowler', 'bowling_team').filter(mid=kwargs.get("id")).exclude(
                dismissal_kind=None).annotate(Count('dismissal_kind')).order_by('-dismissal_kind__count')[:3]
            DICT_QUERY_SET = dict()
            DICT_QUERY_SET['tab1'] = match_id1
            DICT_QUERY_SET['tab2']=match_id2
            DICT_QUERY_SET['permissions'] = request.user.get_all_permissions()
            DICT_QUERY_SET['toprunners']=toprunners
            DICT_QUERY_SET['topbowlers']=topbowlers
            if request.user:
                DICT_QUERY_SET['user'] = request.user
            return render(request, 'iplapp_matches_info.html', DICT_QUERY_SET)



class DisplayPointsTableView(LoginRequiredMixin,View):
    login_url = '/iplapp/login/'
    def get(self, request, *args, **kwargs):
            c = match.objects.filter(season=kwargs.get('season_view')).values('season','winner').annotate(Count('winner')).order_by(
            '-winner__count')
            DICT_QUERY_SET = dict()
            DICT_QUERY_SET['result_set']=c
            return render(request, 'iplapp_points_table.html', DICT_QUERY_SET)


class LoginController(View):
    def get(self, request, *args, **kwargs):
        login = Login()
        return render(
            request,
            template_name="login.html",
            context=
            {
                'login': login
            }
        )

    def post(self, request, *args, **kwargs):
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(request, username=username, password=password)
        if user is not None:
            login(request, user)
            return redirect("http://127.0.0.1:8000/iplapp/seasons_view/")
        else:
            return redirect("http://127.0.0.1:8000/iplapp/signup/")



class SignUpController(View):
    def get(self, request, *args, **kwargs):
        signup = Signup()
        return render(
            request,
            template_name="signup.html",
            context=
            {
                'signup': signup
            }
        )

    def post(self, request, *args, **kwargs):
        form = Signup(request.POST)
        if form.is_valid():
            user = User.objects.create_user(**form.cleaned_data)
        if user is not None:
            login(request, user)
            return redirect("http://127.0.0.1:8000/iplapp/seasons_view/")
        else:
            return redirect("http://127.0.0.1:8000/iplapp/login/")


def logout_user(request):
    logout(request)
    return redirect("http://127.0.0.1:8000/iplapp/seasons_view/")
