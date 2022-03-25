import sqlite3
import click
from flask import current_app, g
from flask.app import Flask
    
def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect(
            'flaskr.sqlite',
            detect_types=sqlite3.PARSE_DECLTYPES
        )
        g.db.row_factory = sqlite3.Row
    return g.db

def close_db(e=None):
    db = g.pop('db', None)

    if db is not None:
        db.close()

def init_db():
    db = get_db()

    with open('schema.sql', encoding='utf8') as f:
        db.executescript(f.read())


def init_db_command(app):
    """Clear the existing data and create new tables."""
    with app.app_context():
        init_db()
    click.echo('Initialized the database.')

def init_app(app:Flask):
    app.teardown_appcontext(close_db)
