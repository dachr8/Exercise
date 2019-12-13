# login/views.py

import hashlib

from django.shortcuts import render, redirect

from login.forms import RegisterForm, QueryForm
from login.models import User


def index(request):
    return render(request, 'login/index.html')


def register(request):
    def hash_code(s, salt='mysite_login'):
        h = hashlib.sha256()
        s += salt
        h.update(s.encode())  # update方法只接收bytes类型
        return h.hexdigest()

    if request.session.get('is_login', None):
        return redirect('index')
    if request.method == "POST":
        register_form = RegisterForm(request.POST)
        message = "请检查填写的内容！"
        if register_form.is_valid():  # 获取数据
            username = register_form.cleaned_data['username']
            password1 = register_form.cleaned_data['password1']
            password2 = register_form.cleaned_data['password2']
            email = register_form.cleaned_data['email']
            sex = register_form.cleaned_data['sex']
            if password1 != password2:  # 判断两次密码是否相同
                message = "两次输入的密码不同！"
                return render(request, 'login/register.html', locals())
            else:
                same_name_user = User.objects.filter(name=username)
                if same_name_user:  # 用户名唯一
                    message = '用户已经存在，请重新选择用户名！'
                    return render(request, 'login/register.html', locals())
                same_email_user = User.objects.filter(email=email)
                if same_email_user:  # 邮箱地址唯一
                    message = '该邮箱地址已被注册，请使用别的邮箱！'
                    return render(request, 'login/register.html', locals())

                # 当一切都OK的情况下，创建新用户

                new_user = User.objects.create()
                new_user.name = username
                new_user.password = hash_code(password1)  # 使用加密密码
                new_user.email = email
                new_user.sex = sex
                new_user.save()
                return redirect('index')  # 自动跳转到登录页面
    register_form = RegisterForm()
    return render(request, 'login/register.html', locals())


def query(request):
    def query_filter(query_set, filter_condition, filter_data, field):
        if field == 'name':
            if filter_condition == 'equal':
                query_set = query_set.filter(name=filter_data)
            elif filter_condition == 'not equal':
                query_set = query_set.exclude(name=filter_data)
            elif filter_condition == 'greater than':
                query_set = query_set.filter(name__gt=filter_data)
            elif filter_condition == 'greater than or equal':
                query_set = query_set.filter(name__gte=filter_data)
            elif filter_condition == 'lower than':
                query_set = query_set.filter(name__lt=filter_data)
            elif filter_condition == 'lower than or equal':
                query_set = query_set.filter(name__lte=filter_data)
            elif filter_condition == 'starts with':
                query_set = query_set.filter(name__startswith=filter_data)
            elif filter_condition == 'not starts with':
                query_set = query_set.exclude(name__startswith=filter_data)
            elif filter_condition == 'ends with':
                query_set = query_set.filter(name__endswith=filter_data)
            elif filter_condition == 'not ends with':
                query_set = query_set.exclude(name__endswith=filter_data)
            elif filter_condition == 'contains':
                query_set = query_set.filter(name__contains=filter_data)
            elif filter_condition == 'not contains':
                query_set = query_set.exclude(name__contains=filter_data)
        elif field == 'email':
            if filter_condition == 'equal':
                query_set = query_set.filter(email=filter_data)
            elif filter_condition == 'not equal':
                query_set = query_set.exclude(email=filter_data)
            elif filter_condition == 'greater than':
                query_set = query_set.filter(email__gt=filter_data)
            elif filter_condition == 'greater than or equal':
                query_set = query_set.filter(email__gte=filter_data)
            elif filter_condition == 'lower than':
                query_set = query_set.filter(email__lt=filter_data)
            elif filter_condition == 'lower than or equal':
                query_set = query_set.filter(email__lte=filter_data)
            elif filter_condition == 'starts with':
                query_set = query_set.filter(email__startswith=filter_data)
            elif filter_condition == 'not starts with':
                query_set = query_set.exclude(email__startswith=filter_data)
            elif filter_condition == 'ends with':
                query_set = query_set.filter(email__endswith=filter_data)
            elif filter_condition == 'not ends with':
                query_set = query_set.exclude(email__endswith=filter_data)
            elif filter_condition == 'contains':
                query_set = query_set.filter(email__contains=filter_data)
            elif filter_condition == 'not contains':
                query_set = query_set.exclude(email__contains=filter_data)

        return query_set

    if request.method == "POST":
        query_form = QueryForm(request.POST)
        if query_form.is_valid():  # 获取数据
            username1 = query_form.cleaned_data['username1']
            username2 = query_form.cleaned_data['username2']
            email1 = query_form.cleaned_data['email1']
            email2 = query_form.cleaned_data['email2']
            text_filter_username1 = query_form.cleaned_data['text_filter_username1']
            text_filter_username2 = query_form.cleaned_data['text_filter_username2']
            text_filter_email1 = query_form.cleaned_data['text_filter_email1']
            text_filter_email2 = query_form.cleaned_data['text_filter_email2']
            custom_filter_username = query_form.cleaned_data['custom_filter_username']
            custom_filter_email = query_form.cleaned_data['custom_filter_email']

            context = {}
            """
            try:
                data = User.objects.get(name=username1)
                context['users'] = user
            except User.DoesNotExist:
                context['users'] = 'User DoesNotExist'
            """
            users_all = User.objects.all()
            users = users_all

            if username1:
                users = query_filter(users, text_filter_username1, username1, 'name')
            if username2:
                if custom_filter_username == 'and':
                    users = query_filter(users, text_filter_username2, username2, 'name')
                else:
                    users = users.union(query_filter(users_all, text_filter_username2, username2, 'name'))

            users_all = users

            if email1:
                users = query_filter(users, text_filter_email1, email1, 'email')
            if email2:
                if custom_filter_username == 'and':
                    users = query_filter(users, text_filter_email2, email2, 'email')
                else:
                    users = users.union(query_filter(users_all, text_filter_email2, email2, 'email'))

            if users:
                context['users'] = users
            else:
                context['message'] = 'User DoesNotExist'
            return render(request, 'login/index.html', context)  # 自动跳转到登录页面
    query_form = QueryForm()
    return render(request, 'query/query.html', locals())
