SELECT ROUND(AVG(rating), 2) AS average
FROM ratings WHERE (SELECT id FROM movies WHERE year = 2012)


--average rating of all movies released in 2012