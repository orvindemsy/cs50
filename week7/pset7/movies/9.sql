-- write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
SELECT name FROM people WHERE id IN (SELECT DISTINCT person_id FROM stars
    JOIN movies ON stars.movie_id = movies.id
    WHERE year = 2004)
    ORDER BY birth ASC;

-- Other possible solution
-- SELECT name FROM people
-- WHERE id IN (SELECT DISTINCT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004))
-- ORDER BY birth ASC;