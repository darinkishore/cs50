
SELECT
     movies.title
FROM
     movies
INNER JOIN
     ratings r on movies.id = r.movie_id
WHERE movie_id IN
            (SELECT movie_id AS chad_ids FROM stars WHERE person_id IS
            (SELECT id FROM people WHERE name IS "Chadwick Boseman"))
ORDER BY r.rating DESC
LIMIT 5


--LIMIT 5

-- list the titles of the five highest rated movies (in order) that
-- Chadwick Boseman starred in, starting with the highest rated.