print("""
Project generated!
To create a virtualenv and install requirements:
    cd {{ cookiecutter.project_slug }}
    mkvirtualenv -p `which python` --system-site-packages {{ cookiecutter.project_slug }}
    pip install -r requirements.txt
""")
