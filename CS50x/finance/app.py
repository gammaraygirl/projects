import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import time

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
db.execute("CREATE TABLE  IF NOT EXISTS transactions (id INTEGER, transaction_date DATETIME, transaction_type VARCHAR, stock_symbol VARCHAR, number_shares INTEGER, share_price REAL, FOREIGN KEY(id) REFERENCES users(id));")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Query for stocks tied to the user
    stocks = db.execute("SELECT stock_symbol, SUM(number_shares) as total_shares FROM transactions where id= :id GROUP BY stock_symbol HAVING total_shares > 0;", id=session["user_id"] )

    # Get user's cash and convert it to a float
    cash_result = db.execute("SELECT cash FROM users WHERE id = :id", id= session["user_id"])[0]["cash"]
    cash_result = cash_result.replace("$", "").replace(",", "")
    cash_result = float(cash_result)

    # Initialize values to track total values
    total_value = cash_result
    grand_total = cash_result


    # Loop over stocks and add price and total value
    for stock in stocks:
        quote = lookup(stock["stock_symbol"])
        stock["price"] = (quote["price"])
        stock["value"] = (stock["price"] * stock["total_shares"])
        total_value += stock["value"]
        grand_total += stock["value"]
        #print(stock["value"])
        #print(total_value)
        #print(stocks)

        cash_result = usd(cash_result)
        grand_total = usd(grand_total)

    return render_template("index.html", stocks=stocks, cash=cash_result, grand_total=grand_total, shares="stock.total_shares")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Display form to buy a stock
    if request.method == "GET":
        return render_template("buy.html")
    # Purchase stock
    else:
        # Check if symbol was entered
        if not request.form.get("symbol"):
            return apology("must provide a symbol")
        # Check if shares was entered
        elif not request.form.get("shares"):
            return apology("must provide number of shares")

         # Check if shares is a positive integer
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("shares must be greater than zero")
        except ValueError:
            return apology("shares must be a number")

        # Check that symbol is valid
        quote = lookup(request.form.get("symbol"))
        if quote is None:
            return apology("invalid symbol")
        # Create SQL table to keep track of what users have purchased
        # Check that user has enough cash to afford the stock, else return an apology

        # Debugging statements
        #print("IS THIS THING ON?")
        #print(type(session["user_id"]))
        #print(f"User ID: {session['user_id']}")

        try:
            cash_result = db.execute("SELECT cash FROM users WHERE id = :id", id= session["user_id"])
            # Debugging statement
            print(f"the cash result is {type(cash_result)}")
        except Exception as e:
            #print(f"Error executing query: {e}")
            return apology("Database query error")

        if not cash_result:
            return apology("User not found or no cash information available")

        try:
            user_cash = (cash_result[0]['cash'])
            user_cash = user_cash.replace("$", "").replace(",", "")
            user_cash = float(user_cash)

            #Debugging statement
            #print(f"User cash: {user_cash}")
        except (IndexError, KeyError) as e:
            #print(f"Error accessing cash from result: {3}")
            return apology("Error accessing user cash information")


        user_cash = cash_result[0]['cash']
        share_price = quote["price"]
        transaction_cost = share_price * shares
        str_userID = str(session["user_id"])

        # I think it's being used before its being ggiven a value
        stock_symbol = quote["symbol"]
        number_shares = shares

        share_price = usd(quote["price"])

        # Debugging print statements
        #print(f"share_price: {share_price}")
        #print(f"share_price type: {type(share_price)}")
        #print(f"transaction_cost: {transaction_cost}")
        #print(f"transaction_cost type: {type(transaction_cost)}")
        #print(f"transactionID: {transactionID}")
        #print(f"transactionID type: {type(transactionID)}")
        #print(f"stock_symbol: {stock_symbol}")
        #print(f"stock_symbol type: {type(stock_symbol)}")
        #print(f"number_shares: {number_shares}")
        #print(f"number_shares type: {type(number_shares)}")

        if user_cash < (transaction_cost):
            return apology("not enough cash")
        db.execute("INSERT INTO transactions (transaction_type, id, stock_symbol, number_shares, share_price, transaction_date) VALUES(:transaction_type, :id, :stock_symbol, :number_shares, :share_price, datetime('now'));", transaction_type="Purchase",id= session["user_id"], stock_symbol=stock_symbol, number_shares=number_shares, share_price=share_price)
        # Update user's cash to reflect the purchase

        user_cash = usd(user_cash - transaction_cost)
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash= user_cash, id= session["user_id"])
        # Display purchase confirmation
        #return render_template("purchase_confirmation.html", name=quote["symbol"], shares=shares, cash=user_cash)
        return redirect("/")

@app.route("/history")
@login_required
def history():
   # <th>Symbol</th>
          #      <th>Shares</th>
           #     <th>Price</th>
        #        <th>Transaction Date</th>
     # Query for transactions tied to the user
    transactions = db.execute("SELECT * from transactions WHERE id= :id ORDER BY transaction_date", id=session["user_id"] )
    return render_template("history.html", transactions=transactions)
    # Loop over transactions and find the symbol, shares, price, and date for each
    #for transaction in transactions:
       # quote = lookup(transaction["stock_symbol"])
        #shares = transaction["number_shares"] *-1
        #price = transaction["share_price"]  * transaction["number_shares"]
    #return render_template("history.html", symbol=transaction["stock_symbol"] , price=price, transaction_date=transaction["transaction_date"], shares=shares)

#id INTEGER, transaction_date DATETIME,  VARCHAR, transaction_type VARCHAR, stock_symbol VARCHAR, number_shares INTEGER, share_price REAL, FOREIGN KEY(id) REFERENCES users(id));")



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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    # When requested via GET, display form to request a stock quote
    if request.method == "GET":
        return render_template("quote_request.html")
    # When requested via POST, look up the stock symbol by calling the lookup function and display the results
    else:
        symbol = request.form.get("symbol")
        if symbol is None:
            return apology("must provide a stock symbol")
        else:
            quote = lookup(symbol)
            if quote is None:
                return apology("must provide a valid stock symbol")
            else:
                return render_template("quote_result.html", price=quote['price'], symbol=quote['symbol'])

        # Will need to pass values to HTML template
        # Python: return render_template("hello.html", name="Brian")
        # Jinja: <p>hello, {{ name }}</p>


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("must provide a username")

        password = request.form.get("password")
        if not password:
            return apology("must provide a password")

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("must provide a password confirmation")

        # Check for errors
            # If the form is blank, return an apology
        if not username or not password or not confirmation:
            return apology("must complete all fields")
            # If password and confirmation don't match, return apology
        if password != confirmation:
            return apology("Passwords must match")
            # If the username is already taken, return apology
        user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if user:
            return apology("Username is already taken")
        # Insert new user into USERS table
            # Insert info into table using db.execute and ? as a placeholder, and hashing the password
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, generate_password_hash(password))
        new_user_id = db.execute("SELECT last_insert_rowid()")
        session["user_id"] = new_user_id[0]["last_insert_rowid()"]
        return redirect("/")
    else:
        # User reached route via GET (as by clicking a link or via redirect)
    # Display registration form
        return render_template("register.html")
    # Log user in
        # Set session["user_id"] to the new ID
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #If GET display form
    if request.method == "GET":
        # Gather info about what stocks user owns
        stocks = db.execute("SELECT stock_symbol, SUM(number_shares) as total_shares FROM transactions where id= :id GROUP BY stock_symbol HAVING total_shares > 0;", id=session["user_id"] )
        for stock in stocks:
            quote = lookup(stock["stock_symbol"])
            stock["price"] = quote["price"]
        return render_template("sell.html", stocks=stocks )
    # Submit form via POST
    else:
        print("over here!")
        print(request.form)
        # Check if shares were entered
        if not request.form.get("shares"):
            return apology("must provide number of shares")
        # Check if symbol was entered
        elif not request.form.get("symbol"):
            return apology("must provide a valid symbol")

        # Check that user owns that many shares of the selected stock
        sell_stock = db.execute("SELECT stock_symbol, SUM(number_shares) AS total_shares FROM transactions WHERE id= :id AND stock_symbol= :symbol GROUP BY stock_symbol HAVING total_shares > 0;", id=session["user_id"], symbol=request.form.get("symbol") )
        if not sell_stock:
             return apology("no available stocks to sell")
        num_shares = sell_stock[0]['total_shares']

        try:
            num_shares_to_sell = int(request.form.get("shares"))
            if num_shares < num_shares_to_sell:
                return apology("not enough shares owned")
            # Debugging statement
        except Exception as e:
            print(f"Error executing query: {e}")
            return apology("Database query error")

        # Find user cash
        cash_result = db.execute("SELECT cash FROM users WHERE id = :id", id= session["user_id"])
        user_cash = float(cash_result[0]['cash'])
        user_cash = round(user_cash,2)

        # Prepare information for sale
        quote = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        share_price = quote["price"]
        transaction_cost = share_price * shares
        str_userID = str(session["user_id"])
        stock_symbol = quote["symbol"]

        # Make shares negative to accurately represent a sale
        number_shares = -1* shares

         # Update transaction list with the sale
        try:
            db.execute("INSERT INTO transactions ( transaction_type, id, stock_symbol, number_shares, share_price, transaction_date) VALUES( :transaction_type, :id, :stock_symbol, :number_shares, :share_price, datetime('now'));", transaction_type="Sale",id= session["user_id"], stock_symbol=stock_symbol, number_shares=number_shares, share_price=share_price)
        except Exception as e:
            print(f"Error inserting transaction: {e}")
            return apology("Transaction error")
        # Update user's cash to reflect the sale
        try:
            user_cash = user_cash + transaction_cost
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash= user_cash, id= session["user_id"])
        except Exception as e:
            print(f"Error updating user cash: {e}")
            return apology("Unable to update cash balance")
        return redirect("/")

