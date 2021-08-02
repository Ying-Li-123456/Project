# SMU6

## Initial Setup
1.  Install Node.js
2.  Install clasp:

    npm install @google/clasp -g

    alternatively for mac-user:  sudo npm i -g grpc @google/clasp --unsafe-perm

3.  Login to your Google account

    clasp login

4.  Make sure the App Script API is enabled

    Using web browser to go to: https://script.google.com/u/1/home/usersettings

5.  Clone the project to local computer

    git clone https://github.cs.adelaide.edu.au/a1792259/SMU6.git
    
ps: clasp command: https://developers.google.com/apps-script/guides/clasp

## Testing your code

1.  Upload your script to the google server:

 s   clasp push

2.  On script editor, go to:

    Publish > Deploy as web app

3.  Click “Test web app for your latest code.”

## Push to github

1.  Commit the current work

    git add .
    git commit -m “(message)”

2.  Push to github

    git push
