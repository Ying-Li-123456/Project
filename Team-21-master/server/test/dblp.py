import os

import requests


def download_bib():

    f = open("server/test/researcher_list.txt")
    line = f.readline()
    dict = {}
    # Edited by bruce


    while line:
        researcher_name, pid = line.split()[0], line.split()[1]
        dict[researcher_name] = pid + ".bib"
        line = f.readline()

    for key in dict:
        print(key + " " + dict[key])
        bibfile = requests.get(dict[key])
        open('bib_files/' + key + '.bib', 'wb').write(bibfile.content)
    f.close()
    os.system('./server/test/parser')


def download_bib_single(name, pid):
    if not 'https://dblp.org/pid/' in pid:
        return False
    bibfile = requests.get(pid+'.bib')
    if bibfile.status_code == 404:
        return False
    file = open('bib_files/' + name + '.bib', 'wb')
    file.write(bibfile.content)
    file.close()
    return True



if __name__ == '__main__':
    download_bib()
