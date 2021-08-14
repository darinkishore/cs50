SELECT DISTINCT name FROM people WHERE id IN
    (SELECT person_id
    FROM stars
    WHERE stars.movie_id
            IN (SELECT id FROM movies WHERE year = 2004))
ORDER BY people.birth
--list the names of all people who starred in a movie released in 2004,
-- ordered by birth year.

--Your query should output a table with a single column for the name of each person.
--If a person appeared in more than one movie in 2004,
-- they should only appear in your results once.