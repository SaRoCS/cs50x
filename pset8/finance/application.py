import os
import uuid

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = False

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    name = db.execute("SELECT username FROM users WHERE id=:id", id=session['user_id'])
    username = name[0]['username']

    rows = db.execute("SELECT * FROM :username", username=username)
    cashD = db.execute("SELECT cash FROM users WHERE username=:username", username=username)
    cash = cashD[0]['cash']
    totals = cash
    cash = usd(cash)
    for row in rows:
        price = lookup(row["symbol"])
        price = price["price"]
        price = usd(price)
        row["price"] = price

        total = row["price"]
        total = total[1:len(total)]
        total = float(total) * row['shares']


        totals += total

        total = usd(total)
        row['total'] = total
    totals = usd(totals)
    return render_template("index.html", cash=cash, rows=rows, totals=totals)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #get input
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        #error check

        #check blanks
        if not symbol:
            return apology("Please enter a company's symbol")
        if not shares:
            return apology("Please enter the amount of shares to buy")
        #check valid symbol
        share = lookup(symbol)
        if share == None:
            return apology("Invalid symbol")
        #check cost
        cost = float(share['price']) * int(shares)
        cashD = db.execute("SELECT cash FROM users WHERE id=:user", user=session['user_id'])
        cash = cashD[0]["cash"]
        if cost > cash:
            return apology("You do not have enough money")

        #buy shares
        #add it to user's stocks
        #get username
        row = db.execute("SELECT username FROM users WHERE id=:user", user=session['user_id'])
        username= row[0]['username']
        #see if they own some of the company already
        rows = db.execute("SELECT symbol FROM :username WHERE symbol=:symbol", username=username, symbol=symbol)
        #if they own some
        if len(rows) != 0:
            db.execute("UPDATE :username SET shares=shares+:new_shares WHERE symbol=:symbol", username=username, new_shares=shares, symbol=symbol)
        #if they don't
        else:
            db.execute("INSERT INTO :username (symbol, shares, name) VALUES (:symbol, :shares, :name)",
            username=username, symbol=symbol, shares=shares, name=share['name'])
        #record transaction
        db.execute("INSERT INTO transactions (user_id, name, number, price) VALUES (:user, :name, :number, :price)",
            user=session['user_id'], name=symbol, number=shares, price=share['price'])
        #subtract cost
        cash -= cost
        db.execute("UPDATE users SET cash=:cash WHERE id=:user", cash=cash, user=session['user_id'])

        return redirect("/")


    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE user_id=:user ORDER BY time DESC", user=session['user_id'])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Invalid symbol")

        name = quote["name"]
        symbol = quote["symbol"]
        price = quote["price"]
        price = usd(price)
        return render_template("quoted.html", name=name, symbol=symbol, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        #get inputs
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        #check for blanks and passwords match
        if not username:
            return apology("Please enter a username")
        if not password:
            return apology("Please enter a password")
        if not confirmation:
            return apology("Please confirm your password")
        if password != confirmation:
            return apology("Your passwords do not match")

        pass_hash = generate_password_hash(password)

        #check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = :username", username = username)
        if len(rows) != 0:
            return apology("Username already exists")

        #enter username and password hash
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=username, password=pass_hash)
        db.execute("CREATE TABLE :username (symbol VARCHAR(255), shares INTEGER NOT NULL, name VARCHAR(255))", username=username)

        return redirect("/")


    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        row = db.execute("SELECT username FROM users WHERE id=:user", user=session['user_id'])
        username= row[0]['username']
        #get input
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        shares = int(shares)
        #check blanks
        if not symbol:
            return apology("Please select a stock to sell")
        if not shares:
            return apology("Please enter the number of shares to sell")
        test = db.execute("SELECT shares FROM :username WHERE symbol=:symbol", username=username ,symbol=symbol)
        if test[0]["shares"] < shares:
            return apology("You do not have enough shares")
        #sell
        stock = lookup(symbol)
        price = stock["price"]
        money = price * shares
        #update shares
        db.execute("UPDATE :username SET shares=shares-:shares WHERE symbol=:symbol",username=username, shares=shares,symbol=symbol)
        #update cash
        db.execute("UPDATE users SET cash=cash+:money WHERE id=:user", money=money, user=session["user_id"])
        #check if user has 0 shares and remove it
        test = db.execute("SELECT shares FROM :username WHERE symbol=:symbol", username=username ,symbol=symbol)
        if test[0]["shares"] == 0:
            db.execute("DELETE FROM :username WHERE symbol=:symbol", username=username, symbol=symbol)
        #record transaction
        shares = -shares
        db.execute("INSERT INTO transactions (user_id, name, number, price) VALUES (:user, :name, :number, :price)",
        user=session['user_id'], name=symbol, number=shares, price=price)

        return redirect("/")


    else:
        row = db.execute("SELECT username FROM users WHERE id=:user", user=session['user_id'])
        username= row[0]['username']
        rows = db.execute("SELECT symbol FROM :username", username=username)
        return render_template("sell.html", rows=rows)


@app.route("/groups_login", methods=["GET", "POST"])
@login_required
def groups_login():
    #if trying to login
    if request.method == "POST":
        #get entered key
        key = request.form.get("key")
        #check if it is valid
        rows = db.execute("SELECT * FROM group_keys WHERE key=:key", key=key)
        if not rows:
            return apology("Not a valid group key")
        #add user to group
        row = db.execute("SELECT username FROM users WHERE id=:user", user=session['user_id'])
        username= row[0]['username']
        db.execute("UPDATE users SET group_key = :key WHERE id=:user", key=key, user=session['user_id'])
        name = db.execute("SELECT name FROM group_keys WHERE key=:key", key=key)
        name = name[0]["name"]
        db.execute("INSERT INTO :name (member, user_id) VALUES (:username, :id)", name=name, username=username, id=session['user_id'])
        return redirect("/group")
    else:
        #get group
        group = db.execute("SELECT group_key FROM users WHERE id=:user", user=session['user_id'])
        group = group[0]["group_key"]
        #check group
        #if no group
        if not group:
            return render_template("groups_login.html")
        else:
            return redirect("/group")


@app.route("/groups_register", methods=["GET", "POST"])
@login_required
def groups_register():
    if request.method == "GET":
        #generate key
        key = str(uuid.uuid4())
        key = key[0:8]
        #make sure it is unique
        key_test = db.execute("SELECT key FROM group_keys WHERE key=:key", key=key)
        while len(key_test) != 0:
            key = str(uuid.uuid4())
            key = key[0:8]
            key_test = db.execute("SELECT key FROM group_keys WHERE key=:key", key=key)

        return render_template("groups_register.html", key=key)
    else:
        name = request.form.get("group_name")
        name = name + " Group"
        key = request.form.get("key")
        #create group
        db.execute("INSERT INTO group_keys (key, name) VALUES (:key, :name)", key=key, name=name)
        db.execute("CREATE TABLE :name (member VARCHAR(255), user_id INTEGER NOT NULL, FOREIGN KEY (user_id) REFERENCES users(id))", name=name)
        return redirect("/groups_login")


@app.route("/group", methods=["GET", "POST"])
@login_required
def group():
    if request.method == "GET":
        #get users group
        group = db.execute("SELECT group_key FROM users WHERE id=:id", id=session['user_id'])
        group_key = group[0]['group_key']
        group = db.execute("SELECT name FROM group_keys WHERE key=:key", key=group_key)
        group = group[0]['name']
        #get members
        members = db.execute("SELECT * FROM :group JOIN users ON :group.user_id= users.id ORDER BY cash DESC", group=group)
        for row in members:
            cash = row['cash']
            cash = usd(cash)
            row['cash'] = cash
        return render_template("group.html", group=group, members=members)
    else:
        #get users group
        group = db.execute("SELECT group_key FROM users WHERE id=:id", id=session['user_id'])
        group_key = group[0]['group_key']
        group = db.execute("SELECT name FROM group_keys WHERE key=:key", key=group_key)
        group = group[0]['name']
        #leave
        db.execute("DELETE FROM :group WHERE user_id=:id", group=group, id=session['user_id'])
        db.execute("UPDATE users SET group_key=NULL WHERE id=:id", id=session['user_id'])
        return redirect("/groups_login")




def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
