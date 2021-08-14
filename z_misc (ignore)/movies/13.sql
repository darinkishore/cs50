SELECT p.name
FROM stars
JOIN people p ON p.id = stars.person_id
WHERE (movie_id IN (SELECT movie_id from stars WHERE
        person_id IS (
            (SELECT id FROM people where (name IS "Kevin Bacon") AND (birth = 1958)))))
AND p.name IS NOT "Kevin Bacon"


--Names of all people who starred in a movie kevin bacon was in. not kevin bacon.

