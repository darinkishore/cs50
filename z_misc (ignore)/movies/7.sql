
SELECT (movies.title), r.rating
FROM movies
INNER JOIN ratings r on movies.id = r.movie_id
WHERE movies.year = 2010
ORDER BY r.rating DESC, movies.title



-- list all movies released in 2010 and their ratings, in descending order by rating.
-- For movies with the same rating, order them alphabetically by title.