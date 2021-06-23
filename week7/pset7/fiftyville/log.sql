-- Keep a log of any SQL queries you execute as you solve the mystery.
Looking at crime scene reports on July 28, 2020 at Chamberlin Stree, interview conducted this day mentioned courthouse
SELECT * FROM crime_scene_reports
    WHERE year = 2020
    AND month  = 7
    AND day    = 28
    AND street = "Chamberlin Street";
    -- The theft took place at 10.15 am at Chambelin Street courthouse, three interviews are conducted on the day with three witnesses

-- Looking at the interviews transcript mentioning courthouse
SELECT name, transcript FROM interviews
    WHERE year = 2020
    AND month  = 7
    AND day    = 28
    AND transcript LIKE ("%courthouse%");
    -- There are three information gathered:
    -- Within 10 minutes of theft, thief get into car and left.
    -- Witness saw thief withdrawing some money at ATM on Fifer Street earlier that day (July 28)
    -- When thief left the courthouse, they talked for someone for less than a minute,
    --      they were planning to take EARLIEST flight tomorrow (July 29), the thief as the person on other end to buy flight ticket.


-- Take a look at courthouse_security_logs check the time car enter and exit that is within 10 minutes from 10.15, check the license plate
--- ### FACT 1: Thief drive in and out 10 minutes from the courthouse --
SELECT license_plate FROM courthouse_security_logs
    WHERE year = 2020
    AND month  = 7
    AND day    = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25;

SELECT name FROM people
    WHERE license_plate IN
    (
        SELECT license_plate FROM courthouse_security_logs
        WHERE year = 2020
        AND month  = 7
        AND day    = 28
        AND hour = 10
        AND minute > 15
        AND minute < 25
    )
    ORDER BY name ASC;
    -- Suspect Amber, Danielle, Elizabeth, Ernest, Evelyn, Patrick, Roger, Russel


----- #### FACT 2: Thief withdrawing money at ATM on Fifer Street that day (July 28) ## ----
-- Take a look at ATM transactions on Fifer Street, look at distinct id withdrawing money
SELECT DISTINCT account_number FROM atm_transactions
    WHERE year = 2020
    AND month = 7
    AND day   = 28
    AND transaction_type = "withdraw"
    AND atm_location = "Fifer Street";

-- Check possible suspect based on account number from before
SELECT name FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id

    WHERE account_number IN
    (
    SELECT DISTINCT account_number FROM atm_transactions
        WHERE year = 2020
        AND month = 7
        AND day   = 28
        AND transaction_type = "withdraw"
        AND atm_location = "Fifer Street"
    )
    ORDER BY name ASC;
    -- Suspects: Bobby, Danielle, Elizabeth, Ernest, Madison, Roy, Russel, Victoria

----- ### FACT 3a: Thief phone someone less than a minute ## ----
-- Checking phone transactions
SELECT caller FROM phone_calls
    WHERE year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60;

-- Check who that phone number belongs to
SELECT name FROM people
    WHERE phone_number IN
    (
        SELECT caller FROM phone_calls
        WHERE year = 2020
        AND month = 7
        AND day = 28
        AND duration < 60
    )
    ORDER BY name ASC;
    -- Suspects: Bobby, Ernest, Evelyn, Kimberly, Madison, Roger, Russel, Victoria

----- ### FACT 3b: Thief will take earliest flight tomorrow from Fiftyville ## ----
-- Checking thief passport number through passenger data, the thief will have a flight on July 29, from Fiftyville
SELECT passport_number from passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id

    WHERE year = 2020
    AND month = 7
    AND day = 29
    AND city = "Fiftyville"
    AND hour = 8;
    -- ORDER BY hour ASC;

-- Based on the passport number from previous step we can get the name
SELECT name FROM people
    WHERE passport_number IN
    (
    SELECT passport_number from passengers
        JOIN flights ON passengers.flight_id = flights.id
        JOIN airports ON flights.origin_airport_id = airports.id

        WHERE year = 2020
        AND month = 7
        AND day = 29
        AND city = "Fiftyville"
        AND hour = 8
    )
    ORDER BY name ASC;
    -- Suspects: Bobby, Roger, Madison, Danielle, Evelyn, Edward, Ernest, Doris


-- ### SUSPECT: Given all the facts and suspects, we can see which names exist in each set --
-- From car:        Suspect Amber, Danielle, Elizabeth, Ernest, Evelyn, Patrick, Roger, Russel
-- From ATM:        Amber, Danielle, Elizabeth, Ernest, Evelyn, Patrick, Roger, Russel
-- From call:       Suspects: Bobby, Ernest, Evelyn, Kimberly, Madison, Roger, Russel, Victoria
-- From passport:   Bobby, Roger, Madison, Danielle, Evelyn, Edward, Ernest, Doris

-- Conclusion: Ernest is the thief


-- ### ACCOMPLICE: we can check who the thief is calling at the time through phone_calls
-- Checking the phone_calls table to check phone calls traffic on that day, accomplice's phone number should in the "receiver"
SELECT name FROM people
    WHERE phone_number =
    (
    SELECT receiver FROM phone_calls
        WHERE caller = (SELECT phone_number FROM people WHERE name = "Ernest")
        AND year  = 2020
        AND month = 7
        AND day   = 28
        AND duration < 60
    );
    -- Accomplice: Berthold

-- ### ESCAPED TO ---
SELECT city FROM airports
WHERE id =
    (
    SELECT destination_airport_id FROM passengers
        JOIN flights ON passengers.flight_id = flights.id
        WHERE passport_number = (SELECT passport_number FROM people WHERE name = "Ernest")
        AND year  = 2020
        AND month = 7
        AND day   = 29
        AND hour  = 8
    );
    -- Escaped to: London