-- Keep a log of any SQL queries you execute as you solve the mystery.

-- read crime scene descriptions
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = '28' AND street = 'Humphrey Street';

-- read witness transcripts
SELECT transcript FROM interviews WHERE transcript LIKE '%bakery%';

-- look at for owners of cars leaving the lot between 10:15 and 10:25
SELECT name, passport_number
FROM people
WHERE license_plate IN
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND hour = 10
    AND activity = 'exit'
    AND minute <=25
    AND minute >=15
)
;

-- people ids on bank account list joined with atm transactions where
SELECT name, passport_number, license_plate
FROM people
WHERE people.id IN
(
    SELECT bank_accounts.person_id
    FROM bank_accounts
    JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
    WHERE
        (
        day = 28
        AND month = 7
        AND year = 2023
        AND atm_location = 'Leggett Street'
        AND transaction_type LIKE 'withdraw'
        )
)
;
-- cross reference with cars
SELECT name, passport_number, license_plate
FROM people
WHERE people.id IN
(
    SELECT bank_accounts.person_id
    FROM bank_accounts
    JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
    WHERE
        (
        day = 28
        AND month = 7
        AND year = 2023
        AND atm_location = 'Leggett Street'
        AND transaction_type LIKE 'withdraw'
        )
)
AND people.id IN
(
    SELECT people.id
    FROM people
    WHERE license_plate IN
    (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE
        day = 28
        AND month = 7
        AND year = 2023
        AND hour = 10
        AND activity = 'exit'
        AND minute <=25
        AND minute >=15
    )
)

-- Of the people who withdrew $ on Leggett and left the bakery in the window, did any of them make a call?
SELECT people.name
FROM people
JOIN phone_calls
ON people.phone_number = caller
WHERE
(

        day = 28
        AND month = 7
        AND year = 2023
)
AND
(
    people.name = 'Iman'
    OR people.name = 'Luca'
    OR people.name = 'Diana'
    OR people.name = 'Bruce'
)
ORDER BY phone_calls.day DESC
;
-- look at flights out of Fiftyville on 7/29 morning -- did Diana or Bruce fly out?
SELECT full_name, flights.id, flights.hour, flights.day, flights.month
FROM airports
JOIN flights
ON airports. id = flights.origin_airport_id
WHERE airports.id
IN
(
    SELECT origin_airport_id
    FROM flights
    JOIN passengers
    ON flights.id = passengers.flight_id
    WHERE flights.id IN
    (
        SELECT flight_id
        FROM passengers
        JOIN people
        ON people.passport_number = passengers.passport_number
        WHERE (people.name = 'Diana' or people.name = 'Bruce')
    )
)
AND
(
        flights.year = 2023
        AND flights.month = 7
        AND flights.day = 29
    )
;

-- Get list of passengers on flight 36
SELECT name
FROM people
JOIN passengers
ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number
IN
    (
        SELECT passport_number
        FROM passengers
        WHERE flight_id = 36
    )
;


SELECT airports.city
FROM airports
WHERE airports.id
IN
    (
        SELECT destination_airport_id
        FROM flights
        WHERE flights.id = 36
    );
-- Bruce was on the plane!
-- find reciever phone number of who bruce talked to on the morning of the 228th
-- find their ID
-- match to name
    SELECT people.name, phone_calls.duration
    FROM people
    JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
    WHERE phone_number
    IN
    (
            SELECT phone_calls.receiver
            FROM phone_calls
            WHERE
            (
                phone_calls.caller =
                (
                    SELECT people.phone_number
                    FROM people
                    WHERE people.name = 'Bruce'
                )
            )
    )
    AND
         (
                    phone_calls.day = 28
                    AND phone_calls.month = 7
                    AND phone_calls.year = 2023
                )
;
