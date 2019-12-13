from django.contrib import admin

from . import models


class UserAdmin(admin.ModelAdmin):
    # ...
    list_display = ('name', 'sex', 'email', 'password')
    list_per_page = 5
    search_fields = ['name', 'email']
    list_filter = ['sex']
    #filter_horizontal = ('email',)  # 添加字段内容的搜索框


admin.site.register(models.User, UserAdmin)
