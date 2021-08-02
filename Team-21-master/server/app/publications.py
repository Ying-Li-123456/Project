from flask import Flask, request, render_template, url_for, redirect, jsonify, Blueprint, request
import re

from flask_login import current_user

app_pub = Blueprint('publications', __name__)


@app_pub.route('/')
def pub():
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('Publications.html', login_status=login_status)


@app_pub.route('/years/<year>')
def year(year):
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('/years/' + year + '.html', message=year, login_status=login_status)


@app_pub.route('/single_person/<name>')
def person(name):
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    full_name = ''
    name_array = re.findall('[A-Z][^A-Z]*', name)
    for n in name_array:
        full_name += n + ' '
    full_name = full_name[:-1]
    return render_template('/single_person/' + name + '.html', message=full_name, login_status=login_status)


@app_pub.route('/conferences/<conf>')
def conference(conf):
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('/conferences/' + conf + '.html', message=conf, login_status=login_status)
