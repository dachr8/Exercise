from django import forms


class RegisterForm(forms.Form):
    gender = (
        ('male', "男"),
        ('female', "女"),
    )
    username = forms.CharField(label="用户名", max_length=128, widget=forms.TextInput(attrs={'class': 'form-control'}))
    password1 = forms.CharField(label="密码", max_length=256, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    password2 = forms.CharField(label="确认密码", max_length=256,
                                widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    email = forms.EmailField(label="邮箱地址", widget=forms.EmailInput(attrs={'class': 'form-control'}))
    sex = forms.ChoiceField(label='性别', choices=gender)


class QueryForm(forms.Form):
    text_filter = (
        ('equal', "等于"),
        ('not equal', "不等于"),
        ('greater than', "大于"),
        ('greater than or equal', "大于或等于"),
        ('lower than', "小于"),
        ('lower than or equal', "小于或等于"),
        ('starts with', "开头是"),
        ('not starts with', "开头不是"),
        ('ends with', "结尾是"),
        ('not ends with', "结尾不是"),
        ('contains', "包含"),
        ('not contains', "不包含")
    )

    custom_filter = (
        ('and', "与"),
        ('or', "或")
    )

    username1 = forms.CharField(required=False, label="用户名", widget=forms.TextInput(attrs={'class': 'form-control'}))
    username2 = forms.CharField(required=False, label="用户名", widget=forms.TextInput(attrs={'class': 'form-control'}))
    email1 = forms.CharField(required=False, label="邮箱地址", widget=forms.TextInput(attrs={'class': 'form-control'}))
    email2 = forms.CharField(required=False, label="邮箱地址", widget=forms.TextInput(attrs={'class': 'form-control'}))
    text_filter_username1 = forms.ChoiceField(choices=text_filter)
    text_filter_username2 = forms.ChoiceField(choices=text_filter)
    text_filter_email1 = forms.ChoiceField(choices=text_filter)
    text_filter_email2 = forms.ChoiceField(choices=text_filter)
    custom_filter_username = forms.ChoiceField(choices=custom_filter)
    custom_filter_email = forms.ChoiceField(choices=custom_filter)
