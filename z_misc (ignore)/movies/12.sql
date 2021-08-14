--TODO: like fix this sometime.


WHERE id in (
    SELECT movie_id from stars WHERE
        person_id IN (
       (SELECT id FROM people where name IS "Johnny Depp") AND
       (SELECT id FROM people where name IS "Helena Bonham Carter")))

--list the titles of all movies in which both Johnny Depp
-- and Helena Bonham Carter starred