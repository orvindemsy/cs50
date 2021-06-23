-- write a SQL query to list the names of all people who starred in Toy Story.
SELECT name FROM people
JOIN stars ON stars.person_id = people.id
WHERE movie_id == (SELECT id FROM movies WHERE title == "Toy Story");