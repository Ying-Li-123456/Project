## Team-21 Automated generation and update of group publication lists

### Supervisors: Frank Neumann, Markus Wagner
### Team members: He Zhang, Wei Qin, Ying Li, Yupeng Hou


### Directroy tree

      Team21
    	┝ docs (including Agenda, Minutes, Timesheets and individual README file)
    	┝ parser_src (scource code for parser)
    	┝ server (server programs)
    	┝ static (all globally used CSS, img, and JS)
    	┝ templates (all HTML products)
    	┝ test_results (all test results)
    	┝ webpage__samples (all front-end demo files)
    	┝ .gitignore (the ignored files)
    	┝ Procfile (running commands)
    	┝ requirements.txt (required packets)
    	┕ runtime.txt (runtime requirements)


### Milestone

#### Milesone 1 
Click this link to view files of milestone 1
https://github.cs.adelaide.edu.au/MCI-Projects-2021/Team-21/tree/ea984be16fc454232d7544642a829aa1b0b6d82f

#### Final(second) milestone
Click this link to view files of milestone 2
https://github.cs.adelaide.edu.au/MCI-Projects-2021/Team-21


### Run the app

#### Test in web server 
Now, the web-based application has been deployed on Heroku platform. Users could visit it via https://nameless-forest-88703.herokuapp.com/.

#### Test in local server 
1. install all packets mentioned in requirements.txt and runtime.txt.  
(e.g: for mac users:  
      install heroku using 'brew install heroku'  
      install gunicorn using 'pip install gunicorn'  
      for Ubantu users:  
      install heroku using 'sudo apt install heroku'  
      install gunicorn using 'pip install gunicorn')  
2. run the web app using 'heroku local web'


#### Detailed instructions
Now, all files are executable files. If the app cannot run, please follow the 
below steps to recompile the programs.

##### Parser
The parser no longer need compile any more, but if any unexpected situations 
appeared, please follow the directions to compile the code again.

Then compile the codes with the following command:
`g++ -std=c++17 -o /path/to/destination /path/to/parser.cpp`
(e.g: `g++ -g -std=c++17 -o ./server/test/parser ./parser_src/parser.cpp`)


MacOS user can try this instead, if the previous on cannot work
`clang++ -o /path/to/destination /path/to/parser.cpp`
(e.g: `clang++ -std=c++17 -o ./server/test/parser ./parser_src/parser.cpp`)

The run the program with the following command:
`./path/to/destination`
(e.g: `./server/test/parser`)

The program will automatically generate the html file in the folder htmls/single_person/  

##### Server
Requirements:
Need flask to provide the web module, and need requests to execute the requests
Install using the following command:
`pip3 install flask requests`

The server part no longer need to run dblp.py any more, the functions will be called automatically when it is needed.

Run the dblp.py in test folder to obtain the BibTexes for all researchers in the list
`python3 server/test/dblp.py`

Run the main.py in test folder to run the test server
`python3 server/test/main.py`


### Requirements of researchers list
| NameOfResearcher | PID |
| ---------------- | --- |
| Capitalize every name and live no space| /xxx/xxxx |
| On researcher shell occupy one line |


