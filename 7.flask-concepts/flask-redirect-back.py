from flask import Flask, render_template, request, url_for, flash, redirect, session, current_app
import functools
from flaskext.mysql import MySQL
import pymysql
import os

app = Flask(__name__)

with app.app_context():
	class back(object):
		# http://flask.pocoo.org/snippets/120/
		cfg = current_app.config.get
		cookie = cfg('REDIRECT_BACK_COOKIE', 'back')
		default_view = cfg('REDIRECT_BACK_DEFAULT', 'index')

		@staticmethod
		def anchor(func, cookie=cookie):
			@functools.wraps(func)
			def result(*args, **kwargs):
				session[cookie] = request.url
				return func(*args, **kwargs)
			return result

		@staticmethod
		def url(default=default_view, cookie=cookie):
			return session.get(cookie, url_for(default))

		@staticmethod
		def redirect(default=default_view, cookie=cookie):
			return redirect(back.url(default, cookie))

	back = back()

# app.config['MYSQL_DATABASE_HOST']	= 'us-cdbr-iron-east-05.cleardb.net'
# app.config['MYSQL_DATABASE_USER']	= 'b4b0cc679b8369'
# app.config['MYSQL_DATABASE_PASSWORD']	= '60fbe0a0'
# app.config['MYSQL_DATABASE_DB'] = 'heroku_4e718f6c88d0a40'

app.config['MYSQL_DATABASE_HOST']	= 'localhost'
app.config['MYSQL_DATABASE_USER']	= 'root'
app.config['MYSQL_DATABASE_PASSWORD']	= 'root'
app.config['MYSQL_DATABASE_DB'] = 'pydea'

mysql = MySQL(app)

app.config['SECRET_KEY'] = 'youmayneverknow'

@app.route('/')
@app.route('/blog', methods=['GET', 'POST'])
@back.anchor
def index():
	if request.method == 'GET':
		blogs = []
		db = mysql.connect()
		cur = db.cursor()
		cur.execute('select blogid, title, date from blogpost')
		data = cur.fetchall()
		
		if not data:
			flash('No blog posts to show for now.')
			return redirect(url_for('about'))

		for _id, title, date in sorted(data, key=lambda x: x[2], reverse=True):
			cur.execute("select tag from tags where blogid = '{0}'".format(_id))
			allTags = cur.fetchall()
			tags = [tag[0] for tag in allTags] if allTags else []
			blogs.append((_id, title, date, tags))

		db.close()
		return render_template('index.html', title='', blogs=blogs)

	if request.method == 'POST':
		email = request.form['email']
		try:
			db = mysql.connect()
			cur = db.cursor()
			cur.execute("insert into subscribers (email) values ('{0}')".format(email))
			db.commit()
			db.close()
			flash('You have successfully subscribed to www.pydea.org')
		
		except pymysql.err.IntegrityError:
			flash('You are already a subscriber')

		return redirect(url_for('index'))

@app.route('/about', methods=['GET', 'POST'])
def about():
	return render_template('about.html', title='About | ')

@app.route('/archives', methods=['GET', 'POST'])
@back.anchor
def archives():
	if request.method == 'GET':
		blogs = []
		db = mysql.connect()
		cur = db.cursor()
		cur.execute('select blogid, title, date from blogpost')
		data = cur.fetchall()

		if not data:
			flash('No archives available yet.')#this message is received on about page
			return redirect(url_for('about'))

		for _id, title, date in sorted(data, key=lambda x: x[2]):
			cur.execute("select tag from tags where blogid = '{0}'".format(_id))
			allTags = cur.fetchall()
			tags = [tag[0] for tag in allTags] if allTags else []
			blogs.append((_id, title, date, tags))

		db.close()
		return render_template('archives.html', title='Archives | ', blogs=blogs)

	if request.method == 'POST':
		email = request.form['email']
		try:
			db = mysql.connect()
			cur = db.cursor()
			cur.execute("insert into subscribers (email) values ('{0}')".format(email))
			db.commit()
			db.close()
			flash('You have successfully subscribed to www.pydea.org')

		except pymysql.err.IntegrityError:
			flash('You are already a subscriber')

		return redirect(url_for('archives'))

@app.route('/search', methods=['GET', 'POST'])
def search():
	return render_template('search.html', title='Search | ')

@app.route('/b')
def blog():
	_id = request.args.get('id', None)
	db = mysql.connect()
	cur = db.cursor()
	cur.execute("select filename, title, date from blogpost where blogid = '{0}'".format(_id))
	data = cur.fetchall()
	
	if not data:
		flash('This blog does not exists')
		return back.redirect()
		
	for f, t, d in data:
		filename = f
		blogTitle = t
		date = d

	if filename not in os.listdir(os.path.join(app.static_folder, 'blogs')):
		flash('This blog does not exists')
		return back.redirect()

	with open(filename, 'r') as f:
		blogContent = f.read()

	cur.execute("select tag from tags where blogid = '{0}'".format(_id))
	allTags = cur.fetchall()
	tags = [tag[0] for tag in allTags] if allTags else []
	db.close()
	pageTitle = '{0} | '.format(blogTitle)

	return render_template('blog.html', title=pageTitle, blogTitle=blogTitle, blogContent=blogContent, date=date, tags=tags)

@app.errorhandler(500)
def internal_server_error(e):
	return render_template('errorPage.html', title='Internal Server Error | ', error_code=e), 500

@app.errorhandler(403)
@app.errorhandler(404)
def page_not_found(e):
	return render_template('errorPage.html', title='Page Not Found | ', error_code=e), 404

if __name__ == '__main__':
	app.run(debug=True)