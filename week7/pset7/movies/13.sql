-- write a SQL query to list the names of all people
-- who starred in a movie in which Kevin Bacon also starred.

-- Print those name
SELECT name FROM people WHERE people.id IN
    (
    -- Get other person id that starred in movies in which Kevin Bacon in
    SELECT stars.person_id FROM stars
        JOIN movies ON stars.movie_id = movies.id
        WHERE stars.movie_id IN
        (
        -- movies id in whicn Kevin Bacon starred
        SELECT movies.id FROM movies
            JOIN stars ON movies.id = stars.movie_id
            JOIN people ON stars.person_id = people.id
            -- Get the id of Kevin Bacon
            WHERE stars.person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)
        )
    )
    -- Except the Kevin Bacon himself
    EXCEPT
    SELECT name FROM people WHERE people.name = "Kevin Bacon" AND people.birth = 1958;