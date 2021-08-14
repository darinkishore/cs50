

SELECT name FROM people WHERE id IN
(SELECT person_id
FROM stars
WHERE movie_id IS(SELECT id as toy_id FROM movies WHERE title IS "Toy Story"))

--list the names of all people who starred in Toy Story