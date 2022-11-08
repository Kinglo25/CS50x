-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT *
FROM crime_scene_reports
WHERE street="Humphrey Street" AND year=2021 AND month=7 AND day=28;
--> Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--> Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
--> 295
----------------------------------------------------------------------------------------------------------------------------------------------

SELECT name, transcript
FROM interviews
WHERE year=2021 AND month=7 AND day=28 AND transcript LIKE "%bakery%";

--> | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--> If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

--> | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--> I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

--> | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--> I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--> The thief then asked the person on the other end of the phone to purchase the flight ticket.
----------------------------------------------------------------------------------------------------------------------------------------------

SELECT license_plate
FROM bakery_security_logs
WHERE year=2021 AND month=7 AND day=28 AND hour=10 AND minute >= 15 AND minute <= 25 AND activity="exit";

--> gives license_plate of suspects
----------------------------------------------------------------------------------------------------------------------------------------------

SELECT account_number
FROM atm_transactions
WHERE year=2021 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw";

--> gives account_number of suspects

SELECT person_id
FROM bank_accounts
WHERE account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE year=2021 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw");

--> gives person_id of suspects
----------------------------------------------------------------------------------------------------------------------------------------------

SELECT caller
FROM phone_calls
WHERE year=2021 AND month=7 AND day=28 AND duration < 60;

--> gives caller number of suspect

SELECT receiver
FROM phone_calls
WHERE year=2021 AND month=7 AND day=28 AND duration < 60;

--> gives caller number accomplice
----------------------------------------------------------------------------------------------------------------------------------------------
SELECT city
FROM airports
WHERE id=
    (SELECT destination_airport_id
    FROM flights
    WHERE year=2021 AND month=7 AND day=29 AND origin_airport_id=
        (SELECT id
        FROM airports
        WHERE city="Fiftyville")
    ORDER BY hour, minute
    LIMIT 1);

--> gives me the destination of the flight they took

SELECT passport_number
FROM passengers
where flight_id=
    (SELECT id
    FROM flights
    WHERE year=2021 AND month=7 AND day=29 AND origin_airport_id=
        (SELECT id
        FROM airports
        WHERE city="Fiftyville")
    ORDER BY hour, minute
    LIMIT 1);

--> gives passport_number of suspects
----------------------------------------------------------------------------------------------------------------------------------------------

SELECT name
FROM people
WHERE phone_number IN
    (SELECT caller
    FROM phone_calls
    WHERE year=2021 AND month=7 AND day=28 AND duration < 60)
AND passport_number IN
    (SELECT passport_number
    FROM passengers
    where flight_id=
        (SELECT id
        FROM flights
        WHERE year=2021 AND month=7 AND day=29 AND origin_airport_id=
            (SELECT id
            FROM airports
            WHERE city="Fiftyville")
        ORDER BY hour, minute
        LIMIT 1))
AND license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE year=2021 AND month=7 AND day=28 AND hour=10 AND minute >= 15 AND minute <= 25 AND activity="exit")
AND id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year=2021 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw"));

--> gives one name : Bruce
----------------------------------------------------------------------------------------------------------------------------------------------

SELECT name
FROM people
WHERE phone_number=
    (SELECT receiver
    FROM phone_calls
    WHERE year=2021 AND month=7 AND day=28 AND duration < 60 AND caller=
        (SELECT phone_number
        FROM people
        WHERE name="Bruce"));