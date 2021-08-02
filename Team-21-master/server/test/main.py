import os
import sys

from flask.helpers import make_response, send_from_directory
# for local
# import dblp
# for server
from server.test import dblp
import datetime

sys.path.append('../app/')

from flask import Flask, request, render_template, url_for, redirect, jsonify, Blueprint, request, send_file, \
    send_from_directory, make_response, json, session
from flask_login import UserMixin, LoginManager, login_user, login_required, logout_user, current_user
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import timedelta
# from app import publications

# for local
# from publications import app_pub
# for server
from server.app.publications import app_pub

login_manager = LoginManager()
login_manager.session_protection = "strong"

app = Flask(__name__, template_folder="../../templates", static_folder="../../static", )
app.config['TEMPLATES_AUTO_RELOAD'] = True
# app.config['PERMANENT_SESSION_LIFETIME'] = timedelta(minutes=5)
app.register_blueprint(app_pub, url_prefix='/Publications')
app.secret_key = 'Team 21'

login_manager.init_app(app)
login_manager.login_view = 'api_login'

USERS = [
    {
        "id": 1,
        "name": '1',
        "password": generate_password_hash('1')
    }
]


def read_res_list():
    # for local
    # read = open("researcher_list.txt", 'r')
    # for server
    read = open("server/test/researcher_list.txt", 'r')
    researchers = []
    l = read.readline()
    while l:
        if l is not '\n':
            name, pid, dayin, dayout = l.split()
            researchers += [{'name': name,
                             'pid': pid,
                             'dayin': dayin,
                             'dayout': dayout}]
        l = read.readline()
    return researchers


class User(UserMixin):
    def __init__(self, user):
        self.username = user.get("name")
        self.password_hash = user.get("password")
        self.id = user.get("id")

    def verify_password(self, password):
        if self.password_hash is None:
            return False
        return check_password_hash(self.password_hash, password)

    def get_id(self):
        return self.id

    @staticmethod
    def get(user_id):

        if not user_id:
            return None
        for user in USERS:
            if user.get('id') == user_id:
                return User(user)
        return None


@login_manager.user_loader
def load_user(user_id):
    return User.get(user_id)


@app.before_first_request
def create_dirs():
    path = 'bib_files/'
    if not os.path.exists(path):
        os.system('mkdir ' + path)
    os.system("touch server/test/researcher_list.txt")
    os.system("touch server/test/bib_change.txt")
    os.system("touch server/test/bib_change_log.txt")


@app.before_request
def make_session_permanent():
    session.permanent = True
    app.permanent_session_lifetime = timedelta(minutes=5)


@app.route('/')
def home_page():
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('Home.html', login_status=login_status)


@app.route('/Researchers')
def Researchers():
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('Researchers.html', login_status=login_status)


@app.route('/Projects')
def Projects():
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('Projects.html', login_status=login_status)


@app.route('/Join')
def Join():
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('Join.html', login_status=login_status)


@app.route('/Search')
def Search():
    login_status = '0'
    if not current_user.is_anonymous:
        login_status = '1'
    return render_template('Search.html', login_status=login_status)


@app.route('/login', methods=['GET', 'POST'])
def api_login():
    if not current_user.is_anonymous:
        return redirect('/admin')
    if request.method == 'GET':
        return render_template('login.html')

    username = request.form['username']
    password = request.form['password']

    print(username, password)
    user = load_user(1)
    if user.username == username and user.verify_password(password):
        login_user(user)
        return redirect('/admin')

    else:
        return render_template('login.html', error='1')


@app.route('/admin')
@login_required
def admin():
    return render_template('admin.html')


@app.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect('/')


@app.route('/update')
@login_required
def update():
    # for local
    # os.system('python3 dblp.py')
    # for server
    os.system('python3 server/test/dblp.py')
    return render_template('admin.html', error='0')


@app.route('/admin/add', methods=['GET', 'POST'])
@login_required
def add():
    researchers = read_res_list()

    if request.method == 'GET':
        return render_template('add_researcher.html', researchers=researchers, today=str(datetime.date.today()))
    fullname = request.form['fullname']
    if '/' in fullname:
        return render_template('add_researcher.html', error='3', researchers=researchers, today=str(datetime.date.today()))
    name = fullname.replace(' ', '')
    pid = request.form['pid']
    dayin = request.form['dayin']
    dayout = request.form['dayout']
    if not dayout:
        dayout = '2099-12-12'
    # for local
    # f = open("researcher_list.txt", 'r')
    # for server
    f = open("server/test/researcher_list.txt", 'r')
    line = f.readline()
    count = 0
    while line:
        if pid in line:
            return render_template('add_researcher.html', error='1', researchers=researchers, today=str(datetime.date.today()))
        if name in line:
            count += 1
        line = f.readline()
    if count != 0:
        name += str(count)
    if not dblp.download_bib_single(name, pid):
        return render_template('add_researcher.html', error='2', researchers=researchers, today=str(datetime.date.today()))
    # for local
    # w = open("researcher_list.txt", 'a')
    # for server
    w = open("server/test/researcher_list.txt", 'a')
    w.write(name + ' ' + pid + ' ' + dayin + ' ' + dayout + '\n')
    w.close()
    # for local
    # os.system('./parser')
    # for server
    os.system('./server/test/parser')
    researchers = read_res_list()
    return render_template('add_researcher.html', name=fullname, researchers=researchers, today=str(datetime.date.today()))


@app.route('/admin/remove', methods=['GET', 'POST'])
@login_required
def remove():
    researchers = read_res_list()

    if request.method == 'GET':
        return render_template('remove_researcher.html', researchers=researchers)
    pid = request.form['pid']
    deleted = False
    # for local
    # with open('researcher_list.txt', 'r') as r:
    # for server
    with open('server/test/researcher_list.txt', 'r') as r:
        lines = r.readlines()
    # for local
    # with open('researcher_list.txt', 'w') as w:
    # for server
    with open('server/test/researcher_list.txt', 'w') as w:
        for l in lines:
            if pid == l.split()[1]:
                name = l.split()[0]
                path = os.getcwd() + '/bib_files/' + name + '.bib'
                if os.path.exists(path):
                    os.remove(path)
                    os.system('rm ' + os.getcwd() + '/templates/single_person/*')
                    os.system('rm ' + os.getcwd() + '/templates/years/*')
                    os.system('rm ' + os.getcwd() + '/templates/conferences/*')
                    deleted = True
            else:
                if l is not '\n':
                    w.write(l)
        r.close()
        w.close()
    if deleted:
        # for local
        # os.system('./parser')
        # for server
        os.system('./server/test/parser')
        researchers = read_res_list()
        return render_template('remove_researcher.html', error='0', researchers=researchers)
    return render_template('remove_researcher.html', error='1', researchers=researchers)


@app.route('/admin/edit', methods=['GET', 'POST'])
@login_required
def admin_edit():
    if request.method == 'GET':
        url = request.args.get("url")
        if not url:
            return render_template('edit.html')
        url_path = 'single_bib/' + url.replace('/', '') + '.bib'
        lines = open(url_path, 'r').readlines()
        bib_text = ''
        for line in lines:
            bib_text += line
        return render_template('edit.html', url=url, bib_text=bib_text)
    url = request.form['url']

    nodename = request.form['nodename']
    if not nodename.isalpha():
        return render_template('edit.html', error='2')
    value = request.form['value']
    print(url, nodename, value)

    # for local
    # w = open("bib_change.txt", 'a')
    # for server
    w = open("server/test/bib_change.txt", 'a')
    # for local
    # log = open("bib_change_log.txt", 'a')
    # for server
    log = open("server/test/bib_change_log.txt", 'a')
    # Bruce edited this part
    w.write(url + '\n' + nodename + '={' + value + '},\n\n')
    log.write(
        "User:1\nDate:" + str(datetime.date.today()) + '\n' + url[15:-1] + '\n' + nodename + '={' + value + '},\n\n')
    w.close()
    log.close()
    # Bruce added this part
    # for local
    # os.system('./parser')
    # for server
    os.system('./server/test/parser')
    return render_template('edit.html', error='0')


@app.route('/admin/log')
@login_required
def Log():
    return render_template('log.html')


@app.route('/admin/<file_name>', methods=['GET', 'POST'])
@login_required
def get_file(file_name):
    directory = os.getcwd() + "/server/test/"
    try:
        response = make_response(send_from_directory(directory, file_name, as_attachment=True))

        return response
    except Exception as e:
        return jsonify({"code": "internal server error", "message": "{}".format(e)})


if __name__ == '__main__':
    # for local
    # path = os.getcwd();
    # path = path[:path.find('Team-21')+7]
    # path += '/bib_files/'
    # for server

    app.run()
