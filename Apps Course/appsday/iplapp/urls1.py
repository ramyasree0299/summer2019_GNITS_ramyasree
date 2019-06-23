"""classproject URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.conf import settings
from django.urls import path
from iplapp.views.iplappviews import *


if settings.DEBUG:
    urlpatterns1 = [
    path('iplapp/seasons_view/', DisplaySeasonView.as_view(),name="hompage"),
    path('iplapp/seasons_view/<str:season>/', DisplaySeasonView.as_view(), name="seasonpage"),
    path('iplapp/seasons_view/<str:id>/matches/', DisplayMatchView.as_view(), name="matchpage"),
    path('iplapp/seasons_view/<str:season>/points_table/', DisplayMatchView.as_view(), name="matchpage"),
        path('iplapp/login/', LoginController.as_view(), name='login_page'),
        path('iplapp/signup/', SignUpController.as_view(), name='signup_page'),
        path('iplapp/logout/', logout_user, name='logout_page'),
        path('iplapp/seasons_view/points_table/<str:season_view>/',DisplayPointsTableView.as_view(),name="pointstablepage"),

        # path('onlineapp/collegeret1/college/<str:acronym>/', CollegeView.as_view(), name='onlineapp_queries_link.html'),

    # path('onlineapp/collegeret1/colleges/add/', AddCollegeView.as_view(), name='Create_college'),
    # path('onlineapp/colleges/<str:acronym>/edit/', AddCollegeView.as_view(), name='edit_college'),
    # path('onlineapp/colleges/<str:acronym>/delete/', AddCollegeView.as_view(), name='delete_college'),
    #
    # path('onlineapp/collegeret1/college/<str:acronym>/students/add/', AddStudentView.as_view(), name='Create_student_marks'),
    # path('onlineapp/colleges/<str:acronym>/student/<str:db_folder>/edit', AddStudentView.as_view(), name='edit_student_marks'),
    # path('onlineapp/colleges/<str:acronym>/student/<str:db_folder>/delete/', AddStudentView.as_view(), name='delete_student_marks'),
    #
    # path('onlineapp/login/', LoginController.as_view(),name='login_page'),
    # path('onlineapp/signup/', SignUpController.as_view(), name='signup_page'),
    # path('onlineapp/collegeret1/logout/',logout_user,name='logout_page'),

    ]